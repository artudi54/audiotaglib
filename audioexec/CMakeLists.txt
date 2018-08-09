cmake_minimum_required (VERSION 3.8)
project(audioexec)


#compiler settings
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
	add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


#include directories
include_directories("${PROJECT_SOURCE_DIR}/../audiotaglib/include")


#source files
add_executable(${PROJECT_NAME} main.cpp)


#output settings
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})


#linker settings
link_directories({"${PROJECT_SOURCE_DIR}/../audiotaglib/lib")
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC stdc++fs audiotaglib)
