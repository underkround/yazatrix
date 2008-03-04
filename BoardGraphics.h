#ifndef __BOARDGRAPHICS_H__
#define __BOARDGRAPHICS_H__

/**
 * CBoardGraphics objekti ottaa luonnissa itselleen TetrisBoard-objektin, jota
 * se mallintaa ruudulle.
 *
 * Piirto tapahtuu Graphics-luokkaa k‰ytt‰en.
 *
 * T‰m‰n tulee rekisterˆity‰ omalle TetrisBoardilleen changeListeneriksi:
 * m_board->registerBoardChangeListener(this);
 * jonka j‰lkeen t‰m‰ saa tiedon kun laudalla muuttuu joku, ja osaa piirt‰‰
 * muutoksen.
 *
 */

#include "BoardChangeListener.h"
#include "TetrisBoard.h"

class CBoardGraphics : VBoardChangeListener {

  public:
    /**
     * myBoard = board jonka t‰m‰ luokka piirt‰‰
     * g = Graphics jolla t‰m‰ piirt‰‰ ko. boardin
     * offsetX = mist‰ koordinaatista t‰m‰ alkaa piirt‰‰
     * offsetY = --||--
     *
     */
    CBoardGraphics(CTetrisBoard *myBoard, Graphics *g, int offsetX, int offsetY);

    ~CBoardGraphics();

    void setBorder(bool visible); // borderit p‰‰ll‰? jos moisia jaksaa tehd‰. lis‰‰ tietty leveytt‰ ja korkeutta +2

    void setLocation(int x, int y); // mihin kohtaan ruutua piirt‰‰ itsens‰

    // katso BoardChangeListener n‰iden tarkempaan tarkotukseen
    virtual void handleFreshBoard();
    virtual void handleChangeInCoords(int *changedCoordsX[], int *changedCoordsY[], int numCoords);
    virtual void handleChangeInLines(int *changedLines[], int numLines);
    virtual void handleChangeInCoord(int x, int y);


  private:

    CTetrisBoard *board; // t‰m‰ ei ole vastuussa boardin tuhoamisesta!
    Graphics *g; // eik‰ myˆsk‰‰n grafiikan tuhoamisesta!
    int m_x; //
    int m_y; // koordinaatit joista t‰m‰ alkaa piirt‰‰ itse‰‰n
    int m_width;  // montako merkki‰ vied‰‰n tilaa
    int m_height; // (voi olla eri kun laudankoko esim jos on borderit)

};

#endif // __BOARDGRAPHICS_H__
