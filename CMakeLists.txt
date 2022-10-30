CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(project)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE DEBUG)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# add_subdirectory(/home/dave/glfw /home/dave/glfw/src)

# this works but is messier
# FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

set (SOURCE_DIR      ${PROJECT_SOURCE_DIR}/src)
SET(DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/Dependencies)

set(GLFW_DIR ${DEPENDENCIES_DIR}/glfw-3.3.8)
set(GLEW_DIR ${DEPENDENCIES_DIR}/glew-2.2.0)

SET(GLFW_INCLUDE_DIR         ${GLFW_DIR}/include)
SET(GLEW_INCLUDE_DIR         ${GLEW_DIR}/include)
# add_library(STATIC "${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(SOURCE_FILES 
${SOURCE_DIR}/graphics/VertexArray.h           ${SOURCE_DIR}/graphics/VertexArray.cpp 
${SOURCE_DIR}/graphics/IndexBuffer.h           ${SOURCE_DIR}/graphics/IndexBuffer.cpp 
${SOURCE_DIR}/graphics/VertexBuffer.h          ${SOURCE_DIR}/graphics/VertexBuffer.cpp 
${SOURCE_DIR}/graphics/VertexBufferLayout.h    ${SOURCE_DIR}/graphics/VertexBufferLayout.cpp
${SOURCE_DIR}/graphics/Renderer.h              ${SOURCE_DIR}/graphics/Renderer.cpp 
${SOURCE_DIR}/graphics/Renderable2D.h          ${SOURCE_DIR}/graphics/Renderable2D.cpp 
${SOURCE_DIR}/graphics/Shader.h                         ${SOURCE_DIR}/graphics/Shader.cpp 
${SOURCE_DIR}/math/Vec2.h ${SOURCE_DIR}/math/Vec2.cpp 
${SOURCE_DIR}/math/Vec3.h ${SOURCE_DIR}/math/Vec3.cpp 
${SOURCE_DIR}/math/Vec4.h ${SOURCE_DIR}/math/Vec4.cpp 
${SOURCE_DIR}/math/Mat4.h ${SOURCE_DIR}/math/Mat4.cpp 
${SOURCE_DIR}/math/Math.h
${SOURCE_DIR}/utils/fileutils.h
${SOURCE_DIR}/utils/Error.h 
${SOURCE_DIR}/Window.h ${SOURCE_DIR}/Window.cpp 
${SOURCE_DIR}/main.cpp 

${SOURCE_DIR}/vender/stb_image/stb_image.h

# ${GLFW_INCLUDE_DIR}/GLFW/glfw3.h
# ${GLEW_INCLUDE_DIR}/GL/glew.h
)	
# Dependencies/glew-2.2.0/include/GL/glew.hset
set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)
# SET(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.h)

# specific to linux
# TARGET_LINK_LIBRARIES(project libGLEW.so libGLU.so libGL.so)
# TARGET_LINK_LIBRARIES(project glfw)

# target_include_directories(project PRIVATE "${PROJECT_SOURCE_DIR}/Dependences/glfw-3.3.8/include")

add_subdirectory(${GLFW_DIR} ${GLFW_DIR}/src)

ADD_EXECUTABLE(project ${SOURCE_FILES})
set (OpenGL_GL_PREFERENCE "GLVND")

# target_include_directories(project PUBLIC "${GLEW_INCLUDE_DIR}")
# target_include_directories(project PUBLIC "${GLFW_INCLUDE_DIR}")
target_link_libraries(project ${GLEW_DIR}/lib/libGLEW.a)
target_link_libraries(project glfw)
TARGET_LINK_LIBRARIES(project OpenGL::GL)
