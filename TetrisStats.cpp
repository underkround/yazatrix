#include "TetrisStats.h"

CTetrisStats::CTetrisStats() {
  settings = &SConfig::getInstance();
  m_tetrominoCounter = 0;
  m_score = 0;
  m_level = settings->getValueAsInt("level");
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
    case 1: m_score += settings->getValueAsInt("score 1 line")*m_level;break;
    case 2: m_score += settings->getValueAsInt("score 2 lines")*m_level;break;
    case 3: m_score += settings->getValueAsInt("score 3 lines")*m_level;break;
    case 4: m_score += settings->getValueAsInt("score 4 lines")*m_level;break;
    default: break;
  }
  notifyChangeInStats();
  update();
}

void CTetrisStats::tetrominoAdded() {
  m_tetrominoCounter++;
  m_score += m_level;
  notifyChangeInStats();
  update();
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
  // TODO: oikea delay-logiikka
  int delay = m_dropDelay / m_level;
  return delay;
}

void CTetrisStats::update() {
  // TODO: oikeaoppinen levelin laskeminen. lasketaanko räjäytetyistä riveistä vai palikoiden määrästä?
  int level = (int)(m_tetrominoCounter / settings->getValueAsInt("level increase")) + 1;
  if(m_level <= LEVEL_MAX)
    m_level = level;
}

void CTetrisStats::notifyChangeInStats() {
  for(int i=0; i<m_listenerCount; i++)
    listeners[i]->handleChangeInStats(m_score, m_level, m_removedLines, m_removedLinesLast);
}
