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

file(GLOB SRCFILE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB GLLSTool_ ${CMAKE_CURRENT_SOURCE_DIR}/src/commonTool/*.cpp)
list(APPEND SRCFILE ${GLLSTool_})

file(GLOB GLLSTool_ ${CMAKE_CURRENT_SOURCE_DIR}/src/mainLoopEngine/*.cpp)
list(APPEND SRCFILE ${GLLSTool_})

file(GLOB GLLSTool_ ${CMAKE_CURRENT_SOURCE_DIR}/src/cubeFunc/*.cpp)
list(APPEND SRCFILE ${GLLSTool_})

file(GLOB GLLSTool_ ${CMAKE_CURRENT_SOURCE_DIR}/src/Ui2D/*.cpp)
list(APPEND SRCFILE ${GLLSTool_})

# 打印源代码路径
message(STATUS "Current Source Directory: ${CMAKE_CURRENT_SOURCE_DIR}")
# 打印构建路径
message(STATUS "Current Binary Directory: ${CMAKE_CURRENT_BINARY_DIR}")
# 打印 CMake 项目根目录
message(STATUS "Source Directory: ${CMAKE_SOURCE_DIR}")
# 打印当前 CMakeLists.txt 文件所在的路径
message(STATUS "Current CMake File Directory: ${CMAKE_CURRENT_LIST_DIR}")

link_directories(${CMAKE_SOURCE_DIR}/linux_libs/lib)
include_directories(${CMAKE_SOURCE_DIR}/linux_libs/includes)
include_directories(${CMAKE_SOURCE_DIR}/src/sourceLib)
include_directories(${CMAKE_SOURCE_DIR}/src/mainLoopEngine)
include_directories(${CMAKE_SOURCE_DIR}/src/cubeFunc)
include_directories(${CMAKE_SOURCE_DIR}/src/commonTool)
include_directories(${CMAKE_SOURCE_DIR}/src/Ui2D)

#-lGL -lGLU -lglut
set(DEPENDS_LIB glfw3 assimp glut GLU GL)
# 将 CMake 变量传递给 C++
add_executable(${PROJECT_NAME}_main openGLMain.cpp src/sourceLib/glad.c ${SRCFILE})
#add_executable(${PROJECT_NAME}_main test1.cpp src/sourceLib/glad.c)
target_compile_definitions(${PROJECT_NAME}_main PRIVATE CMAKE_CURRENT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME}_main PUBLIC ${DEPENDS_LIB} )
