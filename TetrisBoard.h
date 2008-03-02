#ifndef __TETRISBOARD_H__
#define __TETRISBOARD_H__
/**
 * TetrisBoard.h
 *
 * $Id$
 *
 * Y-koordinaatit alkavat alhaalta, eli alin rivi on y==0
 */

class CTetrisBoard {

  public:
//    CTetrisBoard(void);

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
    int getSlot(const int x, const int y);
    int setSlot(const int x, const int y, const int content); // returns old content
    bool isEmpty(void); // koko lauta
    bool isEmpty(const int x, const int y); // haluttu ruutu, offgrid = false, paitsi ylhäällä
    bool isEmpty(const int y); // rivi
    bool isFull(const int y); // rivi
    void reset(void);
//    int[][] getMatrix(void); // palauttaa koko matriksin
    int clearFullLines(void); // käytetään joka tickillä
//    bool registerBoardChangeListener(BoardChangeListener* bcl);
//    bool unregisterBoardChangeListener(BoardChangeListener* bcl);



  private:
    int m_width;
    int m_height;
    int **m_matrix;
//    int m_matrix[][]; // taulukko pelilaudasta, joko tyhjä (0 tai negat.), tai palikan tyypin vakion int-arvo
    int m_removedLines; // laskuri räjäytetyistä riveistä
    int m_removedLinesLast; // viimeksi räjähtäneet rivit
//    BoardChangeListener changeListeners[];

    void notifyChange(void);
    bool removeLine(int y); // siirrä yläpuolen rivejä yhdellä
};

#endif //__TETRISBOARD_H__
