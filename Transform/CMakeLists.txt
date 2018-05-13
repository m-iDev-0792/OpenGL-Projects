cmake_minimum_required(VERSION 3.7)
project(Transform)

include_directories("/usr/local/include")
find_package(OpenGL REQUIRED)
link_directories(${OpenGL_LIBRARY_DIRS})
include_directories(${OpenGL_INCLUDE_DIR})

link_directories(${GLFW_LIBRARY_DIRS})
include_directories(${GLFW_INCLUDE_DIR})
set(GLFW3_LIB "/usr/local/lib/libglfw.3.2.dylib")

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(Transform ${SOURCE_FILES})
target_link_libraries(Transform ${GLFW3_LIB} ${OPENGL_LIBRARY})