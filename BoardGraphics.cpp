/**
 *
 *
 */

#include "BoardGraphics.h"

CBoardGraphics::CBoardGraphics(CTetrisBoard *myBoard, CGraphics *graphics, int offsetX, int offsetY) {
  board = myBoard;
  // rekisterˆidy boardille kuuntelijaksi
  VBoardChangeListener *bcl = dynamic_cast<VBoardChangeListener*>(this);
  board->registerBoardChangeListener( bcl );
  g = graphics;
  m_x = offsetX;
  m_y = offsetY;
  // jos ei borderia tms , niin mitat = boardin mitat
  m_width = board->getWidth();
  m_height = board->getHeight();
  m_borders = true;
  setBorderStyle(CGraphics::BORDER_GROOVE);
}

CBoardGraphics::~CBoardGraphics() {
  // poista rekisterˆityminen
  //board->unregisterBoardChangeListener(this);
  // jaa voipa olla ett‰ tulisi ongelmia jos board on jo tuhottu..
  // jollei sitten tee siit‰kin ilmoitusta listenerin kautta =)
}

void CBoardGraphics::setBorder(bool visible) {
  // borderit p‰‰ll‰? jos moisia jaksaa tehd‰. lis‰‰ tietty leveytt‰ ja korkeutta +2
  m_borders = visible; // TODO: pit‰isikˆ olla int, jos bordertyyppej‰ on useita?
  handleFreshBoard(); // koko lauta muuttuu jos borderit muuttuu p‰‰lle / pois
}

// TODO: EI TOIMI >:|
void CBoardGraphics::setBorderStyle(CGraphics::BORDER_STYLE bs) {
  m_borderStyle = bs;
  drawBorder();
}

void CBoardGraphics::drawBorder() {
  printf("boder draw");
  g->setColors(CGraphics::COLOR_WHITE, CGraphics::COLOR_BLACK);
  if(m_borders)
    g->drawBox(m_x, m_y, m_x+m_width+1, m_y+m_height+1, m_borderStyle);
}

void CBoardGraphics::setLocation(int x, int y) {
  // mihin kohtaan ruutua piirt‰‰ itsens‰
  m_x = x;
  m_y = y;
}

// t‰t‰ k‰ytt‰en piirret‰‰n solut
void CBoardGraphics::drawCell(int x, int y, CELL_TYPE ct) {
  // TODO: piirr‰ ct ruudulle
  // x ja y = laudan solunumerot 0 .. board->getWidth()-1
  // eli BoardGraphicsilla on sen alkukoordinaatit ruudulla, m_x ja m_y
  // siihen saattaa tulla lis‰‰ mahdollinen borderin tuoma + 1, johon
  // lis‰t‰‰n annettu x ja y
  // TODO2: koska boardin y kulkee alhaalta ylˆs, y on luultavasti
  // board->getHeight()-1-y ???
  int ax = (m_borders) ? x+m_x+1 : x+m_x;
//  int ay = y + m_y;
  int ay = (m_borders) ? m_height+m_y-y : m_height+m_y-y-1;
//  if(m_borders) { ax++; ay++; } // borderit ottaa yhden merkin tilaa
  g->drawSquare(ax,ay,getCellTypeColor(ct));
}

CGraphics::COLOR CBoardGraphics::getCellTypeColor(CELL_TYPE ct) {
  switch(ct) {
    case OFFGRID: return CGraphics::COLOR_WHITE;
    case BLOCK_Z: return CGraphics::COLOR_RED;
    case BLOCK_S: return CGraphics::COLOR_GREEN;
    case BLOCK_I: return CGraphics::COLOR_CYAN;
    case BLOCK_O: return CGraphics::COLOR_YELLOW;
    case BLOCK_L: return CGraphics::COLOR_BROWN;
    case BLOCK_J: return CGraphics::COLOR_BLUE;
    case BLOCK_T: return CGraphics::COLOR_MAGENTA;
    default:
    case EMPTY: return CGraphics::COLOR_BLACK;
  }
}

// katso BoardChangeListener n‰iden tarkempaan tarkotukseen
void CBoardGraphics::handleFreshBoard() {
  // hae koko board, ja piirr‰ se
  for(int ix=0; ix<m_width; ix++) {
    for(int iy=0; iy<m_height; iy++) {
      drawCell(ix, iy, board->getSlot(ix, iy));
    }
  }
}

// muutos monessa koordinaatissa, ilmoitetaan koordinaattilistana
void CBoardGraphics::handleChangeInCoords(int *changedCoordsX[], int *changedCoordsY[], int numCoords) {
  int ix = 0;
  int iy = 0;
  for(int i=0; i<numCoords; i++) {
    ix = *changedCoordsX[i];
    iy = *changedCoordsY[i];
    // haetaan muuttuneen koordinaatin sis‰ltˆ ja piirret‰‰n se
    drawCell(ix, iy, board->getSlot(ix, iy)); // piirret‰‰n solu
  }
}

// muutos riveiss‰
void CBoardGraphics::handleChangeInLines(int *changedLines[], int numLines) {
  int iy = 0;
  // k‰yd‰‰n muuttuneet rivit l‰pi
  for(int i=0; i<numLines; i++) {
    iy = *changedLines[i];
    // piirret‰‰n rivi uudestaan
    for(int ix=0; ix<m_width; ix++) {
      drawCell(ix, iy, board->getSlot(ix, iy)); // piirret‰‰n solu
    }
  }
}

// muutos yksitt‰isess‰ solussa
void CBoardGraphics::handleChangeInCoord(int x, int y) {
  CELL_TYPE ct = board->getSlot(x, y);
  drawCell(x, y, ct); // piirret‰‰n solu
}
