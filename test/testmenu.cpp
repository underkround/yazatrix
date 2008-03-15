#include "../menu.h"
#include "../Graphics.h"
#include "../KeyboardInput.h"
#include "../TickListener.h"
#include "../Ticker.h"
#include "../CommandListener.h"

/**
 * Menu testi
 *
 * $Id$
 * $Revision$
 *
 */

int main(int argc, char** argv) {
  STicker::getInstance().start();
  //SGraphics * grafiikka = new SGraphics();
  //SKeyboardInput *input = &SKeyboardInput::getInstance();

  CTetrisMenu * menuetti = new CTetrisMenu();
  //input->registerCommandListener( dynamic_cast<VCommandListener*>(menuetti) );
  menuetti->show();
  STicker::getInstance().start();
  delete menuetti;
  //delete grafiikka;
  return 0;
}
