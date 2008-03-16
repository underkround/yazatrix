#include "../Ticker.h"
#include <unistd.h>

// TODO: muuta tarkistamaan viimeisen kutsun aika, ja nuku vain tarvittava m‰‰r‰ t‰ss‰
void STicker::sleepNextInterval(int tickInterval) {
  usleep(tickInterval*1000);
}
