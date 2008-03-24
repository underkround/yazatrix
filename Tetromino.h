#ifndef __TETROMINO_H__
#define __TETROMINO_H__

/**
 * Tetromino.h
 *
 * $Revision$
 * $Id$
 *
 * Tetromino is controllable figure that can be attached to one
 * TetrisBoard at the time.
 *
 * Tetromino has shape defined by maximum of four coordinates
 * relative to it's origo. Tetromino can have 90 degree rotations
 * from 1 to 4 (0..3 in code).
 *
 * Tetromino is capable of attaching itself to TetrisBoard when
 * there is no collapse. When attached, tetromino can be rotated
 * clockwise or counterclockwise or moved to left, right, up, down.
 * when new position is not colliding with anything.
 *
 * Tetromino detects collides by quering TetrisBoard's cells in it's
 * possible new position. If there is no collision, it can remove
 * itself from current position and write it's type to new position
 * in board.
 *
 * Responsibilities:
 *  - has it's shape and rotations, can rotate itself
 *  - can attach to and detach from TetrisBoards
 *    - attach can be made if there is no collision
 *    - detach can be clean -> tetrominoe writes EMPTY to it's former
 *      location
 *  - can detect collisions in TetrisBoard
 *  - can be rotated and moved in board, if no collision
 *  - knows when it has landed (can't move down)
 *  - can write ghost marks to maximum location it could drop (can be
 *    toggled on/off)
 *
 */

#include "TetrisCommon.h"
#include "TetrisBoard.h"

class CTetromino {

public:

  /**
   * Constructor that defines the Tetromino's form.
   *
   * @param cellCoordsX   4 origo-relative x-coordinates defining the shape
   * @param cellCoordsY   4 origo-relative y-coordinates defining the shape
   * @param maxRotation   maximum 90degree rotations from 0 (value of 0..3)
   * @param type          CELL_TYPE that is written to it's location on board
   */
  CTetromino(int cellCoordsX[4], int cellCoordsY[4], int maxRotation, CELL_TYPE type);

  ~CTetromino(void);

  // ================= METODIT =============================================

  /**
   * Sets the ghost marking on/off. If ghost is on, ghost cell-type is written
   * to location that tetromino would drop if hard-dropped.
   *
   * @param value   true, if ghost piece is used
   * @since Revision 115
'   */
  inline void setGhost(bool value) {
    m_ghost = value;
  }

  /**
   * Rotates tetrominoe clockwise, if possible. Tests collision in current
   * attached board before rotation is made. If Tetromino is not attached
   * to any board, nothing is done.
   */
  bool rotateRight(void);

  /**
   * Rotates tetrominoe counterclockwise, if possible. Tests collision in current
   * attached board before rotation is made. If Tetromino is not attached
   * to any board, nothing is done.
   */
  bool rotateLeft(void);

  /**
   * Checks if tetromino is attached to instance of TetrisBoard.
   *
   * @return    true, it tetromino is attached to TetrisBoard
   */
  bool isAttached(void);

  /**
   * Attaches Tetromino to TetrisBoard. While attaching, Tetromino checks
   * that attaching could be done eg. there is no collision in board.
   * In case of collision, no attach is done and false is returned.
   *
   * If attach is successful, Tetromino will position it's origo to horizontal
   * center of board, and vertically to the top row of board.
   *
   * If Tetromino is already attached to another board, clean detach from it
   * is made.
   *
   * @param targetBoard   instance of TetrisBoard that Tetromino needs to attach
   * @return              true, if attaching was possible (no collision)
   */
  bool attach(CTetrisBoard *targetBoard);

  /**
   * @see attach(CTetrisBoard)
   *
   * Vertical attach position is top row of board plus offsetY.
   *
   * @see attach(CTetrisBoard)
   * @param targetBoard   instance of TetrisBoard that Tetromino needs to attach
   * @param offsetY       offset from top row of TetrisBoard (negative shifts downwards)
   * @return              true, if attaching was possible (no collision)
   */
  bool attach(CTetrisBoard *targetBoard, int offsetY);

  /**
   * @see attach(CTetrisBoard)
   *
   * Vertical attach position is top row of board plus offsetY.
   * Horizontal attach position is board center plus offsetX.
   *
   * @param targetBoard   instance of TetrisBoard that Tetromino needs to attach
   * @param offsetY       offset from top row of TetrisBoard (negative shifts downwards)
   * @return              true, if attaching was possible (no collision)
   */
  bool attach(CTetrisBoard *targetBoard, int offsetX, int offsetY);

  /**
   * Detach from current TetrisBoard. If clear flag is set true, makes clean detach
   * (writes EMPTY to current cells in TetrisBoard). If clear is set false,
   * Tetromino's cells in board are left with Tetromino's type.
   *
   * @param clear         if true, writes EMPTY to it's location
   */
  bool detach(bool clear);

  /**
   * Make no-clean detach from current TetrisBoard.
   *
   * @see detach(bool)
   */
  bool detach();

