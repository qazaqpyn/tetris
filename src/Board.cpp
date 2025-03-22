#include "include/Board.h"

/*
==================
Init
==================
*/
Board::Board(Pieces *pPieces, int pScreenHeight) {
  // Get the screen height
  mScreenHeight = pScreenHeight;

  // Get the pointer to the pieces class
  mPieces = pPieces;

  // Init the board blocks with free positions
  InitBoard();
}

/*
======================================
Init the board blocks with free position
======================================
*/
void Board::InitBoard() {
  for (int i = 0; i < BOARD_WIDTH; i++)
    for (int j = 0; j < BOARD_HEIGHT; j++)
      mBoard[i][j] = POS_FREE;
}

/*
======================================
Store pieces in the board by filling the blocks

parameters:

>> pX horizontal position in blocks
>> pY vertical postion in blocks
>> pPieces pieces to draw
>> pRotation 1 of the 4 possible rotation
=======================================
*/
void Board::StorePieces(int pX, int pY, int pPiece, int pRotation) {
  // Store each block of the piece into the board
  for (int i1 = pX, i2 = 0; i1 < pX + PIECES_BLOCKS; i1++, i2++) {
    for (int j1 = pY, j2 = 0; j1 < pY + PIECES_BLOCKS; j1++, j2++) {
      // Store only blocks of the piece that are not holes
      // And check bounds to prevent accessing invalid memory
      if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0 && i1 >= 0 &&
          i1 < BOARD_WIDTH && j1 >= 0 && j1 < BOARD_HEIGHT) {
        mBoard[i1][j1] = POS_FILLED;
      }
    }
  }
}

/*
=========================================
Check if the game is over coz a pieces have achived the upper positon

returns true or false
=========================================
*/
bool Board::IsGameOver() {
  // if the first line has blocks, then game over
  for (int i = 0; i < BOARD_WIDTH; i++) {
    if (mBoard[i][0] == POS_FILLED)
      return true;
  }
  return false;
}

/*
=========================================
Delete a line of the board by moving all above lines down

parameters
>> pY vertical postion in blocks of the line to delete
=========================================
*/
void Board::DeleteLine(int pY) {
  // moves all the upper lines one row down
  for (int j = pY; j > 0; j--) {
    for (int i = 0; i < BOARD_WIDTH; i++) {
      mBoard[i][j] = mBoard[i][j - 1];
    }
  }
}

/*
 =======================================
  delete all the lines that should be removed
 =======================================
*/
void Board::DeletePossibleLines() {
  for (int j = 0; j < BOARD_HEIGHT; j++) {
    int i = 0;
    while (i < BOARD_WIDTH) {
      if (mBoard[i][j] != POS_FILLED)
        break;
      i++;
    }

    if (i == BOARD_WIDTH) {
      DeleteLine(j);
    }
  }
}

/*
 ==============================
  Returns 1 if this block of the board is empty, 0 if it's filled

  parameters:
  >> pX horizontal position in blocks
  >> pY vertical position in blocks
 ==============================
*/
bool Board::IsFreeBlock(int pX, int pY) {
  if (mBoard[pX][pY] == POS_FREE) {
    return true;
  }
  return false;
}

/*
 =================================
  returns the horizontal positon (in pixels) of the block given like parameter

  parameters:
  >> pPos horizontal positon of the block in the board
 =================================
*/
int Board::GetXPosInPixels(int pPos) {
  return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) +
          (pPos * BLOCK_SIZE));
}

/*
 ================================
 returns the vertical positon (in pixels) of the block given like parameter

 parameters:
 >> pPos horizontal positon of the block in the board
 ================================
*/
int Board::GetYPosInPixels(int pPos) {
  return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
}

/*
 ===================================
  check if the piece can be stored at this postion without any collision
  returns true if the movement is possible, false if it not possible

  parameters:
  >> pX horizontal positon in blocks
  >> pY vertical position in blocks
  >> pPiece piece to draw
  >> pRotation 1 of the 4 possible rotations
 ===================================
*/
bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation) {
  // Checks collision with pieces already stored in the board or the board
  // limits This is just to check the 5x5 blocks of a piece with the appropiate
  // area in the board
  for (int i1 = pX, i2 = 0; i1 < pX + PIECES_BLOCKS; i1++, i2++) {
    for (int j1 = pY, j2 = 0; j1 < pY + PIECES_BLOCKS; j1++, j2++) {
      // Check if the piece is outside the limits of the board
      if (i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1) {
        if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0)
          return 0;
      }

      // Check if the piece have collisioned with a block already stored in the
      // map
      if (j1 >= 0) {
        if ((mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) &&
            (!IsFreeBlock(i1, j1)))
          return false;
      }
    }
  }

  // No collision
  return true;
}
