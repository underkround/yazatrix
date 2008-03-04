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

class Graphics {
  public:
  Graphics(void);
  ~Graphics(void);

  //peruspiirtotyökalut
  void drawChar(const int x, const int y, const char c);
  void drawChar(const int x, const int y, const int fg, const int bg, const char c);
  void drawString(const int x, const int y, const char* str);
  void drawString(const int x, const int y, const int bg, const int fg, const char* str);

  //älykkäämmät piirtotyökalut
  void drawBox(const int from_x, const int from_y, const int to_x, const int to_y, const int borderstyle);

  //muuta tarpeellista
  int getX();
  int getY();
  int getHeight();
  int getWidth();
  void setColors(const int fg, const int bg);

  private:
  void moveCursor(const int x, const int y);
  void resetColors(void);
  void setForegroundColor(const int fg);
  void setBackgroundColor(const int bg);
};

 #endif //__GRAPHICS_H__
