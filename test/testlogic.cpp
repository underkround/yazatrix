#include "../Graphics.h"
#include "../BoardGraphics.h"
#include "../TetrisLogic.h"
#include <stdio.h>

void pause() {
  fflush ( stdout );
  getchar();
}

int main(void) {
  CGraphics *g = new CGraphics();
  CTetrisLogic *logic = new CTetrisLogic();
  CTetrisBoard *gameBoard = logic->getGameBoard();
  CTetrisBoard *previewBoard = logic->getPreviewBoard();
  CBoardGraphics *gbg = new CBoardGraphics(gameBoard, g, 2, 1);
  CBoardGraphics *pbg = new CBoardGraphics(previewBoard, g, 20, 1);
  pbg->setBorderStyle(CGraphics::BORDER_SINGLE);

  pause();

  logic->run();

  delete gbg;
//  delete pbg;
  delete g;
  delete logic;
  return 0;
}
