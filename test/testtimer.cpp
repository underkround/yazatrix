#define __TESTTIMER__

#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "../TickListener.h"
#include "../Ticker.h"
#include "../KeyboardInput.h"


int main(void) {
//  SKeyboardInput::getInstance().handleTick();
  SKeyboardInput *input = &SKeyboardInput::getInstance();
//  input->handleTick();
  CTickTask *task = ticker->registerListener( dynamic_cast<VTickListener*>(input) , 100 );
//  if(task != 0) {
    printf("Näppiskuuntelija rekisteroitiin =)\n");
    STicker::getInstance().start();
//    STicker::getInstance().start();
//  } else {
    printf("Rekisterointi epaonnistui :<\n");
//  }
//  STicker::getInstance().start();
  return 0;
}

/*
bool handleKey() {
  char ch = 0;
  if(kbhit()) {
    ch = getch();
    printf(" %d ", ch);
    printf(" paina ESC lopettaaksesi\n");
  }
  if(ch == 27) return true;
  return false;
}

void sleepMore() {
  printf("sleeping..");
  Sleep(1000);
  printf("..done!");
}
int main(void) {
  //CTetrisTimer * ajastin;
  printf("Timer testi, paina ESC lopettaaksesi\n");
  bool done = false;
  while(!done) {
    Sleep(1000);
    done = handleKey();
    sleepMore();
  }
  return 0;
}
*/
