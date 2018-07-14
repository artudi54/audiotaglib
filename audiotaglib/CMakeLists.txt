cmake_minimum_required (VERSION 3.8)

#add source files
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/audiotaglib/*.cpp)
add_executable(audiotaglib ${SRC_FILES})
include_directories(${PROJECT_SOURCE_DIR}/audiotaglib)


#set output directory
set_target_properties(audiotaglib PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/x64")





if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
	add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)


if(gcc)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)
	add_definitions(-lstdc++fs)
	target_link_libraries(${PROJECT_NAME} stdc++fs)
endif(gcc)



set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON) 

find_package(Boost REQUIRED COMPONENTS iostreams zlib)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})




# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
