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
#include <string>
#include <process.h>
#include <windows.h>

void TKeyboardInput::create(const char* inputName)
{
  //m_boolRunning = true;
  (new TKeyboardInput(inputName))->run(); //säie ajoon
}

void TKeyboardInput::code() {
  while(1) {
  }
}
