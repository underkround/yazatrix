#include "../TetrisBoard.h"
#include <iostream>

using namespace std;

int main(void) {
    CTetrisBoard *board = new CTetrisBoard(10, 10);
    for(int y=0; y<board->getHeight(); y++) {
        for(int x=0; x<board->getWidth(); x++) {
            cout << board->getSlot(x, y);
            cout << " ";
        }
        cout << "\n";
    }
    return 0;
}
