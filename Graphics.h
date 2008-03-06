#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
/**
 * Grafiikka luokka windowsissa piirtämiseen
 *
 * $Id$
 * $HeadURL$
 *
 * conion asentaminen code::blocksiin onnistuu helpoiten käyttmällä devpak pluginiä:
 * hae devpak installer/updater pluginillä devpaks.org -> text console -> conio 2.0
 * lisää build asetuksien linker asetuksiiin link libraries listaan libconio.a
 */

class CGraphics {
  public:
  CGraphics(void);
  ~CGraphics(void);

  // tuetut borderit
  enum BORDER_STYLE {
    BORDER_NONE,
    BORDER_SIMPLE,
    BORDER_GROOVE,
    BORDER_DOTTED
  };

  // tuetut värit
  enum COLOR {
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_YELLOW,
    COLOR_WHITE,
    COLOR_LIGHTGRAY,
    COLOR_DARKGRAY,
    COLOR_LIGHTBLUE,
    COLOR_LIGHTGREEN,
    COLOR_LIGHTCYAN,
    COLOR_LIGHTRED,
    COLOR_LIGHTMAGENTA
  };

  //peruspiirtotyökalut
  void drawChar(const int x, const int y, const char c);
  void drawChar(const int x, const int y, const int fg, const int bg, const char c); // DEPRICATED
  void drawChar(const int x, const int y, const COLOR fg, const COLOR bg, const char c);
  void drawSquare(const int x, const int y, const int color); // DEPRICATED
  void drawSquare(const int x, const int y, const COLOR color);
  void drawString(const int x, const int y, const char* str);
  void drawString(const int x, const int y, const int bg, const int fg, const char* str); // DEPRICATED
  void drawString(const int x, const int y, const COLOR bg, const COLOR fg, const char* str);

  //älykkäämmät piirtotyökalut
//  void drawBox(const int from_x, const int from_y, const int to_x, const int to_y, const int borderstyle); // DEPRICATED
  void drawBox(const int from_x, const int from_y, const int to_x, const int to_y, BORDER_STYLE borderstyle);

  //muuta tarpeellista
  int getX();
  int getY();
  int getHeight();
  int getWidth();
  void setColors(const int fg, const int bg); // DEPRICATED
  void setColors(const COLOR fg, const COLOR bg);

  private:
  void moveCursor(const int x, const int y);
  void resetColors(void);
  void setForegroundColor(const int fg); // DEPRICATED
  void setBackgroundColor(const int bg); // DEPRICATED
  void setForegroundColor(const COLOR fg);
  void setBackgroundColor(const COLOR bg);
  int getForegroundColor(COLOR col);
  int getBackgroundColor(COLOR col);
};

 #endif //__GRAPHICS_H__
