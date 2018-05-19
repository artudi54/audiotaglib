# CMakeList.txt: projekt CMake dla elementu audiotaglib, uwzględnij źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)


if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
	add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif(MSVC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions(-lstdc++fs)



set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON) 

find_package(Boost REQUIRED COMPONENTS iostreams)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})




# Dodaj źródło do pliku wykonywalnego tego projektu.
# get all *.cpp files recursively
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(audiotaglib ${SRC_FILES})
#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set_target_properties(audiotaglib PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/x64/Debug")
#endif()
# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
