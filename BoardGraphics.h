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
#include "Graphics.h"

class CBoardGraphics : VBoardChangeListener {

public:
  /**
   * myBoard = board jonka t‰m‰ luokka piirt‰‰
   * g = Graphics jolla t‰m‰ piirt‰‰ ko. boardin
   * offsetX = mist‰ koordinaatista t‰m‰ alkaa piirt‰‰
   * offsetY = --||--
   *
   */
  CBoardGraphics(CTetrisBoard *myBoard, CGraphics *graphics, int offsetX, int offsetY);

  virtual ~CBoardGraphics();

  void setBorder(bool visible); // borderit p‰‰ll‰? jos moisia jaksaa tehd‰. lis‰‰ tietty leveytt‰ ja korkeutta +2

  void setBorderStyle(CGraphics::BORDER_STYLE bs);

  void setLocation(int x, int y); // mihin kohtaan ruutua piirt‰‰ itsens‰

  inline int getWidth() {
    if(m_width) return m_width + 2;
    else return m_width;
  };

  inline int getHeight() {
    if(m_borders) return m_height + 2;
    else return m_height;
  };

  // katso BoardChangeListener n‰iden tarkempaan tarkotukseen
  virtual void handleFreshBoard();
  virtual void handleChangeInCoords(int *changedCoordsX[], int *changedCoordsY[], int numCoords);
  virtual void handleChangeInLines(int *changedLines[], int numLines);
  virtual void handleChangeInCoord(int x, int y);

private:

  CTetrisBoard *board; // t‰m‰ ei ole vastuussa boardin tuhoamisesta!
  CGraphics *g; // eik‰ myˆsk‰‰n grafiikan tuhoamisesta!
  bool m_borders; // n‰ytet‰‰nkˆ borderit
  CGraphics::BORDER_STYLE m_borderStyle; // borderin tyyli
  int m_x; //
  int m_y; // koordinaatit joista t‰m‰ alkaa piirt‰‰ itse‰‰n
  int m_width;  // montako merkki‰ vied‰‰n tilaa
  int m_height; // (voi olla eri kun laudankoko esim jos on borderit)

  void drawCell(int x, int y, CELL_TYPE ct); // x ja y ovat boardin koordinaatteja, eiv‰t ruudun

  void drawBorder();

  CGraphics::GCOLOR getCellTypeColor(CELL_TYPE ct);

};

#endif // __BOARDGRAPHICS_H__
