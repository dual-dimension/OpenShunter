cmake_minimum_required(VERSION 3.16)

file(STRINGS "${CMAKE_SOURCE_DIR}/mod.config" _config)
foreach(_line ${_config})
    if(_line MATCHES "^MOD_NAME=(.+)$")
        set(MOD_NAME "${CMAKE_MATCH_1}")
    endif()
endforeach()

project(${MOD_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(Mod SHARED
    src/mymod.cpp
)

target_include_directories(Mod PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Link against the OpenShunter import library so RegisterMod etc. resolve
target_link_libraries(Mod PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/openttd.lib
)

# Output the .dll next to the game's mods folder for convenience
set_target_properties(Mod PROPERTIES
    OUTPUT_NAME ${MOD_NAME}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out
)
