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
#include "Observable.h"
#include "TickListener.h"
#include "TickTask.h"
#include "TetrisStats.h"
#include "TetrisBoard.h"
#include "Tetromino.h"
#include "TetrisCommon.h"
#include "TetrominoFactory.h"
#include "GameStateListener.h"

//#define PREVIEW_TETROMINOES 3
#define GAMEBOARD_WIDTH 12
#define GAMEBOARD_HEIGHT 20
//#define PREVIEWBOARD_WIDTH 4
//#define PREVIEWBOARD_HEIGHT 20 //jahas t‰t‰ ei k‰ytet‰ miss‰‰n

class CTetrisLogic : public VObservable<VGameStateListener>, public VCommandListener, public VTickListener {

friend class VObservable<VGameStateListener>;

public:

  CTetrisLogic();

  CTetrisLogic(const int gameboardWidth, const int gameboardHeight);

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
   * start()
   *
   * Asettaa pelin ajotilaan.
   */
  bool start(void);

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
   * getStats()
   *
   * @return    TetrisStats -luokka, joka tiet‰‰ pelitilanteen (statsit)
   */
  inline CTetrisStats* getStats(void) {
    return m_stats;
  }

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

  inline bool isRunning() { return m_running; }

// ==================== PRIVATE ====================

private:

  SConfig *settings;
  int             m_previewBoardSize;
  //int             m_previewBoardHeight;
  int             m_previewBoardWidth;

  // r‰j‰ytetyt rivit saadaan boardilta kysym‰ll‰
  CTetrisBoard    *m_gameBoard;        // pelilauta, jossa pelaaminen tapahtuu
  CTetrisBoard    *m_previewBoard;     // previewBoard, jossa n‰kyy seuraavat palikat
  CTetromino      *m_currentTetromino; // nykyinen palikka, kiinnitetty pelilautaan
  //CTetromino      *m_previewTetrominoes[m_previewBoardSize];
  CTetromino      *m_previewTetrominoes[3]; //TODO: yhyy miksi n‰m‰ on tehty arrayn‰, kun ei voida lukea arvoa configista t‰h‰n ennen t‰t‰ m‰‰rittely‰!
  CTetrisStats    *m_stats;
  bool            m_gameOver;
  bool            m_running;
  bool            m_moveLock;         // true = nykyist‰ palikkaa ei voida liikuttaa
  CTetrominoFactory *m_factory;
  CTickTask       *myTickTask; // ei vastaa t‰m‰n tuhoamisesta
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

  void initialize(void);

  void notifyGameState(VGameStateListener::GAMESTATE state);

};

#endif // __TETRISLOGIC_H__
