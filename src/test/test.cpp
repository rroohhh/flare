#include <iostream>

// #include "../flare/average.h"
#include "../flare/geometry/icosphere.h"
#include "../flare/type/introspect/tracker.h"
#include <iterator>
#include <list>
#include <vector>
// Link statically with GLEW
#define GLEW_STATIC

// Headers
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shader sources
const GLchar * vertexSource =
    "#version 330 core\n"
    "in vec3 position;"
    "in vec3 color;"
    "in vec2 texcoord;"
    "out vec3 Color;"
    "out vec2 Texcoord;"
    "uniform mat4 model;"
    "uniform mat4 view;"
    "uniform mat4 proj;"
    "uniform float scale;"
    "void main()"
    "{"
    "    Color = color;"
    "    Texcoord = texcoord;"
    "    gl_Position = proj * view * model * vec4(position * scale, 1.0);"
    "}";
const GLchar * fragmentSource = "#version 330 core\n"
                                "in float vertexID;"
                                "in vec3 Color;"
                                "in vec2 Texcoord;"
                                "out vec4 outColor;"
                                "void main()"
                                "{"
                                "        outColor = vec4(Color, 1.0);"
                                "}";

template <typename T, typename U, typename V>
auto clamp(const T && x, const U && min, const V && max) {
    auto ret        = x;
    if(x < min) ret = min;
    if(x > max) ret = max;

    return ret;
}

template <typename T, typename U, typename V>
auto smoothstep(const T & edge0, const U & edge1, const V & x) {
    x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return x * x * (3 - 2 * x);
}

template <typename T, typename U, typename V>
auto smootherstep(const T & edge0, const U & edge1, const V & x) {
    auto tmp = x;
    tmp      = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    return tmp * tmp * tmp * (tmp * (tmp * 6 - 15) + 10);
}

