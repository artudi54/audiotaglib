#pragma once
#include <audiotaglib/manager/write/TagWriteManager.hpp>

namespace audiotaglib::manager::write {
    class StaticWriteManagerFactory {
    public:
        static std::shared_ptr<TagWriteManager> getWriteManager(ContainerFormat format);
    };
}