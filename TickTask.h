#ifndef __TICKTASK_H__
#define __TICKTASK_H__
/**
 * TickTask.h
 *
 * Informaatioluokka, jonka avulla ticker pitää kirjaa
 * kohteista, joita sen tulee kutsua määritetyin ajoin.
 *
 * TickTask sisältää tiedon mitä tickerin tulee kutsua,
 * miten pitkän ajan päästä sen tulee kutsua jne.
 */

#include "TickListener.h"

class CTickTask {

public:

  enum TICK_RETURN_VALUE {
    TICK_REMOVE = -1,
    TICK_KEEPDELAY = 0,
  };

  inline CTickTask(VTickListener *listener, int delay) {
    subject = listener;
    m_lastDelay = delay;
    m_delayToNext = delay;
    m_skips = 0;
  }

  /**
   * Kutsuu subjektia, jos sen asettama viive on ylittynyt.
   * Saa subjektilta uuden viiveen.
   * Jos subjekti ei halua enää tickejä (palauttaa negatiivisen),
   * tämä palauttaa false, jolloin STickerin pitäisi poistaa tämä
   * tehtävä.
   *
   * @return    false, jos ei haluta enään tickejä ja tämä task tulee poistaa
   */
  inline bool tick(int sleepTime) {
    if(m_delayToNext > 0) {
      m_delayToNext -= sleepTime;
      return true;
    }
    if(m_skips > 0) {
      m_skips--;
    } else {
      int ret = subject->handleTick();
      if(ret == TICK_REMOVE) {
        // poistetaan ajastustehtävä
        return false;
      } else if(ret == TICK_KEEPDELAY) {
        // käytetään edellistä delayn arvoa
        m_delayToNext = m_lastDelay;
      } else {
        if(ret > 0) {
          // seuraava delay on palautuksen arvo
          m_lastDelay = ret;
          m_delayToNext = ret;
        } else {
          // tuntematon vastaus: poistetaan ajastustehtävä
          return false;
        }
      }
    }
    return true;
  }

  inline void resetTick(void) {
    m_delayToNext = m_lastDelay;
  }

  inline void skip(unsigned int count) {
    m_skips = count;
  }

private:

  VTickListener *subject; // tickin kohde
  int m_lastDelay;
  int m_delayToNext;      //
  int m_skips;            // ohittaa kutsun kohteeseen m_skips tickin ajan, vähenee joka tick

};

#endif // __TICKTASK_H__
