/*****************************************************************************************
/* File: IO.cpp
/* Desc: Class for handling input & drawing, updated to use SDL2
/*****************************************************************************************
*/

#include "include/IO.h"
#include <iostream>

// Initialize static members
SDL_Window *IO::window = nullptr;
SDL_Renderer *IO::renderer = nullptr;

// Color definitions in RGBA format for SDL2
SDL_Color sdlColors[COLOR_MAX] = {
    {0, 0, 0, 255},      // BLACK
    {255, 0, 0, 255},    // RED
    {0, 255, 0, 255},    // GREEN
    {0, 0, 255, 255},    // BLUE
    {0, 255, 255, 255},  // CYAN
    {255, 0, 255, 255},  // MAGENTA
    {255, 255, 0, 255},  // YELLOW
    {255, 255, 255, 255} // WHITE
};

/*
======================================
Constructor
======================================
*/
IO::IO() { InitGraph(); }

/*
======================================
Clear the screen to black
======================================
*/
void IO::ClearScreen()
{
  // Set renderer color to black
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

/*
======================================
Draw a rectangle of a given color

Parameters:
>> pX1, pY1: Upper left corner of the rectangle
>> pX2, pY2: Lower right corner of the rectangle
>> pC: Rectangle color
======================================
*/
void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC)
{
  // Set renderer color
  SDL_SetRenderDrawColor(renderer, sdlColors[pC].r, sdlColors[pC].g,
                         sdlColors[pC].b, sdlColors[pC].a);

  // Create a rectangle
  SDL_Rect rect;
  rect.x = pX1;
  rect.y = pY1;
  rect.w = pX2 - pX1 + 1;
  rect.h = pY2 - pY1 + 1;

  // Fill the rectangle
  SDL_RenderFillRect(renderer, &rect);
}

