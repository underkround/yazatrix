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
//  TKeyboardInput::create("keyb");

  CGraphics *g = new CGraphics();
  CTetrisLogic *logic = new CTetrisLogic();
  CTetrisBoard *gameBoard = logic->getGameBoard();
  CTetrisBoard *previewBoard = logic->getPreviewBoard();
  SKeyboardInput *input = &SKeyboardInput::getInstance();
//  STicker *ticker = &STicker::getInstance();

pause();
//  ticker->registerListener(dynamic_cast<VTickListener*>(input), 20);
//  ticker->registerListener(dynamic_cast<VTickListener*>(logic), 500);
  input->registerCommandListener( dynamic_cast<VCommandListener*>(logic) );
  CBoardGraphics *gbg = new CBoardGraphics(gameBoard, g, 2, 2);
  CBoardGraphics *pbg = new CBoardGraphics(previewBoard, g, 20, 8);
  gbg->setBorderStyle(CGraphics::BORDER_BLOCK);
  pbg->setBorderStyle(CGraphics::BORDER_SQUARE);

//  pause();
//  input->handleTick();
//  if(ticker->registerListener( dynamic_cast<VTickListener*>(input) , 100 )) {
    STicker::getInstance().start();
    logic->start();
//    STicker::getInstance().start();
//  }

//  logic->run();

  delete gbg;
  delete pbg;
  delete g;
  delete logic;
  return 0;
}
