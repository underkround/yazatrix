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
  m_rotationMax = maxRotation;
  m_rotation = 0;
  *m_cellCoordsX = cellCoordsX;
  *m_cellCoordsY = cellCoordsY;
}

CTetromino::~CTetromino(void) {
}

// ================= METODIT =============================================

/** K‰‰nt‰‰ palikkaa myˆt‰p‰iv‰‰n */
bool CTetromino::rotateRight() {
  return false;
}

/** @return true jos palikka on kiinnitetty johonkin boardiin */
bool CTetromino::isAttached() {
  return false;
}

/**
 * Kiinnitt‰‰ palikan lautaan jos ei tule collisionia (jolloin palauttaa
 * false).
 * Kiinnittyminen tapahtuu vaakasuunnassa keskelle, pystysuunnassa
 * palikan pivot-point/origo tulee kent‰n ylimp‰‰n riviin. Jos palikka
 * on ennest‰‰n toisessa laudassa, tehd‰‰n siihen ensin clean
 * detach.
 */
bool CTetromino::attach(CTetrisBoard* board) {
  return false;
}

/**
 * Kiinnittyy boardiin jos ei tule collisionia (collisionissa liitosta ei
 * tapahdu ja palautetaan false)
 * Kiinnittyminen tapahtuu vaakasuunnassa keskelle, pystysuunnassa laudan
 * ylimp‰‰n koordinaattiin + offset
 */
bool CTetromino::attach(TetrisBoard* board, int offsetY) {
  return false;
}

/** Detachaa nykyisest‰ boardista, jos bool = true, tyhj‰‰ sijaintinsa laudassa */
bool CTetromino::detach(bool clear) {
  return false;
}

bool CTetromino::moveLeft() {
  return false;
}

bool CTetromino::moveRight() {
  return false;
}

bool CTetromino::moveUp(int n) {
  return false;
}

bool CTetromino::moveDown() {
  return false;
}

bool CTetromino::moveDown(int n) {
  return false;
}

bool CTetromino::drop() {
  return false;
}

bool CTetromino::contains(const int x, const int y) {
  return false;
}

/**
 * Onko palikka laskeutunut:
 * a) seuraava tiputus olisi collision
 * b) palikka ei ole miss‰‰n boardissa
 */
void CTetromino::hasLanded() {
}

/**
 * Palikka on boardissa ja jokainen sen ruutu on laudan sis‰puolella
 * (palikka voi aluksi olla yl‰puolelta boardin ulkopuolella)
 */
bool CTetromino::isFullyVisible() {
  return false;
}

// ===========================================================================
// PRIVATE
// ===========================================================================

/**
 * Asettaa rotaaion r jos mahdollista
 * @return  asettamisen onnistuminen
 */
bool CTetromino::setRotation(int r) {
  return false;
}

/**
 * Testaa voiko palikka olla laudalla annetuissa koordinaateissa,
 * annetulla orientaatiolla.
 *
 * @return  false, jos joku palikan ruuduista ei ole tyhj‰ laudalla,
 *          tai jos palikka menee ohi laudasta sivusuunnassa (tai pohjasta)
 */
bool CTetromino::canMoveTo(const int x, const int y, const int rotation) {
  return false;
}

/**
 * Palauttaa halutun rotaation relatiivisen koordinaatin
 */
int CTetromino::getRelativeX(const int x, const int rotation) {
  return 0;
}

int CTetromino::getRelativeY(const int y, const int rotation) {
  return 0;
}

/**
 * "Polttaa" palikan pelilaudan kentt‰‰n, eli vaihtaa omat ruutunsa
 * pelilaudassa oman tyyppins‰ mukaisiksi.
 */
void CTetromino::insertToBoard() {
}

/**
 * Poistaa itsens‰ pelilaudalta, eli kirjoittaa tyhj‰n ruudun arvon
 * jokaiseen ruutuunsa pelilaudassa
 */
void CTetromino::removeFromBoard() {
}
