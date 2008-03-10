/**
 * windows/KeyboardInput.cpp
 *
 * $Revision$
 * $Id$
 *
 * Näppäimistöbufferin kuuntelun implementaatio windowsissa
 *
 * @see KeyboardInput.h
 *
 */
#include "../KeyboardInput.h"
#include "../Ticker.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>

#define KEYBOARDINPUT_TICKDELAY 20

SKeyboardInput::SKeyboardInput() {
//  STicker::instance().
}

int SKeyboardInput::handleTick() {
#ifdef __TESTTIMER__
  printf(",");
  char ch = 0;
  if(kbhit()) {
    ch = getch();
    printf("\n %d ", ch);
    printf(" paina ESC lopettaaksesi\n");
  }
  if(ch == 27) return -1;
  return KEYBOARDINPUT_TICKDELAY;
#endif // __TESTTIMER__

#ifndef __TESTTIMER__
  char ch=0;
  if(kbhit()) {
    ch = getch();
    handleKeyPress(ch);
  }
  if(ch == 27) return -1;
  return KEYBOARDINPUT_TICKDELAY;
#endif // __TESTTIMER__
}

SKeyboardInput::~SKeyboardInput() {
}

void SKeyboardInput::handleKeyPress(char key) {
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
//      notifyCommand(VCommandListener::GAME_COMMAND_ROTATE_CW);
      notifyCommand(VCommandListener::GAME_COMMAND_ROTATE_CCW);
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

void SKeyboardInput::registerCommandListener(VCommandListener *listener) {
  listeners.push_back(listener);
}

void SKeyboardInput::notifyCommand(VCommandListener::COMMAND cmd) {
	for(unsigned int i=0; i<listeners.size(); i++) {
		VCommandListener* listener = listeners[i];
		listener->handleCommand(cmd);
  }
}
