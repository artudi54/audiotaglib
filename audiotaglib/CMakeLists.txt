cmake_minimum_required (VERSION 3.5)
project(audiotaglib)


#compiler settings
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


#boost
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS iostreams unit_test_framework zlib)


#include directories
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/tag")
include_directories("${PROJECT_SOURCE_DIR}/include/tag/config")
include_directories("${PROJECT_SOURCE_DIR}/include/tag/except")
include_directories("${PROJECT_SOURCE_DIR}/include/tag/manager")
include_directories("${PROJECT_SOURCE_DIR}/include/tag/manager/write")
include_directories("${PROJECT_SOURCE_DIR}/include/tag/reader")
include_directories("${PROJECT_SOURCE_DIR}/include/tag/scanner")
include_directories("${PROJECT_SOURCE_DIR}/include/tag/string")
include_directories("${PROJECT_SOURCE_DIR}/include/tag/types")
include_directories("${PROJECT_SOURCE_DIR}/include/tag/util")
include_directories("${PROJECT_SOURCE_DIR}/include/tag/writer")
include_directories(${Boost_INCLUDE_DIRS})


#source files
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE INCLUDE_FILES_PRIV ${PROJECT_SOURCE_DIR}/src/*.hpp)
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${INCLUDE_FILES} ${INCLUDE_FILES_PRIV})

#output settings
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})


#linker settings
link_directories(${Boost_LIBRARY_DIRS})

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(LIBRARIES ${Boost_LIBRARIES} stdc++fs)
else()
	set(LIBRARIES ${Boost_LIBRARIES})
endif()

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${LIBRARIES})

#boost test
file(GLOB_RECURSE TEST_SRCS ${PROJECT_SOURCE_DIR}/test/*.cpp)
link_directories({"${PROJECT_SOURCE_DIR}/lib")

add_executable(test_audiotaglib ${TEST_SRCS})
set_target_properties(test_audiotaglib PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin/test)
target_link_libraries(test_audiotaglib LINK_PUBLIC ${LIBRARIES} audiotaglib)

foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)
    if (${testName} STREQUAL "main")
        continue()
    endif()
    add_executable(${testName} ${PROJECT_SOURCE_DIR}/test/main.cpp ${testSrc})
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin/test)
    target_link_libraries(${testName} LINK_PUBLIC ${LIBRARIES} audiotaglib)
    add_test(NAME ${testName} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/test COMMAND ${PROJECT_SOURCE_DIR}/bin/test/${testName})

endforeach(testSrc)

#all tests - excluded from "make test"
#add_test(NAME test_audiotaglib WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/test COMMAND ${PROJECT_SOURCE_DIR}/bin/test/test_audiotaglib)


#install configuration
install(TARGETS audiotaglib
       RUNTIME DESTINATION bin
       LIBRARY DESTINATION lib
       ARCHIVE DESTINATION lib)
install(DIRECTORY include/tag
        DESTINATION include)
