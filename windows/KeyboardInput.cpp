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
#include <conio.h>

void TKeyboardInput::create(const char* inputName)
{
  (new TKeyboardInput(inputName))->run(); //säie ajoon
}

void TKeyboardInput::code() {
  char ch;
  while(1) {
    if(kbhit()) {
      ch = getch();
      printf("%d\n", ch);
    }
    Sleep(10);
  }
}
