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
  settings = &SConfig::getInstance();
  m_creationCount = 0;
  srand((unsigned)time(0));
  m_normBlocks = settings->getValueAsBool("normal blocks");
  m_xiitBlocks = settings->getValueAsBool("xiit blocks");
  m_randomBlocks = settings->getValueAsBool("random blocks");
}

CTetrominoFactory::~CTetrominoFactory() {
}

/**
 * Luo uuden halutun tyyppisen tetrominon
 */
CTetromino* CTetrominoFactory::create(CELL_TYPE t) {
  m_creationCount++;

  if(t == BLOCK_RANDOM) {
    int x[4];
    int y[4];
    x[0] = 0; y[0] = 0;
    for(int i=1; i<4; i++) {
      x[i] = x[i-1] + (rand() % 3) - 1;
      y[i] = x[i-1] + (rand() % 3) - 1;
    }
    CELL_TYPE type;
    type = (CELL_TYPE)(rand() % 7 + 1);
    int r = 3;
    return new CTetromino(x, y, r, type);
  }

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
      int y[4] = {  0,  1,  0,  1 };
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
  if(m_randomBlocks)
    return create(BLOCK_RANDOM);

  // arvotaan uusi palikka
  int next = -1;
  if(m_xiitBlocks && !m_normBlocks)
    next = rand() % 4;
  else if(m_normBlocks && m_xiitBlocks)
    next = rand() % 11;
  else
    next = rand() % 7;

  switch(next) {
    case 0: return create(BLOCK_I);
    case 1: return create(BLOCK_O);
    case 2: return create(BLOCK_T);
    case 3: return create(BLOCK_S);
    case 4: return create(BLOCK_Z);
    case 5: return create(BLOCK_J);
    case 6: return create(BLOCK_L);

    case 7: return create(BLOCK_XIIT1);
    case 8: return create(BLOCK_XIIT2);
    case 9: return create(BLOCK_XIIT3);
    case 10: return create(BLOCK_XIIT4);
  }
  return create(BLOCK_I); // ei pitäisi tapahtua, vältetään vaan käännövaroitukset
}

