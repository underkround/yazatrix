#ifndef __TICKTASK_H__
#define __TICKTASK_H__
/**
 * TickTask.h
 *
 * Informaatioluokka, jonka avulla ticker pit�� kirjaa
 * kohteista, joita sen tulee kutsua m��ritetyin ajoin.
 *
 * TickTask sis�lt�� tiedon mit� tickerin tulee kutsua,
 * miten pitk�n ajan p��st� sen tulee kutsua jne.
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
   * Jos subjekti ei halua en�� tickej� (palauttaa negatiivisen),
   * t�m� palauttaa false, jolloin STickerin pit�isi poistaa t�m�
   * teht�v�.
   *
   * @return    false, jos ei haluta en��n tickej� ja t�m� task tulee poistaa
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
        // poistetaan ajastusteht�v�
        return false;
      } else if(ret == TICK_KEEPDELAY) {
        // k�ytet��n edellist� delayn arvoa
        m_delayToNext = m_lastDelay;
      } else {
        if(ret > 0) {
          // seuraava delay on palautuksen arvo
          m_lastDelay = ret;
          m_delayToNext = ret;
        } else {
          // tuntematon vastaus: poistetaan ajastusteht�v�
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
  int m_skips;            // ohittaa kutsun kohteeseen m_skips tickin ajan, v�henee joka tick

};

#endif // __TICKTASK_H__
