cmake_minimum_required(VERSION 3.8)

project("audiotaglib")


#print build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("This is a \"Debug\" build\n")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	message("This is a \"Release\" build\n")
else()
	message(FATAL_ERROR "Unknown version of build - \"${CMAKE_BUILD_TYPE}\"\n")
endif()

add_subdirectory("audiotaglib")
