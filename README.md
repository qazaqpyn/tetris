# Tetris

A classic Tetris game implemented in C++ using SDL2 graphics library.

## Features

- Standard Tetris gameplay mechanics
- Seven classic tetromino shapes
- Keyboard controls for movement and rotation
- Line clearing functionality
- Game over detection

## Requirements

- C++11 or higher
- CMake 3.11 or higher

## Building

```bash
# Clone the repository
git clone https://github.com/yourusername/tetris.git
cd tetris

# Create build directory
mkdir build && cd build

# Configure and build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .

# Run the game
./tetris  # or ./tetris.app/Contents/MacOS/tetris on macOS