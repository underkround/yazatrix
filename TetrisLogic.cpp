/**
 * TetrisLogic.cpp
 *
 * $Revision$
 * $Id$
 *
 * @see TetrisLogic.h
 *
 */

#include "TetrisLogic.h"
#include "Ticker.h"
//#include "KeyboardInput.h"
#include <cstdlib> // TODO: TEMPORARY, timerille
#include <process.h>
#include <windows.h>

CTetrisLogic::CTetrisLogic() {
  // rekisteröidytään komentokuuntelijaksi
//  TKeyboardInput::registerCommandListener( dynamic_cast<VCommandListener*>(this) );
  // luodaan gameboard ja previewboard
  m_gameBoard = new CTetrisBoard(GAMEBOARD_WIDTH, GAMEBOARD_HEIGHT);
  // luodaan factory
  m_factory = new CTetrominoFactory();
  m_previewSpacingY = 4;
  m_previewBoard = new CTetrisBoard(PREVIEWBOARD_WIDTH, m_previewSpacingY*PREVIEW_TETROMINOES);
  // luodaan nykyinen tetrominoe ja liitetään se gameBoardiin
  m_currentTetromino = m_factory->createRandom();
  m_currentTetromino->attach(m_gameBoard);
  // luodaan previewTetrominoet ja liitetään ne previewBoardiin
  for(int i=0; i<PREVIEW_TETROMINOES; i++) {
    m_previewTetrominoes[i] = m_factory->createRandom();
    m_previewTetrominoes[i]->attach(m_previewBoard, m_previewSpacingY * i * -1 - m_previewSpacingY/2);
  }
  m_previewCount = 0;
  m_tetrominoCounter = 0;
  m_gameOver = false;
  m_moveLock = false;
  m_running = false;
  m_delay = 500;
  myTickTask = 0;

  STicker *ticker = &STicker::getInstance();
  myTickTask = ticker->registerListener(dynamic_cast<VTickListener*>(this), m_delay);
}

CTetrisLogic::~CTetrisLogic() {
  for(int i=0; i<PREVIEW_TETROMINOES; i++)
    delete m_previewTetrominoes[i];
  delete m_currentTetromino;
  delete m_factory;
  delete m_gameBoard;
  delete m_previewBoard;
}

bool CTetrisLogic::start(void) {
  if(!m_gameOver) {
    printf("Logic starting..\n");
//    if(myTickTask != 0) {
      m_running = true;
      return true;
//    }
  }
  return false;
}

void CTetrisLogic::handleCommand(VCommandListener::COMMAND cmd) {
//  if(m_running && !m_gameOver) {
    switch(cmd) {
      case GAME_COMMAND_LEFT:
        m_currentTetromino->moveLeft();
        break;
      case GAME_COMMAND_RIGHT:
        m_currentTetromino->moveRight();
        break;
      case GAME_COMMAND_ROTATE_CW:
        m_currentTetromino->rotateRight();
        break;
      case GAME_COMMAND_ROTATE_CCW:
        m_currentTetromino->rotateLeft();
        break;
      case GAME_COMMAND_SOFTDROP:
        m_currentTetromino->moveDown();
        // TODO: reset tick
        break;
      case GAME_COMMAND_HARDDROP:
        m_currentTetromino->drop();
        // TODO: reset tick
        break;
      case GAME_COMMAND_PAUSE:
        // TODO: toggle pause
        break;
      case GAME_COMMAND_QUIT:
        // TODO: pysäytä timer
        m_gameOver = true;
        break;
      default:
        break;
    }
//  }
}

int CTetrisLogic::handleTick() {
  // testataan onko nykyinen palikka jos laskeutunut
  if(m_currentTetromino->hasLanded()) {
    // käsketään lautaa tyhjäämään täydet rivit
    m_gameBoard->clearFullLines();
    // pyöräytetään palikoita
    rotateTetrominoes();
    // säädetään tickin timeria laudan räjäytettyjen rivien perusteella tai pelissä olleiden palikoiden mukaan
    adjustDelay();
  } else {
    // tiputetaan nykyistä palikkaa
    m_currentTetromino->moveDown();
  }
  if(m_gameOver) {
    myTickTask = 0;
    return -1;
  }
  return m_delay;
}

void CTetrisLogic::rotateTetrominoes() {
  if(!m_gameOver) {
    // Tuhoaa nykyisen pelipalikan (currentTetromino)
    delete m_currentTetromino;
    // Irrottaa seuraavaksi vuorossa olevan preview-palikan previewBoardista
    m_previewTetrominoes[0]->detach(true);
    // Ottaa previewTetromino-taulukosta seuraavaksi vuorossa olevan nykyiseksi.
    m_currentTetromino = m_previewTetrominoes[0];
    // Nostaa jäljelle jääneiden preview-palikoiden vuoronumeroa yhdellä.
    for(int i=0; i<PREVIEW_TETROMINOES-1; i++) {
      m_previewTetrominoes[i] = m_previewTetrominoes[i+1];
      // Nostaa jäljelle jääneiden preview-palikoiden sijaintia previewBoardissa
      m_previewTetrominoes[i]->moveUp(m_previewSpacingY);
    }
    // Luo preview-taulun loppuun uuden palikan.
    m_previewTetrominoes[PREVIEW_TETROMINOES-1] = m_factory->createRandom();
    // Kiinnittää preview-taulun loppuun luodun palikan previewBoardiin omalle paikalleen
    m_previewTetrominoes[PREVIEW_TETROMINOES-1]->attach(m_previewBoard, m_previewSpacingY * PREVIEW_TETROMINOES * -1 + m_previewSpacingY/2);
    // Yrittää kiinnittää uuden nykyisen palikan gameBoardiin. Jos ei onnistu, peli loppuu
    if(!m_currentTetromino->attach(m_gameBoard)) {
      m_gameOver = true;
    }
  }
}

void CTetrisLogic::adjustDelay() {
  if(m_delay >= 50) {
    m_delay -= 50;
  }
}
