//: pieces.w

#ifndef __PIECES__
#define __PIECES__

//------------------------------
// Pieces
//------------------------------

class Pieces
{
public:
  int GetBlockType(int pPieces, int pRotation, int pX, int pY);
  int GetXInitialPosition(int pPieces, int pRotation);
  int GetYInitialPosition(int pPieces, int pRotation);
};

#endif //__PIECES__
