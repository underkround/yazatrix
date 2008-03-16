/**
 * (windows) näppäimistöluokan testiohjelma
 *
 * $Revision$
 * $Id$
 * $HeadURL$
 *
 */

#include "../KeyboardInput.h"
#include <process.h>
#include <windows.h>

int main() {
  SKeyboardInput *keyb = &SKeyboardInput::getInstance();
//  char ch=0;
  printf("Keyboard testi, paina ctrl+c lopettaaksesi!\n");
  while(1) {
    Sleep(10000);
  }
  return 0;

}
