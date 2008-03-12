#include "../Graphics.h"
#include "../BoardGraphics.h"
#include "../TetrisLogic.h"
#include "../KeyboardInput.h"
#include "../TickListener.h"
#include "../Ticker.h"
#include <stdio.h>


void pause() {
  fflush ( stdout );
  getchar();
}

int main(void) {
  system("mode con:lines=50"); //windowskomento, pistää grafiikkatilan 80x25:ksi (mulla oletuksena 80x50)

//  SGraphics *g = &SGraphics::getInstance();

  CTetrisLogic *logic = new CTetrisLogic();
  CTetrisBoard *gameBoard = logic->getGameBoard();
  CTetrisBoard *previewBoard = logic->getPreviewBoard();
  SKeyboardInput *input = &SKeyboardInput::getInstance();

  //pause();

  input->registerCommandListener( dynamic_cast<VCommandListener*>(logic) );
  CBoardGraphics *gbg = new CBoardGraphics(gameBoard, 2, 2);
  CBoardGraphics *pbg = new CBoardGraphics(previewBoard, 20, 2);
  gbg->setBorderStyle(SGraphics::BORDER_BLOCK);
  pbg->setBorderStyle(SGraphics::BORDER_SQUARE);

  STicker::getInstance().start();
  logic->start();

//  delete gbg;
//  delete pbg;
  delete logic;
  return 0;
}
