cmake_minimum_required (VERSION 3.9)
project(audioexec)

#source files
add_executable(${PROJECT_NAME} main.cpp)


#output settings
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})


#linker settings
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(LIBRARIES audiotaglib stdc++fs)
else()
	set(LIBRARIES audiotaglib)
endif()

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${LIBRARIES})
