/**
 * TetrominoFactory
 *
 * $Id$
 * $Revision$
 */

#include "TetrominoFactory.h"

CTetrominoFactory::CTetrominoFactory() {
  // todo: alusta lastlog jne
  m_creationCount = 0;
}


/**
 * Luo uuden halutun tyyppisen tetrominon
 */
CTetromino* CTetrominoFactory::create(CELL_TYPE t) {
  m_creationCount++;
  // kommenteissa: X = tetrominon origo
  switch(t) {

    /** max rot = 1
     *
     * #X##
     */
    case BLOCK_I: {
      int x[4] = { -1,  0,  1,  2 };
      int y[4] = {  0,  0,  0,  0 };
      return new CTetromino(x, y, 1, BLOCK_I);
      break;
    }

    /** max rot = 0
     * ##
     * #X
     */
    case BLOCK_O: {
      int x[4] = { -1, -1,  0,  0 };
      int y[4] = {  0, -1,  0, -1 };
      return new CTetromino(x, y, 0, BLOCK_O);
      break;
    }

    /** max rot = 3
     *  #
     * #X#
     */
    case BLOCK_T: {
      int x[4] = { -1,  0,  0,  1 };
      int y[4] = {  0, -1,  0,  0 };
      return new CTetromino(x, y, 3, BLOCK_T);
      break;
    }

    /** max rot = 1
     *  ##
     * #X
     */
    case BLOCK_S: {
      int x[] = { -1,  0,  0,  1 };
      int y[] = {  0,  0, -1, -1 };
      return new CTetromino(x, y, 1, BLOCK_S);
      break;
    }

    /** max rot = 1
     * ##
     *  X#
     */
    case BLOCK_Z: {
      int x[] = { -1,  0,  0,  1 };
      int y[] = { -1, -1,  0,  1 };
      return new CTetromino(x, y, 1, BLOCK_Z);
      break;
    }

    /** max rot = 3
     * #
     * #X#
     */
    case BLOCK_J: {
      int x[] = { -1, -1,  0,  1 };
      int y[] = { -1,  0,  0,  0 };
      return new CTetromino(x, y, 3, BLOCK_J);
      break;
    }

    /** max rot = 3
     *   #
     * #X#
     */
    case BLOCK_L: {
      int x[] = { -1,  0,  1,  1 };
      int y[] = {  0,  0,  0, -1 };
      return new CTetromino(x, y, 3, BLOCK_L);
      break;
    }

    default: {
      // jos tyyppi ei ole tuettu, palautetaan random
      return createRandom();
      break;
    }

  }
}


/**
 * Palauta random palikka
 * TODO: random =) ja joku logiikka sille
 */
CTetromino* CTetrominoFactory::createRandom() {
  return create(BLOCK_T);
}

