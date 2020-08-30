add_library(LibCyberCraft
        include/Core/BTreePlus.h
        include/Core/Common.h
        src/Core/Common.cpp
        include/Core/Error.h
        src/Core/Error.cpp
        include/Core/Math.h
        include/ECS/Scene.h
        src/Core/Scene.cpp
        include/Core/Update.h
        src/Core/Update.cpp
        include/Core/Window.h
        src/Core/Window.cpp
        include/ECS/Basic.h
        include/ECS/Scene.h
        src/ECS/Scene.cpp
        include/ECS/Iterator.h
        src/ECS/Iterator.cpp
        include/ECS/Range.h
        src/ECS/Range.cpp
        include/ECS/Iterator.h)

target_include_directories(LibCyberCraft PUBLIC include)