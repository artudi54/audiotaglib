#pragma once
#include <tag/manager/write/TagWriteManager.hpp>

namespace tag::manager::write {
    class StaticWriteManagerFactory {
    public:
        static std::shared_ptr<TagWriteManager> getWriteManager(ContainerFormat format);
    };
}