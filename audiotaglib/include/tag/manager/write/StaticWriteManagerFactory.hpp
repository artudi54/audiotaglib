#pragma once
#include <tag/manager/write/TagWriteManager.hpp>

namespace tag::manager::write {
    class StaticWriteManagerFactory {
    public:
        static SharedTagWriteManager getWriteManager(AudioContainerFormat format);
    };
}