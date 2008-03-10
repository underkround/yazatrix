#ifndef __TETROMINOFACTORY_H__
#define __TETROMINOFACTORY_H__

/**
 * TetrominoFactory
 *
 * $Revision$
 * $Id$
 *
 * Alustaa halutun palikan, tai random-palikan ‰lykk‰‰ll‰ logiikalla
 * esim: http://www.tetrisconcept.com/wiki/index.php?title=TGM_randomizer
 *
 * TODO: ‰lyk‰s logiikka palikan arpomiselle
 * TODO: siivoa
 */

#include "Tetromino.h"
#include "TetrisCommon.h"

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
    bool m_xiitBlocks;

    // tilastoa luoduista palikoista
    // todo: indeksitaulukko jossa totals[TETROMINOE] = m‰‰r‰

    // lastlogin koko, eli montako viimeist‰ palikkaa otetaan huomioon arvonnassa
    // (katso vaikka http://www.tetrisconcept.com/wiki/index.php?title=TGM_randomizer )
//    int m_lastlogSize;

    // tilastoa viimeksi luoduista palikoista
    // TODO: k‰yt‰ jotain palikka-painoarvo -pareja?

};

#endif // __TETROMINOFACTORY_H__
