#ifndef __TETRISBOARD_H__
#define __TETRISBOARD_H__
/**
 * TetrisBoard.h
 *
 * $Id$
 * $HeadURL$
 *
 * Y-koordinaatit alkavat alhaalta, eli alin rivi on y==0
 */

class CTetrisBoard {

  public:
    TetrisBoard(void);

    TetrisBoard(const int cols, const int rows);

    ~TetrisBoard(void);

    const int* getWidth(void);
    const int* getHeight(void);
    int getRemovedLines(void);
    int getRemovedLinesLast(void);
    int getSlot(const int x, const int y);
    int setSlot(const int x, const int y, const int content); // returns old content
    bool isEmpty(void); // koko lauta
    bool isEmpty(const int x, const int y); // haluttu ruutu, offgrid = false, paitsi ylhäällä
    bool isEmpty(const int y); // rivi
    bool isFull(const int y); // rivi
    void reset(void);
    int clearFullLines(void);
    void notifyChange(void);
    bool registerBoardChangeListener(BoardChangeListener* bcl);
    bool unregisterBoardChangeListener(BoardChangeListener* bcl);

  private:
    int width;
    int height;
    int matrix[][]; // taulukko pelilaudasta, joko tyhjä (0 tai negat.), tai palikan tyypin vakion int-arvo
    int removedLines; // laskuri räjäytetyistä riveistä
    int removedLinesLast; // viimeksi räjähtäneet rivit
    BoardChangeListener changeListeners[];

    bool removeLine(int y); // siirrä yläpuolen rivejä yhdellä
}

#endif //__TETRISBOARD_H__
