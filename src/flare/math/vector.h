#ifndef _FLR_VECTOR
#define _FLR_VECTOR

#include "../type/introspect/flare_class.h"
#include "../type/types.h"
#include <cmath>
#include <ostream>

using namespace flr;

namespace flr {
    template <typename valueType>
    struct Vector2D : private flr::internal::FlareClass<Vector2D<valueType>> {
        valueType   comp[2];
        valueType & x;
        valueType & y;

        Vector2D() : comp(), x(comp[0]), y(comp[1]) {}
        Vector2D(const valueType & a, const valueType & b)
            : comp{a, b}, x(comp[0]), y(comp[1]) {}
        Vector2D(const Vector2D & other)
            : comp{other.x, other.y}, x(comp[0]), y(comp[1]) {
            this->x = other.x;
            this->y = other.y;
        }

        template <typename VT>
        friend std::ostream & operator<<(std::ostream &       output,
                                         const Vector2D<VT> & vec) {
            return output << "[" << vec.x << ", " << vec.y << "]";
        }

        Vector2D<valueType> operator+(const Vector2D<valueType> & rhs) const {
            Vector2D<valueType> vec(*this);
            vec += rhs;
            return vec;
        }

        Vector2D<valueType> operator-(const Vector2D<valueType> & rhs) const {
            Vector2D<valueType> vec(*this);
            vec -= rhs;
            return vec;
        }

        template <typename scalaType>
        Vector2D<valueType> operator*(const scalaType & rhs) const {
            Vector2D<valueType> vec(*this);
            vec *= rhs;
            return vec;
        }

        template <typename scalaType>
        Vector2D<valueType> operator/(const scalaType & rhs) const {
            Vector2D<valueType> vec(*this);
            vec /= rhs;
            return vec;
        }

        Vector2D<valueType> operator-() const {
            Vector2D<valueType> vec(*this);
            vec -= Vector2D<valueType>();
            return vec;
        }

        Vector2D<valueType> & operator+=(const Vector2D<valueType> & rhs) {
            this->x += rhs.x;
            this->y += rhs.y;

            return *this;
        }

        Vector2D<valueType> & operator-=(const Vector2D<valueType> & rhs) {
            this->x -= rhs.x;
            this->y -= rhs.y;

            return *this;
        }

        template <typename scalaType>
        Vector2D<valueType> & operator*=(const scalaType & rhs) {
            this->x *= rhs;
            this->y *= rhs;

            return *this;
        }

        template <typename scalaType>
        Vector2D<valueType> & operator/=(const scalaType & rhs) {
            this->x /= rhs;
            this->y /= rhs;

            return *this;
        }

        bool operator==(const Vector2D<valueType> & rhs) const {
            return (this->x == rhs.x) && (this->y == rhs.y);
        }

        auto dot(const Vector2D<valueType> & other) const {
            return x * other.x + y * other.y;
        }

        auto norm() const { return std::sqrt(x * x + y * y); }

        auto angleBetween(const Vector2D<valueType> & other) const {
            return std::acos(this->dot(other) / (this->norm() * other.norm()));
        }
    };

    template <typename valueType>
    struct Vector3D : private flr::internal::FlareClass<Vector3D<valueType>> {
        valueType   comp[3];
        valueType & x;
        valueType & y;
        valueType & z;

        Vector3D() : comp(), x(comp[0]), y(comp[1]), z(comp[2]) {}
        Vector3D(const valueType & a, const valueType & b, const valueType & c)
            : comp{a, b, c}, x(comp[0]), y(comp[1]), z(comp[2]) {}
        Vector3D(const Vector3D & other)
            : comp{other.x, other.y, other.z}, x(comp[0]), y(comp[1]),
              z(comp[2]) {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
        }

        template <typename VT>
        friend std::ostream & operator<<(std::ostream &       output,
                                         const Vector3D<VT> & vec) {
            return output << "[" << vec.x << ", " << vec.y << ", " << vec.z
                          << "]";
        }

        Vector3D<valueType> operator+(const Vector3D<valueType> & rhs) const {
            Vector3D<valueType> vec(*this);
            vec += rhs;
            return vec;
        }

        Vector3D<valueType> operator-(const Vector3D<valueType> & rhs) const {
            Vector3D<valueType> vec(*this);
            vec -= rhs;
            return vec;
        }

        Vector3D<valueType> operator-() const {
            Vector3D<valueType> vec(*this);
            vec -= Vector3D<valueType>();
            return vec;
        }

