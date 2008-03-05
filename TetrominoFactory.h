#ifndef __TETROMINOFACTORY_H__
#define __TETROMINOFACTORY_H__

#include "Tetromino.h"
#include "CellType.h"

/**
 * TetrominoFactory
 *
 * $Id$
 * $Revision$
 *
 * Alustaa halutun palikan, tai random-palikan ‰lykk‰‰ll‰ logiikalla
 * esim: http://www.tetrisconcept.com/wiki/index.php?title=TGM_randomizer
 *
 * TODO:
 *  - create(..) joka luo ja antaa muodon tunnetuille tetrominoille
 *  - logiikka randomille
 */

class CTetrominoFactory {

  public:
    CTetrominoFactory(void);

    ~CTetrominoFactory(void);

    // palauttaa halutun palikan
    // palikan vastaanottaja vastaa sen tuhoamisesta
    CTetromino* create(CELL_TYPE t);

    // valitsee logiikalla seuraavan palikan ja palauttaa sen:
    // return create(TETROMINO);
    // palikan vastaanottaja vastaa sen tuhoamisesta
    CTetromino* createRandom(void);

  private:

    // count luoduista palikoista
    int m_creationCount;

    // tilastoa luoduista palikoista
    // todo: indeksitaulukko jossa totals[TETROMINOE] = m‰‰r‰

    // lastlogin koko, eli montako viimeist‰ palikkaa otetaan huomioon arvonnassa
    // (katso vaikka http://www.tetrisconcept.com/wiki/index.php?title=TGM_randomizer )
//    int m_lastlogSize;

    // tilastoa viimeksi luoduista palikoista
    // TODO: k‰yt‰ jotain palikka-painoarvo -pareja?

};

#endif // __TETROMINOFACTORY_H__
