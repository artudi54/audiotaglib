#include "StaticWriteManagerFactory.hpp"

namespace tag::manager::write {

    std::shared_ptr<TagWriteManager> StaticWriteManagerFactory::getWriteManager(ContainerFormat format) {
        return std::shared_ptr<TagWriteManager>();
    }
}