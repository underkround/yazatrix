/**
 * Tetromino
 *
 * $Revision$
 * $Id$
 *
 * @see Tetromino.h
 *
 */

#include "Tetromino.h"
#include <iostream>

CTetromino::CTetromino(int cellCoordsX[4], int cellCoordsY[4], int maxRotation, CELL_TYPE type) {
  m_type = type;
  m_x = -10;
  m_y = -10;
  m_rotationMax = maxRotation;
  m_rotation = 0;
  for(int i=0; i<4; i++) {
    m_cellCoordsX[i] = cellCoordsX[i];
    m_cellCoordsY[i] = cellCoordsY[i];
  }
  board = 0;
  m_ghost = false;
  m_ghostOnBoard = false;
  m_gy = 0;
}

CTetromino::~CTetromino(void) {
}

// ================= METODIT =============================================

bool CTetromino::rotateRight() {
  if(!isAttached() || m_rotationMax == 0) return false;
  if(canMoveTo(m_x, m_y, getNextRotation())) {
    removeFromBoard();
    setRotation(getNextRotation());
    insertToBoard();
    return true;
  }
  return false;
}

bool CTetromino::rotateLeft() {
  if(!isAttached() || m_rotationMax == 0) return false;
  if(canMoveTo(m_x, m_y, getPreviousRotation())) {
    removeFromBoard();
    setRotation(getPreviousRotation());
    insertToBoard();
    return true;
  }
  return false;
}

bool CTetromino::isAttached() {
  return (board != 0) ? true : false;
}

bool CTetromino::attach(CTetrisBoard *targetBoard) {
  return attach(targetBoard, 0, 0);
}

bool CTetromino::attach(CTetrisBoard *targetBoard, int offsetY) {
  return attach(targetBoard, 0, offsetY);
}

bool CTetromino::attach(CTetrisBoard *targetBoard, int offsetX, int offsetY) {
  if(board != 0)
    detach(true);
  int x = getBoardCenterX(targetBoard) + offsetX;
  int y = targetBoard->getHeight()-1 + offsetY;
  if(y < 0) return false;
  if(canMoveTo(x, y, m_rotation, targetBoard)) {
    m_x = x;
    m_y = y;
    board = targetBoard;
    insertToBoard();
    return true;
  }
  return false;
}

bool CTetromino::detach(bool clear) {
  if(clear && board != 0)
    removeFromBoard();
  board = 0;
  return true;
}

bool CTetromino::detach() {
  return detach(false);
}

bool CTetromino::moveLeft() {
  if(!isAttached()) return false;
  if(canMoveTo(m_x-1, m_y, m_rotation)) {
    removeFromBoard();
    m_x--;
    insertToBoard();
    return true;
  }
  return false;
}

bool CTetromino::moveRight() {
  if(!isAttached()) return false;
  if(canMoveTo(m_x+1, m_y, m_rotation)) {
    removeFromBoard();
    m_x++;
    insertToBoard();
    return true;
  }
  return false;
}

bool CTetromino::moveUp(int n) {
  if(!isAttached()) return false;
  return moveDown(-n);
}

bool CTetromino::moveDown() {
  if(!isAttached()) return false;
  return moveDown(1);
}

bool CTetromino::moveDown(int n) {
  if(!isAttached()) return false;
  if(canMoveTo(m_x, m_y-n, m_rotation)) {
    removeFromBoard();
    m_y -= n;
    insertToBoard();
    return true;
  }
  return false;
}

bool CTetromino::drop() {
  if(!isAttached()) return false;
  int y = m_y;
  while( canMoveTo(m_x, y-1, m_rotation) ) {
    y--;
  }
  if(y == m_y)
    return false; // ei voitu tiputtaa yhtään
  removeFromBoard();
  m_y = y;
  insertToBoard();
  return true;
}

bool CTetromino::hasLanded() {
  if(board == 0) return true;
  if( !canMoveTo(m_x, m_y - 1, m_rotation) )
    return true;
  return false;
}

