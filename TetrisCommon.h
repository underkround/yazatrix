#ifndef __TETRISCOMMON_H__
#define __TETRISCOMMON_H__

/**
 * TetrisCommon.h
 *
 * $Revision$
 * $Id$
 *
 * Pelille keskeisi‰ enumeja
 *
 */


/**
 * CELL_TYPE
 *
 * CELL_TYPE on laudan matrixin yksitt‰isen solun tyyppi.
 *
 * Nolla edustaa tyhj‰‰ solua.
 * Negatiiviset arvot ovat tyhji‰ soluja joissa on metadataa/merkityst‰ (esim ghost).
 * Positiiviset arvot ovat t‰ysi‰ soluja, jotka eroavat toisistaan l‰hinn‰
 * piirtov‰rins‰ perusteella.
 */
enum CELL_TYPE {
  // ghost palikka
  GHOST = -2,
  // ei kent‰ll‰, palautetaan jos kysyt‰‰n koordinaattia kent‰n matrixin ohi
  OFFGRID = -1,
  // tyhj‰
  EMPTY = 0,

  BLOCK_Z = 1,
  BLOCK_S = 2,
  BLOCK_I = 3,
  BLOCK_O = 4,
  BLOCK_L = 5,
  BLOCK_J = 6,
  BLOCK_T = 7,

  BLOCK_XIIT1,
  BLOCK_XIIT2,
  BLOCK_XIIT3,
  BLOCK_XIIT4,

  BLOCK_RANDOM

};


#endif // __TETRISCOMMON_H__
