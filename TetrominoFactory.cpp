/**
 * TetrominoFactory
 *
 * $Id$
 * $Revision$
 */

#include "TetrominoFactory.h"

CTetrominoFactory::CTetrominoFactory() {
  CELL_TYPE SUPPORTED[] = {
    BLOCK_Z,
    BLOCK_S,
    BLOCK_I,
    BLOCK_O,
    BLOCK_L,
    BLOCK_J,
    BLOCK_T
  };

}

/**
 * Luo halutun tyyppisen palikan
 */
CTetromino CTetrominoFactory::create(CELL_TYPE type) {
  switch(type) {
    //inits
    case BLOCK_Z:
      break;
    default:
      break;
  }
}

