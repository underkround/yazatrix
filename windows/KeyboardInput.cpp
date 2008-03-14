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
#include <windows.h>
#include <stdio.h>
#include <iostream>
//#define KEYBOARDINPUT_TICKDELAY 2

SKeyboardInput::SKeyboardInput() {
  m_tickDelay = 2;
//  CTickTask *myTask = STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), m_tickDelay);
  STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), m_tickDelay);
  m_listenerCount = 0;
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

bool SKeyboardInput::registerCommandListener(VCommandListener *listener) {
  if(m_listenerCount >= LISTENERS_MAX)
    return false;
  listeners[m_listenerCount] = listener;
  m_listenerCount++;
  return true;
}

bool SKeyboardInput::unregisterCommandListener(VCommandListener *listener) {
  int index = -1;
  for(int i=0; i<m_listenerCount; i++) {
    if(listeners[i] == listener) {
      index = i;
      i = m_listenerCount;
      break;
    }
  }
  if(index >= 0) {
    // poistettava löytyi
    listeners[index] = 0;
    m_listenerCount--;
    for(int i=index; index<m_listenerCount; i++) {
      listeners[i] = listeners[i+1]; // siirretään poistetusta seuraavia yhdellä alaspäin
    }
    listeners[m_listenerCount] = 0; // tyhjätään viimeinen alkio, joka olisi nyt kaksi kertaa listassa
    return true;
  }
  return false;
}

void SKeyboardInput::notifyCommand(VCommandListener::COMMAND cmd) {
  for(int i=0; i<m_listenerCount; i++)
    listeners[i]->handleCommand(cmd);
}
