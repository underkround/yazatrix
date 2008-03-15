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
  SGraphics *konsoli = &SGraphics::getInstance();

#ifdef ENUMSTYLE
  konsoli->drawBox(2,2,12,12, SGraphics::BORDER_SIMPLE);
  konsoli->drawChar(10,4, 'x');
  konsoli->drawChar(4,10, 'y');
  konsoli->drawSquare(5,4,SGraphics::GCOLOR_LIGHTCYAN);
  konsoli->drawSquare(5,5,SGraphics::GCOLOR_LIGHTCYAN);
  konsoli->drawSquare(6,5,SGraphics::GCOLOR_LIGHTCYAN);
  konsoli->drawSquare(6,6,SGraphics::GCOLOR_LIGHTCYAN);
  konsoli->drawString(2, 14, SGraphics::GCOLOR_LIGHTMAGENTA, SGraphics::GCOLOR_BLACK, "hello jussi <3");
  konsoli->setColors(SGraphics::GCOLOR_GREEN, SGraphics::GCOLOR_WHITE);
  printf("\nkorkeus: %d\nleveys: %d", konsoli->getHeight(), konsoli->getWidth());
  char ch[2];
  for(int i=0;i<16;i++) {
    for(int j=0;j<16;j++) {
      //char *ch = itoa(i, ch, 10);
      sprintf(ch, "%d", i);
      konsoli->setColors(i, j);
      konsoli->drawString(20+3*j, i+4, ch);
    }
  }
  konsoli->setColors(SGraphics::GCOLOR_WHITE,SGraphics::GCOLOR_BLACK);
  konsoli->drawBox(18, 2, 69, 21, SGraphics::BORDER_GROOVE);
#endif //ENUMSTYLE

#ifdef INTSTYLE
  konsoli->drawBox(2,2,12,12, SGraphics::BORDER_SIMPLE);
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
  konsoli->setColors(SGraphics::GCOLOR_WHITE,SGraphics::GCOLOR_BLACK);
  konsoli->drawBox(18, 2, 69, 21, SGraphics::BORDER_GROOVE);
#endif //INTSTYLE

  //delete konsoli;
  return 0;
}