void prepareBuffers(int vao, int vbo, int ebo, IcoSphere & s) {
    std::vector<GLfloat> vertices(s.points().size() * 8, 0.0);
    std::vector<GLuint>  elems(s.faces().size() * 3, 0);
    int                  i = 0;

    for(const auto & vertex : s.points()) {
        // std::cout << vertex << std::endl;
        vertices[i++] = vertex.x;
        vertices[i++] = vertex.y;
        vertices[i++] = vertex.z;

        // Color
        vertices[i++] = std::abs(vertex.y);
        vertices[i++] = std::abs(vertex.z);
        vertices[i++] = std::abs(vertex.x);

        // vertices[i++] = 1;
        // vertices[i++] = 0;
        // vertices[i++] = 0;

        // unused
        vertices[i++] = 0;
        vertices[i++] = 0;
    }

    i = 0;
    for(const auto & face : s.faces()) {
        for(const auto & elem : face.vertices()) { elems[i++] = elem; }
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elems.size() * sizeof(GLuint),
                 elems.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat),
                 vertices.data(), GL_STATIC_DRAW);

    // glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int main() {
    sf::ContextSettings settings;
    settings.attributeFlags    = sf::ContextSettings::Core;
	settings.majorVersion      = 4;
	settings.minorVersion      = 5;
	settings.antialiasingLevel = 0;
	settings.depthBits         = 24;
	settings.stencilBits       = 8;
	 

	sf::Window window(sf::VideoMode(800, 600, 16), "OpenGL",
                      sf::Style::Titlebar | sf::Style::Close, settings);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    flr::f64 t = (1.0 + sqrt(5.0)) / 2.0;

    std::vector<flr::v3> verts{{-1, t, 0}, {1, t, 0}, {-1, -t, 0}, {1, -t, 0},
                               {0, -1, t}, {0, 1, t}, {0, -1, -t}, {0, 1, -t},
                               {t, 0, -1}, {t, 0, 1}, {-t, 0, -1}, {-t, 0, 1}};
    std::vector<flr::Face> fcs{
        {{0, 11, 5}}, {{0, 5, 1}},  {{0, 1, 7}},   {{0, 7, 10}}, {{0, 10, 11}},
        {{1, 5, 9}},  {{5, 11, 4}}, {{11, 10, 2}}, {{10, 7, 6}}, {{7, 1, 8}},
        {{3, 9, 4}},  {{3, 4, 2}},  {{3, 2, 6}},   {{3, 6, 8}},  {{3, 8, 9}},
        {{4, 9, 5}},  {{2, 4, 11}}, {{6, 2, 10}},  {{8, 6, 7}},  {{9, 8, 1}}};

    flr::Mesh      m(verts, fcs);
    flr::IcoSphere s(m, 0.4, 6);

    std::vector<v3> directions{{0, 1, 0}, {0, 0, 1}, {0, 1, 1}};

    for(auto & direction : directions) { direction /= direction.norm(); }

    // GLfloat * vertices      = new GLfloat[s.points().size() * 8];
    f64 multiplicator = 5;

    for(auto & vertex : s.points()) {
        for(const auto & direction : directions) {
            v3 tmp = vertex;
            multiplicator =
                tmp.dot(direction) / (tmp.norm() * direction.norm());
            if(multiplicator < 0.9) continue;

            multiplicator = smootherstep(0.9, 1.0, multiplicator);
            // std::cout << multiplicator << std::endl;

            vertex += direction * multiplicator;
        }
    }

    // GLuint * elems = new GLuint[s.faces().size() * 3];

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    // GLuint eboHelp;
    // glGenBuffers(1, &eboHelp);

    // GLuint vboHelp;
    // glGenBuffers(1, &vboHelp);

    // flr::IcoSphere sHelp(m, 0.4, 6);

    // for(auto & point : sHelp.points()) { point += {1, 1, 1}; }

    // prepareBuffers(vao, vboHelp, eboHelp, sHelp);
    prepareBuffers(vao, vbo, ebo, s);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

        std::cerr << &errorLog[0] << std::endl;

        glDeleteShader(vertexShader);

        std::exit(EXIT_FAILURE);
    }

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);

        std::cerr << &errorLog[0] << std::endl;

        glDeleteShader(fragmentShader);

        std::exit(EXIT_FAILURE);
    }

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          reinterpret_cast<void *>((3 * sizeof(GLfloat))));

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                          reinterpret_cast<void *>(6 * sizeof(GLfloat)));

    GLint uniModel = glGetUniformLocation(shaderProgram, "model");

    // Set up projection
    glm::mat4 view =
        glm::lookAt(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 1.0f));
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj =
        glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    glEnable(GL_DEPTH_TEST);

    glm::mat4 model;
    glm::vec4 xAxis(0.0f, 0.0f, 1.0f, 0.0f);
    glm::vec4 yAxis(1.0f, 0.0f, 0.0f, 0.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    bool  running  = true;
    bool  leftDown = false;
    s64   originX = 0, originY = 0, totalX = 0, totalY = 0;
    float ratio    = 800.0 / 600.0;
    float distance = 0.4f;
    glUniform1f(glGetUniformLocation(shaderProgram, "scale"), distance);

    flr::internal::TrackerInfo::print_infos();

    while(running) {
        sf::Event windowEvent;
        while(window.pollEvent(windowEvent)) {
            switch(windowEvent.type) {
            default: /* ignore */
                break;
            case sf::Event::MouseWheelScrolled:
                if(windowEvent.mouseWheelScroll.delta == 1)
                    distance *= 0.95;
                else
                    distance *= 1.05;

                glUniform1f(glGetUniformLocation(shaderProgram, "scale"),
                            distance);
                break;
            case sf::Event::MouseButtonPressed:
                if(windowEvent.mouseButton.button == sf::Mouse::Left) {
                    leftDown = true;
                    originX  = windowEvent.mouseButton.x;
                    originY  = windowEvent.mouseButton.y;
                }
                break;
            case sf::Event::MouseButtonReleased:
                if(windowEvent.mouseButton.button == sf::Mouse::Left)
                    leftDown = false;
                break;
            case sf::Event::MouseMoved:
                if(leftDown) {
                    s64 currentX = windowEvent.mouseMove.x;
                    s64 currentY = windowEvent.mouseMove.y;
                    s64 deltaX   = (originX - currentX) * 0.5;
                    s64 deltaY   = (originY - currentY) * 0.5;
                    totalX += deltaX;
                    totalY += deltaY;

                    // auto tmp = model * xAxis;
                    // std::cout << "xAxis " << v3{tmp.x, tmp.y, tmp.z}
                    //           << std::endl;
                    // tmp = model * yAxis;
                    // std::cout << "yAxis " << v3{tmp.x, tmp.y, tmp.z}
                    //           << std::endl;

                    model = glm::rotate(
                        model, glm::radians(-float(deltaX)),
                        glm::vec3(glm::normalize(glm::inverse(model) * xAxis)));

                    model = glm::rotate(
                        model, glm::radians(float(deltaY)),
                        glm::vec3(glm::normalize(glm::inverse(model) * yAxis)));

                    // model = tmpModel2 * tmpModel;
                    glUniformMatrix4fv(uniModel, 1, GL_FALSE,
                                       glm::value_ptr(model));

                    originX = currentX;
                    originY = currentY;
                }
                // 				glm::vec3 va =
                // get_arcball_vector(originX,
                // originX,);
                // glm::vec3 vb = get_arcball_vector( cur_mx,  cur_my);
                // float angle = acos(min(1.0f, glm::dot(va, vb)));
                // glm::vec3 axis_in_camera_coord = glm::cross(va, vb);
                // glm::mat3 camera2object =
                // glm::inverse(glm::mat3(transforms[MODE_CAMERA]) *
                // glm::mat3(mesh.object2world));
                // glm::vec3 axis_in_object_coord = camera2object *
                // axis_in_camera_coord;
                // mesh.object2world = glm::rotate(mesh.object2world,
                // glm::degrees(angle), axis_in_object_coord);
                // last_mx = cur_mx;
                // last_my = cur_my;

                // glm::mat4 tmpModel, tmpModel2;
                break;
            case sf::Event::Resized:
                glViewport(0, 0, windowEvent.size.width,
                           windowEvent.size.height);

                ratio = float(windowEvent.size.width) /
                        float(windowEvent.size.height);

                proj =
                    glm::perspective(glm::radians(45.0f), ratio, 1.0f, 10.0f);

                glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
                break;
            case sf::Event::Closed:
                running = false;
                break;
            }
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw sphere
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
        // glEnableVertexAttribArray(posAttrib);
        // glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
        //                       8 * sizeof(GLfloat), 0);

        // glEnableVertexAttribArray(colAttrib);
        // glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
        //                       8 * sizeof(GLfloat),
		//                       reinterpret_cast<void *>((3 *
		//                       sizeof(GLfloat))));

        // glEnableVertexAttribArray(texAttrib);
        // glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
        //                       8 * sizeof(GLfloat),
        //                       reinterpret_cast<void *>(6 * sizeof(GLfloat)));
        glDrawElements(GL_TRIANGLES, s.faces().size() * 3, GL_UNSIGNED_INT, 0);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboHelp);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHelp);
        // glDrawElements(GL_TRIANGLES, sHelp.faces().size() * 3,
        // GL_UNSIGNED_INT, 0);

        // Swap buffers
        window.display();
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    window.close();

    return 0;
}
