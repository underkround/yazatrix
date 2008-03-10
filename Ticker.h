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
#include "Singleton.h"
#include "TickTask.h"

//#define TICKER_MAX_TASKS 10;

class STicker : public Singleton<STicker> {

friend class Singleton<STicker>;

public:

  /**
   * Rekisteröi ticklistenerin, joka haluaa tickin
   */
  CTickTask* registerListener(VTickListener *listener, int tickDelay);

  /**
   * Pyydetään poistumaan pääloopista
   */
  void stop();

  /**
   * Päälooppi jossa sleepataan ja kutsutaan kuuntelijoita
   */
  void start();

private:

//  std::map<VTickListener*,int> listeners; // value: int[ms_to_next_tick][last_delay]
//  std::vector<*TickTask> tasks;
  CTickTask * m_tasks[10]; // TODO: kiintee arvo tilapäisesti
  int m_taskCount;

  bool m_running; // flag jonka ollessa true, mainloop pyörii

  void removeTask(int index);

//  std::vector<VTickListener*> listeners; // ticker ei ole vastuussa listenereiden tuhoamisesta

protected:

  /**
   * Konstruktori määritellään näkyvyydellä protected, jolloin
   * pakotetaan käyttämään Instance() -metodia
   */
  STicker();

};

#endif // __TICKER_H__
