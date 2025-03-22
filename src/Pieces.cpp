#include "include/Pieces.h"
#include "assets/Blocks.cpp"

// Return the type of block (0-no block, 1-normal block, 2-pivot block)
// pPieces - piece to draw
// pRotation - 1 of the 4 possible rotations
// px - horizontal position in blocks
// py - vertical position in blocks
int Pieces::GetBlockType(int pPieces, int pRotation, int pX, int pY)
{
  return mPieces[pPieces][pRotation][pX][pY];
}

// Return the horizontal displacement of the piece that has to be applied
// to create it in the correct positon
// pPieces - pieces to draw
// pRotation - 1 out of the 4 possible rotations
int Pieces::GetXInitialPosition(int pPieces, int pRotation)
{
  return mPiecesInitialPosition[pPieces][pRotation][0];
}

// Return the vertical displacement of the pieces that has to be applied
// in order to create it in the correct position
int Pieces::GetYInitialPosition(int pPieces, int pRotation)
{
  return mPiecesInitialPosition[pPieces][pRotation][1];
}