void IO::DrawText(const char *text, int pX1, int pY1, int pX2, int pY2, enum color pC)
{
  // Calculate the total width available
  int width = pX2 - pX1 + 1;
  int height = pY2 - pY1 + 1;

  // Draw a simple rectangle for the text area
  DrawRectangle(pX1, pY1, pX2, pY2, BLACK);

  // Draw a border
  SDL_SetRenderDrawColor(renderer, sdlColors[pC].r, sdlColors[pC].g,
                         sdlColors[pC].b, sdlColors[pC].a);

  SDL_Rect border;
  border.x = pX1;
  border.y = pY1;
  border.w = width;
  border.h = height;
  SDL_RenderDrawRect(renderer, &border);

  // Determine character width based on available space and text length
  int len = strlen(text);
  int charWidth = width / (len > 0 ? len : 1);
  int charHeight = height - 4; // Leave some margin

  // Start position for drawing text
  int xPos = pX1 + 2; // Margin

  // Draw each character
  for (int i = 0; i < len; i++)
  {
    char c = text[i];

    // Position for this character
    int x = xPos + i * charWidth;

    // Skip if out of bounds
    if (x + charWidth > pX2)
      break;

    switch (c)
    {
    case '0':
      // Draw '0' - a rectangle with hole
      SDL_SetRenderDrawColor(renderer, sdlColors[pC].r, sdlColors[pC].g,
                             sdlColors[pC].b, sdlColors[pC].a);
      DrawRectangle(x, pY1 + 2, x + charWidth - 2, pY1 + height - 3, pC);
      DrawRectangle(x + 2, pY1 + 4, x + charWidth - 4, pY1 + height - 5, BLACK);
      break;

    case '1':
      // Draw '1' - vertical line
      DrawRectangle(x + charWidth / 2 - 1, pY1 + 2, x + charWidth / 2 + 1, pY1 + height - 3, pC);
      break;

    case '2':
      // Draw '2' - like a 'Z'
      DrawRectangle(x, pY1 + 2, x + charWidth - 2, pY1 + 4, pC);                          // Top
      DrawRectangle(x + charWidth - 4, pY1 + 4, x + charWidth - 2, pY1 + height / 2, pC); // Top-Right
      DrawRectangle(x, pY1 + height / 2, x + charWidth - 2, pY1 + height / 2 + 2, pC);    // Middle
      DrawRectangle(x, pY1 + height / 2, x + 2, pY1 + height - 3, pC);                    // Bottom-Left
      DrawRectangle(x, pY1 + height - 5, x + charWidth - 2, pY1 + height - 3, pC);        // Bottom
      break;

    case '3':
      // Draw '3' - like an 'E' without the left side
      DrawRectangle(x, pY1 + 2, x + charWidth - 2, pY1 + 4, pC);                          // Top
      DrawRectangle(x, pY1 + height / 2, x + charWidth - 2, pY1 + height / 2 + 2, pC);    // Middle
      DrawRectangle(x, pY1 + height - 5, x + charWidth - 2, pY1 + height - 3, pC);        // Bottom
      DrawRectangle(x + charWidth - 4, pY1 + 4, x + charWidth - 2, pY1 + height - 3, pC); // Right
      break;

    case '4':
      // Draw '4'
      DrawRectangle(x, pY1 + 2, x + 2, pY1 + height / 2 + 2, pC);                         // Top-Left
      DrawRectangle(x, pY1 + height / 2, x + charWidth - 2, pY1 + height / 2 + 2, pC);    // Middle
      DrawRectangle(x + charWidth - 4, pY1 + 2, x + charWidth - 2, pY1 + height - 3, pC); // Right
      break;

    case '5':
      // Draw '5' - like an 'S'
      DrawRectangle(x, pY1 + 2, x + charWidth - 2, pY1 + 4, pC);                                       // Top
      DrawRectangle(x, pY1 + 4, x + 2, pY1 + height / 2, pC);                                          // Left-Top
      DrawRectangle(x, pY1 + height / 2, x + charWidth - 2, pY1 + height / 2 + 2, pC);                 // Middle
      DrawRectangle(x + charWidth - 4, pY1 + height / 2 + 2, x + charWidth - 2, pY1 + height - 5, pC); // Right-Bottom
      DrawRectangle(x, pY1 + height - 5, x + charWidth - 2, pY1 + height - 3, pC);                     // Bottom
      break;

    case '6':
    case '7':
    case '8':
    case '9':
      // Basic pattern for other numbers
      DrawRectangle(x, pY1 + 2, x + charWidth - 2, pY1 + height - 3, pC);
      break;

    case 'S':
    case 's':
      // Draw 'S'
      DrawRectangle(x + 2, pY1 + 2, x + charWidth - 2, pY1 + 4, pC);                                   // Top
      DrawRectangle(x, pY1 + 4, x + 2, pY1 + height / 2, pC);                                          // Left-Top
      DrawRectangle(x + 2, pY1 + height / 2 - 1, x + charWidth - 4, pY1 + height / 2 + 1, pC);         // Middle
      DrawRectangle(x + charWidth - 4, pY1 + height / 2 + 1, x + charWidth - 2, pY1 + height - 5, pC); // Right-Bottom
      DrawRectangle(x + 2, pY1 + height - 5, x + charWidth - 4, pY1 + height - 3, pC);                 // Bottom
      break;

    case 'c':
    case 'C':
      // Draw 'C'
      DrawRectangle(x + 2, pY1 + 2, x + charWidth - 4, pY1 + 4, pC);                   // Top
      DrawRectangle(x, pY1 + 4, x + 2, pY1 + height - 5, pC);                          // Left
      DrawRectangle(x + 2, pY1 + height - 5, x + charWidth - 4, pY1 + height - 3, pC); // Bottom
      break;

    case 'o':
    case 'O':
      // Draw 'O' (like a '0')
      DrawRectangle(x, pY1 + 2, x + charWidth - 2, pY1 + height - 3, pC);
      DrawRectangle(x + 2, pY1 + 4, x + charWidth - 4, pY1 + height - 5, BLACK);
      break;

    case 'r':
    case 'R':
      // Draw 'R'
      DrawRectangle(x, pY1 + 2, x + 2, pY1 + height - 3, pC);                                          // Left
      DrawRectangle(x, pY1 + 2, x + charWidth - 4, pY1 + 4, pC);                                       // Top
      DrawRectangle(x + charWidth - 4, pY1 + 4, x + charWidth - 2, pY1 + height / 2, pC);              // Right-Top
      DrawRectangle(x, pY1 + height / 2 - 1, x + charWidth - 4, pY1 + height / 2 + 1, pC);             // Middle
      DrawRectangle(x + charWidth / 2, pY1 + height / 2 + 1, x + charWidth - 2, pY1 + height - 3, pC); // Right-Bottom
      break;

    case 'e':
    case 'E':
      // Draw 'E'
      DrawRectangle(x, pY1 + 2, x + 2, pY1 + height - 3, pC);                              // Left
      DrawRectangle(x, pY1 + 2, x + charWidth - 2, pY1 + 4, pC);                           // Top
      DrawRectangle(x, pY1 + height / 2 - 1, x + charWidth - 4, pY1 + height / 2 + 1, pC); // Middle
      DrawRectangle(x, pY1 + height - 5, x + charWidth - 2, pY1 + height - 3, pC);         // Bottom
      break;

    case ':':
      // Draw ':'
      DrawRectangle(x + charWidth / 2 - 1, pY1 + height / 3, x + charWidth / 2 + 1, pY1 + height / 3 + 2, pC);
      DrawRectangle(x + charWidth / 2 - 1, pY1 + 2 * height / 3, x + charWidth / 2 + 1, pY1 + 2 * height / 3 + 2, pC);
      break;

    case ' ':
      // Space - draw nothing
      break;

    default:
      // For other characters, just draw a rectangle
      DrawRectangle(x + 1, pY1 + 2, x + charWidth - 3, pY1 + height - 3, pC);
    }
  }
}

