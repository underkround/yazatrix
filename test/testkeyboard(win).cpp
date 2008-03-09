/**
 * (windows) näppäimistöluokan testiohjelma
 *
 * $Revision$
 * $Id$
 * $HeadURL$
 *
 */

#include "../KeyboardInput.h"

int main() {
  TKeyboardInput::create("keyb");
  char ch=0;
  printf("Keyboard testi, paina ctrl+c lopettaaksesi!\n");
  while(1) {
    sleep(10000);
  }
  return 0;

}
