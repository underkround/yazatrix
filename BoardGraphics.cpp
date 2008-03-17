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
  board->registerListener( bcl );
  m_x = offsetX;
  m_y = offsetY;
  m_squareWidth = 1;
  m_squareHeight = 1;
  // jos ei borderia tms , niin mitat = boardin mitat
  m_width = board->getWidth() * m_squareWidth;
  m_height = board->getHeight() * m_squareHeight;
//  setBorderStyle(SGraphics::BORDER_GROOVE);
  handleFreshBoard();
}

CBoardGraphics::~CBoardGraphics() {
  // poista rekisterˆityminen
  //board->unregisterBoardChangeListener(this);
  // jaa voipa olla ett‰ tulisi ongelmia jos board on jo tuhottu..
  // jollei sitten tee siit‰kin ilmoitusta listenerin kautta =)
}

// t‰t‰ k‰ytt‰en piirret‰‰n solut
void CBoardGraphics::drawCell(const int x, const int y, CELL_TYPE ct) {
  int ax = (m_border) ? x*m_squareWidth+m_x+1 : x*m_squareWidth+m_x;
  int ay = (m_border) ? m_height+m_y-y*m_squareHeight : m_height+m_y-y*m_squareHeight-1;
  g->drawSquare(ax,ay,getCellTypeColor(x, y, ct));
  char chr = getCellTypeChar(x, y, ct);
  if(chr > 0) {
    g->drawChar(ax, ay, SGraphics::GCOLOR_DARKGRAY, getCellTypeColor(x, y, ct), chr);
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
    case GHOST: return SGraphics::GCOLOR_BLACK;
    default: return SGraphics::GCOLOR_WHITE;
  }
}

char CBoardGraphics::getCellTypeChar(const int x, const int y, const CELL_TYPE ct) {
  switch(ct) {
    case EMPTY: return (x%2) ? '.' : ' ';
    case GHOST: return 'x';
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
