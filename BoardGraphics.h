#ifndef __BOARDGRAPHICS_H__
#define __BOARDGRAPHICS_H__

/**
 * BoardGraphics.h
 *
 * $Revision$
 * $Id$
 *
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
#include "Panel.h"
#include "TetrisBoard.h"
#include "Graphics.h"

class CBoardGraphics : public VBoardChangeListener, public VPanel {

public:
  /**
   * myBoard = board jonka t‰m‰ luokka piirt‰‰
   * g = Graphics jolla t‰m‰ piirt‰‰ ko. boardin
   * offsetX = mist‰ koordinaatista t‰m‰ alkaa piirt‰‰
   * offsetY = --||--
   *
   */
//  CBoardGraphics(CTetrisBoard *myBoard, SGraphics *graphics, int offsetX, int offsetY);
  CBoardGraphics(CTetrisBoard *myBoard, int offsetX, int offsetY);

  virtual ~CBoardGraphics();

  void setBorder(bool visible); // borderit p‰‰ll‰? jos moisia jaksaa tehd‰. lis‰‰ tietty leveytt‰ ja korkeutta +2

  void setBorderStyle(SGraphics::BORDER_STYLE bs);

  void setLocation(const int x, const int y); // mihin kohtaan ruutua piirt‰‰ itsens‰

  inline virtual int getX(void) {
    return m_x;
  }

  inline virtual int getY(void) {
    return m_y;
  }

  inline virtual void setX(int newX) {
    m_x = newX;
  }

  inline virtual void setY(int newY) {
    m_y = newY;
  }

  inline virtual int getWidth(void) {
    if(m_width) return m_width + 2;
    else return m_width;
  };

  inline virtual int getHeight(void) {
    if(m_borders) return m_height + 2;
    else return m_height;
  };

  /** Tarkemmat selitykset @ BoardChangeListener.h */
  virtual void handleFreshBoard();

  virtual void handleChangeInLines(const int *changedLines[], const int numLines);

  virtual void handleChangeInCoord(const int x, const int y, const CELL_TYPE ct);

private:

  CTetrisBoard *board;    // t‰m‰ ei ole vastuussa boardin tuhoamisesta!
  SGraphics *g;           // eik‰ myˆsk‰‰n grafiikan tuhoamisesta!
  bool m_borders;         // n‰ytet‰‰nkˆ borderit
  SGraphics::BORDER_STYLE m_borderStyle; // borderin tyyli
  int m_x;                //
  int m_y;                // koordinaatit joista t‰m‰ alkaa piirt‰‰ itse‰‰n
  int m_width;            // montako merkki‰ vied‰‰n tilaa
  int m_height;           // (voi olla eri kun laudankoko esim jos on borderit)
  int m_squareWidth;
  int m_squareHeight;

  void drawCell(const int x, const int y, CELL_TYPE ct); // x ja y ovat boardin koordinaatteja, eiv‰t ruudun

  void drawBorder();

  SGraphics::GCOLOR getCellTypeColor(CELL_TYPE ct);

  char getCellTypeChar(CELL_TYPE ct);

};

#endif // __BOARDGRAPHICS_H__