void IO::DrawScore(int score)
{
  // Top-right position
  int topX = 450;
  int topY = 30;
  int blockSize = 10; // Size of each pixel block
  int spacing = 2;    // Space between blocks

  // Draw "SCORE:" text
  DrawText("SCORE:", topX, topY, topX + 100, topY + 20, WHITE);

  // Draw the score digits
  char scoreStr[20];
  sprintf(scoreStr, "%d", score);
  int scoreLen = strlen(scoreStr);

  // Position for the score digits (below the "SCORE:" text)
  int digitY = topY + 30;

  // Draw each digit
  for (int i = 0; i < scoreLen; i++)
  {
    int digit = scoreStr[i] - '0'; // Convert char to int
    int digitX = topX + i * (blockSize * 4 + spacing);

    // Draw the digit as blocks
    DrawDigitAsBlocks(digit, digitX, digitY, blockSize, WHITE);
  }
}

void IO::DrawDigitAsBlocks(int digit, int x, int y, int blockSize, enum color pC)
{
  // Define digits as 3x5 arrays where 1 represents a block
  const bool digitPatterns[10][5][3] = {
      // 0
      {
          {1, 1, 1},
          {1, 0, 1},
          {1, 0, 1},
          {1, 0, 1},
          {1, 1, 1}},
      // 1
      {
          {0, 1, 0},
          {0, 1, 0},
          {0, 1, 0},
          {0, 1, 0},
          {0, 1, 0}},
      // 2
      {
          {1, 1, 1},
          {0, 0, 1},
          {1, 1, 1},
          {1, 0, 0},
          {1, 1, 1}},
      // 3
      {
          {1, 1, 1},
          {0, 0, 1},
          {1, 1, 1},
          {0, 0, 1},
          {1, 1, 1}},
      // 4
      {
          {1, 0, 1},
          {1, 0, 1},
          {1, 1, 1},
          {0, 0, 1},
          {0, 0, 1}},
      // 5
      {
          {1, 1, 1},
          {1, 0, 0},
          {1, 1, 1},
          {0, 0, 1},
          {1, 1, 1}},
      // 6
      {
          {1, 1, 1},
          {1, 0, 0},
          {1, 1, 1},
          {1, 0, 1},
          {1, 1, 1}},
      // 7
      {
          {1, 1, 1},
          {0, 0, 1},
          {0, 0, 1},
          {0, 0, 1},
          {0, 0, 1}},
      // 8
      {
          {1, 1, 1},
          {1, 0, 1},
          {1, 1, 1},
          {1, 0, 1},
          {1, 1, 1}},
      // 9
      {
          {1, 1, 1},
          {1, 0, 1},
          {1, 1, 1},
          {0, 0, 1},
          {1, 1, 1}}};

  // Draw the digit according to its pattern
  for (int row = 0; row < 5; row++)
  {
    for (int col = 0; col < 3; col++)
    {
      if (digitPatterns[digit][row][col])
      {
        // Calculate block position
        int blockX = x + col * blockSize;
        int blockY = y + row * blockSize;

        // Draw the block
        DrawRectangle(blockX, blockY,
                      blockX + blockSize - 1,
                      blockY + blockSize - 1,
                      pC);
      }
    }
  }
}

/*
======================================
Return the screen height
======================================
*/
int IO::GetScreenHeight()
{
  int height;
  SDL_GetWindowSize(window, nullptr, &height);
  return height;
}

/*
======================================
Update screen
======================================
*/
void IO::UpdateScreen() { SDL_RenderPresent(renderer); }

/*
======================================
Keyboard Input - Poll for a keypress
======================================
*/
int IO::PollKey()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_KEYDOWN:
      return event.key.keysym.sym;
    case SDL_QUIT:
      exit(3);
    }
  }
  return -1;
}

/*
======================================
Keyboard Input - Wait for a keypress
======================================
*/
int IO::Getkey()
{
  SDL_Event event;
  while (true)
  {
    if (SDL_WaitEvent(&event))
    {
      if (event.type == SDL_KEYDOWN)
        return event.key.keysym.sym;
      if (event.type == SDL_QUIT)
        exit(3);
    }
  }
}

/*
======================================
Keyboard Input - Check if a key is down
======================================
*/
int IO::IsKeyDown(int pKey)
{
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  SDL_Scancode sc = SDL_GetScancodeFromKey(pKey);
  return keystate[sc];
}

/*
======================================
SDL2 Graphical Initialization
======================================
*/
int IO::InitGraph()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Set up clean exit
  atexit(SDL_Quit);

  // Create window - 640x480 is the original resolution
  window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

  if (window == nullptr)
  {
    std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
    return 2;
  }

  // Create renderer
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (renderer == nullptr)
  {
    std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
    return 3;
  }

  // Set up blending
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  return 0;
}
