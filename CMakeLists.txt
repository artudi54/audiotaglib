cmake_minimum_required(VERSION 3.5)
enable_testing()

add_subdirectory("audiotaglib")
add_subdirectory("audioexec")

install(DIRECTORY audiotaglib/include/tag
	DESTINATION include)
