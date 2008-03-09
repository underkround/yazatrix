/**
 * windows/KeyboardInput.cpp
 *
 * $Revision$
 * $Id$
 *
 * Huolehtii näppäimistötapahtumien käsittelystä
 *
 * @see KeyboardInput.h
 *
 */

#include "../KeyboardInput.h"
#include "../Thread.h"
#include "../CommandListener.h"
#include <string>
#include <process.h>
#include <windows.h>
#include <conio.h>
#include <vector>

void TKeyboardInput::create(const char* inputName) {
  (new TKeyboardInput(inputName))->run(); //säie ajoon
}

void TKeyboardInput::code() {
  char ch;
  while(1) {
    if(kbhit()) {
      ch = getch();
//      printf("%d\n", ch);
      handleKeyPress(ch);
    }
    Sleep(100);
  }
}

void TKeyboardInput::handleKeyPress(char key) {
  switch(key) {

    // left
    case 75:
      notifyCommand(VCommandListener::GAME_COMMAND_LEFT);
      break;

    // right
    case 77:
      notifyCommand(VCommandListener::GAME_COMMAND_RIGHT);
      break;

    // up
    case 72:
      notifyCommand(VCommandListener::GAME_COMMAND_ROTATE_CW);
      break;

    // down
    case 80:
      notifyCommand(VCommandListener::GAME_COMMAND_SOFTDROP);
      break;

    // avaruusnäppäin
    case 32:
      notifyCommand(VCommandListener::GAME_COMMAND_HARDDROP);
      break;

    // pakonäppäin
    case 27:
      notifyCommand(VCommandListener::GAME_COMMAND_QUIT);
      break;

    // random-näppäin
    default:
      break;
  }
}

std::vector<VCommandListener*> TKeyboardInput::listeners; // declare listeners

void TKeyboardInput::registerCommandListener(VCommandListener *listener) {
  listeners.push_back(listener);
}

void TKeyboardInput::notifyCommand(VCommandListener::COMMAND cmd) {
	for(unsigned int i=0; i<listeners.size(); i++) {
		VCommandListener* listener = listeners[i];
		listener->handleCommand(cmd);
  }
}
