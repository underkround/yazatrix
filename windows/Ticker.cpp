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
#include <windows.h>
#include <stdio.h>

STicker::STicker() {
  m_taskCount = 0;
  m_running = false;
  m_sleepTime = 5;
  for(int i=0; i<TICKER_MAX_TASKS; i++)
    m_tasks[i] = 0;
}

STicker::~STicker() {
  if(m_taskCount > 0) {
    for(int i=0; i<m_taskCount; i++) {
      delete m_tasks[i];
    }
  }
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
//  int counter = 0;
  while(m_running) {
    Sleep(m_sleepTime);
    for(int i=0; i<m_taskCount; i++) {
      if(m_tasks[i] != 0) {
        if(!m_tasks[i]->tick(m_sleepTime))
          removeTask(i);
      }
    }
    if(m_taskCount <= 0)
      m_running = false;
//    if(counter > 50)
//      m_running = false;
//    counter++;
  }
}

void STicker::removeTask(int index) {
  delete m_tasks[index];
  for(int i=index+1; i<TICKER_MAX_TASKS; i++) {
    m_tasks[i-1] = m_tasks[i];
  }
  m_taskCount--;
}
