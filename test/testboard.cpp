#include "../TetrisBoard.h"
#include "../TetrominoFactory.h"
#include "../Tetromino.h"
#include <iostream>

using namespace std;

#define TEST2

void printBoard(CTetrisBoard *board);
void fillRow(CTetrisBoard *board, const int y, CELL_TYPE ct);


// --------------------------------------------------------------------
#ifdef TEST2

int main(void) {
    CTetrisBoard *board = new CTetrisBoard(10, 10);
    CTetrominoFactory *factory = new CTetrominoFactory();
    CTetromino *block = factory->create(BLOCK_T);

    if(block->attach(board, 5)) cout << "Palikka pitaisi olla nyt laudassa (" << block->getX() << ":" << block->getY() << ")\n";
    else cout << "Palikka ei halunnut mennä lautaan :(\n";

    printBoard(board);
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
