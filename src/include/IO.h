//: IO.h

#ifndef __IO__
#define __IO__
#include <SDL.h>

enum color
{
  BLACK,
  RED,
  GREEN,
  BLUE,
  CYAN,
  MAGENTA,
  YELLOW,
  WHITE,
  COLOR_MAX
};

class IO
{
public:
  IO();

  void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
  void ClearScreen();
  int GetScreenHeight();
  int InitGraph();
  int PollKey();
  int Getkey();
  int IsKeyDown(int pKey);
  void UpdateScreen();
  void DrawText(const char *text, int pX1, int pY1, int pX2, int pY2, enum color pC);
  void DrawScore(int score);

private:
  static SDL_Window *window;
  static SDL_Renderer *renderer;
  void DrawDigitAsBlocks(int digit, int x, int y, int blockSize, enum color pC);
};
#endif // __IO__
