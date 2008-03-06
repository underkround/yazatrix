/**
 * grafiikkaluokan testiohjelma
 *
 * $Id$
 */

#include "../graphics.h"
#include <string>

#define ENUMSTYLE
//#define INTSTYLE

int main() {
  CGraphics *konsoli = new CGraphics();

#ifdef ENUMSTYLE
  konsoli->drawBox(2,2,12,12, CGraphics::BORDER_SIMPLE);
  konsoli->drawChar(10,4, 'x');
  konsoli->drawChar(4,10, 'y');
  konsoli->drawSquare(5,4,CGraphics::COLOR_LIGHTCYAN);
  konsoli->drawSquare(5,5,CGraphics::COLOR_LIGHTCYAN);
  konsoli->drawSquare(6,5,CGraphics::COLOR_LIGHTCYAN);
  konsoli->drawSquare(6,6,CGraphics::COLOR_LIGHTCYAN);
  konsoli->drawString(2, 14, CGraphics::COLOR_LIGHTMAGENTA, CGraphics::COLOR_BLACK, "hello jussi <3");
  konsoli->setColors(CGraphics::COLOR_GREEN, CGraphics::COLOR_WHITE);
  printf("\nkorkeus: %d\nleveys: %d", konsoli->getHeight(), konsoli->getWidth());
  char ch[2];
  for(int i=0;i<16;i++) {
    for(int j=0;j<16;j++) {
      //char *ch = itoa(i, ch, 10);
      sprintf(ch, "%d", i);
      konsoli->drawString(20+3*j, i+4, i, j, ch);
    }
  }
  konsoli->setColors(15,0);
  konsoli->drawBox(18, 2, 69, 21, CGraphics::BORDER_GROOVE);
#endif ENUMSTYLE

#ifdef INTSTYLE
  konsoli->drawBox(2,2,12,12, CGraphics::BORDER_SIMPLE);
  konsoli->drawChar(10,4, 'x');
  konsoli->drawChar(4,10, 'y');
  konsoli->drawSquare(5,4,4);
  konsoli->drawSquare(5,5,4);
  konsoli->drawSquare(6,5,4);
  konsoli->drawSquare(6,6,4);
  konsoli->drawString(2, 14, 4, 0, "hello jussi <3");
  konsoli->setColors(15,0);
  printf("\nkorkeus: %d\nleveys: %d", konsoli->getHeight(), konsoli->getWidth());
  char ch[2];
  for(int i=0;i<16;i++) {
    for(int j=0;j<16;j++) {
      //char *ch = itoa(i, ch, 10);
      sprintf(ch, "%d", i);
      konsoli->drawString(20+3*j, i+4, i, j, ch);
    }
  }
  konsoli->setColors(15,0);
  konsoli->drawBox(18, 2, 69, 21, CGraphics::BORDER_GROOVE);
#endif INTSTYLE

  delete konsoli;
  return 0;
}
