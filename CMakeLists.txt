cmake_minimum_required(VERSION 3.20)

project(jvm-class-builder
        VERSION 0.1.0
        DESCRIPTION "Structured JVM class file builder."
        LANGUAGES CXX
)

option(BUILD_SHARED_LIBS "Build libraries as shared" OFF)

add_library(jvm-class-builder
        src/class.cpp
        src/constant.cpp
        src/constant-utf-8-info.cpp
        src/constant-class.cpp
        src/constant-name-and-type.cpp
        src/constant-fieldref.cpp
        src/constant-methodref.cpp
        src/constant-interface-methodref.cpp
        src/constant-string.cpp
        src/constant-integer.cpp
        src/constant-float.cpp
        src/constant-double.cpp
        src/constant-long.cpp
        src/field.cpp
        src/method.cpp
        src/attribute.cpp
        src/attribute-code.cpp
        src/instruction.cpp
        src/instruction-jump.cpp
        src/instruction-ldc.cpp
        src/instruction-with-constant.cpp
        src/label.cpp
        src/exception-handler.cpp
        src/internal/utils.cpp
)

target_compile_features(jvm-class-builder PUBLIC cxx_std_20)
set_target_properties(jvm-class-builder PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(jvm-class-builder
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/internal

)

add_library(Jvm::ClassBuilder ALIAS jvm-class-builder)
