/**
 * StatsPanel.cpp
 *
 * $Revision$
 * $Id$
 *
 * Graafinen esitys pelin pistetilanneoliosta.
 */

#include "StatsPanel.h"
#include "Ticker.h"
#include <stdio.h>
#include <string>

CStatsPanel::CStatsPanel(const CTetrisStats *stats, const int x, const int y) {
  g = &SGraphics::getInstance();
  m_borderStyle = SGraphics::BORDER_SINGLE;
  m_borderFG = SGraphics::GCOLOR_LIGHTCYAN;
//  stats->registerListener(dynamic_cast<VStatsListener*>(this));
  m_width = 12;
  m_height = 6;
  m_x = x;
  m_y = y;
  m_score = 0;
  m_level = 1;
  m_reml = 0;
  m_remll = 0;
  m_foreground = SGraphics::GCOLOR_LIGHTMAGENTA;
  m_foreground2 = SGraphics::GCOLOR_MAGENTA;
  m_flashCount = 0;
  m_flashOn = true;
  drawBorder();
  draw();
}

CStatsPanel::~CStatsPanel() {
}

int CStatsPanel::handleTick() {
  if(m_flashOn) {
    m_borderFG = SGraphics::GCOLOR_LIGHTCYAN;
    m_flashOn = false;
  } else {
    m_borderFG = SGraphics::GCOLOR_LIGHTMAGENTA;
    m_flashOn = true;
  }
  m_flashCount--;
  drawBorder();
  if(m_flashCount < 0 && !m_flashOn)
    return -1;
  return m_flashDelay;
}

void CStatsPanel::drawBackground() {
  for(int y=0; y<m_height; y++) {
    for(int x=0; x<m_width; x++) {
      g->drawSquare(m_x+x+1, m_y+y+1, m_background);
    }
  }
  draw();
}

void CStatsPanel::handleChangeInStats(const int score, const int level, const int reml, const int remll) {
  m_score = score;
  m_level = level;
  m_reml = reml;
//  m_remll = remll;
  if(remll > 0) {
    // rekisteröidy tickerille efektin vuoksi
    STicker::getInstance().registerListener(static_cast<VTickListener*>(this), m_flashDelay);
    // aseta flashcounter
    m_flashCount = remll*2;
  }
  draw();
}

void CStatsPanel::draw() {
  g->drawString(m_x+2, m_y+2, m_foreground2, m_background, "score");
  g->drawString(m_x+2, m_y+3, m_foreground2, m_background, "lvl");
  g->drawString(m_x+2, m_y+4, m_foreground2, m_background, "lines");
//  g->drawString(m_x+2, m_y+5, m_foreground2, m_background, "llns");

  g->drawString(m_x+8, m_y+2, m_foreground, m_background, intToString(m_score));
  g->drawString(m_x+8, m_y+3, m_foreground, m_background, intToString(m_level));
  g->drawString(m_x+8, m_y+4, m_foreground, m_background, intToString(m_reml));
//  g->drawString(m_x+8, m_y+5, m_foreground, m_background, intToString(m_remll));
}

std::string CStatsPanel::intToString(const int i) {
  std::ostringstream s;
  s << i;
  return s.str();
}
