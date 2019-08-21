#include "StaticWriteManagerFactory.hpp"

namespace audiotaglib::manager::write {

    std::shared_ptr<TagWriteManager> StaticWriteManagerFactory::getWriteManager(ContainerFormat format) {
        return std::shared_ptr<TagWriteManager>();
    }
}