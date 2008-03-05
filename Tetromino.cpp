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

/**
 * Konstruktori, jossa m‰‰ritet‰‰n palikan muoto, sek‰ mit‰ se maalaa.
 */
CTetromino::CTetromino(int cellCoordsX[4], int cellCoordsY[4], int maxRotation, CELL_TYPE type) {
  m_type = type;
  m_x = 0;
  m_y = 0;
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

/** K‰‰nt‰‰ palikkaa myˆt‰p‰iv‰‰n */
bool CTetromino::rotateRight() {
  if(canMoveTo(m_x, m_y, getNextRotation()))
    return setRotation(getNextRotation());
  return false;
}

/** K‰‰nt‰‰ palikkaa vastap‰iv‰‰n */
bool CTetromino::rotateLeft() {
  if(canMoveTo(m_x, m_y, getPreviousRotation()))
    return setRotation(getPreviousRotation());
  return false;
}

/** @return true jos palikka on kiinnitetty johonkin boardiin */
bool CTetromino::isAttached() {
  return (board != 0) ? true : false;
}

/**
 * Kiinnitt‰‰ palikan lautaan jos ei tule collisionia (jolloin palauttaa
 * false).
 * Kiinnittyminen tapahtuu vaakasuunnassa keskelle, pystysuunnassa
 * palikan pivot-point/origo tulee kent‰n ylimp‰‰n riviin. Jos palikka
 * on ennest‰‰n toisessa laudassa, tehd‰‰n siihen ensin clean detach.
 */
bool CTetromino::attach(CTetrisBoard *targetBoard) {
  return attach(targetBoard, 0, 0);
}

/**
 * Kiinnittyy boardiin jos ei tule collisionia (collisionissa liitosta ei
 * tapahdu ja palautetaan false)
 * Kiinnittyminen tapahtuu vaakasuunnassa keskelle, pystysuunnassa laudan
 * ylimp‰‰n koordinaattiin + offset
 */
bool CTetromino::attach(CTetrisBoard *targetBoard, int offsetY) {
  return attach(targetBoard, 0, offsetY);
}

bool CTetromino::attach(CTetrisBoard *targetBoard, int offsetX, int offsetY) {
  if(board != 0)
    detach(true);
  int x = getBoardCenterX(targetBoard) + offsetX;
  int y = targetBoard->getHeight()-1 + offsetY;
  if(canMoveTo(x, y, m_rotation, targetBoard)) {
    board = targetBoard;
    insertToBoard();
    return true;
  }
  return false;
}

/** Detachaa nykyisest‰ boardista, jos clear = true, tyhj‰‰ sijaintinsa laudassa */
bool CTetromino::detach(bool clear) {
  if(clear && board != 0)
    removeFromBoard();
  board = 0;
  return true;
}

bool CTetromino::moveLeft() {
  if(canMoveTo(m_x-1, m_y, m_rotation)) {
    m_x--;
    insertToBoard();
    return true;
  }
  return false;
}

bool CTetromino::moveRight() {
  if(canMoveTo(m_x+1, m_y, m_rotation)) {
    m_x++;
    insertToBoard();
    return true;
  }
  return false;
}

bool CTetromino::moveUp(int n) {
  return moveDown(-n);
}

bool CTetromino::moveDown() {
  return moveDown(1);
}

bool CTetromino::moveDown(int n) {
  if(canMoveTo(m_x, m_y-n, m_rotation)) {
    m_y -= n;
    insertToBoard();
    return true;
  }
  return false;
}


/**
 * Tiputtaa palikkaa niinkauan alas kuin se ei tˆrm‰‰ mihink‰‰n
 */
bool CTetromino::drop() {
  int y = m_y;
  while( canMoveTo(m_x, y, m_rotation) ) {
    y--;
  }
  if(y == m_y)
    return false; // ei voitu tiputtaa yht‰‰n
  m_y = y;
  insertToBoard();
  return true;
}


/**
 * Onko palikka laskeutunut:
 * a) seuraava tiputus olisi collision
 * b) palikka ei ole miss‰‰n boardissa
 */
bool CTetromino::hasLanded() {
  if(board == 0) return true;
  if( !canMoveTo(m_x, m_y - 1, m_rotation) )
    return true;
  return false;
}


/**
 * Palikka on boardissa ja jokainen sen ruutu on laudan sis‰puolella
 * (palikka voi aluksi olla yl‰puolelta boardin ulkopuolella)
 */
bool CTetromino::isFullyVisible() {
  if(board == 0) return false;
  // etsi ylin y-koordinaatti ja vertaa sit‰ laudan ylimp‰‰n koordinaattiin
  for(int i=0; i<4; i++)
    if(m_y + getRelativeY(i, m_rotation) > board->getHeight() - 1)
      return false;
  return true;
}


// ===========================================================================
// == PRIVATE


int CTetromino::getBoardCenterX(CTetrisBoard *targetBoard) {
  int center = targetBoard->getWidth() / 2;
  return center;
}

/**
 * Asettaa rotaaion r jos mahdollista
 * @return  asettamisen onnistuminen
 */
bool CTetromino::setRotation(int r) {
  if(0 > r || r > m_rotationMax)
    return false;
  m_rotation = r;
  insertToBoard();
  return true;
}

// siirretty inlineen
//int CTetromino::getNextRotation() { return (m_rotation+1 > m_rotationMax) ? 0 : m_rotation+1; }
//int CTetromino::getPreviousRotation() { return (m_rotation-1 < 0) ? m_rotationMax : m_rotation-1; }

/**
 * Testaa voiko palikka olla laudalla annetuissa koordinaateissa,
 * annetulla orientaatiolla.
 *
 * @return  false, jos joku palikan ruuduista ei ole tyhj‰ laudalla,
 *          tai jos palikka menee ohi laudasta sivusuunnassa (tai pohjasta)
 */
bool CTetromino::canMoveTo(const int x, const int y, const int rotation, CTetrisBoard *targetBoard) {
  // tarkistetaan onko tulevan sijainnin kaikki paikat boardissa tyhji‰
  for(int i=0; i<4; i++) {
    if( !targetBoard->isEmpty( x + getRelativeX(i, rotation), y + getRelativeY(i, rotation) ) )
      return false;
  }
  return true;
}
/** Yll‰oleva omalla laudalla */
bool CTetromino::canMoveTo(const int x, const int y, const int rotation) {
  return canMoveTo(x, y, rotation, board);
}


/**
 * Palauttaa halutun rotaation relatiivisen koordinaatin
 */
int CTetromino::getRelativeX(const int x, const int rotation) {
  switch(rotation) {
    case 0: { return  m_cellCoordsX[x]; }
    case 1: { return -m_cellCoordsY[x]; }
    case 2: { return -m_cellCoordsX[x]; }
    case 3: { return  m_cellCoordsY[x]; }
  }
  return -1;
}

int CTetromino::getRelativeY(const int y, const int rotation) {
  switch(rotation) {
    case 0: { return  m_cellCoordsY[y]; }
    case 1: { return  m_cellCoordsX[y]; }
    case 2: { return -m_cellCoordsY[y]; }
    case 3: { return -m_cellCoordsX[y]; }
  }
  return -1;
}


/**
 * "Polttaa" palikan pelilaudan kentt‰‰n, eli vaihtaa omat ruutunsa
 * pelilaudassa oman tyyppins‰ mukaisiksi.
 */
void CTetromino::insertToBoard() {
  if(board == 0) return;
  for(int i=0; i<4; i++) {
    board->setSlot(
      m_x + getRelativeX(i, m_rotation),
      m_y + getRelativeY(i, m_rotation),
      m_type
    );
  }
}

/**
 * Poistaa itsens‰ pelilaudalta, eli kirjoittaa tyhj‰n ruudun arvon
 * jokaiseen ruutuunsa pelilaudassa
 */
void CTetromino::removeFromBoard() {
  if(board == 0) return;
  for(int i=0; i<4; i++) {
    board->setSlot(
      m_x + getRelativeX(i, m_rotation),
      m_y + getRelativeY(i, m_rotation),
      EMPTY
    );
  }
}