bool CTetromino::isFullyVisible() {
  if(!isAttached()) return false;
  // etsi ylin y-koordinaatti ja vertaa sitä laudan ylimpään koordinaattiin
  for(int i=0; i<4; i++)
    if(m_y + getRelativeY(i, m_rotation) > board->getHeight() - 1)
      return false;
  return true;
}

// ==================== PRIVATE ====================

int CTetromino::getBoardCenterX(CTetrisBoard *targetBoard) {
  int center = (targetBoard->getWidth() - 1) / 2;
  return center;
}

bool CTetromino::setRotation(int r) {
  if(0 > r || r > m_rotationMax)
    return false;
  m_rotation = r;
//  insertToBoard();
  return true;
}

bool CTetromino::canMoveTo(const int x, const int y, const int rotation, CTetrisBoard *targetBoard) {
  // tarkistetaan onko tulevan sijainnin kaikki paikat boardissa tyhjiä
  for(int i=0; i<4; i++) {
    // testataan: a) koordinaatti ei ole oma nykyinen, b) on tyhjä laudalla
    int tx = x + getRelativeX(i, rotation);
    int ty = y + getRelativeY(i, rotation);
    if(!containsBoardCoord(tx, ty))
      if(!targetBoard->isEmpty(tx, ty))
        return false;
  }
  return true;
}

bool CTetromino::canMoveTo(const int x, const int y, const int rotation) {
  if(!isAttached()) return false;
  return canMoveTo(x, y, rotation, board);
}

int CTetromino::getRelativeX(const int x, const int rotation) {
  switch(rotation) {
    case 0: return  m_cellCoordsX[x];
    case 3: return -m_cellCoordsY[x];
    case 2: return -m_cellCoordsX[x];
    case 1: return  m_cellCoordsY[x];
  }
  return -1;
}

int CTetromino::getRelativeY(const int y, const int rotation) {
  switch(rotation) {
    case 0: return  m_cellCoordsY[y];
    case 3: return  m_cellCoordsX[y];
    case 2: return -m_cellCoordsY[y];
    case 1: return -m_cellCoordsX[y];
  }
  return -1;
}

bool CTetromino::containsBoardCoord(int x, int y) {
  for(int i=0; i<4; i++)
    if(
        m_x + getRelativeX(i, m_rotation) == x &&
        m_y + getRelativeY(i, m_rotation) == y
    ) return true;
  return false;
}

void CTetromino::insertToBoard() {
  if(!isAttached()) return;
  for(int i=0; i<4; i++) {
    board->setSlot(
      m_x + getRelativeX(i, m_rotation),
      m_y + getRelativeY(i, m_rotation),
      m_type
    );
  }
  insertGhostToBoard();
  board->update();
}

void CTetromino::insertGhostToBoard() {
  if(!isAttached() || !m_ghost) return;
  int gy = m_y;
  int gx = m_x;
  while(canMoveTo(gx, gy, m_rotation)) {
    gy--;
  }
  gy++;
  if(gy != m_y) {
    for(int i=0; i<4; i++) {
      int rgx = gx + getRelativeX(i, m_rotation);
      int rgy = gy + getRelativeY(i, m_rotation);
      if(!containsBoardCoord(rgx, rgy))
        board->setSlot(rgx, rgy, m_ghostType);
    }
    m_gy = gy;
    m_ghostOnBoard = true;
  }
}

void CTetromino::removeFromBoard() {
  if(!isAttached()) return;
  for(int i=0; i<4; i++) {
    board->setSlot(
      m_x + getRelativeX(i, m_rotation),
      m_y + getRelativeY(i, m_rotation),
      EMPTY
    );
  }
  removeGhostFromBoard();
  board->update();
}

void CTetromino::removeGhostFromBoard() {
  if(!isAttached() || !m_ghost || !m_ghostOnBoard) return;
  for(int i=0; i<4; i++) {
    int rgx = m_x + getRelativeX(i, m_rotation);
    int rgy = m_gy + getRelativeY(i, m_rotation);
    if(!containsBoardCoord(rgx, rgy) && board->getSlot(rgx, rgy) == m_ghostType)
      board->setSlot(rgx, rgy, EMPTY);
  }
}
