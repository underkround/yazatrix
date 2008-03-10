/**
 * windows/Ticker.cpp
 *
 * $Revision$
 * $Id$
 *
 * @see Ticker.h
 *
 *
 * TODO: tee hyvin paljon järkevämpi =P järjestä tasks-taulusta tyhjät pois äläkä käy sitä kokonaan läpi
 */

#include "../Ticker.h"
#include <stdio.h>
#include <windows.h>

#define TICKER_DEFAULT_SLEEP 1
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
    //return true;
    printf("Palautetaan task\n");
    return m_tasks[m_taskCount-1];
  }
  printf("Palautetaan 0\n");
  //return false;
  return 0;
}

void STicker::stop() {
  m_running = false;
}

void STicker::start() {
  m_running = true;
  while(m_running) {
    Sleep(TICKER_DEFAULT_SLEEP);
    // check if listeners need tick
//#ifdef __TESTTIMER__
//    printf(".");
//#endif
    for(int i=0; i<m_taskCount; i++) {
      if(m_tasks[i] != 0) {
        if(!m_tasks[i]->tick(TICKER_DEFAULT_SLEEP)) {
//#ifdef __TESTTIMER__
          printf("POISTETAAN!!\n");
//#endif
          removeTask(i);
        }
      }
    }
    if(m_taskCount <= 0) {
      printf("Ei yhtään tickattavaa :(\n");
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
