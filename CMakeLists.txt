cmake_minimum_required(VERSION 3.24)
project(JUI)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

# Add SDL2 CMake add_library modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

#add_subdirectory(lib)

add_subdirectory(lib/SDL_FontCache)

# Add all c++ source
file(GLOB_RECURSE SRC_FILES "include/JUI/*.hpp"  "src/JUI/*.cpp")

file(GLOB_RECURSE TEST_SRC_FILES "include/TestBench/*.hpp" "src/TestBench/*.cpp")

include_directories(include)
include_directories(lib)
add_library(JUI SHARED ${SRC_FILES})

add_executable(JUI_Demo ${TEST_SRC_FILES})

target_link_libraries(JUI_Demo PUBLIC JUI SDL2 SDL2_image SDL2_ttf FontCache )