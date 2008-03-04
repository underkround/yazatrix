/**
 *
 *
 */

#include "BoardGraphics.h"

CBoardGraphics::CBoardGraphics(CTetrisBoard *myBoard, Graphics *graphics, int offsetX, int offsetY) {
  board = myBoard;
  g = graphics;
  m_x = offsetX;
  m_y = offsetY;
  // jos ei borderia tms , niin mitat = boardin mitat
  m_width = board->getWidth();
  m_height = board->getHeight();
}

// Todo..
