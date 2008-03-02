#ifndef __CELLTYPE_H__
#define __CELLTYPE_H__
/**
 * CellType
 *
 * $Id: ESlotType.h 17 2008-03-02 21:07:19Z antsy $
 * $HeadURL: svn+ssh://zem@192.168.5.1_WTF-8_key/svn/tetris/ESlotType.h $
 *
 * Kentän matriisin yhden solun tila
 *
 */

enum CELL_TYPE
{
    /* ei kentällä */
    OFFGRID = -1,

    /*  */
    EMPTY = 0,

    /*
      ZZ
       ZZ
    */
    BLOCK_Z = 1,

    /*
       SS
      SS
    */
    BLOCK_S = 2,

    /*
      IIII
    */
    BLOCK_I = 3,

    /*
      OO
      OO
    */
    BLOCK_O = 4,

    /*
        L
      LLL
    */
    BLOCK_L = 5,

    /*
      J
      JJJ
    */
    BLOCK_J = 6,

    /*
       T
      TTT
    */
    BLOCK_T = 7,
};

#endif // __CELLTYPE_H__
