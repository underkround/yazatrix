/**
 * TetrominoFactory.cpp
 *
 * $Revision$
 * $Id$
 *
 * @see TetrominoFactory.h
 */

#include "TetrominoFactory.h"
#include <ctime>
#include <cstdlib>

CTetrominoFactory::CTetrominoFactory() {
  // todo: alusta lastlog jne
  m_creationCount = 0;
  srand((unsigned)time(0));
  m_xiitBlocks = false;
}

CTetrominoFactory::~CTetrominoFactory() {
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
      int y[4] = {  0,  1,  0,  0 };
      return new CTetromino(x, y, 3, BLOCK_T);
      break;
    }

    /** max rot = 1
     *  ##
     * #X
     */
    case BLOCK_S: {
      int x[] = { -1,  0,  0,  1 };
      int y[] = {  0,  0,  1,  1 };
      return new CTetromino(x, y, 1, BLOCK_S);
      break;
    }

    /** max rot = 1
     * ##
     *  X#
     */
    case BLOCK_Z: {
      int x[] = { -1,  0,  0,  1 };
      int y[] = {  1,  1,  0,  0 };
      return new CTetromino(x, y, 1, BLOCK_Z);
      break;
    }

    /** max rot = 3
     * #
     * #X#
     */
    case BLOCK_J: {
      int x[] = { -1, -1,  0,  1 };
      int y[] = {  1,  0,  0,  0 };
      return new CTetromino(x, y, 3, BLOCK_J);
      break;
    }

    /** max rot = 3
     *   #
     * #X#
     */
    case BLOCK_L: {
      int x[] = { -1,  0,  1,  1 };
      int y[] = {  0,  0,  0,  1 };
      return new CTetromino(x, y, 3, BLOCK_L);
      break;
    }

    case BLOCK_XIIT1: {
      int x[] = { -1, 1, 1, -1 };
      int y[] = { -1, 0, 1,  2 };
      return new CTetromino(x, y, 3, BLOCK_L);
    }
    case BLOCK_XIIT2: {
      int x[] = { -1, 0, 0, 2 };
      int y[] = { 0, -1,-1,  2 };
      return new CTetromino(x, y, 3, BLOCK_Z);
    }
    case BLOCK_XIIT3: {
      int x[] = { -1, 0, 1, 2 };
      int y[] = { 1, 0, -1, 0 };
      return new CTetromino(x, y, 3, BLOCK_O);
    }
    case BLOCK_XIIT4: {
      int x[] = { -1,-1, 1, 1 };
      int y[] = { -1, 1,-1, 1 };
      return new CTetromino(x, y, 0, BLOCK_I);
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
  // arvotaan uusi palikka
  if(m_xiitBlocks) {
    int next = rand() % 4;
    switch(next) {
      case 0: return create(BLOCK_XIIT1);
      case 1: return create(BLOCK_XIIT2);
      case 2: return create(BLOCK_XIIT3);
      case 3: return create(BLOCK_XIIT4);
    }
  } else {
    int next = rand() % 7;
    switch(next) {
      case 0: return create(BLOCK_I);
      case 1: return create(BLOCK_O);
      case 2: return create(BLOCK_T);
      case 3: return create(BLOCK_S);
      case 4: return create(BLOCK_Z);
      case 5: return create(BLOCK_J);
      case 6: return create(BLOCK_L);
    }
  }
  return create(BLOCK_I); // ei pitäisi tapahtua, vältetään vaan käännövaroitukset
}

