# Sets compiler settings for specified target

function(CompilerSettings TARGET)
    # C++ version
    target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
    set_target_properties(${PROJECT_NAME}
            PROPERTIES
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF)

    # Warnings
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${TARGET} PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion)

    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(IGNORED_WARNINGS /wd4514 /wd4571 /wd4623 /wd4625 /wd4626 /wd4668 /wd4710 /wd4774 /wd4820 /wd5026 /wd5027 /wd5045)
        target_compile_options(${TARGET} PRIVATE /Wall /Za /permissive- ${IGNORED_WARNINGS})
        if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
        endif()
        target_compile_definitions(${TARGET} PRIVATE -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS)
    endif()

endfunction()