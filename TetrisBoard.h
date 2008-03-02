#ifndef __TETRISBOARD_H__
#define __TETRISBOARD_H__
/**
 * TetrisBoard
 *
 * $Id$
 * $HeadURL$
 *
 * Y-koordinaatit alkavat alhaalta, eli alin rivi on y==0
 */

 #define __X__ 16
 #define __Y__ 20

class TetrisBoard {
  public:
    TetrisBoard(void);
    ~TetrisBoard(void);

    int getWidth();
    int getHeight();
    int getRemovedLines();
    int getRemovedLinesLast();
    int getSlot(int x, int y);
    int setSlot(int x, int y, int content); // returns old content
    bool isEmpty(); // koko lauta
    bool isEmpty(int x, int y); // haluttu ruutu, offgrid = false, paitsi ylhäällä
    bool isEmpty(int y); // rivi
    bool isFull(int y); // rivi
    void reset();
    int clearFullLines();
    void notifyChange();
    bool registerBoardChangeListener(BoardChangeListener bcl);
    bool unregisterBoardChangeListener(BoardChangeListener bcl);
  private:
    int width;
    int height;
    int matrix[__Y__][__X__]; // taulukko pelilaudasta, joko tyhjä (0 tai negat.), tai palikan tyypin vakion int-arvo
    int removedLines; // laskuri räjäytetyistä riveistä
    int removedLinesLast; // viimeksi räjähtäneet rivit
    BoardChangeListener[] changeListeners;

    bool removeLine(int y); // siirrä yläpuolen rivejä yhdellä
}
#endif //__TETRISBOARD_H__
