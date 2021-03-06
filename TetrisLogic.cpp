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
#include <iostream>

CTetrisLogic::CTetrisLogic() {
  settings = &SConfig::getInstance();
  m_previewBoardSize = settings->getValueAsInt("preview size");
  //m_previewBoardHeight = settings->getValueAsInt("preview height");
  m_previewBoardWidth = settings->getValueAsInt("preview width");
  m_gameBoard = new CTetrisBoard(settings->getValueAsInt("board width"), settings->getValueAsInt("board height"));
  initialize();
}

/**
 * @deprecated didn't work well with configuration file and was never used anyway
 */
/*CTetrisLogic::CTetrisLogic(const int gameboardWidth, const int gameboardHeight) {
  settings = &SConfig::getInstance();
  m_gameBoard = new CTetrisBoard(gameboardWidth, gameboardHeight);
  initialize();
}*/

void CTetrisLogic::initialize() {
  // luodaan factory
  m_factory = new CTetrominoFactory();
  m_previewSpacingY = 5;
  m_previewBoard = new CTetrisBoard(m_previewBoardWidth, m_previewSpacingY*m_previewBoardSize);
  // luodaan nykyinen tetrominoe ja liitetään se gameBoardiin
  m_currentTetromino = m_factory->createRandom();
  m_currentTetromino->attach(m_gameBoard);
  m_currentTetromino->setGhost(settings->getValueAsBool("ghost"));
  m_stats = new CTetrisStats();
  // luodaan previewTetrominoet ja liitetään ne previewBoardiin
  for(int i=0; i<m_previewBoardSize; i++) {
    m_previewTetrominoes[i] = m_factory->createRandom();
    m_previewTetrominoes[i]->attach(m_previewBoard, m_previewSpacingY * i * -1 - m_previewSpacingY/2);
  }
  m_previewCount = 0;
  m_gameOver = false;
  m_moveLock = false;
  m_running = false;
  myTickTask = STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), m_stats->getDropDelay());
}

CTetrisLogic::~CTetrisLogic() {
  for(int i=0; i<m_previewBoardSize; i++) {
    delete m_previewTetrominoes[i];
  }
  delete m_currentTetromino;
  delete m_factory;
  delete m_stats;
  delete m_gameBoard;
  delete m_previewBoard;
}

bool CTetrisLogic::start(void) {
  if(!m_gameOver) {
    m_running = true;
    notifyGameState(VGameStateListener::RESUME);
    return true;
  }
  return false;
}

void CTetrisLogic::handleCommand(VCommandListener::COMMAND cmd) {
  /*if(m_gameOver) {
    STicker::getInstance().stop();
    return;
  }*/
  if(!m_running)
    start();
  if(m_running && !m_gameOver) {
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
        myTickTask->resetTick();
        // TODO: reset tick
        break;
      case GAME_COMMAND_PAUSE:
        m_running = false; // TODO: parempi pause. tämä on vaan tilapäinen
        notifyGameState(VGameStateListener::PAUSE);
        break;
      case GAME_COMMAND_QUIT:
        // TODO: pysäytä timer
        m_gameOver = true;
        notifyGameState(VGameStateListener::GAMEOVER); // abort running game
        break;
      default:
        break;
    }
  } else if(m_gameOver && cmd == GAME_COMMAND_QUIT) {
    notifyGameState(VGameStateListener::EXIT); // game already over - exit from game
  }
}

int CTetrisLogic::handleTick() {
  if(m_gameOver) {
    myTickTask = 0;
    return -1;
  }
  // testataan onko nykyinen palikka jos laskeutunut
  if(!m_running)
    return 10;
  if(m_currentTetromino->hasLanded()) {
    // käsketään lautaa tyhjäämään täydet rivit
    int lines = m_gameBoard->clearFullLines();
    m_stats->linesRemoved(lines);
    // pyöräytetään palikoita
    rotateTetrominoes();
  } else {
    // tiputetaan nykyistä palikkaa
    m_currentTetromino->moveDown();
  }
  return m_stats->getDropDelay();
}

void CTetrisLogic::rotateTetrominoes() {
  if(!m_gameOver) {
    m_stats->tetrominoAdded();
    // Tuhoaa nykyisen pelipalikan (currentTetromino)
    delete m_currentTetromino;
    // Irrottaa seuraavaksi vuorossa olevan preview-palikan previewBoardista
    m_previewTetrominoes[0]->detach(true);
    // Ottaa previewTetromino-taulukosta seuraavaksi vuorossa olevan nykyiseksi.
    m_currentTetromino = m_previewTetrominoes[0];
    // Nostaa jäljelle jääneiden preview-palikoiden vuoronumeroa yhdellä.
    for(int i=0; i<m_previewBoardSize-1; i++) {
      m_previewTetrominoes[i] = m_previewTetrominoes[i+1];
      // Nostaa jäljelle jääneiden preview-palikoiden sijaintia previewBoardissa
      m_previewTetrominoes[i]->moveUp(m_previewSpacingY);
    }
    // Luo preview-taulun loppuun uuden palikan.
    m_previewTetrominoes[m_previewBoardSize-1] = m_factory->createRandom();
    // Kiinnittää preview-taulun loppuun luodun palikan previewBoardiin omalle paikalleen
    m_previewTetrominoes[m_previewBoardSize-1]->attach(m_previewBoard, m_previewSpacingY * m_previewBoardSize * -1 + m_previewSpacingY/2);
    // Yrittää kiinnittää uuden nykyisen palikan gameBoardiin. Jos ei onnistu, peli loppuu
    if(!m_currentTetromino->attach(m_gameBoard)) {
      m_gameOver = true;
      notifyGameState(VGameStateListener::GAMEOVER);
    } else {
      // asetetaan ghost päälle gameboardissa olevalle palikalle
      m_currentTetromino->setGhost(settings->getValueAsBool("ghost"));
    }
  }
}

void CTetrisLogic::notifyGameState(VGameStateListener::GAMESTATE state) {
  for(int i=0; i<m_listenerCount; i++)
    listeners[i]->handleGameState(state);
}
