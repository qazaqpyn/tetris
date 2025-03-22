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
IO::IO()
{
    InitGraph();
}

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
    SDL_SetRenderDrawColor(renderer,
                           sdlColors[pC].r,
                           sdlColors[pC].g,
                           sdlColors[pC].b,
                           sdlColors[pC].a);

    // Create a rectangle
    SDL_Rect rect;
    rect.x = pX1;
    rect.y = pY1;
    rect.w = pX2 - pX1 + 1;
    rect.h = pY2 - pY1 + 1;

    // Fill the rectangle
    SDL_RenderFillRect(renderer, &rect);
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
void IO::UpdateScreen()
{
    SDL_RenderPresent(renderer);
}

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
    window = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cerr << "Couldn't create window: " << SDL_GetError() << std::endl;
        return 2;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        std::cerr << "Couldn't create renderer: " << SDL_GetError() << std::endl;
        return 3;
    }

    // Set up blending
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    return 0;
}