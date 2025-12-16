add_executable(06-01
    06-01.cpp
    Rational.cpp
    Rational.hpp
)

target_include_directories(06-01 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME 06-01 COMMAND 06-01)