#ifndef __TETRISBOARD_H__
#define __TETRISBOARD_H__
/**
 * TetrisBoard.h
 *
 * $Id$
 * $Revision$
 *
 * Y-koordinaatit alkavat alhaalta, eli alin rivi on y==0
 */

#include "CellType.h"
#include "BoardChangeListener.h"

using namespace std;

class CTetrisBoard {

  public:

    CTetrisBoard(const int cols, const int rows);

    ~CTetrisBoard();

    /** Inline-getterit */

    inline int getWidth(void) {
        return m_width;
    }

    inline int getHeight(void) {
        return m_height;
    }

    inline int getRemovedLines(void) {
        return m_removedLines;
    }

    /** @return  viimeisellä siivouksella räjähtäneiden rivien määrä */
    inline int getRemovedLinesLast(void) {
        return m_removedLinesLast;
    }

    /** */
    CELL_TYPE getSlot(const int x, const int y);

    CELL_TYPE setSlot(const int x, const int y, const CELL_TYPE content); // returns old content

    bool isEmpty(void); // koko lauta

    bool isEmpty(const int x, const int y); // haluttu ruutu, offgrid = false, paitsi ylhäällä

    bool isEmpty(const int y); // rivi

    bool isFull(const int y); // rivi

    void reset(void);

    CELL_TYPE** getMatrix(void); // palauttaa koko matriksin

    int clearFullLines(void); // käytetään joka tickillä

    bool registerBoardChangeListener(VBoardChangeListener* bcl);

    bool unregisterBoardChangeListener(VBoardChangeListener* bcl);

    bool removeLine(int y); // siirrä yläpuolen rivejä yhdellä

  private:

    int m_width;
    int m_height;
    CELL_TYPE **m_matrix; // kentän sisältö CELL_TYPE vakioina
    int m_removedLines; // räjähtäneet rivit yhteensä
    int m_removedLinesLast; // viimeksi räjähtäneet rivit

    void resetLine(const int y); // asettaa rivin alkiot EMPTY:n mukaiseksi

//    vector<VBoard..
//    VBoardChangeListener changeListeners[4];
//    const int maxListeners = 4;
//    int numListeners;

    void notifyChange(void);

};

#endif //__TETRISBOARD_H__
