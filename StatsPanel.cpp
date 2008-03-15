/**
 * StatsPanel.cpp
 *
 * $Revision$
 * $Id$
 *
 * Graafinen esitys pelin pistetilanneoliosta.
 */

#include "StatsPanel.h"
#include <stdio.h>
#include <string>

CStatsPanel::CStatsPanel(const CTetrisStats *stats, const int x, const int y) {
  g = &SGraphics::getInstance();
  m_borderStyle = SGraphics::BORDER_SINGLE;
  m_borderFG = SGraphics::GCOLOR_LIGHTCYAN;
  m_width = 8;
  m_height = 6;
  m_x = x;
  m_y = y;
  m_score = 0;
  m_level = 1;
  m_reml = 0;
  m_remll = 0;
  drawBorder();
  draw();
}

CStatsPanel::~CStatsPanel() {
}

void CStatsPanel::handleChangeInStats(const int score, const int level, const int reml, const int remll) {
//  printf("[[ %d %d %d %d ]]", score, level, reml, remll);
  m_score = score;
  m_level = level;
  m_reml = reml;
  m_remll = remll;
  draw();
}

void CStatsPanel::draw() {
  g->drawString(m_x+2, m_y+2, m_background, m_foreground, intToString(m_score));
  g->drawString(m_x+2, m_y+3, m_background, m_foreground, intToString(m_level));
  g->drawString(m_x+2, m_y+4, m_background, m_foreground, intToString(m_reml));
  g->drawString(m_x+2, m_y+5, m_background, m_foreground, intToString(m_remll));
}

std::string CStatsPanel::intToString(const int i) {
  std::ostringstream s;
  s << i;
  return s.str();
}
