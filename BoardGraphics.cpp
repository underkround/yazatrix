/**
 *
 *
 */

#include "BoardGraphics.h"

CBoardGraphics::CBoardGraphics(CTetrisBoard *myBoard, CGraphics *graphics, int offsetX, int offsetY) {
  board = myBoard;
  g = graphics;
  m_x = offsetX;
  m_y = offsetY;
  // jos ei borderia tms , niin mitat = boardin mitat
  m_width = board->getWidth();
  m_height = board->getHeight();
}

CBoardGraphics::~CBoardGraphics() {
}

void CBoardGraphics::setBorder(bool visible) {
  // borderit p‰‰ll‰? jos moisia jaksaa tehd‰. lis‰‰ tietty leveytt‰ ja korkeutta +2
  m_borders = visible;
}

void CBoardGraphics::setLocation(int x, int y) {
  // mihin kohtaan ruutua piirt‰‰ itsens‰
  m_x = x;
  m_y = y;
}

// katso BoardChangeListener n‰iden tarkempaan tarkotukseen
void CBoardGraphics::handleFreshBoard() {}

void CBoardGraphics::handleChangeInCoords(int *changedCoordsX[], int *changedCoordsY[], int numCoords) {}

void CBoardGraphics::handleChangeInLines(int *changedLines[], int numLines) {}

void CBoardGraphics::handleChangeInCoord(int x, int y) {}
