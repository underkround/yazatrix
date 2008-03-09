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

#include "Thread.h"
#include <string>
#include <process.h>
#include <windows.h>

void KeyboardInput::create(const char* inputName)
{
  (new CTetrisTimer(timerName))->run();
}
