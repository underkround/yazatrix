/**
 * TetrisBoard.cpp
 *
 * $Id$
 * $Revision$
 * $HeadURL$
 *
 * Y-koordinaatit alkavat alhaalta, eli alin rivi on y==0
 */

#include "TetrisBoard.h"
#include "CellType.h"

/**
 * Kutsuu pääkonstruktoria oletusarvoilla
 */
//CTetrisBoard::CTetrisBoard(void) {
    // TODO: miten kutsun toista rakentajaa default-arvoilla?
    // TetrisBoard::TetrisBoard(10, 16);
//}

/**
 * Pääkonstruktori
 */

CTetrisBoard::CTetrisBoard(const int cols, const int rows) {
    m_width = cols;
    m_height = rows;
    // luo vaaditun kokoinen matrix-taulukko
    // TODO: lolapua miten alustan taulukon
    m_matrix = new CELL_TYPE*[rows];
    for(int iy=0; iy<rows; iy++)
        m_matrix[iy] = new CELL_TYPE[cols];
    // alusta matrix nollilla
    reset();
}


CTetrisBoard::~CTetrisBoard() {
    // tuhotaan matrix
    for(int iy=0; iy<m_height; iy++)
        delete []m_matrix[iy];
    delete [] m_matrix;
    // listenereitä ei pidä tuhota..
    // muut onkin sitten kai primitiivejä
}


/**
 * Alustaa pelikentän taulukon (matrix) nollilla
 */
void CTetrisBoard::reset(void) {
    // nollataan linecountit
    m_removedLines = 0;
    m_removedLinesLast = 0;
    // foreach matrix.. = 0
    for(int iy=0; iy<m_height; iy++) {
        for(int ix=0; ix<m_width; ix++) {
            m_matrix[iy][ix] = EMPTY;
        }
    }
}


/**
 * @return  matrixin solun {x,y} arvon tai OFFGRID jos menee yli
 *          kentän rajojen
 */
CELL_TYPE CTetrisBoard::getSlot(const int x, const int y) {
    if(x < 0 || x >= m_width) return OFFGRID;
    if(y < 0 || y >= m_height) return OFFGRID;
    return m_matrix[y][x];
}


/**
 * Asettaa kentän koordinaatin {x,y} annettuun arvoon, jos koordinaatti
 * on kentän rajojen sisäpuolella.
 * @param   content koordinaattiin asetettava arvo
 * @return  koordinaatin entinen arvo, tai OFFGRID jos koordinaatti oli
 *          yli kentän rajojen
 */
CELL_TYPE CTetrisBoard::setSlot(const int x, const int y, const CELL_TYPE content) {
    if(x < 0 || x >= m_width) return OFFGRID;
    if(y < 0 || y >= m_height) return OFFGRID;
    CELL_TYPE old = m_matrix[y][x];
    m_matrix[y][x] = content;
    return old;
}


/**
 * Koko laudan tyhjyyden tarkistus
 * @return  true, jos jokainen laudan ruutu on EMPTY
 */
bool CTetrisBoard::isEmpty(){
    for(int iy=0; iy<m_height; iy++) {
        for(int ix=0; ix<m_width; ix++) {
            if(m_matrix[iy][ix] != EMPTY)
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
bool CTetrisBoard::isEmpty(const int x, const int y) {
    if(x < 0 || x >= m_width || y < 0) return false;
    if(y >= m_height) return true;
    return (m_matrix[y][x] == EMPTY) ? true : false;
}


/**
 * Yksittäisen rivin tyhjyyden tarkistus
 * @return  true, jos rivi y on kokonaan tyhjä (kaikkien rivin
 *          ruudut < 1)
 *          false, jos rivillä on jotain tai se on yli rajojen
 */
bool CTetrisBoard::isEmpty(const int y) {
    if(y < 0 || y >= m_height) return false;
    for(int i=0; i<m_width; i++)
        if(m_matrix[y][i] != EMPTY)
            return false; // vähintään yksi ruutu ei ole tyhjä
    return true;
}


/**
 * Yksittäisen rivin täynnä olemisen tarkistus
 * @return  true, jos rivin y mikään koordinaatti ei ole tyhjä
 *          (jokainen ruutu > 0)
 */
bool CTetrisBoard::isFull(const int y){
    for(int i=0; i<m_width; i++)
        if(m_matrix[y][i] == EMPTY)
            return false; // vähintään yksi ruutu on tyhjä
    return true;
}


/**
 * Käy pelilaudan rivit läpi poistaen täynnä olevat. Kasvattaa
 * poistettujen rivien laskuria.
 */
int CTetrisBoard::clearFullLines(void) {
    m_removedLinesLast = 0;
    // rivit pitää käydä ylhäältä alaspäin läpi, koska ne poistetaan
    // samantien, ja korkeat indeksit muuttuvat
    for(int i=m_height-1; i>=0; i--) {
        if(isFull(i)) {
            removeLine(i);
            m_removedLinesLast++;
        }
    }
    if(m_removedLinesLast > 0)
        notifyChange();

        return m_removedLines; //??
}


/**
 * Ilmoittaa laudan rekisteröityneille tapahtumakuuntelijoille
 * muutoksesta pelilaudassa (matrixissa)
 */
void CTetrisBoard::notifyChange(void) {
    // foreach listeners
        // notify listener
}


/**
 * Lisää laudan tapahtumakuuntelijan kuuntelijavektoriin.
 * Ei vastaa kuuntelijaolioiden tuhoamisesta.
 */
//bool CTetrisBoard::registerBoardChangeListener(BoardChangeListener* bcl) {
    // TODO
//}


/**
 * Poistaa laudan tapahtumakuuntelijan kuuntelijavektorista
 * Ei tuhoa kuuntelijaa.
 */
//bool CTetrisBoard::unregisterBoardChangeListener(BoardChangeListener* bcl) {
    // TODO
//}


/**
 * Poistaa kentän rivin, ja siirtää ylempiä rivejä yhdellä alaspäin.
 * @return  false, jos kentässä ei ole riviä y (yli rajojen)
 */
bool CTetrisBoard::removeLine(const int y) {
    if(y >= m_height || y < 0)
        return false;

    // aseta ylempien rivien indeksit yhdellä alaspäin
    for(int iy=y+1; iy<m_height; iy++) {
        // TODO, voiko taulukkoa kopioida valmiilla funkkarilla? matrix[iy-1] = matrix[iy]
    }

    // alusta uusi rivi matriksiin (ylimmäksi)
    for(int ix=0; ix<m_width; ix++) {
        m_matrix[m_height-1][ix] = EMPTY;
    }
    return true;
}
