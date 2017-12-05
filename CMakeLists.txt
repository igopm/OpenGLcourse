cmake_minimum_required(VERSION 3.1)
project (OpenGLcourse)

set (CMAKE_CXX_STANDARD 14)

# OpenGL, GLEW, GLFW :
FIND_LIBRARY(GLFW_LIB NAMES glfw glfw3)
FIND_LIBRARY(GLEW_LIB NAMES glew GLEW glew32)
find_package(OpenGL REQUIRED)
set(GL_LIBS  ${GLEW_LIB} ${GLFW_LIB} ${OPENGL_gl_LIBRARY})

# Set include dirs
include_directories(
    MotokoGL
    Soil
    )

# Threads
#find_package(Threads)

# Build SOIL library
add_subdirectory(Soil)

# Build MotokoGL library
add_subdirectory(MotokoGL)

add_subdirectory(15112017)
add_subdirectory(Dz1)
add_subdirectory(Dz2)
add_subdirectory(Dz3)