        template <typename scalaType>
        Vector3D<valueType> operator*(const scalaType & rhs) const {
            Vector3D<valueType> vec(*this);
            vec *= rhs;
            return vec;
        }

        template <typename scalaType>
        Vector3D<valueType> operator/(const scalaType & rhs) const {
            Vector3D<valueType> vec(*this);
            vec /= rhs;
            return vec;
        }

        Vector3D<valueType> & operator+=(const Vector3D<valueType> & rhs) {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;

            return *this;
        }

        Vector3D<valueType> & operator-=(const Vector3D<valueType> & rhs) {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;

            return *this;
        }

        template <typename scalaType>
        Vector3D<valueType> & operator*=(const scalaType & rhs) {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;

            return *this;
        }

        template <typename scalaType>
        Vector3D<valueType> & operator/=(const scalaType & rhs) {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;

            return *this;
        }

        bool operator==(const Vector3D<valueType> & rhs) const {
            return (this->x == rhs.x) && (this->y == rhs.y) &&
                   (this->z == rhs.z);
        }

        auto dot(const Vector3D<valueType> & other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        auto norm() const { return std::sqrt(x * x + y * y + z * z); }

        auto angleBetween(const Vector3D<valueType> & other) const {
            return std::acos(this->dot(other) / (this->norm() * other.norm()));
        }
    };

    template <typename valueType>
    struct Vector4D : private flr::internal::FlareClass<Vector4D<valueType>> {
        valueType   comp[4];
        valueType & x;
        valueType & y;
        valueType & z;
        valueType & w;

        Vector4D() : comp(), x(comp[0]), y(comp[1]), z(comp[2]), w(comp[3]) {}
        Vector4D(const valueType & a, const valueType & b, const valueType & c,
                 const valueType & d)
            : comp{a, b, c, d}, x(comp[0]), y(comp[1]), z(comp[2]), w(comp[3]) {
        }
        Vector4D(const Vector4D & other)
            : comp{other.x, other.y, other.z, other.w}, x(comp[0]),
              y(comp[1]), z(comp[2]), w(comp[3]) {}

        template <typename VT>
        friend std::ostream & operator<<(std::ostream &       output,
                                         const Vector4D<VT> & vec) {
            return output << "[" << vec.x << ", " << vec.y << ", " << vec.z
                          << ", " << vec.w << "]";
        }

        Vector4D<valueType> operator+(const Vector4D<valueType> & rhs) const {
            Vector4D<valueType> vec(*this);
            vec += rhs;
            return vec;
        }

        Vector4D<valueType> operator-(const Vector4D<valueType> & rhs) const {
            Vector4D<valueType> vec(*this);
            vec -= rhs;
            return vec;
        }

        template <typename scalaType>
        Vector4D<valueType> operator*(const scalaType & rhs) const {
            Vector4D<valueType> vec(*this);
            vec *= rhs;
            return vec;
        }

        template <typename scalaType>
        Vector4D<valueType> operator/(const scalaType & rhs) const {
            Vector4D<valueType> vec(*this);
            vec /= rhs;
            return vec;
        }

        Vector4D<valueType> operator-() const {
            Vector4D<valueType> vec(*this);
            vec -= Vector4D<valueType>();
            return vec;
        }

        Vector4D<valueType> & operator+=(const Vector4D<valueType> & rhs) {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            this->w += rhs.w;

            return *this;
        }

        Vector4D<valueType> & operator-=(const Vector4D<valueType> & rhs) {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;
            this->w -= rhs.w;

            return *this;
        }

        template <typename scalaType>
        Vector4D<valueType> & operator*=(const scalaType & rhs) {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;
            this->w *= rhs;

            return *this;
        }

        template <typename scalaType>
        Vector4D<valueType> & operator/=(const scalaType & rhs) {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;
            this->w /= rhs;

            return *this;
        }

        bool operator==(const Vector4D<valueType> & rhs) const {
            return (this->x == rhs.x) && (this->y == rhs.y) &&
                   (this->z == rhs.z) && (this->w == rhs.w);
        }

        auto dot(const Vector4D<valueType> & other) const {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        auto norm() const { return std::sqrt(x * x + y * y + z * z + w * w); }

        auto angleBetween(const Vector4D<valueType> & other) const {
            return std::acos(this->dot(other) / (this->norm() * other.norm()));
        }
    };

    typedef Vector2D<double> v2;
    typedef Vector3D<double> v3;
    typedef Vector4D<double> v4;
}

#endif
