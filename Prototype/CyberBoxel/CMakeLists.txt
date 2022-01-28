#GameEngine
file(GLOB_RECURSE CB_source_files src/*)
add_executable(CyberBoxel ${CB_source_files})
TARGET_LINK_LIBRARIES(CyberBoxel
            ${OPENGL_LIBRARIES}
            ${CMAKE_DL_LIBS}
            Glad
            stb
            Imgui
            LibCyberCraftSystem
)
target_include_directories(CyberBoxel PUBLIC include)
