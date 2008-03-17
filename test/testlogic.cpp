#include "../Graphics.h"
#include "../BoardGraphics.h"
#include "../TetrisLogic.h"
#include "../KeyboardInput.h"
#include "../TickListener.h"
#include "../Ticker.h"
#include "../StatsPanel.h"
#include "../StatsListener.h"
#include <stdio.h>


void pause() {
  fflush ( stdout );
  getchar();
}

int main(void) {
  system("mode con:lines=50"); //windowskomento, pistää grafiikkatilan 80x25:ksi (mulla oletuksena 80x50)

  SKeyboardInput *input = &SKeyboardInput::getInstance();

  CTetrisLogic *logic = new CTetrisLogic();
  // ui
  CBoardGraphics *gbg = new CBoardGraphics(logic->getGameBoard(), 18, 2);
  CBoardGraphics *pbg = new CBoardGraphics(logic->getPreviewBoard(), 34, 4);
  CStatsPanel *stats = new CStatsPanel(logic->getStats(), 3, 5);

  logic->getStats()->registerListener(dynamic_cast<VStatsListener*>(stats));

  input->registerListener( dynamic_cast<VCommandListener*>(logic) );
  gbg->setBorderStyle(SGraphics::BORDER_BLOCK);
  pbg->setBorderColor(SGraphics::GCOLOR_LIGHTGREEN, SGraphics::GCOLOR_GREEN);
  pbg->setBorderStyle(SGraphics::BORDER_SQUARE);

  STicker::getInstance().start();
  logic->start();

//  delete gbg;
//  delete pbg;
  delete logic;
  return 0;
}