  /**
   * Try to move Tetromino one cell. If there would be
   * collision in new coordinates in board, nothing is done.
   */
  bool moveLeft(void);
  bool moveRight(void);
  bool moveDown(void);

  /**
   * Try to move Tetromino by given count of cells.
   * If there would be collision in new coordinates in board,
   * nothing is done.
   *
   * @param n     number of cells to move
   */
  bool moveUp(int n);
  bool moveDown(int n);

  /**
   * Move Tetromino down until next move would collide.
   */
  bool drop(void);

  /**
   * Check if Tetromino has landed. Tetromino has landed if next move
   * downwards would collide.
   * Tetromino is also [TODO: tulkittu laskeutuneeksi jos] it's not attached
   * to any TetrisBoard.
   *
   * @return    true, if next move downwards would collide, or not detached
   */
  bool hasLanded(void);

  /**
   * Check if Tetromino is attached to TetrisBoard and all of it's cells are
   * visible in board (cells can go over board from top).
   *
   * @return    true, if all cells are inside TetrisBoard
   */
  bool isFullyVisible(void);

// ===========================================================================
// PRIVATE MEMBERS

// TODO: lontoonna

private:

  /**
   * Kentt� (TetrisBoard), johon t�m� palikka on kiinnittyneen�.
   * NULL, jos palikka ei ole kiinni miss��n kent�ss�.
   */
  CTetrisBoard *board;

  /**
   * palikan oma tyyppi, jota se piirt�� pelikentt��n
   * omiin koordinaatteihinsa
   */
  CELL_TYPE m_type;
  static const CELL_TYPE m_ghostType = GHOST;

  /**
   * Palikan koordinaatit nykyisess� kent�ss��n.
   * Palikka tarkistaa kentt��n kiinnittyess��n, ett� sen sijainti
   * koordinaateissa on sallittu, tai kiinnittymist� ei tapahdu.
   */
  int m_x;
  int m_y;

  /**
   * The form of the tetromino. 4 pairs of coordinates relative to
   * Tetromino's origo defining the cells it has in rotation 0.
   */
  int m_cellCoordsX[4];
  int m_cellCoordsY[4];

  /**
   * Current 90degree rotation of Tetromino. Value of 0..3.
   */
  int m_rotation;

  /**
   * Palikan suurin sallittu rotaatio (0 -> m_rotationMax)
   * Asetetaan constructorissa.
   */
  int m_rotationMax;

  bool m_ghost;
  bool m_ghostOnBoard; // kertoo removeGhostFromBoardille onko boardilla ghostia joka poistettaisiin
  int m_gy;

// ===========================================================================
// PRIVATE METHODS

private:

  /**
   * Asettaa rotaaion r jos mahdollista
   * @return  asettamisen onnistuminen
   */
  bool setRotation(int r);

  /**
   * Testaa voiko palikka olla laudalla annetuissa koordinaateissa,
   * annetulla orientaatiolla.
   *
   * @return  false, jos joku palikan ruuduista ei ole tyhj� laudalla,
   *          tai jos palikka menee ohi laudasta sivusuunnassa (tai pohjasta)
   */
  bool canMoveTo(const int x, const int y, const int rotation);

  /** Yll�oleva omalla laudalla */
  bool canMoveTo(const int x, const int y, const int rotation, CTetrisBoard *targetBoard);

  /**
   * @return  nykyinen rotaatio (arvo v�lilt� 0..3)
   */
  inline int getRotation() {
      return m_rotation;
  }

  /**
   * @return  nykyisest� seuraava rotaatio (py�r�ytett�ess� my�t�p�iv��n)
   *          arvo v�lilt� 0..3
   */
  inline int getNextRotation() {
      return (m_rotation+1 > m_rotationMax) ? 0 : m_rotation+1;
  }

  /**
   * @return  nykyisest� edellinen rotaatio (py�r�ytett�ess� vastap�iv��n)
   *          arvo v�lilt� 0..3
   */
  inline int getPreviousRotation() {
      return (m_rotation-1 < 0) ? m_rotationMax : m_rotation-1;
  }

  /**
   * Palauttaa halutun rotaation relatiivisen koordinaatin
   */
  int getRelativeX(const int x, const int rotation);
  int getRelativeY(const int y, const int rotation);

  /** Laske mik� on boardin keski-x -koordinaatti */
  int getBoardCenterX(CTetrisBoard *targetBoard);

  /** Testaa onko boardin koordinaatti {x,y} t�m�n palikan */
  bool containsBoardCoord(int x, int y);

  /**
   * "Polttaa" palikan pelilaudan kentt��n, eli vaihtaa omat ruutunsa
   * pelilaudassa oman tyyppins� mukaisiksi.
   */
  void insertToBoard();
  void insertGhostToBoard();

  /**
   * Poistaa itsens� pelilaudalta, eli kirjoittaa tyhj�n ruudun arvon
   * jokaiseen ruutuunsa pelilaudassa
   */
  void removeFromBoard();
  void removeGhostFromBoard();

};

#endif //__TETROMINO_H__
