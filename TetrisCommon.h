#ifndef __TETRISCOMMON_H__
#define __TETRISCOMMON_H__

/**
 * TetrisCommon.h
 *
 * $Revision$
 * $Id$
 *
 * Pelille keskeisiä enumeja
 *
 */

enum CELL_TYPE {
  /* ei kentällä */
  OFFGRID = -1,
  /*  */
  EMPTY = 0,
  /* ZZ
   *  ZZ
   */
  BLOCK_Z = 1,
  /*  SS
   * SS
   */
  BLOCK_S = 2,
  /* IIII
   */
  BLOCK_I = 3,
  /* OO
   * OO
   */
  BLOCK_O = 4,
  /*   L
   * LLL
   */
  BLOCK_L = 5,
  /* J
   * JJJ
   */
  BLOCK_J = 6,
  /*  T
   * TTT
   */
  BLOCK_T = 7,

  BLOCK_XIIT1,
  BLOCK_XIIT2,
  BLOCK_XIIT3,
  BLOCK_XIIT4,
};


#endif // __TETRISCOMMON_H__
