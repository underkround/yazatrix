/**
 * BoardGraphics.cpp
 *
 * $Revision$
 * $Id$
 *
 * @see BoardGraphics.h
 *
 */

#include "BoardGraphics.h"

CBoardGraphics::CBoardGraphics(CTetrisBoard *myBoard, int offsetX, int offsetY) {
  board = myBoard;
  g = &SGraphics::getInstance();
  // rekisterˆidy boardille kuuntelijaksi
  VBoardChangeListener *bcl = dynamic_cast<VBoardChangeListener*>(this);
  board->registerBoardChangeListener( bcl );
  m_x = offsetX;
  m_y = offsetY;
  m_squareWidth = 1;
  m_squareHeight = 1;
  // jos ei borderia tms , niin mitat = boardin mitat
  m_width = board->getWidth() * m_squareWidth;
  m_height = board->getHeight() * m_squareHeight;
  m_borders = true;
  setBorderStyle(SGraphics::BORDER_GROOVE);
  handleFreshBoard();
}

CBoardGraphics::~CBoardGraphics() {
  // poista rekisterˆityminen
  //board->unregisterBoardChangeListener(this);
  // jaa voipa olla ett‰ tulisi ongelmia jos board on jo tuhottu..
  // jollei sitten tee siit‰kin ilmoitusta listenerin kautta =)
}

void CBoardGraphics::setBorder(bool visible) {
  // borderit p‰‰ll‰? jos moisia jaksaa tehd‰. lis‰‰ tietty leveytt‰ ja korkeutta +2
  m_borders = visible; // TODO: pit‰isikˆ olla int, jos bordertyyppej‰ on useita?
  handleFreshBoard(); // koko lauta muuttuu jos borderit muuttuu p‰‰lle / pois
}

void CBoardGraphics::setBorderStyle(SGraphics::BORDER_STYLE bs) {
  m_borderStyle = bs;
  drawBorder();
}

void CBoardGraphics::drawBorder() {
  g->setColors(SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK);
  if(m_borders)
    g->drawBox(m_x, m_y, m_x+m_width*m_squareWidth+1, m_y+m_height*m_squareWidth+1, m_borderStyle);
}

void CBoardGraphics::setLocation(const int x, const int y) {
  // mist‰ ruudun koordinaatista t‰m‰ aloittaa piirt‰m‰‰n itse‰‰n (yl‰vasen koord)
  m_x = x;
  m_y = y;
}

// t‰t‰ k‰ytt‰en piirret‰‰n solut
void CBoardGraphics::drawCell(const int x, const int y, CELL_TYPE ct) {
  int ax = (m_borders) ? x*m_squareWidth+m_x+1 : x*m_squareWidth+m_x;
  int ay = (m_borders) ? m_height+m_y-y*m_squareHeight : m_height+m_y-y*m_squareHeight-1;
  g->drawSquare(ax,ay,getCellTypeColor(x, y, ct));
  char chr = getCellTypeChar(x, y, ct);
  if(chr > 0) {
    g->drawChar(ax,ay,SGraphics::GCOLOR_DARKGRAY,getCellTypeColor(x, y, ct),chr);
  }
}

SGraphics::GCOLOR CBoardGraphics::getCellTypeColor(const int x, const int y, const CELL_TYPE ct) {
  switch(ct) {
    case OFFGRID: return SGraphics::GCOLOR_WHITE;
    case BLOCK_Z: return SGraphics::GCOLOR_LIGHTRED;
    case BLOCK_S: return SGraphics::GCOLOR_LIGHTGREEN;
    case BLOCK_I: return SGraphics::GCOLOR_LIGHTCYAN;
    case BLOCK_O: return SGraphics::GCOLOR_YELLOW;
    case BLOCK_L: return SGraphics::GCOLOR_BROWN;
    case BLOCK_J: return SGraphics::GCOLOR_LIGHTBLUE;
    case BLOCK_T: return SGraphics::GCOLOR_LIGHTMAGENTA;
    case EMPTY: return SGraphics::GCOLOR_BLACK;
    default: return SGraphics::GCOLOR_WHITE;
  }
}

char CBoardGraphics::getCellTypeChar(const int x, const int y, const CELL_TYPE ct) {
  switch(ct) {
    case EMPTY: return (x%2) ? '.' : ',';
    default: return 0;
  }
}

void CBoardGraphics::handleFreshBoard() {
  // tarkistetaan boardin koko
  m_width = board->getWidth();
  m_height = board->getHeight();
  // piirret‰‰n borderit uudelleen
  drawBorder();
  // hae koko board, ja piirr‰ se
  for(int ix=0; ix<m_width; ix++) {
    for(int iy=0; iy<m_height; iy++) {
      drawCell(ix, iy, board->getSlot(ix, iy));
    }
  }
}

void CBoardGraphics::handleChangeInLines(const int *changedLines[], const int numLines) {
  int iy = 0;
  // k‰yd‰‰n muuttuneet rivit l‰pi
  for(int i=0; i<numLines; i++) {
    iy = *changedLines[i];
    // piirret‰‰n rivi uudestaan
    for(int ix=0; ix<m_width; ix++) {
      drawCell(ix, iy, board->getSlot(ix, iy));
    }
  }
}

void CBoardGraphics::handleChangeInCoord(const int x, const int y, const CELL_TYPE ct) {
  drawCell(x, y, ct);
}

void CBoardGraphics::handleChangeInStats(int score, int reml, int remll, int level) {
  // atm ei tehd‰ mit‰‰n muutosilmoituksilla
}
