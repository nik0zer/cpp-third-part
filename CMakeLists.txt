cmake_minimum_required(VERSION 3.20)
project(CppSolutions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

file(GLOB CPP_SOURCES CONFIGURE_DEPENDS "*.cpp")

enable_testing()

set(ALL_TARGETS "")

foreach(SOURCE_FILE ${CPP_SOURCES})
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)

    add_executable(${TARGET_NAME} ${SOURCE_FILE})

    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})

    list(APPEND ALL_TARGETS ${TARGET_NAME})
endforeach()

add_custom_target(run-all
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --verbose
    DEPENDS ${ALL_TARGETS}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    USES_TERMINAL
)

find_program(CLANG_FORMAT_EXE clang-format)
if(CLANG_FORMAT_EXE)
    add_custom_target(clang-force-format
        COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${CPP_SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()