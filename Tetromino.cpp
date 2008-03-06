/**
 * Tetromino
 *
 * $Id$
 * $Revision$
 *

 TODO:
   ongelma:
    palikan muoto ja rotaatiot tulee antaa konstruktorissa (blockfactory antaa ne),
    mutta miten muoto pidet‰‰n? ja onko pivot point aina toinen piste x ja y-suunnassa?
    l‰hdet‰‰n siit‰ ett‰ annetaan ainoastaan rotaation 0 muoto, jota pyˆritet‰‰n
    laskennallisesti, eli getRotation(int r)-metodi palauttaa halutun rotaation r
   metodit joihin t‰m‰ vaikuttaa:
    konstruktori
    getRotation(int r)

 * Palikka huolehtii seuraavista asioista:
 *  - palikka voi olla liitettyn‰ yhteen pelilautaan kerrallaan
 *  - palikka tiet‰‰ muotonsa ja mahdolliset rotaationsa
 *  - palikka tiet‰‰ omat koordinaattinsa pelilaudalla
 *  - palikka osaa k‰‰nt‰‰ omaa rotaatiotaan, ja tiet‰‰ uudet koordinaattinsa
 *    pelilaudalla
 *  - palikka osaa liikuttaa itse‰‰n eri suuntiin, ja tiet‰‰ uudet
 *    koordinaattinsa pelilaudalla
 *  - palikka osaa muuttuessaan testata ett‰ sen ruudut ovat tyhj‰t
 *    pelilaudalla
 *  - palikka osaa "polttaa/maalata" itsens‰ pelilautaan kun sen tila on
 *    muuttunut
 *  - palikan tilan muuttuessa se osaa asettaa vanhat ruutunsa laudalla
 *    tyhjiksi
 *  - palikka osaa kertoa onko se laskeutunut (seuraava tiputus osuisi laudan
 *    maastoon)
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
  int oldY = m_y;
  int oldX = m_x;
  int y = m_y;
  while( canMoveTo(m_x, y-1, m_rotation) ) {
    y--;
  }
  if(y == m_y)
    return false; // ei voitu tiputtaa yht‰‰n
  removeFromBoard();
  m_y = y;
  insertToBoard();
  return true;
}

bool CTetromino::hasLanded() {
  // TODO: palikan liikutus dropin j‰lkeen viel‰ yhden tickin verran
  // Tee hasLanded boolean
  //  - kun palikka dropataan, sit‰ ei aseteta viel‰
  //  - kun palikkaa tiputetaan yhdell‰ (pelaaja tai tick), eik‰ se liiku
  //    en‰‰, hasLanded = true (ja detach laudasta?)
  if(board == 0) return true;
  if( !canMoveTo(m_x, m_y - 1, m_rotation) )
    return true;
  return false;
}

bool CTetromino::isFullyVisible() {
  if(!isAttached()) return false;
  // etsi ylin y-koordinaatti ja vertaa sit‰ laudan ylimp‰‰n koordinaattiin
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
  // tarkistetaan onko tulevan sijainnin kaikki paikat boardissa tyhji‰
  for(int i=0; i<4; i++) {
    // testataan: a) koordinaatti ei ole oma nykyinen, b) on tyhj‰ laudalla
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
    case 0: { return  m_cellCoordsY[y]; }
    case 3: { return  m_cellCoordsX[y]; }
    case 2: { return -m_cellCoordsY[y]; }
    case 1: { return -m_cellCoordsX[y]; }
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
  board->update();
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
  board->update();
}
