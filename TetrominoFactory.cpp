/**
 * TetrominoFactory
 *
 * $Id$
 * $Revision$
 */

#include "TetrominoFactory.h"

/**
 * Luo halutun tyyppisen palikan
 */
CTetrominoFactory::create(CELL_TYPE type) {
    switch(type) {
        //inits
        case BLOCK_Z:
            break;
        default: return null;
    }
}

CTetrominoFactory::SUPPORTED[] = {
        BLOCK_Z,
        BLOCK_S,
        BLOCK_I,
        BLOCK_O,
        BLOCK_L,
        BLOCK_J,
        BLOCK_T
    };
