cmake_minimum_required(VERSION 3.11)
project(tetris VERSION 1.0)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Declare SDL2 dependency
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.5
    GIT_SHALLOW TRUE
)

# Make SDL2 available
FetchContent_MakeAvailable(SDL2)

# List all your source files with exact case matching
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Board.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/IO.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Pieces.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against SDL2
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

# Platform-specific settings
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
    )
endif()