#include <conio.h>
#include <stdio.h>
#include "../Sleeper.h"

int main(void) {
  //CTetrisTimer * ajastin;
  CSleeper sleeper;
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
