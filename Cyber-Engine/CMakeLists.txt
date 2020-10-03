#Output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Game)

#SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})


#GameEngine
file(GLOB_RECURSE ext_source_files ext/src/*)
file(GLOB_RECURSE GE_source_files src/*)
add_executable(GameEngine ${GE_source_files} ${ext_source_files})
TARGET_LINK_LIBRARIES(GameEngine
            ${SDL2_LIBRARY} 
            ${OPENGL_LIBRARIES}
            ${CMAKE_DL_LIBS}
            LibCyberCraftCore
)
target_include_directories(GameEngine PUBLIC include)
target_include_directories(GameEngine PUBLIC ext/include)