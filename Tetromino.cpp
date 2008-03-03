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

/**
 * Konstruktori, jossa m‰‰ritet‰‰n palikan muoto, sek‰ mit‰ se maalaa.
 */
CTetromino::CTetromino(int cellCoordsX[], int cellCoordsY[], int maxRotation, CELL_TYPE type) {

}

CTetromino::~CTetromino(void) {
}

// ================= METODIT =============================================

/** Palauttaa nykyisen rotaation */
int CTetromino::getRotation() {
}

/** K‰‰nt‰‰ palikkaa myˆt‰p‰iv‰‰n */
bool CTetromino::rotateRight() {
}

/** K‰‰nt‰‰ palikkaa vastap‰iv‰‰n */
bool CTetromino::rotateRight() {
}

/** @return true jos palikka on kiinnitetty johonkin boardiin */
bool CTetromino::isAttached() {
}

/**
 * Kiinnitt‰‰ palikan lautaan jos ei tule collisionia (jolloin palauttaa
 * false).
 * Kiinnittyminen tapahtuu vaakasuunnassa keskelle, pystysuunnassa
 * palikan pivot-point/origo tulee kent‰n ylimp‰‰n riviin. Jos palikka
 * on ennest‰‰n toisessa laudassa, tehd‰‰n siihen ensin clean
 * detach.
 */
bool CTetromino::attach(TetrisBoard board) {
}

/**
 * Kiinnittyy boardiin jos ei tule collisionia (collisionissa liitosta ei
 * tapahdu ja palautetaan false)
 * Kiinnittyminen tapahtuu vaakasuunnassa keskelle, pystysuunnassa laudan
 * ylimp‰‰n koordinaattiin + offset
 */
bool CTetromino::attach(TetrisBoard board, int offsetY) {
}

/** Detachaa nykyisest‰ boardista, jos bool = true, tyhj‰‰ sijaintinsa laudassa */
bool CTetromino::detach(bool clear) {
}

bool CTetromino::moveLeft() {
}

bool CTetromino::moveRight() {
}

bool CTetromino::moveUp(int n) {
}

bool CTetromino::moveDown() {
}

bool CTetromino::moveDown(int n) {
}

bool CTetromino::drop() {
}

bool CTetromino::contains(const int x, const int y) {
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
}

// ===========================================================================
// PRIVATE
// ===========================================================================

// ================= METODIT =============================================

/**
 * Asettaa rotaaion r jos mahdollista
 * @return  asettamisen onnistuminen
 */
bool CTetromino::setRotation(int r) {
}

/**
 * Testaa voiko palikka olla laudalla annetuissa koordinaateissa,
 * annetulla orientaatiolla.
 *
 * @return  false, jos joku palikan ruuduista ei ole tyhj‰ laudalla,
 *          tai jos palikka menee ohi laudasta sivusuunnassa (tai pohjasta)
 */
bool CTetromino::canMoveTo(const int x, const int y, const int rotation) {
}

/**
 * Palauttaa halutun rotaation relatiivisen koordinaatin
 */
int CTetromino::getRelativeX(const int x, const int rotation) {
}

int CTetromino::getRelativeY(const int y, const int rotation) {
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
