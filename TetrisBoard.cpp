/**
 * TetrisBoard.cpp
 *
 * $Id$
 * $HeadURL$
 *
 * Y-koordinaatit alkavat alhaalta, eli alin rivi on y==0
 */

#include "TetrisBoard.h"

/**
 * Alustetaan pelilauta rakentajassa nollilla
 */
TetrisBoard::TetrisBoard(void) {
    // TODO: miten kutsun toista rakentajaa default-arvoilla?
    // TetrisBoard::TetrisBoard(10, 16);
}
TetrisBoard::TetrisBoard(const int cols, const int rows) {
    width = cols;
    height = rows;
    // luo vaaditun kokoinen matrix-taulukko
    // TODO: lolapua miten alustan taulukon
    // alusta matrix nollilla
    reset();
}

/**
 */
TetrisBoard::~TetrisBoard(void) {
    // pitääkö matrix delliä? alustettiinko se new .. ?
    // listenereitä ei pidä tuhota..
    // muut onkin sitten kai primitiivejä
}

/**
 * @return  kentän leveys
 */
const int* TetrisBoard::getWidth(void) {
  return width;
}

/**
 * @return  kentän korkeus
 */
const int* TetrisBoard::getHeight(void) {
  return height;
}

/**
 * @return  räjäytettyjen rivien kokonaismäärä
 */
int TetrisBoard::getRemovedLines(void) {
    return removedLines;
}

/**
 * @return  viimeisellä siivouksella räjähtäneiden rivien määrä
 */
int TetrisBoard::getRemovedLinesLast(void) {
    return removedLinesLast;
}

/**
 * @return  matrixin solun {x,y} arvon tai tai -1 jos menee yli
 *          kentän rajojen
 */
int TetrisBoard::getSlot(const int x, const int y) {
    if(x < 0 || x > width) return -1;
    if(y < 0 || y > height) return -1;
    return matrix[y][x];
}

/**
 * Asettaa kentän koordinaatin {x,y} annettuun arvoon, jos koordinaatti
 * on kentän rajojen sisäpuolella.
 * @param   content koordinaattiin asetettava arvo
 * @return  koordinaatin entinen arvo, tai -1 jos koordinaatti oli
 *          yli kentän rajojen
 */
int TetrisBoard::setSlot(const int x, const int y, const int content) {
    if(x < 0 || x > width) return -1;
    if(y < 0 || y > height) return -1;
    int old = matrix[y][x];
    matrix[y][x] = content;
    return old;
}

/**
 * Koko laudan tyhjyyden tarkistus
 * @return  true, jos jokainen laudan ruutu on EMPTY
 */
bool TetrisBoard::isEmpty(){
    for(int iy=0; iy<height; iy++) {
        for(int ix=0; ix<width; ix++) {
            if(matrix[iy][ix] > 0)
                return false; // vähintään yksi ruutu ei ole tyhjä
        }
    }
    return true;
}

/**
 * Yksittäisen koordinaatin tyhjyyden tarkistus
 * @return  true, jos koordinaatti {x,y} on
 *          a) vapaa (< 1)
 *          b) kentän rajojen sisäpuolella sivusuunnassa ja pohjasta
 *             katsoen (sivusuunnassa kentällä, ylhäältä yli = true)
 */
bool TetrisBoard::isEmpty(const int x, const int y) {
    return (matrix[y][x] < 1);
}

/**
 * Yksittäisen rivin tyhjyyden tarkistus
 * @return  true, jos rivi y on kokonaan tyhjä (kaikkien rivin
 *          ruudut < 1)
 */
bool TetrisBoard::isEmpty(const int y) {
    for(int i=0; i<width; i++)
        if(matrix[y][i] > 0)
            return false; // vähintään yksi ruutu ei ole tyhjä
    return true;
}

/**
 * Yksittäisen rivin täynnä olemisen tarkistus
 * @return  true, jos rivin y mikään koordinaatti ei ole tyhjä
 *          (jokainen ruutu > 0)
 */
bool TetrisBoard::isFull(const int y){
    for(int i=0; i<width; i++)
        if(matrix[y][i] < 1)
            return false; // vähintään yksi ruutu on tyhjä
    return true;
}

/**
 * Alustaa pelikentän taulukon (matrix) nollilla
 */
void TetrisBoard::reset(void) {
    // foreach matrix.. = 0
    for(int iy=0; iy<height; iy++) {
        for(int ix=0; ix<width; ix++) {
            matrix[y][x] = 0;
        }
    }
}

/**
 * Käy pelilaudan rivit läpi poistaen täynnä olevat. Kasvattaa
 * poistettujen rivien laskuria.
 */
int TetrisBoard::clearFullLines(void) {
    removedLinesLast = 0;
    // rivit pitää käydä ylhäältä alaspäin läpi, koska ne poistetaan
    // samantien, ja korkeat indeksit muuttuvat
    for(int i=height-1; i>=0; i--) {
        if(isFull(i)) {
            removeLine(i);
            removedLinesLast++;
        }
    }
    if(removedLinesLast > 0)
        notifyChange();
}

/**
 * Ilmoittaa laudan rekisteröityneille tapahtumakuuntelijoille
 * muutoksesta pelilaudassa (matrixissa)
 */
void TetrisBoard::notifyChange(void) {
    // foreach listeners
        // notify listener
}

/**
 * Lisää laudan tapahtumakuuntelijan kuuntelijavektoriin.
 * Ei vastaa kuuntelijaolioiden tuhoamisesta.
 */
bool TetrisBoard::registerBoardChangeListener(BoardChangeListener* bcl) {

}

/**
 * Poistaa laudan tapahtumakuuntelijan kuuntelijavektorista
 * Ei tuhoa kuuntelijaa.
 */
bool TetrisBoard::unregisterBoardChangeListener(BoardChangeListener* bcl) {

}

/**
 * Poistaa kentän rivin, ja siirtää ylempiä rivejä yhdellä alaspäin.
 * @return  false, jos kentässä ei ole riviä y (yli rajojen)
 */
bool TetrisBoard::removeLine(const int y) {
    if(y >= height || y < 0)
        return false;

    // aseta ylempien rivien indeksit yhdellä alaspäin
    for(int iy=y+1; iy<height; iy++) {
        // TODO, voiko taulukkoa kopioida valmiilla funkkarilla? matrix[iy-1] = matrix[iy]
    }

    // alusta uusi rivi matriksiin (ylimmäksi)
    for(int i=0; i<width; i++) {
        matrix[height-1][ix] = 0;
    }
    return true;
}
