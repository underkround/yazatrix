/**
 * Panel.cpp
 *
 * $Revision$
 * $Id$
 *
 * @see Panel.h
 */

#include "Panel.h"

// asetetaan jonkinlaiset defaultit
VPanel::VPanel() {
  m_borderStyle = SGraphics::BORDER_SIMPLE;
  m_borderBG    = SGraphics::GCOLOR_BLACK;
  m_borderFG    = SGraphics::GCOLOR_LIGHTGREEN;
  m_foreground  = SGraphics::GCOLOR_WHITE;
  m_background  = SGraphics::GCOLOR_BLACK;
  m_border      = true;
  m_x           = 1;
  m_y           = 1;
  m_width       = 10;
  m_height      = 10;
}

void VPanel::setLocation(const int x, const int y) {
  m_x = (x > 0) ? x : m_x;
  m_y = (y > 0) ? y : m_y;
}

int VPanel::getX() {
  return m_x;
}

int VPanel::getY() {
  return m_y;
}

void VPanel::setX(const int newX) {
  m_x = newX;
}

void VPanel::setY(const int newY) {
  m_y = newY;
}

int VPanel::getWidth(void) {
  return (m_border) ? m_width+2 : m_width;
}

int VPanel::getHeight(void) {
  return (m_border) ? m_height+2 : m_height;
}

/*
void VPanel::setBorderVisible(bool visible) {
  return; // TODO: t‰m‰ ei ole viel‰ kokonaan tuettu, pidet‰‰n borderit toistaiseksi p‰‰ll‰..
  m_border = visible;
  drawBorder();
}*/

void VPanel::setBorderColor(const SGraphics::GCOLOR fg, const SGraphics::GCOLOR bg) {
  m_borderFG = fg;
  m_borderBG = bg;
}

void VPanel::setBorderStyle(const SGraphics::BORDER_STYLE bs) {
  m_borderStyle = bs;
  drawBorder();
}

// panelin tulee piirt‰‰ itsens‰ kun t‰t‰ kutsutaan
void VPanel::draw(void) {
  drawBorder();
}

// piirret‰‰n borderi
void VPanel::drawBorder(void) {
  if(m_border) {
    SGraphics::getInstance().setColors(m_borderFG, m_borderBG);
    SGraphics::getInstance().drawBox(m_x, m_y, m_x+m_width+1, m_y+m_height+1, m_borderStyle);
  }
}

void VPanel::hide(void) {
  int w = (m_border) ? m_width+2 : m_width;
  int h = (m_border) ? m_height+2 : m_height;
  for(int x = m_x; x<m_x+w; x++)
    for(int y = m_y; y<m_y+h; y++)
      SGraphics::getInstance().drawChar(x, y, SGraphics::GCOLOR_BLACK, SGraphics::GCOLOR_BLACK, ' ');
}
