#TODO rework to use GTest
enable_testing()
file(GLOB_RECURSE TEST_SRCS ${PROJECT_SOURCE_DIR}/test/*.cpp)

add_executable(test_audiotaglib ${TEST_SRCS})
set_target_properties(test_audiotaglib PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin/test)
target_link_libraries(test_audiotaglib LINK_PUBLIC ${LIBRARIES} audiotaglib)

foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)
    if (${testName} STREQUAL "main")
        continue()
    endif()
    add_executable(${testName} main.cpp ${testSrc})
    target_link_libraries(${testName} PUBLIC ${PROJECT_NAME})
    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin/test)
    target_link_libraries(${testName} LINK_PUBLIC ${LIBRARIES} audiotaglib)
    add_test(NAME ${testName} WORKING_DIRECTORY test COMMAND ${PROJECT_SOURCE_DIR}/bin/test/${testName})
endforeach(testSrc)

#all tests - excluded from "make test"
#add_test(NAME test_audiotaglib WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/test COMMAND ${PROJECT_SOURCE_DIR}/bin/test/test_audiotaglib)