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

CBoardGraphics::CBoardGraphics(CTetrisBoard *myBoard, CGraphics *graphics, int offsetX, int offsetY) {
  board = myBoard;
  // rekisteröidy boardille kuuntelijaksi
  VBoardChangeListener *bcl = dynamic_cast<VBoardChangeListener*>(this);
  board->registerBoardChangeListener( bcl );
  g = graphics;
  m_x = offsetX;
  m_y = offsetY;
  // jos ei borderia tms , niin mitat = boardin mitat
  m_width = board->getWidth();
  m_height = board->getHeight();
  m_borders = true;
  setBorderStyle(CGraphics::BORDER_GROOVE);
  handleFreshBoard();
}

CBoardGraphics::~CBoardGraphics() {
  // poista rekisteröityminen
  //board->unregisterBoardChangeListener(this);
  // jaa voipa olla että tulisi ongelmia jos board on jo tuhottu..
  // jollei sitten tee siitäkin ilmoitusta listenerin kautta =)
}

void CBoardGraphics::setBorder(bool visible) {
  // borderit päällä? jos moisia jaksaa tehdä. lisää tietty leveyttä ja korkeutta +2
  m_borders = visible; // TODO: pitäisikö olla int, jos bordertyyppejä on useita?
  handleFreshBoard(); // koko lauta muuttuu jos borderit muuttuu päälle / pois
}

void CBoardGraphics::setBorderStyle(CGraphics::BORDER_STYLE bs) {
  m_borderStyle = bs;
  drawBorder();
}

void CBoardGraphics::drawBorder() {
  g->setColors(CGraphics::GCOLOR_WHITE, CGraphics::GCOLOR_BLACK);
  if(m_borders)
    g->drawBox(m_x, m_y, m_x+m_width+1, m_y+m_height+1, m_borderStyle);
}

void CBoardGraphics::setLocation(int x, int y) {
  // mistä ruudun koordinaatista tämä aloittaa piirtämään itseään (ylävasen koord)
  m_x = x;
  m_y = y;
}

// tätä käyttäen piirretään solut
void CBoardGraphics::drawCell(int x, int y, CELL_TYPE ct) {
  int ax = (m_borders) ? x+m_x+1 : x+m_x;
  int ay = (m_borders) ? m_height+m_y-y : m_height+m_y-y-1;
  g->drawSquare(ax,ay,getCellTypeColor(ct));
}

CGraphics::GCOLOR CBoardGraphics::getCellTypeColor(CELL_TYPE ct) {
  switch(ct) {
    case OFFGRID: return CGraphics::GCOLOR_WHITE;
    case BLOCK_Z: return CGraphics::GCOLOR_LIGHTRED;
    case BLOCK_S: return CGraphics::GCOLOR_LIGHTGREEN;
    case BLOCK_I: return CGraphics::GCOLOR_LIGHTCYAN;
    case BLOCK_O: return CGraphics::GCOLOR_YELLOW;
    case BLOCK_L: return CGraphics::GCOLOR_BROWN;
    case BLOCK_J: return CGraphics::GCOLOR_LIGHTBLUE;
    case BLOCK_T: return CGraphics::GCOLOR_LIGHTMAGENTA;
    default:
    case EMPTY: return CGraphics::GCOLOR_BLACK;
  }
}

void CBoardGraphics::handleFreshBoard() {
  // tarkistetaan boardin koko
  m_width = board->getWidth();
  m_height = board->getHeight();
  // piirretään borderit uudelleen
  drawBorder();
  // hae koko board, ja piirrä se
  for(int ix=0; ix<m_width; ix++) {
    for(int iy=0; iy<m_height; iy++) {
      drawCell(ix, iy, board->getSlot(ix, iy));
    }
  }
}

void CBoardGraphics::handleChangeInLines(const int *changedLines[], const int numLines) {
  int iy = 0;
  // käydään muuttuneet rivit läpi
  for(int i=0; i<numLines; i++) {
    iy = *changedLines[i];
    // piirretään rivi uudestaan
    for(int ix=0; ix<m_width; ix++) {
      drawCell(ix, iy, board->getSlot(ix, iy));
    }
  }
}

void CBoardGraphics::handleChangeInCoord(const int x, const int y, const CELL_TYPE ct) {
//  printf("%d:%d\n", x, y);
  drawCell(x, y, ct);
}

/*
 * !! DEPRICATED !!
 *
void CBoardGraphics::handleChangeInCoords(
    const int *changedCoordsX[],
    const int *changedCoordsY[],
    const CELL_TYPE *cts[],
    const int numChanges
) {
  for(int i=0; i<numChanges; i++) {
    drawCell(*changedCoordsX[i], *changedCoordsY[i], *cts[i]);
  }
}
 */
