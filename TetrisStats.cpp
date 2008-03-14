#include "TetrisStats.h"

CTetrisStats::CTetrisStats() {
  int m_tetrominoCounter = 0;
  int m_score = 0;
  int m_level = 1;
  int m_removedLines = 0;
  int m_removedLinesLast = 0;
  int m_dropDelay = 500;
}

CTetrisStats::~CTetrisStats() {
}

void CTetrisStats::linesRemoved(const int lines) {
  m_removedLinesLast = lines;
  m_removedLines += lines;
  switch(lines) {
    case 1: m_score += 10*m_level;break;
    case 2: m_score += 30*m_level;break;
    case 3: m_score += 60*m_level;break;
    case 4: m_score += 100*m_level;break;
    default: break;
  }
}

void CTetrisStats::tetrominoAdded() {
  m_tetrominoCounter++;
  m_score += m_level;
}

int CTetrisStats::getLevel() {
  return m_level;
}

int CTetrisStats::getScore() {
  return m_score;
}

int CTetrisStats::getRemovedLines() {
  return m_removedLines;
}

int CTetrisStats::getRemovedLinesLast() {
  return m_removedLinesLast;
}

int CTetrisStats::getDropDelay() {
  return m_dropDelay;
}

void CTetrisStats::update() {
  m_level = (int)(m_tetrominoCounter / 50) + 1;
}

void CTetrisStats::notifyChangeInStats() {
  for(int i=0; i<m_listenerCount; i++)
    listeners[i]->handleChangeInStats(m_score, m_level, m_removedLines, m_removedLinesLast);
}

bool CTetrisStats::registerListener(VStatsListener* listener) {
  if(m_listenerCount >= LISTENERS_MAX)
    return false;
  listeners[m_listenerCount] = listener;
  m_listenerCount++;
  return true;
}

bool CTetrisStats::unregisterListener(VStatsListener* listener) {
  int index = -1;
  for(int i=0; i<m_listenerCount; i++) {
    if(listeners[i] == listener) {
      index = i;
      i = m_listenerCount;
      break;
    }
  }
  if(index >= 0) {
    listeners[index] = 0;
    m_listenerCount--;
    for(int i=index; index<m_listenerCount; i++) {
      listeners[i] = listeners[i+1];
    }
    listeners[m_listenerCount] = 0;
    return true;
  }
  return false;
}
