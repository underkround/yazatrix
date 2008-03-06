#define __DEBUG
#include "../TetrisBoard.h"
#include "../TetrominoFactory.h"
#include "../Tetromino.h"
#include "../Graphics.h"
#include "../BoardGraphics.h"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

// Boardin toiminnan testausta
//#define TEST1

// Palikoiden liikkumisen testausta
#define TEST2
#define TEST2_GRAFIIKALLA
//#define FUNKKARITULOSTE

void printBoard(CTetrisBoard *board);
void fillRow(CTetrisBoard *board, const int y, CELL_TYPE ct);
void pause(void);
bool boolReport(bool result, string testStr);




#ifdef TEST2

int main(void) {
  CTetrisBoard *board = new CTetrisBoard(10, 10);
  CTetrominoFactory *factory = new CTetrominoFactory();
  CTetromino *blockA = factory->create(BLOCK_T);
  CTetromino *blockB = factory->create(BLOCK_S);
  // filleripalikoita laudalle
  blockA->attach(board,-2); blockA->drop(); blockA->detach();
  blockB->attach(board,-2); blockB->rotateLeft(); blockB->drop(); blockB->detach();

#ifdef TEST2_GRAFIIKALLA
  CGraphics *graphics = new CGraphics();
  CBoardGraphics *boardGraphics = new CBoardGraphics(board, graphics, 1, 1);

#endif // TEST2_GRAFIIKALLA

  CTetromino *block = factory->create(BLOCK_T);
  int i = 0;

  // --------- TESTEJÄ

  boolReport(block->attach(board, -1), "Palikka laudassa" );
  printBoard(board);

  pause();
  boolReport(block->moveDown(), "Palikan tiputus");
  printBoard(board);

  pause();
  boolReport(block->rotateRight(), "Palikan kaanto");
  printBoard(board);
  boolReport(block->rotateRight(), "Palikan kaanto");
  printBoard(board);
  boolReport(block->rotateRight(), "Palikan kaanto");
  printBoard(board);

  pause();
  while(boolReport(block->moveLeft(), "Palikan siirto vasemmalle"));
  printBoard(board);

  pause();
  while(boolReport(block->moveRight(), "Palikkan siirto oikealle"));
  printBoard(board);

  pause();
  for(i=0; i<3; i++)
    boolReport(block->rotateRight(), "Palikan kaanto oikealle");
  printBoard(board);

  pause();
  for(i=0; i<3; i++)
    boolReport(block->moveLeft(), "Palikan siirto vasemmalle");
  printBoard(board);

  pause();
  for(i=0; i<3; i++)
    boolReport(block->rotateRight(), "Palikan kaanto oikealle");
  printBoard(board);

  pause();
  boolReport(block->drop(), "Palikan tiputus");
  printBoard(board);

//  cout << block->hasLanded();

  delete factory;
  delete blockA;
  delete blockB;
  delete block;
  delete board;
#ifdef TEST2_GRAFIIKALLA
  delete graphics;
  delete boardGraphics;
#endif // TEST2_GRAFIIKALLA

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
#ifdef FUNKKARITULOSTE
  cout << endl << "         ";
  for(int x=0; x<board->getWidth(); x++)
    cout << x << " ";
  cout << endl;
  for(int y=board->getHeight()-1; y>=0; y--) {
    cout << "    " << y << ":   ";
  for(int x=0; x<board->getWidth(); x++)
    cout << board->getSlot(x, y) << " ";
  if(board->isEmpty(y)) cout << "  IS EMPTY";
  else cout << "  NOTEMPTY";
  if(board->isFull(y)) cout << "  IS FULL";
  else cout << "  NOTFULL" << endl;
  }
  cout << "    Removed lines: " << board->getRemovedLines();
  cout << ", removed lines on last remove: " << board->getRemovedLinesLast() << endl << endl;
#endif
}

void pause() {
#ifdef FUNKKARITULOSTE
  cout << "----------------------------------------- ";
  cout << "Press ENTER ..." << endl;
#endif
  fflush ( stdout );
  getchar();
}

bool boolReport(bool result, string testStr) {
#ifdef FUNKKARITULOSTE
  if(result) cout << "(TEST) " << testStr << ": onnistui\n";
  else cout << "(TEST) " << testStr << ": epaonnistui\n";
#endif
  return result;
}
