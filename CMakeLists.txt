cmake_minimum_required(VERSION 3.16)

project(pt_proj_c
        VERSION 1.0.0 
        LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    message(FATAL_ERROR "gnu c extension is required")
endif()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS ">> build: DEBUG")

    target_compile_options(${PROJECT_NAME} PRIVATE
        -O0
        -g
        -fsanitize=address
    )
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS ">> build: RELEASE")

    target_compile_options(${PROJECT_NAME} PRIVATE
        -O3
        -flto
        -fomit-frame-pointer
        -DNDEBUG
    )
    target_link_options(${PROJECT_NAME} PRIVATE -flto)
endif()
