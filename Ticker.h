#ifndef __TICKER_H__
#define __TICKER_H__

/**
 * Ticker.h
 *
 * $Revision$
 * $Id$
 *
 * STicker-singeton on käytännössä olioversio mainloopista.
 * STicker pyörittää sleep-looppia, ja kutsuu sille rekisteröityneiden
 * TickListener -luokkien handleTick() metodia niiden määrittämän
 * viiveen välein.
 */

#include "TickListener.h"
#include "TickTask.h"

class STicker {

public:

  static STicker& getInstance() {
    static STicker theSingleInstance;
    return theSingleInstance;
  }

  /**
   * Rekisteröi ticklistenerin, joka haluaa tickin
   */
  CTickTask* registerListener(VTickListener *listener, int tickDelay);

  /**
   * Pyydetään poistumaan pääloopista
   */
  void stop(void);

  /**
   * Päälooppi jossa sleepataan ja kutsutaan kuuntelijoita
   */
  void start(void);

private:

  static const int TICKER_MAX_TASKS = 5;
  int m_sleepTime;

  CTickTask * m_tasks[TICKER_MAX_TASKS]; // TODO: kiintee arvo tilapäisesti
  int m_taskCount;
  bool m_running; // flag jonka ollessa true, mainloop pyörii
  void removeTask(int index);

  /**
   * Nukkuu tarvittavan määrän jotta valittu tick-intervalli pysyy.
   */
  void sleepNextInterval(int tickInterval);

protected:

  /**
   * Konstruktori määritellään näkyvyydellä protected, jolloin
   * pakotetaan käyttämään Instance() -metodia
   */
  STicker();
  ~STicker();

};

#endif // __TICKER_H__
