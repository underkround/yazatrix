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
// #include <windows.h>
#include <stdio.h>
#include <iostream>

SKeyboardInput::SKeyboardInput() {
//  CTickTask *myTask = STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), m_tickDelay);
  STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), m_tickDelay);
}

int SKeyboardInput::handleTick() {
  char ch=0;
  if(kbhit()) {
    ch = getch();
    handleKeyPress(ch);
  }
//  if(ch == 27) {
//    STicker::getInstance().stop();
//    return -1;
//  }
  return m_tickDelay;
}

SKeyboardInput::~SKeyboardInput() {
}

void SKeyboardInput::handleKeyPress(char key) {
//  if(listeners.size() > 0) {
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
        notifyCommand(VCommandListener::MENU_COMMAND_UP);
        break;

      // down
      case 80:
        notifyCommand(VCommandListener::GAME_COMMAND_SOFTDROP);
        notifyCommand(VCommandListener::MENU_COMMAND_DOWN);
        break;

      // avaruusnäppäin
      case 32:
        notifyCommand(VCommandListener::GAME_COMMAND_HARDDROP);
        notifyCommand(VCommandListener::MENU_COMMAND_SELECT);
        break;

      // vuoronäppäin
      case 13:
        notifyCommand(VCommandListener::MENU_COMMAND_SELECT);
        break;

      // pakonäppäin
      case 27:
        notifyCommand(VCommandListener::GAME_COMMAND_QUIT);
        break;

      case 112:
        notifyCommand(VCommandListener::GAME_COMMAND_PAUSE);
        break;

      // q - instant exitco
      case 113:
        STicker::getInstance().stop();
        break;

      // random-näppäin
      default:
        break;
    }
//  } else {
//    printf("(%d) ", key);
//  }
}


void SKeyboardInput::notifyCommand(VCommandListener::COMMAND cmd) {
  for(int i=0; i<m_listenerCount; i++)
    listeners[i]->handleCommand(cmd);
}
