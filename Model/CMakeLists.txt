cmake_minimum_required(VERSION 3.7)
project(Model)

include_directories("/usr/local/include")
find_package(OpenGL REQUIRED)


link_directories(${OpenGL_LIBRARY_DIRS})
include_directories(${OpenGL_INCLUDE_DIR})

link_directories(${GLFW_LIBRARY_DIRS})
include_directories(${GLFW_INCLUDE_DIR})
set(GLFW3_LIB "/usr/local/lib/libglfw.3.2.dylib")
set(ASSIMP_LIB "/usr/local/Cellar/assimp/4.0.1/lib/libassimp.4.0.1.dylib")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(Model ${SOURCE_FILES})
target_link_libraries(Model ${GLFW3_LIB} ${OPENGL_LIBRARY} ${ASSIMP_LIB})