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
#include <cstdlib> // TODO: TEMPORARY

CTetrisLogic::CTetrisLogic() {
  // luodaan gameboard ja previewboard
  m_gameBoard = new CTetrisBoard(GAMEBOARD_WIDTH, GAMEBOARD_HEIGHT);
  m_previewBoard = new CTetrisBoard(PREVIEWBOARD_WIDTH, PREVIEWBOARD_HEIGHT);
  // luodaan factory
  m_factory = new CTetrominoFactory();
  m_previewSpacingY = 4;
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
}

CTetrisLogic::~CTetrisLogic() {
  for(int i=0; i<PREVIEW_TETROMINOES; i++)
    delete m_previewTetrominoes[i];
  delete m_currentTetromino;
  delete m_factory;
  delete m_gameBoard;
  delete m_previewBoard;
}

void CTetrisLogic::run(void) {
  while(!m_gameOver) {
    Sleep(100);
    tick();
  }
}

void CTetrisLogic::handleCommand(VCommandListener::COMMAND cmd) {
  switch(cmd) {
    default:
      break;
  }
}

void CTetrisLogic::tick() {
  // testataan onko nykyinen palikka jos laskeutunut
  if(m_currentTetromino->hasLanded()) {
    // käsketään lautaa tyhjäämään täydet rivit
    m_gameBoard->clearFullLines();
    // pyöräytetään palikoita
    rotateTetrominoes();
  } else {
    // tiputetaan nykyistä palikkaa
    m_currentTetromino->moveDown();
  }
  // säädetään tickin timeria laudan räjäytettyjen rivien perusteella tai pelissä olleiden palikoiden mukaan

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
