cmake_minimum_required(VERSION 3.24)
project(JUI)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

# Add SDL2 CMakeadd_library modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

#add_subdirectory(lib)

add_subdirectory(lib/SDL_FontCache)

# Add all c++ source
file(GLOB SOURCES "src/*.cpp")

include_directories(include)
add_library(JUI SHARED ${SOURCES})

add_executable(JUI_Demo ${SOURCES})

target_link_libraries(JUI_Demo PUBLIC JUI SDL2 SDL2_image SDL2_ttf)