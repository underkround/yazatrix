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
  CGraphics * grafiikka = new CGraphics();
  SKeyboardInput *input = &SKeyboardInput::getInstance();

  CTetrisMenu * menuetti = new CTetrisMenu(grafiikka);
  input->registerCommandListener( dynamic_cast<VCommandListener*>(menuetti) );

  delete menuetti;
  delete grafiikka;
  return 0;
}
