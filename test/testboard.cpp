#define __DEBUG
#include "../TetrisBoard.h"
#include "../TetrominoFactory.h"
#include "../Tetromino.h"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

// Boardin toiminnan testausta
//#define TEST1

// Palikoiden liikkumisen testausta
#define TEST2

// ---------------------------------------------------------------------------

void printBoard(CTetrisBoard *board);
void fillRow(CTetrisBoard *board, const int y, CELL_TYPE ct);
void pause(void);
bool boolRaport(bool result, string testStr);


#ifdef TEST2

int main(void) {
  CTetrisBoard *board = new CTetrisBoard(10, 10);
  CTetrominoFactory *factory = new CTetrominoFactory();
  CTetromino *blockA = factory->create(BLOCK_T);
  CTetromino *blockB = factory->create(BLOCK_S);
  // filleripalikoita laudalle
  blockA->attach(board,-2); blockA->drop(); blockA->detach();
  blockB->attach(board,-2); blockB->rotateLeft(); blockB->drop(); blockB->detach();

  CTetromino *block = factory->create(BLOCK_T);
  int i = 0;

  // --------- TESTEJÄ

  boolRaport(block->attach(board, -1), "Palikka laudassa" );
  printBoard(board);

  pause();
  boolRaport(block->moveDown(), "Palikan tiputus");
  printBoard(board);

  pause();
  boolRaport(block->rotateRight(), "Palikan kaanto");
  printBoard(board);
  boolRaport(block->rotateRight(), "Palikan kaanto");
  printBoard(board);
  boolRaport(block->rotateRight(), "Palikan kaanto");
  printBoard(board);

  pause();
  while(boolRaport(block->moveLeft(), "Palikan siirto vasemmalle"));
  printBoard(board);

  pause();
  while(boolRaport(block->moveRight(), "Palikkan siirto oikealle"));
  printBoard(board);

  pause();
  for(i=0; i<3; i++)
    boolRaport(block->rotateRight(), "Palikan kaanto oikealle");
  printBoard(board);

  pause();
  for(i=0; i<3; i++)
    boolRaport(block->moveLeft(), "Palikan siirto vasemmalle");
  printBoard(board);

  pause();
  for(i=0; i<3; i++)
    boolRaport(block->rotateRight(), "Palikan kaanto oikealle");
  printBoard(board);

  pause();
  boolRaport(block->drop(), "Palikan tiputus");
  printBoard(board);

//  cout << block->hasLanded();

  return 0;
}

#endif // TEST2

// --------------------------------------------------------------------

#ifdef TEST1

int main(void) {
    CTetrisBoard *board = new CTetrisBoard(10, 10);

    board->setSlot(5, 1, BLOCK_T);
    board->setSlot(2, 2, BLOCK_T);
    board->setSlot(3, 4, BLOCK_I);
    board->setSlot(4, 6, BLOCK_O);
    board->setSlot(5, 6, BLOCK_O);
    board->setSlot(5, 8, BLOCK_Z);
    board->setSlot(4, 6, EMPTY);
    board->setSlot(4, 9, BLOCK_T);

    printBoard(board);

    fillRow(board, 3, BLOCK_S);
    fillRow(board, 2, BLOCK_Z);
    fillRow(board, 4, BLOCK_O);
    fillRow(board, 6, BLOCK_I);

    printBoard(board);
    board->clearFullLines();
    printBoard(board);

    return 0;
}

#endif // TEST2
// --------------------------------------------------------------------

void fillRow(CTetrisBoard *board, const int y, CELL_TYPE ct) {
    for(int x=0; x<board->getWidth(); x++)
        board->setSlot(x, y, ct);
}

void printBoard(CTetrisBoard *board) {
    cout << "\n         ";
    for(int x=0; x<board->getWidth(); x++)
        cout << x << " ";
    cout << "\n";
    for(int y=board->getHeight()-1; y>=0; y--) {
        cout << "    " << y << ":   ";
        for(int x=0; x<board->getWidth(); x++) {
            cout << board->getSlot(x, y) << " ";
        }
        if(board->isEmpty(y))
            cout << "  IS EMPTY";
        else
            cout << "  NOTEMPTY";
        if(board->isFull(y))
            cout << "  IS FULL";
        else
            cout << "  NOTFULL";
        cout << "\n";
    }
    cout << "    Removed lines: " << board->getRemovedLines();
    cout << ", removed lines on last remove: " << board->getRemovedLinesLast();
    cout << "\n\n";
}

void pause() {
  cout << "----------------------------------------- ";
  cout << "Press ENTER ...\n";
  fflush ( stdout );
  getchar();
}

bool boolRaport(bool result, string testStr) {
  if(result) cout << "(TEST) " << testStr << ": onnistui\n";
  else cout << "(TEST) " << testStr << ": epaonnistui\n";
  return result;
}
