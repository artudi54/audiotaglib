cmake_minimum_required (VERSION 3.10)
project(audiotaglib)


# CMake Modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules)
include(CompilerSettings)


# Configuration
option(${PROJECT_NAME}_BUILD_TESTS "Build ${PROJECT_NAME} tests" ON)
option(${PROJECT_NAME}_INSTALL "Generate CMake install for ${PROJECT_NAME}" ON)


# Dependencies
## boost
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS iostreams unit_test_framework)
## zlib
find_package(ZLIB REQUIRED)


# Library
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE INCLUDE_FILES_PRIV ${PROJECT_SOURCE_DIR}/src/*.hpp)
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${INCLUDE_FILES} ${INCLUDE_FILES_PRIV})


# Compiler Settings
CompilerSettings(${PROJECT_NAME})


#Include Directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/audiotaglib
        ${PROJECT_SOURCE_DIR}/include/audiotaglib/config
        ${PROJECT_SOURCE_DIR}/include/audiotaglib/except
        ${PROJECT_SOURCE_DIR}/include/audiotaglib/manager
        ${PROJECT_SOURCE_DIR}/include/audiotaglib/manager/write
        ${PROJECT_SOURCE_DIR}/include/audiotaglib/reader
        ${PROJECT_SOURCE_DIR}/include/audiotaglib/string
        ${PROJECT_SOURCE_DIR}/include/audiotaglib/types
        ${PROJECT_SOURCE_DIR}/include/audiotaglib/util
        ${PROJECT_SOURCE_DIR}/include/audiotaglib/writer
        ${PROJECT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIRS})


# Linked libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} ZLIB::ZLIB)


# Tests
if(${PROJECT_NAME}_BUILD_TESTS)
    add_subdirectory(test)
endif()


# Install configuration
if(${PROJECT_NAME}_INSTALL)
    install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-export
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
            DESTINATION include
            PATTERN "*.hpp")
    install(EXPORT ${PROJECT_NAME}-export
            DESTINATION lib/cmake/${PROJECT_NAME})
    install(FILES ${PROJECT_SOURCE_DIR}/cmake/audiotaglib-config.cmake
            DESTINATION lib/cmake/${PROJECT_NAME})
endif()







#TODO remove
add_subdirectory("audioexec")
