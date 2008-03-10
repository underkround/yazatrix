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

//#define TICKER_MAX_TASKS 10;

class STicker : public Singleton<STicker> {

friend class Singleton<STicker>;

public:

  /**
   * Rekister�i ticklistenerin, joka haluaa tickin
   */
  CTickTask* registerListener(VTickListener *listener, int tickDelay);

  /**
   * Pyydet��n poistumaan p��loopista
   */
  void stop();

  /**
   * P��looppi jossa sleepataan ja kutsutaan kuuntelijoita
   */
  void start();

private:

//  std::map<VTickListener*,int> listeners; // value: int[ms_to_next_tick][last_delay]
//  std::vector<*TickTask> tasks;
  CTickTask * m_tasks[10]; // TODO: kiintee arvo tilap�isesti
  int m_taskCount;

  bool m_running; // flag jonka ollessa true, mainloop py�rii

  void removeTask(int index);

//  std::vector<VTickListener*> listeners; // ticker ei ole vastuussa listenereiden tuhoamisesta

protected:

  /**
   * Konstruktori m��ritell��n n�kyvyydell� protected, jolloin
   * pakotetaan k�ytt�m��n Instance() -metodia
   */
  STicker();

};

#endif // __TICKER_H__
