/**
 * TetrisBoard.cpp
 *
 * $Id$
 * $Revision$
 * $HeadURL$
 *
 * Y-koordinaatit alkavat alhaalta, eli alin rivi on y==0
 */

#include "TetrisBoard.h"
#include "TetrisCommon.h"

#define TETRIS_GUIDELINE_WIDTH 10
#define TETRIS_GUIDELINE_HEIGHT 22


CTetrisBoard::CTetrisBoard(void) {
  m_firstReset = true;
  m_width = TETRIS_GUIDELINE_WIDTH;
  m_height = TETRIS_GUIDELINE_HEIGHT;
  m_matrix = new CELL_TYPE*[TETRIS_GUIDELINE_HEIGHT];
  for(int iy=0; iy<TETRIS_GUIDELINE_HEIGHT; iy++)
    m_matrix[iy] = new CELL_TYPE[TETRIS_GUIDELINE_WIDTH];
  reset();
}


CTetrisBoard::CTetrisBoard(const int cols, const int rows) {
  m_firstReset = true;
  m_width = cols;
  m_height = rows;
  // luo vaaditun kokoinen matrix-taulukko
  // TODO: lolapua miten alustan taulukon
  m_matrix = new CELL_TYPE*[rows];
  for(int iy=0; iy<rows; iy++)
    m_matrix[iy] = new CELL_TYPE[cols];
  // alusta matrix nollilla
  reset();
}


CTetrisBoard::~CTetrisBoard() {
  // tuhotaan matrix
  for(int iy=0; iy<m_height; iy++)
    delete [] m_matrix[iy];
  delete [] m_matrix;
  // listenereitä ei pidä tuhota..
  // muut onkin sitten kai primitiivejä
}

void CTetrisBoard::reset(void) {
  // nollataan changebufferit
  while(!m_changeBufferX.empty())   m_changeBufferX.pop();
  while(!m_changeBufferY.empty())   m_changeBufferY.pop();
  while(!m_changeBufferCT.empty())  m_changeBufferCT.pop();
  // nollataan linecountit
  m_removedLines = 0;
  m_removedLinesLast = 0;
  // foreach matrix.. = 0
  for(int iy=0; iy<m_height; iy++) {
    resetLine(iy);
  }
  // ilmoitetaan tuoreesta boardista
  notifyFreshBoard();
  if(m_firstReset)
    m_firstReset = false;
}

void CTetrisBoard::resetLine(const int y) {
  for(int ix=0; ix<m_width; ix++) {
    m_matrix[y][ix] = EMPTY;
  }
}

CELL_TYPE CTetrisBoard::getSlot(const int x, const int y) {
  if(x < 0 || x >= m_width) return OFFGRID;
  if(y < 0 || y >= m_height) return OFFGRID;
  return m_matrix[y][x];
}

CELL_TYPE CTetrisBoard::setSlot(const int x, const int y, const CELL_TYPE content) {
  if(x < 0 || x >= m_width) return OFFGRID;
  if(y < 0 || y >= m_height) return OFFGRID;
  CELL_TYPE old = m_matrix[y][x];
  m_matrix[y][x] = content;
  m_changeBufferX.push(x);
  m_changeBufferY.push(y);
  m_changeBufferCT.push(content);
  return old;
}

bool CTetrisBoard::isEmpty(){
  for(int iy=0; iy<m_height; iy++)
    for(int ix=0; ix<m_width; ix++)
      if(m_matrix[iy][ix] != EMPTY)
        return false; // vähintään yksi ruutu ei ole tyhjä
  return true;
}

bool CTetrisBoard::isEmpty(const int x, const int y) {
  if(x < 0 || x >= m_width || y < 0) return false;
  if(y >= m_height) return true;
  return (m_matrix[y][x] == EMPTY) ? true : false;
}

bool CTetrisBoard::isEmpty(const int y) {
  if(y < 0 || y >= m_height) return false;
  for(int i=0; i<m_width; i++)
    if(m_matrix[y][i] != EMPTY)
      return false; // vähintään yksi ruutu ei ole tyhjä
  return true;
}

bool CTetrisBoard::isFull(const int y){
  for(int i=0; i<m_width; i++)
    if(m_matrix[y][i] == EMPTY)
      return false; // vähintään yksi ruutu on tyhjä
  return true;
}

int CTetrisBoard::clearFullLines(void) {
  m_removedLinesLast = 0;
  // rivit pitää käydä ylhäältä alaspäin läpi, koska ne poistetaan
  // samantien, ja korkeat indeksit muuttuvat
  for(int i=m_height-1; i>=0; i--) {
    if(isFull(i)) {
      removeLine(i);
      m_removedLinesLast++;
    }
  }
  if(m_removedLinesLast > 0)
    notifyFreshBoard(); // TODO: ilmoita vain muuttuneet rivit
  return m_removedLinesLast; //??
}

bool CTetrisBoard::removeLine(const int y) {
  if(y >= m_height || y < 0)
    return false;
  // tuhotaan rivi
  delete [] m_matrix[y];
  // aseta ylempien rivien indeksit yhdellä alaspäin
  for(int iy=y+1; iy<m_height; iy++) {
    // TODO, voiko taulukkoa kopioida valmiilla funkkarilla? matrix[iy-1] = matrix[iy]
    m_matrix[iy-1] = m_matrix[iy];
  }
  // luodaan uusi rivi päällimmäiseksi
  m_matrix[m_height-1] = new CELL_TYPE[m_width];
  // alusta uusi rivi matriksiin (ylimmäiseksi)
  resetLine(m_height-1);
  m_removedLines++;
  return true;
}

void CTetrisBoard::update() {
//  notifyFreshBoard(); // TODO: käytä changeBufferia ja ilmoita pelkät muutokset
  // lähetetään bufferin sisältö kuuntelijalle
  while(!m_changeBufferCT.empty()) {
    notifyChangeInCoord(m_changeBufferX.top(), m_changeBufferY.top(), m_changeBufferCT.top());
    m_changeBufferX.pop();
    m_changeBufferY.pop();
    m_changeBufferCT.pop();
  }
}

// ==================== METODIT LISTENEREILLE ====================

void CTetrisBoard::notifyFreshBoard(void) {
  // foreach listeners
	for(int i=0; i<changeListeners.size(); i++) {
		VBoardChangeListener* listener = changeListeners[i];
		listener->handleFreshBoard();
	}
}

void CTetrisBoard::notifyChangeInCoord(const int x, const int y, const CELL_TYPE ct) {
	for(unsigned int i=0; i<changeListeners.size(); i++) {
		VBoardChangeListener* listener = changeListeners[i];
		listener->handleChangeInCoord(x, y, ct);
  }
}

bool CTetrisBoard::registerBoardChangeListener(VBoardChangeListener* bcl) {
  changeListeners.push_back(bcl);
  //notifyFreshBoard();
  return true;
}

bool CTetrisBoard::unregisterBoardChangeListener(VBoardChangeListener* bcl) {
  // TODO: poista kuuntelija changeListeners -vektroista
  return false;
}

// DEPRICATED
//void CTetrisBoard::notifyChangeInCoords() {
  // käytetään changebufferia
  // tyhjennetään changebuffer
//}
