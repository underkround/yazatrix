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
    Tetromino create(CELL_TYPE);

    // valitsee logiikalla seuraavan palikan ja palauttaa sen:
    // return create(TETROMINO);

    Tetromino createRandom(void);

private:

    // Factory osaa luoda n‰m‰
    const CELL_TYPES[] KNOWN_TYPES = {
        BLOCK_Z,
        BLOCK_S,
        BLOCK_I,
        BLOCK_O,
        BLOCK_L,
        BLOCK_J,
        BLOCK_T,
    };

    // count luoduista palikoista
    int tetrominoCount = 0;

    // tilastoa luoduista palikoista
    // todo: indeksitaulukko jossa totals[TETROMINOE] = m‰‰r‰

    // lastlogin koko, eli montako viimeist‰ palikkaa otetaan huomioon arvonnassa
    // (katso vaikka http://www.tetrisconcept.com/wiki/index.php?title=TGM_randomizer )
    const int lastlogSize = 10;

    // tilastoa viimeksi luoduista palikoista
    // TODO: k‰yt‰ jotain palikka-painoarvo -pareja?

};

#endif // __TETROMINOFACTORY_H__
