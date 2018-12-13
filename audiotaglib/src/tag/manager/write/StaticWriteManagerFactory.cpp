#include "StaticWriteManagerFactory.hpp"

namespace tag::manager::write {

    SharedTagWriteManager StaticWriteManagerFactory::getWriteManager(AudioContainerFormat format) {
        return tag::manager::write::SharedTagWriteManager();
    }
}