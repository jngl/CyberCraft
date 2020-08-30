add_library(LibCyberCraftSFML
        src/conversion.h
        src/conversion.cpp
        include/CyberCraftSFML/WindowSFML.h
        src/WindowSFML.cpp
        )

target_include_directories(LibCyberCraftSFML PUBLIC include)
target_link_libraries(LibCyberCraftSFML LibCyberCraft sfml-graphics)