cmake_minimum_required(VERSION 3.16)
project(MyMod)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(MyMod SHARED
    src/mymod.cpp
)

target_include_directories(MyMod PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Link against the OpenShunter import library so RegisterMod etc. resolve
target_link_libraries(MyMod PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/openttd.lib
)

# Output the .dll next to the game's mods folder for convenience
set_target_properties(MyMod PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)
