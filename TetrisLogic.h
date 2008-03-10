#ifndef __TETRISLOGIC_H__
#define __TETRISLOGIC_H__

/**
 * TetrisLogic.h
 *
 * $Revision$
 * $Id$
 *
 * Pit‰‰ sis‰ll‰‰n / vastaa luonnista ja tuhoamisesta:
 *  - TetrisBoard gameBoard
 *  - Tetromino currentTetromino
 *  - Tetromino[] nextTetrominoes
 *  - Timer -> logiikka rekisterˆityy timerille tick-kuuntelijaksi
 *  -
 */

#include "CommandListener.h"
#include "TickListener.h"
#include "TetrisBoard.h"
#include "Tetromino.h"
#include "TetrisCommon.h"
#include "TetrominoFactory.h"

#define PREVIEW_TETROMINOES 3
#define GAMEBOARD_WIDTH 12
#define GAMEBOARD_HEIGHT 20
#define PREVIEWBOARD_WIDTH 4
#define PREVIEWBOARD_HEIGHT 20

class CTetrisLogic : public VCommandListener, public VTickListener {

public:

  CTetrisLogic();

  virtual ~CTetrisLogic();

  /**
   * reset()
   *
   * @deprecated  revision 72 j‰lkeen logiikkaa ei en‰‰ voi resetoida, luonnit
   *              hoidetaan konstruktorissa ja tuhoamiset destruktorissa.
   *              Uuden pelin aloittamiseksi luodaan kokonaan uusi TetrisLogic.
   */
//  void reset(void);

  /**
   * run()
   *
   * Pelisilmukka, jossa itse pelaaminen tapahtuu. Logiikka hoitaa
   * pelisilmukassa palikoiden luomisen ja tuhoamisen
   * ...
   */
  void run(void);

  /**
   * getGameBoard()
   *
   * @return    TetrisBoard, jossa peli tapahtuu
   */
  inline CTetrisBoard* getGameBoard(void) {
    return m_gameBoard;
  }

  /**
   * getPreviewBoard()
   *
   * @return    TetrisBoard, jossa preview-palikat ovat kiinni
   */
  inline CTetrisBoard* getPreviewBoard(void) {
    return m_previewBoard;
  }

  /**
   * getCurrentTetromino()
   *
   * @deprecated  Kukaan ei itseasiassa tarvitse nykyist‰ palikkaa, koska
   *              sen ohjaaminen tapahtuu CommandListener -interfacen kautta.
   */
//  inline CTetromino   getCurrentTetromino(void) { return *m_currentTetromino; }

  /**
   * handleKeyCommand()
   *
   * @see CommandListener.h
   */
  virtual void handleCommand(VCommandListener::COMMAND cmd);


  /**
   * tick()
   *
   * Toiminta timerin antaman tickin aikana
   * Tickiss‰ logiikka:
   *  - yritt‰‰ tiputtaa nykyist‰ palikkaa
   *    - jos nykyinen palikka ei voi en‰‰n tippua (block->hasLanded = true)
   *      - nykyinen palikka tuhotaan
   *      - preview-palikoista seuraava siirret‰‰n nykyiseksi
   *      - luodaan uusi preview-palikka poistetun tilalle
   *      - nostetaan j‰ljellej‰‰neiden preview-palikoiden sijaintia
   *        preview-boardissa
   *      - liitet‰‰n uusi preview-palikka preview-lautaan
   *  - k‰skee lautaa tyhj‰‰m‰‰n t‰ydet rivit
   *  - mik‰li uusi palikka on otettu k‰yttˆˆn, lis‰t‰‰n se (block->attach())
   *    (nimenomaan vasta t‰ysien rivien tyhjennyksen j‰lkeen??)
   *  - s‰‰det‰‰n tickin timeria laudan r‰j‰ytettyjen rivien perusteella
   *    tai peliss‰ olleiden palikoiden mukaan
   */
  int handleTick(void);

// ==================== PRIVATE ====================

private:

  // r‰j‰ytetyt rivit saadaan boardilta kysym‰ll‰
  bool            m_gameOver;
  bool            m_moveLock;         // true = nykyist‰ palikkaa ei voida liikuttaa
  int             m_tetrominoCounter; // gameBoardissa olleiden palikoiden m‰‰r‰
  CTetrisBoard    *m_gameBoard;        // pelilauta, jossa pelaaminen tapahtuu
  CTetrisBoard    *m_previewBoard;     // previewBoard, jossa n‰kyy seuraavat palikat
  CTetromino      *m_currentTetromino; // nykyinen palikka, kiinnitetty pelilautaan
  CTetromino      *m_previewTetrominoes[PREVIEW_TETROMINOES];
  CTetrominoFactory *m_factory;
  int             m_previewSpacingY;
  int             m_previewCount;
//  CTetrisTimer  m_timer; // timer, joka osaa kutsua t‰m‰n luokan tick():‰ ja jota voi s‰‰t‰‰

  /**
   * rotateTetrominoes()
   *
   * Pyˆr‰ytt‰‰ palikkajonoa yhdell‰ eteenp‰in:
   * - Tuhoaa nykyisen pelipalikan (currentTetromino), ja ottaa
   *   previewTetromino-taulukosta seuraavaksi vuorossa olevan nykyiseksi.
   * - Irrottaa seuraavaksi vuorossa olevan preview-palikan previewBoardista
   * - Kiinnitt‰‰ uuden nykyisen gameBoardiin
   * - Nostaa j‰ljelle j‰‰neiden preview-palikoiden vuoronumeroa yhdell‰.
   * - Nostaa j‰ljelle j‰‰neiden preview-palikoiden sijaintia previewBoardissa
   * - Luo preview-taulun loppuun uuden palikan.
   * - Kiinnitt‰‰ preview-taulun loppuun luodun palikan previewBoardiin
   *   omalle paikalleen
   */
  void rotateTetrominoes(void);

};

#endif // __TETRISLOGIC_H__
