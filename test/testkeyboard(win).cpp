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
  TKeyboardInput::create("ajastin");
  char ch=0;
  printf("Timer testi, paina ESC lopettaaksesi\n");
  while(ch != 27) {
    if(kbhit()) {
      ch = getch();
      printf(" %d ", ch);
      printf(" ajastin on käynnissä, paina ESC lopettaaksesi\n");
    }
  }
  return 0;

}
