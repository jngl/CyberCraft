add_library(LibCyberCraft
        include/Core/BTreePlus.h
        include/Core/Common.h
        src/Core/Common.cpp
        include/Core/Error.h
        src/Core/Error.cpp
        include/Core/Math.h
        include/Core/Scene.h
        src/Core/Scene.cpp
        include/Core/Update.h
        src/Core/Update.cpp
        include/Core/Window.h
        src/Core/Window.cpp)

target_include_directories(LibCyberCraft PUBLIC include)
target_link_libraries(LibCyberCraft sfml-graphics)