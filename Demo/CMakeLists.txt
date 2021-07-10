file(GLOB_RECURSE demo_source_files src/*)
add_library(Demo SHARED ${demo_source_files})
target_link_libraries(Demo
<<<<<<< HEAD
        LibCyberCraftCore
        LibCyberCraftKernel)
=======
        LibCyberCraftCore)
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f
