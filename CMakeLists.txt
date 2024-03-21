cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Game VERSION 0.1.0)

set(SDL2_DIR ".")
include_directories(${SDL2_DIR}/include)
link_directories(${SDL2_DIR}/lib)

# find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_ttf REQUIRED)
# find_package(SDL2_mixer REQUIRED)

set(SOURCES
    src/main.cpp
    src/renderWindow.cpp
)

add_executable(Game ${SOURCES})

# target_link_libraries(Game
#     PRIVATE
#     SDL2::SDL2main    
#     SDL2::SDL2
#     SDL2_image::SDL2_image
#     # SDL2_ttf::SDL2_ttf
#     # SDL2_mixer::SDL2_mixer
# )

target_link_libraries(Game
    PRIVATE
    mingw32
    SDL2main    
    SDL2
    SDL2_image
    # SDL2_ttf
    # SDL2_mixer
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../bin)