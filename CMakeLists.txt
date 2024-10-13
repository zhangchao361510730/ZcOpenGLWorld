cmake_minimum_required (VERSION 3.0)
cmake_policy(VERSION 3.0)

project(zhcOpenGl)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

if (WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
	link_directories(${CMAKE_SOURCE_DIR}/windows_libs/lib)
	include_directories(${CMAKE_SOURCE_DIR}/windows_libs/includes)
elseif (UNIX)
    add_definitions(-DPLATFORM_UNIX)
	link_directories(${CMAKE_SOURCE_DIR}/linux_libs/lib)
	include_directories(${CMAKE_SOURCE_DIR}/linux_libs/includes)
endif()


link_directories(${CMAKE_SOURCE_DIR}/linux_libs/lib)
include_directories(${CMAKE_SOURCE_DIR}/linux_libs/includes)

set(DEPENDS_LIB glfw3)

add_executable(${PROJECT_NAME}_main openGLMain.cpp src/glad.c)
target_link_libraries(${PROJECT_NAME}_main PUBLIC ${DEPENDS_LIB})
