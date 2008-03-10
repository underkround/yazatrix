/**
 * linux/Ticker.cpp
 *
 * $Revision$
 * $Id$
 *
 * @see Ticker.h
 *
 */

#include "../Ticker.h"
#include <unistd.h>

#define TICKER_DEFAULT_SLEEP 1
#define TICKER_MILLIS 1000
#define TICKER_MAX_TASKS 10

STicker::STicker() {
  m_taskCount = 0;
  m_running = false;
  for(int i=0; i<TICKER_MAX_TASKS; i++)
    m_tasks[i] = 0;
}

CTickTask* STicker::registerListener(VTickListener *listener, int tickDelay) {
  if(m_taskCount < TICKER_MAX_TASKS) {
    m_tasks[m_taskCount] = new CTickTask(listener, tickDelay);
    m_taskCount++;
    return m_tasks[m_taskCount-1];
  }
  return 0;
}

void STicker::stop() {
  m_running = false;
}

void STicker::start() {
  m_running = true;
  while(m_running) {
    usleep(TICKER_DEFAULT_SLEEP * TICKER_MILLIS);
    for(int i=0; i<m_taskCount; i++) {
      if(m_tasks[i] != 0) {
        if(!m_tasks[i]->tick(TICKER_DEFAULT_SLEEP)) {
          removeTask(i);
        }
      }
    }
    if(m_taskCount <= 0) {
      m_running = false;
    }
  }
}

void STicker::removeTask(int index) {
  delete m_tasks[index];
  for(int i=index+1; i<TICKER_MAX_TASKS; i++) {
    m_tasks[i-1] = m_tasks[i];
  }
  m_taskCount--;
}

