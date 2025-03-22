//: Board.h

#ifndef __BOARD__
#define __BOARD__
#include "Pieces.h"

#define BOARD_LINE_WIDTH 6      // width of each of the two lines that delimit the board
#define BLOCK_SIZE 15           // width and height of each block of a piece
#define BOARD_POSITION 320      // center positon of the board from left of the screen
#define BOARD_WIDTH 10          // board width in blocks
#define BOARD_HEIGHT 20         // board height in blocks
#define MIN_VERTICAL_MARGIN 20  // minimum vertical margin for the board limit
#define MIN_HORIZONAL_MARGIN 20 // minimum horizontal margin for the board limit
#define PIECES_BLOCKS 5         // number of horizontal and vertical blocks of martrix pieces

class Board
{
  enum
  {
    POS_FREE,
    POS_FILLED
  }; // POS_FREE = free podsiton of the board, POS_FILLED = filled positon of
     // board
  int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
  Pieces *mPieces;
  int mScreenHeight;

  void InitBoard();
  void DeleteLine(int pY);

public:
  Board(Pieces *pPieces, int pScreenHeight);

  int GetXPosInPixels(int pPos);
  int GetYPosInPixels(int pPos);
  bool IsFreeBlock(int pX, int pY);
  bool IsPossibleMovement(int pX, int pY, int pPieces, int pRotation);
  void StorePieces(int pX, int pY, int pPieces, int pRotation);
  void DeletePossibleLines();
  bool IsGameOver();
};
#endif // !__BOARD__
