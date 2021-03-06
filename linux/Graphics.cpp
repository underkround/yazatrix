/**
 * linux/Graphics.cpp
 *
 * $Revision$
 * $Id$
 *
 * Grafiikkaluokan implementaatio linux-piirtämiseen
 *
 * @see Graphics.h
 *
 */
#define DEFAULT_FOREGROUND_GCOLOR 7
#define DEFAULT_BACKGROUND_GCOLOR 0

#ifdef __LINUX__

#include "../Graphics.h"
#include <ncurses.h>
#include <iostream>

using namespace std;

//*** public ***
/**
 * Piirtotilan initialisoinnit
 */
SGraphics::SGraphics(void) {
  //piilotetaan kursori (asettamalla sen korkeudeksi 0%)
  curs_set(0);
  //ncurses tila
  initscr();
  //tyhjennetään ruutu
  //näppäimistökaiku pois päältä
  noecho();
  raw()
  //värit päälle
  start_color();
}

/**
 * Piirtotilan sulkeminen
 */
SGraphics::~SGraphics(void) {
  //varmistetaan että käyttäjä palaa konsoliin perusväreissä
  //resetColors();
  endwin();
  //clrscr();
}

/**
 * drawChar
 *
 * Piirtää yhden merkin määrättyyn kohtaan ruudulle
 *
 * @param x   x-koordinaatti
 * @param y   y-koordinaatti
 * @param c   merkki
 */
void SGraphics::drawChar(const int x, const int y, const char c) {
  mvaddstr(y,x,c);
}

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
void SGraphics::drawChar(const int x, const int y, const GCOLOR fg, const GCOLOR bg, const char c) {
  setColors(getForegroundColor(fg), getBackgroundColor(bg));
  putchxy(x, y, c);
}
// DEPRICATED
void SGraphics::drawChar(const int x, const int y, const int fg, const int bg, const char c) {
  setColors(fg, bg);
  putchxy(x, y, c);
}

/**
 * drawSquare
 *
 * värittää yhden ruudun halutulla värillä
 *
 * @param x       x-koordinaatti
 * @param y       y-koordinaatti
 * @param color   väri
 */
void SGraphics::drawSquare(const int x, const int y, const int color) {
  setColors(0, color);
  putchxy(x, y, ' '); //'█'
}
// DEPRICATED
void SGraphics::drawSquare(const int x, const int y, const GCOLOR color) {
  setColors(0, getBackgroundColor(color));
  putchxy(x, y, ' '); //'█'
}

/**
 * drawString
 *
 * Piirtää merkkijonon määrättyyn kohtaan ruudulle
 *
 * @param x     x-koordinaatti
 * @param y     y-koordinaatti
 * @param str   merkkijono
 */
void SGraphics::drawString(const int x, const int y, const char* str) {
  moveCursor(y, x);
  cout << str;
}

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
void SGraphics::drawString(const int x, const int y, const GCOLOR fg, const GCOLOR bg, const char* str) {
  moveCursor(y, x);
  setColors(getForegroundColor(fg), getBackgroundColor(bg));
  cout << str;
}
//DEPRICATED
void SGraphics::drawString(const int x, const int y, const int fg, const int bg, const char* str) {
  moveCursor(y, x);
  setColors(fg, bg);
  cout << str;
}

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
//void SGraphics::drawBox(const int from_x, const int from_y, const int to_x, const int to_y, const int borderstyle) {
void SGraphics::drawBox(const int from_x, const int from_y, const int to_x, const int to_y, const BORDER_STYLE borderstyle) {
  char n,e,w,s,se,nw,ne,sw;
  switch(borderstyle) {
    case BORDER_NONE:
      n  = ' ';
      s  = ' ';
      w  = ' ';
      e  = ' ';
      nw = ' ';
      ne = ' ';
      sw = ' ';
      se = ' ';
      break;
    case BORDER_SIMPLE:
      n  = '-';
      s  = '-';
      w  = '|';
      e  = '|';
      nw = '+';
      ne = '+';
      sw = '+';
      se = '+';
      break;
    case BORDER_GROOVE:
      n  = 205;
      s  = 205;
      w  = 186;
      e  = 186;
      nw = 201;
      ne = 187;
      sw = 200;
      se = 188;
      break;
    default:
    case BORDER_DOTTED:
      n  = '.';
      s  = '.';
      w  = ':';
      e  = ':';
      nw = '.';
      ne = '.';
      sw = ':';
      se = ':';
      break;
  }
  int i=0;
  //north,south (vaaka)
  for(i=from_x+1;i<=to_x-1;i++) {
    drawChar(i, from_y, n);
    drawChar(i, to_y, s);
  }
  //east,west (pysty)
  for(i=from_y+1;i<=to_y-1;i++) {
    drawChar(from_x, i, e);
    drawChar(to_x, i, w);
  }
  //nw
  drawChar(from_x, from_y, nw);
  //ne
  drawChar(to_x, from_y, ne);
  //sw
  drawChar(from_x, to_y, sw);
  //se
  drawChar(to_x, to_y, se);
}


