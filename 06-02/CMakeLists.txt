cmake_minimum_required(VERSION 3.28)

add_executable(06-02
    06-02.cpp
)

target_sources(06-02
    PUBLIC
        FILE_SET CXX_MODULES FILES
        Rational.cppm
        RationalMixins.cppm
    PRIVATE
        Rational.cpp
)

target_compile_features(06-02 PUBLIC cxx_std_20)

add_test(NAME 06-02 COMMAND 06-02)