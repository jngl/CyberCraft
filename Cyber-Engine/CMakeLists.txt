cmake_minimum_required (VERSION 3.0)
project (MyGameEngine)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${MyGameEngine_SOURCE_DIR}/cmake")

#Output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MyGameEngine_SOURCE_DIR}/Game)

#C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

#ext
include_directories("${MyGameEngine_SOURCE_DIR}/ext/include")
file(GLOB_RECURSE ext_source_files ext/src/*)

#include
include_directories("${MyGameEngine_SOURCE_DIR}/include")

#GameEngine
file(GLOB_RECURSE GE_source_files src/*)
add_executable(GameEngine ${GE_source_files} ${ext_source_files})
TARGET_LINK_LIBRARIES(GameEngine
            ${SDL2_LIBRARY} 
            ${OPENGL_LIBRARIES}
            ${CMAKE_DL_LIBS}
)
