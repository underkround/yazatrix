#include "TetrisLogic.h"
/*
 */


CTetrisLogic::CTetrisLogic() {
  m_gameBoard = new CTetrisBoard(GAMEBOARD_WIDTH, GAMEBOARD_HEIGHT);
  m_previewBoard = new CTetrisBoard(PREVIEWBOARD_WIDTH, PREVIEWBOARD_HEIGHT);
  //  CTetrisTimer  m_timer = new CTetrisTimer(); // timer, joka osaa kutsua tämän luokan tick():ä ja jota voi säätää
  m_factory = new CTetrominoFactory();
  m_currentTetromino = m_factory->createRandom();
  m_previewSpacingY = 5;
}

CTetrisLogic::~CTetrisLogic() {
  delete [] m_previewTetrominoes;
  if(m_currentTetromino != 0)
    delete m_currentTetromino;
  delete m_gameBoard;
  delete m_previewBoard;
  delete m_factory;
}

CTetrisBoard CTetrisLogic::getGameBoard(void) {
  return *m_gameBoard;
}

CTetrisBoard CTetrisLogic::getPreviewBoard(void) {
  return *m_previewBoard;
}

CTetromino CTetrisLogic::getCurrentTetromino(void) {
  return *m_currentTetromino;
}

void CTetrisLogic::reset(void) {
  // Luo uuden tetrominoFactoryn
  // TODO: Asettaa timerille asianmukaisen viiveen (luo uuden timerin?)

  // Luo uudet gameBoardin ja previewBoardin
  // Luo uudet previewTetrominot ja currentTetrominon
  for(int i=0; i<PREVIEW_TETROMINOES; i++) {
    m_previewTetrominoes[i] = m_factory->createRandom();
  }
  // Nollaa laskurit (tetrominoCounter jne)
  m_previewCount = 0;
  m_tetrominoCounter = 0;
}

void CTetrisLogic::handleCommand(VCommandListener::COMMAND cmd) {
  //
}

void CTetrisLogic::rotateTetrominoes() {
  // Tuhoaa nykyisen pelipalikan (currentTetromino)
  delete m_currentTetromino;
  // Irrottaa seuraavaksi vuorossa olevan preview-palikan previewBoardista
  m_previewTetrominoes[0]->detach(true);
  // Ottaa previewTetromino-taulukosta seuraavaksi vuorossa olevan nykyiseksi.
  m_currentTetromino = m_previewTetrominoes[0];
  // Kiinnittää uuden nykyisen gameBoardiin
  m_currentTetromino->attach(m_gameBoard);
  // Nostaa jäljelle jääneiden preview-palikoiden vuoronumeroa yhdellä.
  for(int i=0; i<PREVIEW_TETROMINOES-1; i++) {
    m_previewTetrominoes[i] = m_previewTetrominoes[i+1];
    // Nostaa jäljelle jääneiden preview-palikoiden sijaintia previewBoardissa
    m_previewTetrominoes[i]->moveUp(m_previewSpacingY);
  }
  // Luo preview-taulun loppuun uuden palikan.
  m_previewTetrominoes[PREVIEW_TETROMINOES-1] = m_factory->createRandom();
  // Kiinnittää preview-taulun loppuun luodun palikan previewBoardiin omalle paikalleen
  m_previewTetrominoes[PREVIEW_TETROMINOES-1]->attach(m_previewBoard, m_previewSpacingY * PREVIEW_TETROMINOES);
}
