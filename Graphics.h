#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

/**
 * Graphics.h
 *
 * $Revision$
 * $Id$
 *
 * Grafiikkaluokka windowsin komentorivillä piirtämiseen
 *
 * conion asentaminen code::blocksiin onnistuu helpoiten käyttmällä devpak pluginiä:
 * hae devpak installer/updater pluginillä devpaks.org -> text console -> conio 2.0
 * lisää build asetuksien linker asetuksiiin link libraries listaan libconio.a
 */

#include "Singleton.h"
#include <sstream>

//class SGraphics : public Singleton<SGraphics> {
class SGraphics {
//friend class Singleton<SGraphics>;

public:

static SGraphics& getInstance() {
  static SGraphics theSingleInstance;  // assumes T has a protected default constructor
  return theSingleInstance;
}

  // tuetut borderit
  enum BORDER_STYLE {
    BORDER_NONE,        BORDER_SIMPLE,    BORDER_SINGLE,    BORDER_GROOVE,
    BORDER_DOTTED,      BORDER_SQUARE,    BORDER_BLOCK
  };

  // tuetut värit
  enum GCOLOR {
    GCOLOR_BLACK,       GCOLOR_BLUE,      GCOLOR_GREEN,     GCOLOR_CYAN,
    GCOLOR_RED,         GCOLOR_MAGENTA,   GCOLOR_BROWN,     GCOLOR_YELLOW,
    GCOLOR_WHITE,       GCOLOR_LIGHTGRAY, GCOLOR_DARKGRAY,  GCOLOR_LIGHTBLUE,
    GCOLOR_LIGHTGREEN,  GCOLOR_LIGHTCYAN, GCOLOR_LIGHTRED,  GCOLOR_LIGHTMAGENTA
  };

  //peruspiirtotyökalut
  void drawChar(const int x, const int y, const char c);
  void drawChar(const int x, const int y, const GCOLOR fg, const GCOLOR bg, const char c);
  void drawSquare(const int x, const int y, const GCOLOR color);
  void drawString(const int x, const int y, const char* str);
  void drawString(const int x, const int y, const GCOLOR bg, const GCOLOR fg, const char* str);
  void drawString(const int x, const int y, const GCOLOR bg, const GCOLOR fg, const std::string str);

  //älykkäämmät piirtotyökalut
  void drawBox(const int from_x, const int from_y, const int to_x, const int to_y, BORDER_STYLE borderstyle);

  //muuta tarpeellista
  int getX();
  int getY();
  int getHeight();
  int getWidth();
  void setColors(const GCOLOR fg, const GCOLOR bg);

private:
  void moveCursor(const int x, const int y);
  void resetColors(void);
  void setForegroundColor(const GCOLOR fg);
  void setBackgroundColor(const GCOLOR bg);
  void setColors(const int fg, const int bg);
  int getForegroundColor(GCOLOR col);
  int getBackgroundColor(GCOLOR col);

  //muistetaan nykyiset käytössä olevat värit
  GCOLOR currentForegroundColor;
  GCOLOR currentBackgroundColor;

protected:

  SGraphics(void);
  ~SGraphics(void);

};

 #endif //__GRAPHICS_H__
