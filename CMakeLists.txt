cmake_minimum_required(VERSION 3.20)

project(jvm-class-builder
        VERSION 0.1.0
        DESCRIPTION "Structured JVM class file builder."
        LANGUAGES CXX
)

option(BUILD_SHARED_LIBS "Build libraries as shared" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)

find_program(MAVEN_EXECUTABLE mvn REQUIRED)

set(JAVA_INTERNAL_PROJECT_DIR
        ${CMAKE_SOURCE_DIR}/java-internal
)
set(JAVA_INTERNAL_BUILD_DIR
        ${CMAKE_BINARY_DIR}/java
)
set(JAVA_INTERNAL_JAR
        ${JAVA_INTERNAL_BUILD_DIR}/fix_code_attribute.jar
)
add_custom_command(
        OUTPUT ${JAVA_INTERNAL_JAR}
        COMMAND ${MAVEN_EXECUTABLE}
        -q
        -DskipTests
        clean package
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${JAVA_INTERNAL_BUILD_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy
        ${JAVA_INTERNAL_PROJECT_DIR}/target/fix_code_attribute.jar
        ${JAVA_INTERNAL_JAR}
        WORKING_DIRECTORY ${JAVA_INTERNAL_PROJECT_DIR}
        COMMENT "Building internal Java helper (Maven)"
)

# new target for build java
add_custom_target(java-internal ALL
        DEPENDS ${JAVA_INTERNAL_JAR}
)

# generate paths for internal java project
configure_file(
        cmake/java-internal-paths.h.in.h
        generated/java-internal-paths.h
)

add_library(jvm-class-builder
        include/jvm/serializable.h
        include/jvm/owner-aware.h
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
        src/descriptor-field.cpp
        src/descriptor-method.cpp
)

target_compile_features(jvm-class-builder PUBLIC cxx_std_20)
set_target_properties(jvm-class-builder PROPERTIES
        CXX_EXTENSIONS OFF
        EXPORT_NAME ClassBuilder
)

target_include_directories(jvm-class-builder
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal
        ${CMAKE_BINARY_DIR}/generated
)

add_library(jvm::ClassBuilder ALIAS jvm-class-builder)

# add dependence to main project
add_dependencies(jvm-class-builder java-internal)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS jvm-class-builder
        EXPORT jvm-class-builderTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT jvm-class-builderTargets
        FILE jvm-class-builderTargets.cmake
        NAMESPACE jvm::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/jvm-class-builder
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/jvm-class-builderConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/jvm-class-builderConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/jvm-class-builderConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/jvm-class-builder
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/jvm-class-builderConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/jvm-class-builderConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/jvm-class-builder
)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
