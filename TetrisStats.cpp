#include "TetrisStats.h"

CTetrisStats::CTetrisStats() {
  m_tetrominoCounter = 0;
  m_score = 0;
  m_level = 1;
  m_removedLines = 0;
  m_removedLinesLast = 0;
  m_dropDelay = 500;
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
  notifyChangeInStats();
}

void CTetrisStats::tetrominoAdded() {
  m_tetrominoCounter++;
  m_score += m_level;
  notifyChangeInStats();
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
  int delay = m_dropDelay / m_level; // TODO: delay logiikka
  return delay;
}

void CTetrisStats::update() {
  m_level = (int)(m_tetrominoCounter / 20) + 1;
}

void CTetrisStats::notifyChangeInStats() {
  for(int i=0; i<m_listenerCount; i++)
    listeners[i]->handleChangeInStats(m_score, m_level, m_removedLines, m_removedLinesLast);
}
