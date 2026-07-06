cmake_minimum_required(VERSION 3.10)
project(billiard_sim VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OpenGL_GL_PREFERENCE GLVND)

set(ENV{PKG_CONFIG_PATH} "/home/user/glfw/build/src:$ENV{PKG_CONFIG_PATH}")

find_package(Freetype REQUIRED)

find_package(OpenGL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)

set_target_properties(PkgConfig::GLFW PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "")

# 1. Automatically find all .cpp and .h files in the "src" directory and its subfolders
file(GLOB_RECURSE SOURCE_FILES 
    CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

# 2. Pass the generated list to your executable
add_executable(billiard_sim ${SOURCE_FILES})

target_include_directories(billiard_sim PRIVATE 
                            /home/user/glfw/include 
                            ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
                            ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm
                            ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb
                            ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(billiard_sim PRIVATE PkgConfig::GLFW OpenGL::OpenGL ${FREETYPE_LIBRARIES})


