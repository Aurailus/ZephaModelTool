# Set the C++ Standard
cmake_minimum_required (VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set project variables
set(PROJECT_NAME "ModelTool")
set(MAIN_EXEC_NAME "ModelTool")
set(MAIN_LIB_NAME "Core")
project(${PROJECT_NAME})

# Load GLEW
find_path(GLEW_HEADERS GL/glew.h)
include_directories(${GLEW_HEADERS})

# Load GLFW
find_path(GLFW_HEADERS GLFW/glfw3.h)

# Load GLM
find_path(GLM_HEADERS glm/glm.hpp)
include_directories(${GLM_HEADERS})

# Load Assimp
#find_path(ASSIMP_HEADERS assimp/Importer.hpp)
#include_directories(${ASSIMP_HEADERS})

# Load Noise
find_path(NOISE_HEADERS noise/noise.h)
find_library(NOISE_LIB NAMES libnoise noise noise-static)
include_directories(${NOISE_HEADERS})

# Include Threading
#find_path(PTHREAD_HEADERS pthread.h)
#if (WIN32)
#    find_library(PTHREAD_LIB pthreadVC3)
#else()
#    find_library(PTHREAD_LIB pthread)
#endif()
#include_directories(${PTHREAD_HEADERS}

# Load Header-only-libraries
include_directories(lib/header/cute_files/include)
include_directories(lib/header/stb_image/include)
#include_directories(lib/header/json/include)

add_subdirectory(src)
add_executable(${MAIN_EXEC_NAME} src/Main.cpp)
target_link_libraries(${MAIN_EXEC_NAME} ${MAIN_LIB_NAME})

# Include GLFW
target_include_directories(${MAIN_EXEC_NAME} PRIVATE ${GLFW_HEADERS})

# Link OpenGL
find_package (OpenGL REQUIRED)
target_link_libraries(${MAIN_EXEC_NAME} ${OPENGL_gl_LIBRARY})

# Build and link GLFW
if (WIN32)
    find_library(GLFW_LIB glfw3dll)
else()
    set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory (lib/static/glfw)
    target_link_libraries (${MAIN_EXEC_NAME} glfw)
    include_directories(lib/static/glfw/src)
endif()

if (WIN32)
    find_library(GLEW_LIB glew32)
else()
    set(GLEW_LIB ${CMAKE_SOURCE_DIR}/lib/static/glew/libGLEW.a)
endif()

# Link Glew
target_link_libraries(${MAIN_EXEC_NAME} ${GLEW_LIB})

# Build and Link Assimp
#if (WIN32)
#    find_library(ASSIMP_LIB assimp-vc142-mt)
#else()
#    set(BUILD_SHARED_LIBS OFF)
#    set(ASSIMP_NO_EXPORT ON)
#    set(ASSIMP_BUILD_TESTS OFF)
#    set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
#
#    set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
#    set(ASSIMP_BUILD_B3D_IMPORTER ON)
#    set(ASSIMP_BUILD_X3D_IMPORTER ON) # Doesn't compile if not defined
#
#    add_subdirectory(lib/static/assimp)
#    target_compile_options(assimp PRIVATE -w)
#    target_link_libraries(${MAIN_EXEC_NAME} assimp)
#endif()

# Link Noise
target_link_libraries(${MAIN_EXEC_NAME} ${NOISE_LIB})

# Link PThread
#target_link_libraries (${MAIN_EXEC_NAME} ${PTHREAD_LIB})
