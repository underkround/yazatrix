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

#include <sstream>

class SGraphics {

public:

  /** Singleton */
  static SGraphics& getInstance() {
    static SGraphics theSingleInstance;
    return theSingleInstance;
  }

  // handled borders
  enum BORDER_STYLE {
    BORDER_NONE,        BORDER_SIMPLE,    BORDER_SINGLE,    BORDER_GROOVE,
    BORDER_DOTTED,      BORDER_SQUARE,    BORDER_BLOCK
  };

  // handled colors
  enum GCOLOR {
    GCOLOR_BLACK,       GCOLOR_BLUE,      GCOLOR_GREEN,     GCOLOR_CYAN,
    GCOLOR_RED,         GCOLOR_MAGENTA,   GCOLOR_BROWN,     GCOLOR_YELLOW,
    GCOLOR_WHITE,       GCOLOR_LIGHTGRAY, GCOLOR_DARKGRAY,  GCOLOR_LIGHTBLUE,
    GCOLOR_LIGHTGREEN,  GCOLOR_LIGHTCYAN, GCOLOR_LIGHTRED,  GCOLOR_LIGHTMAGENTA
  };

  //*** peruspiirtotyökalut ***

  /**
   * drawChar
   *
   * Piirtää yhden merkin määrättyyn kohtaan ruudulle
   *
   * @param x   x-koordinaatti
   * @param y   y-koordinaatti
   * @param c   merkki
   */
  void drawChar(const int x, const int y, const char c);

  /**
   * drawChar
   *
   * Piirtää yhden merkin määrättyyn kohtaan ruudulle halutuilla väreillä
   *
   * @param x     x-koordinaatti
   * @param y     y-koordinaatti
   * @param fg    tekstin väri
   * @param bg    taustan väri
   * @param c     merkki
   */
  void drawChar(const int x, const int y, const GCOLOR fg, const GCOLOR bg, const char c);

  /**
   * drawSquare
   *
   * värittää yhden ruudun halutulla värillä
   *
   * @param x       x-koordinaatti
   * @param y       y-koordinaatti
   * @param color   väri
   */
  void drawSquare(const int x, const int y, const GCOLOR color);

  /**
   * drawString
   *
   * Piirtää merkkijonon määrättyyn kohtaan ruudulle
   *
   * @param x     x-koordinaatti
   * @param y     y-koordinaatti
   * @param str   merkkijono
   */
  void drawString(const int x, const int y, const char* str);

  /**
   * drawString
   *
   * Piirtää merkkijonon määrättyyn kohtaan ruudulle halutulla värillä
   *
   * @param x     x-koordinaatti
   * @param y     y-koordinaatti
   * @param fg    tekstin väri
   * @param bg    taustan väri
   * @param str   merkkijono
   */
  void drawString(const int x, const int y, const GCOLOR bg, const GCOLOR fg, const char* str);
  void drawString(const int x, const int y, const GCOLOR bg, const GCOLOR fg, const std::string str);

  //*** älykkäämmät piirtotyökalut ***

  /**
   * drawBox
   *
   * Piirtää ruudulle laatikon
   *
   * @param from_x        vasemman yläkulman x-koordinaatti
   * @param from_y        vasemman yläkulman y-koordinaatti
   * @param to_x          oikean alakulman x-koordinaatti
   * @param to_y          oikean alakulman y-koordinaatti
   * @param borderstyle   reunuksen tyyli
   */
  void drawBox(const int from_x, const int from_y, const int to_x, const int to_y, BORDER_STYLE borderstyle);

  //*** muuta tarpeellista ***

  /**
   * getX
   *
   * @return kursorin sijainti ruudulla x-akselin suhteen
   */
  int getX();

  /**
   * getY
   *
   * @return kursorin sijainti ruudulla y-akselin suhteen
   */
  int getY();

  /**
   * getHeight
   *
   * @return käytössä olevan ruudun korkeus
   */
  int getHeight();

  /**
   * getWidth
   *
   * @return käytössä olevan ruudun leveys
   */
  int getWidth();

  /**
   * setColors
   *
   * Asettaa sekä tekstin että taustan piirtovärit
   *
   * @param fg    tekstin väri
   * @param bg    taustan väri
   */
  void setColors(const GCOLOR fg, const GCOLOR bg);

  /**
   * setColors
   *
   * Asettaa sekä tekstin että taustan piirtovärit
   *
   * @param fg    tekstin väri
   * @param bg    taustan väri
   */
  void setColors(const int fg, const int bg);

  /**
   * getColor
   *
   * Palauttaa värin nimen perusteella
   *
   * @param color   haluttu väri
   * @return        väri
   *
   */
  GCOLOR getColor(const std::string& color);

  /**
   * getBorder
   *
   * Palauttaa borderin nimen perusteella
   *
   * @param border  haluttu border
   * @return        border
   *
   */
  BORDER_STYLE getBorder(const std::string& border);

private:

  /**
   * moveCursor
   *
   * Siirtää kursoria kohtaan (x, y)
   *
   * @param x     x-koordinaatti
   * @param y     y-koordinaatti
   */
  void moveCursor(const int x, const int y);

  /**
   * resetColors
   *
   * @deprecated tämä olikin ihan turha, käytä => conio.h::normvideo();
   */
  void resetColors(void);

  /**
   * setForegroundColor
   *
   * Asettaa tekstin piirtovärin
   *
   * @param fg    väri
   */
  void setForegroundColor(const GCOLOR fg);

  /**
   * setBackgroundColor
   *
   * Asettaa taustan piirtovärin
   *
   * @param bg    väri
   */
  void setBackgroundColor(const GCOLOR bg);

  /**
   * getForegroundColor
   *
   * Palauttaa implementoinnin mukaisen numeron taustavärille
   * (jos alusta ei tue kaikkia värejä, päätetään mikä väri
   * korvaa)
   *
   * @param col   värin nimi
   * @return      värin numeroarvo tässä implementaatiossa
   */
  int getForegroundColor(GCOLOR col);

  /**
   * getBackgroundColor
   *
   * Palauttaa implementoinnin mukaisen numeron piirtovärille
   *
   * @param col   värin nimi
   * @return      värin numeroarvo tässä implementaatiossa
   */
  int getBackgroundColor(GCOLOR col);

  //muistetaan nykyiset käytössä olevat värit
  GCOLOR currentForegroundColor;
  GCOLOR currentBackgroundColor;

protected:

  /**
   * Piirtotilan initialisoinnit
   */
  SGraphics(void);

  /**
   * Piirtotilan sulkeminen
   */
  ~SGraphics(void);

};

 #endif //__GRAPHICS_H__
