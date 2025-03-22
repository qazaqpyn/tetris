//: Game.h
#ifndef __GAME__
#define __GAME__

#include "IO.h"
#include "Board.h"
#include "Pieces.h"
#include <time.h>

#define WAIT_TIME 700

class Game
{
  int mScreenHeight;
  int mNextPosX, mNextPosY;
  int mNextPiece, mNextRotation;

  Board *mBoard;
  Pieces *mPieces;
  IO *mIO;

  int GetRand(int pA, int pB);
  void InitGame();
  void DrawPiece(int pX, int pY, int pPieces, int pRotation);
  void DrawBoard();

public:
  Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);

  void DrawScene();
  void CreateNewPiece();

  int mPosX, mPosY;      // Position of the piece that is falling down
  int mPiece, mRotation; // kind and rotation the piece is falling down
};

#endif // !__GAME__
