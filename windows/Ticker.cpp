#include "../Ticker.h"
#include <windows.h>

#include <iostream>
#include <stdio.h>

//static LONGLONG lCountLast; // aika edellisen loopin alkaessa

// TODO: muuta tarkistamaan viimeisen kutsun aika, ja nuku vain tarvittava m‰‰r‰ t‰ss‰
void STicker::sleepNextInterval(int tickInterval) {
/*  LARGE_INTEGER count;
  LARGE_INTEGER freq;
  LONGLONG lNow;
  LONGLONG lFreq;

  QueryPerformanceCounter(&count);
  QueryPerformanceFrequency(&freq);
  lFreq = freq.QuadPart;
  lNow = count.QuadPart;

  LONGLONG diff = lNow - lCountLast;
  float millis = (float)diff / (float)lFreq;
*/
  Sleep(tickInterval);

//  QueryPerformanceCounter(&count);
//  lCountLast = count.QuadPart;
}
