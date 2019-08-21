cmake_minimum_required (VERSION 3.10)
project(audiotaglib)


# Source files
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE INCLUDE_FILES_PRIV ${PROJECT_SOURCE_DIR}/src/*.hpp)


# Library
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${INCLUDE_FILES} ${INCLUDE_FILES_PRIV})


# Compiler Settings
# Language
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

# Compile warnings
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            -Wall
            -Wextra
            -pedantic)
endif()

# Ignore depracation and secure warnings from msvc
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
            -D_SCL_SECURE_NO_WARNINGS
            -D_CRT_SECURE_NO_WARNINGS)
endif()


#boost
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS iostreams unit_test_framework zlib)

#include directories
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


#output settings
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})


#linker settings
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_link_libraries(${PROJECT_NAME} PUBLIC stdc++fs)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})


#boost test
enable_testing()
file(GLOB_RECURSE TEST_SRCS test/*.cpp)
link_directories({"${PROJECT_SOURCE_DIR}/lib")

add_executable(test_audiotaglib ${TEST_SRCS})
set_target_properties(test_audiotaglib PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin/test)
target_link_libraries(test_audiotaglib LINK_PUBLIC ${LIBRARIES} audiotaglib)

foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)
    if (${testName} STREQUAL "main")
        continue()
    endif()
    add_executable(${testName} test/main.cpp ${testSrc})
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin/test)
    target_link_libraries(${testName} LINK_PUBLIC ${LIBRARIES} audiotaglib)
    add_test(NAME ${testName} WORKING_DIRECTORY test COMMAND ${PROJECT_SOURCE_DIR}/bin/test/${testName})
endforeach(testSrc)

#all tests - excluded from "make test"
#add_test(NAME test_audiotaglib WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/test COMMAND ${PROJECT_SOURCE_DIR}/bin/test/test_audiotaglib)


# Install configuration
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

#TODO remove
add_subdirectory("audioexec")
