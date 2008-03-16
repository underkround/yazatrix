#include "../Ticker.h"
#include <windows.h>

// TODO: muuta tarkistamaan viimeisen kutsun aika, ja nuku vain tarvittava m‰‰r‰ t‰ss‰
void STicker::sleepNextInterval(int tickInterval) {
  Sleep(tickInterval);
}
