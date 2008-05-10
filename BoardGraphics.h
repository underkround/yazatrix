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
#include "Config.h"
#include "GameStateListener.h"

class CBoardGraphics : public VBoardChangeListener, public VPanel, public VGameStateListener {

public:
  /**
   * myBoard = board jonka t‰m‰ luokka piirt‰‰
   * offsetX = mist‰ koordinaatista t‰m‰ alkaa piirt‰‰
   * offsetY = --||--
   *
   */
  CBoardGraphics(CTetrisBoard *myBoard, int offsetX, int offsetY);

  virtual ~CBoardGraphics();

  /** @see BoardChangeListener.h */
  virtual void handleFreshBoard();
  virtual void handleChangeInLines(const int *changedLines[], const int numLines);
  virtual void handleChangeInCoord(const int x, const int y, const CELL_TYPE ct);
  virtual void handleChangeInStats(const int score, const int reml, const int remll, const int level);

  /** @see GameStateListener.h */
  virtual void handleGameState(VGameStateListener::GAMESTATE state);

private:

  CTetrisBoard *board;    // t‰m‰ ei ole vastuussa boardin tuhoamisesta!
  SGraphics *g;           // eik‰ myˆsk‰‰n grafiikan tuhoamisesta!
  SConfig *settings;
  int m_squareWidth;
  int m_squareHeight;
  bool m_visible;

  void drawCell(const int x, const int y, CELL_TYPE ct); // x ja y ovat boardin koordinaatteja, eiv‰t ruudun

  SGraphics::GCOLOR getCellTypeColor(const int x, const int y, const CELL_TYPE ct);

  char getCellTypeChar(const int x, const int y, const CELL_TYPE ct);

};

#endif // __BOARDGRAPHICS_H__
