cmake_minimum_required (VERSION 3.9)
project(audiotaglib)

# Compiler Settings
# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compile warnings
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "CLANG")
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Ignore depracation and secure warnings from msvc
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

#boost
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS iostreams unit_test_framework zlib)


#source files
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE INCLUDE_FILES_PRIV ${PROJECT_SOURCE_DIR}/src/*.hpp)
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${INCLUDE_FILES} ${INCLUDE_FILES_PRIV})


#include directories
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag/config")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag/except")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag/manager")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag/manager/write")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag/reader")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag/scanner")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag/string")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag/types")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag/util")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include/tag/writer")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

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
	set(LIBRARIES ${Boost_LIBRARIES} stdc++fs)
else()
	set(LIBRARIES ${Boost_LIBRARIES})
endif()

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${LIBRARIES})


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
#TODO finish
install(TARGETS audiotaglib
        RUNTIME DESTINATION audiotag/lib
        LIBRARY DESTINATION audiotag/lib
        ARCHIVE DESTINATION audiotag/lib)
install(DIRECTORY include/tag
        DESTINATION audiotag/include)

#TODO remove
add_subdirectory("audioexec")
