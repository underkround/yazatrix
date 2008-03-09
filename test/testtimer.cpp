#include "../TetrisTimer.h"
#include <conio.h>
#include <stdio.h>
#include "../Thread.h"
#include "../TetrisTimer.h"

int main(void) {
  //CTetrisTimer * ajastin;
  CTetrisTimer::create("ajastin");
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
