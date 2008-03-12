#ifndef __TICKER_H__
#define __TICKER_H__

/**
 * Ticker.h
 *
 * $Revision$
 * $Id$
 *
 * STicker-singeton on k�yt�nn�ss� olioversio mainloopista.
 * STicker py�ritt�� sleep-looppia, ja kutsuu sille rekister�ityneiden
 * TickListener -luokkien handleTick() metodia niiden m��ritt�m�n
 * viiveen v�lein.
 */

#include "TickListener.h"
#include "Singleton.h"
#include "TickTask.h"

//class STicker : public Singleton<STicker> {
class STicker {
//friend class Singleton<STicker>;

public:

static STicker& getInstance() {
  static STicker theSingleInstance;  // assumes T has a protected default constructor
  return theSingleInstance;
}

  /**
   * Rekister�i ticklistenerin, joka haluaa tickin
   */
  CTickTask* registerListener(VTickListener *listener, int tickDelay);

  /**
   * Pyydet��n poistumaan p��loopista
   */
  void stop(void);

  /**
   * P��looppi jossa sleepataan ja kutsutaan kuuntelijoita
   */
  void start(void);

private:

  static const int TICKER_MAX_TASKS = 10;
  int m_sleepTime;

  CTickTask * m_tasks[TICKER_MAX_TASKS]; // TODO: kiintee arvo tilap�isesti
  int m_taskCount;
  bool m_running; // flag jonka ollessa true, mainloop py�rii
  void removeTask(int index);

protected:

  /**
   * Konstruktori m��ritell��n n�kyvyydell� protected, jolloin
   * pakotetaan k�ytt�m��n Instance() -metodia
   */
  STicker();
  ~STicker();

};

#endif // __TICKER_H__
