#ifndef __TETRISCOMMON_H__
#define __TETRISCOMMON_H__
/**
 * TetrisCommon
 *
 * $Id$
 *
 * Pelille keskeisi‰ enumeja
 *
 */

enum CELL_TYPE {
  /* ei kent‰ll‰ */
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
};

enum COMMAND {
  GAME_COMMAND_LEFT,        // liikuttaa palikkaa vasemmalle
  GAME_COMMAND_RIGHT,       // liikuttaa palikkaa oikealle
  GAME_COMMAND_ROTATE_CW,   // k‰‰nt‰‰ palikkaa myˆt‰p‰iv‰‰n
  GAME_COMMAND_ROTATE_CCW,  // k‰‰nt‰‰ palikkaa vastap‰iv‰‰n
  GAME_COMMAND_SOFTDROP,    // tiputtaa yhdell‰ rivill‰, resetoi tickin
  GAME_COMMAND_HARDDROP,    // tiputtaa palikan alas, resetoi tickin
//  GAME_COMMAND_SWAP,        // vaihtaa nykyisen ja seuraavan palikan kesken‰‰n (vain kerran)
  GAME_COMMAND_QUIT         // lopettaa nykyisen pelin
};

#endif // __TETRISCOMMON_H__