/**
 * getX
 *
 * @return kursorin sijainti ruudulla x-akselin suhteen
 */
int SGraphics::getX() {
  //return wherex();
  return 0;
}

/**
 * getY
 *
 * @return kursorin sijainti ruudulla y-akselin suhteen
 */
int SGraphics::getY() {
  //return wherey();
  return 0;
}

/**
 * getHeight
 *
 * @return käytössä olevan ruudun korkeus
 */
int SGraphics::getHeight() {
  int out,temp = 0;
  getmaxyx(stdscr,out,temp);
  return out;
}

/**
 * getWidth
 *
 * @return käytössä olevan ruudun leveys
 */
int SGraphics::getWidth() {
  int out,temp = 0;
  getmaxyx(stdscr,temp,out);
  return out;
}


//*** private ***
/**
 * moveCursor
 *
 * Siirtää kursoria kohtaan (x, y)
 *
 * @param x     x-koordinaatti
 * @param y     y-koordinaatti
 */
void SGraphics::moveCursor(const int x, const int y) {
  move(y, x);
}

/**
 * resetColors
 *
 * @deprecated tämä olikin ihan turha, käytä => ncurses.h::endwin();
 */
void SGraphics::resetColors(void) {
  if(has_colors()) {
    textcolor(DEFAULT_FOREGROUND_GCOLOR);
    textbackground(DEFAULT_BACKGROUND_GCOLOR);
  }
}

/**
 * setForegroundColor
 *
 * Asettaa tekstin piirtovärin
 *
 * @param fg    väri
 */
void SGraphics::setForegroundColor(const GCOLOR fg) {
  textcolor(getForegroundColor(fg));
}

/**
 * setBackgroundColor
 *
 * Asettaa taustan piirtovärin
 *
 * @param bg    väri
 */
void SGraphics::setBackgroundColor(const GCOLOR bg) {
  textbackground(getBackgroundColor(bg));
}

/**
 * setForegroundColor
 *
 * Asettaa sekä tekstin että taustan piirtovärit
 *
 * @param fg    tekstin väri
 * @param bg    taustan väri
 */
void SGraphics::setColors(const GCOLOR fg, const GCOLOR bg) {
  textcolor(getForegroundColor(fg));
  textbackground(getBackgroundColor(bg));
}
// DEPRICATED
void SGraphics::setColors(const int fg, const int bg) {
  textcolor(fg);
  textbackground(bg);
}

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
int SGraphics::getForegroundColor(GCOLOR col) {
  switch(col) {
    case GCOLOR_BLACK:     return 0;
    case GCOLOR_BLUE:      return 1;
    case GCOLOR_GREEN:     return 2;
    case GCOLOR_CYAN:      return 3;
    case GCOLOR_RED:       return 4;
    case GCOLOR_MAGENTA:   return 5;
    case GCOLOR_BROWN:     return 6;
    case GCOLOR_LIGHTGRAY: return 7;
    case GCOLOR_DARKGRAY:  return 8;
    case GCOLOR_LIGHTBLUE: return 9;
    case GCOLOR_LIGHTGREEN:return 10;
    case GCOLOR_LIGHTCYAN: return 11;
    case GCOLOR_LIGHTRED:  return 12;
    case GCOLOR_LIGHTMAGENTA: return 13;
    case GCOLOR_YELLOW:    return 14;
    default:
    case GCOLOR_WHITE:     return 15;
  }
}

/**
 * getBackgroundColor
 *
 * Palauttaa implementoinnin mukaisen numeron piirtovärille
 *
 * @param col   värin nimi
 * @return      värin numeroarvo tässä implementaatiossa
 */
int SGraphics::getBackgroundColor(GCOLOR col) {
  return getForegroundColor(col); // ainakin coniossa background on sama kuin foreground
}

#endif //__LINUX__
