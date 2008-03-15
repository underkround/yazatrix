/**
 *
 *
 *
 */

#include "StatsPanel.h"
#include <stdio.h>
#include <string>

#include <sstream>

CStatsPanel::CStatsPanel() {
  g = &SGraphics::getInstance();
  m_borderStyle = SGraphics::BORDER_SIMPLE;
  m_width = 8;
  m_height = 6;
  m_x = 40;
  m_y = 1;
}

CStatsPanel::~CStatsPanel() {
}

//int CStatsPanel::getWidth() { return m_width + 2; }
//int CStatsPanel::getWidth() { return m_height + 2; }

void CStatsPanel::handleChangeInStats(const int score, const int level, const int reml, const int remll) {
  m_score = score;
  m_level = level;
  m_reml = reml;
  m_remll = remll;
  draw();
}

void CStatsPanel::draw() {
  //void drawBox(const int from_x, const int from_y, const int to_x, const int to_y, BORDER_STYLE borderstyle);
  std::string s;
  std::stringstream out;
  g->drawBox(m_x, m_y, m_x+m_width+2, m_y+m_width+2, m_borderStyle);
  out << m_level; s = out.str();
  g->drawString(m_x+2, m_y+1, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, s);
  out << m_score; s = out.str();
  g->drawString(m_x+2, m_y+2, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, s);
}
