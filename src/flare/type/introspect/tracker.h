#ifndef _FLR_TRACKER_H
#define _FLR_TRACKER_H

// ToDo(robin): use unordered_map

#include <iostream>
#include <map>

#include "../null_type.h"
#include "type_name.h"
#include "../types.h"

namespace flr {
    namespace internal {
        struct status_info {
            flr::s64 constructed = 0;
            flr::s64 alive       = 0;
        };

        class TrackerBase {
        public:
            static void print_info(std::string name, status_info info) {
                std::cout << name << ":" << std::endl
                          << "\talive: " << info.alive << std::endl
                          << "\tconstructed: " << info.constructed << std::endl
                          << "\tdeconstructed: " << info.constructed - info.alive
                          << std::endl;
            }

            static void print_infos() {
                for(auto info : infos) print_info(info.first, info.second);
            }

        protected:
            static std::map<const std::string, flr::internal::status_info>
                infos;
        };

        std::map<const std::string, flr::internal::status_info>
            TrackerBase::infos =
                std::map<const std::string, flr::internal::status_info>();

        template <typename T>
        class Tracker : public TrackerBase {
        private:
            static const std::string name;

        public:
            Tracker() {
                infos[name].constructed++;
                infos[name].alive++;
            }

            ~Tracker() { infos[name].alive--; }

            static status_info & info() { return infos[name]; }

            static void print_info() { print_info(name, infos[name]); }
        };

        template <typename T>
        const std::string Tracker<T>::name = flr::type_name<T>().toStdString();

        using TrackerInfo = TrackerBase;
    }
}

#endif
