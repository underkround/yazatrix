/**
 * windows/Graphics.cpp
 *
 * $Revision$
 * $Id$
 *
 * Grafiikkaluokka windowsissa piirtämiseen implementaatio
 *
 * @see Graphics.h
 *
 */
#define DEFAULT_FOREGROUND_GCOLOR 7
#define DEFAULT_BACKGROUND_GCOLOR 0

#include "../Graphics.h"
#include <conio2.h>
#include <iostream>

using namespace std;

//*** public ***
SGraphics::SGraphics(void) {
  //piilotetaan kursori (asettamalla sen korkeudeksi 0%)
  _setcursortype(0);
  //tyhjennetään ruutu
  clrscr();
}

SGraphics::~SGraphics(void) {
  //varmistetaan että käyttäjä palaa konsoliin perusväreissä
  //resetColors();
  normvideo();
  //clrscr();
}

void SGraphics::drawChar(const int x, const int y, const char c) {
  putchxy(x, y, c);
}

void SGraphics::drawChar(const int x, const int y, const GCOLOR fg, const GCOLOR bg, const char c) {
  setColors(fg, bg);
  putchxy(x, y, c);
}
// DEPRICATED
/*void SGraphics::drawChar(const int x, const int y, const int fg, const int bg, const char c) {
  setColors(fg, bg);
  putchxy(x, y, c);
}*/

void SGraphics::drawSquare(const int x, const int y, const GCOLOR color) {
  setColors(GCOLOR_BLACK, getBackgroundColor(color));
  putchxy(x, y, ' '); //'█'
  _setcursortype(0);
}

void SGraphics::drawString(const int x, const int y, const char* str) {
  moveCursor(y, x);
  cout << str;
}

void SGraphics::drawString(const int x, const int y, const GCOLOR fg, const GCOLOR bg, const char* str) {
  moveCursor(y, x);
  setColors(getForegroundColor(fg), getBackgroundColor(bg));
  cout << str;
}

void SGraphics::drawString(const int x, const int y, const GCOLOR fg, const GCOLOR bg, const string str) {
  moveCursor(y, x);
  setColors(getForegroundColor(fg), getBackgroundColor(bg));
  cout << str;
}

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
    case BORDER_SINGLE:
      n  = 196;
      s  = 196;
      w  = 179;
      e  = 179;
      nw = 218;
      ne = 191;
      sw = 192;
      se = 217;
      break;
    default:
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
    case BORDER_SQUARE:
      n  = 254;
      s  = 254;
      w  = 254;
      e  = 254;
      nw = 254;
      ne = 254;
      sw = 254;
      se = 254;
      break;
    case BORDER_BLOCK:
      n  = 220;
      s  = 223;
      w  = 219;
      e  = 219;
      nw = 220;
      ne = 220;
      sw = 223;
      se = 223;
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

int SGraphics::getX() {
  return wherex();
}

int SGraphics::getY() {
  return wherey();
}

int SGraphics::getHeight() {
  text_info *x = new text_info;
  gettextinfo(x);
  int out = 0;
  out = x->screenheight;
  delete x;
  return out;
}

int SGraphics::getWidth() {
  text_info *x = new text_info;
  gettextinfo(x);
  int out = 0;
  out = x->screenwidth;
  delete x;
  return out;
}

//*** private ***
void SGraphics::moveCursor(const int x, const int y) {
  gotoxy(y, x);
}

void SGraphics::resetColors(void) {
  textcolor(DEFAULT_FOREGROUND_GCOLOR);
  textbackground(DEFAULT_BACKGROUND_GCOLOR);
}

void SGraphics::setForegroundColor(const GCOLOR fg) {
  textcolor(getForegroundColor(fg));
  currentForegroundColor = fg;
}

void SGraphics::setBackgroundColor(const GCOLOR bg) {
  textbackground(getBackgroundColor(bg));
  currentBackgroundColor = bg;
}

void SGraphics::setColors(const GCOLOR fg, const GCOLOR bg) {
  textcolor(getForegroundColor(fg));
  currentForegroundColor = fg;
  textbackground(getBackgroundColor(bg));
  currentBackgroundColor = bg;
}

void SGraphics::setColors(const int fg, const int bg) {
  textcolor(fg);
  currentForegroundColor = (GCOLOR)fg;
  textbackground(bg);
  currentBackgroundColor = (GCOLOR)bg;
}

SGraphics::GCOLOR SGraphics::getColor(const std::string& color) {
    if(color == "black")         return GCOLOR_BLACK;
    if(color == "blue")          return GCOLOR_BLUE;
    if(color == "green")         return GCOLOR_GREEN;
    if(color == "cyan")          return GCOLOR_CYAN;
    if(color == "red")           return GCOLOR_RED;
    if(color == "magenta")       return GCOLOR_MAGENTA;
    if(color == "brown")         return GCOLOR_BROWN;
    if(color == "light gray")    return GCOLOR_LIGHTGRAY;
    if(color == "dark gray")     return GCOLOR_DARKGRAY;
    if(color == "light blue")    return GCOLOR_LIGHTBLUE;
    if(color == "light green")   return GCOLOR_LIGHTGREEN;
    if(color == "light cyan")    return GCOLOR_LIGHTCYAN;
    if(color == "light red")     return GCOLOR_LIGHTRED;
    if(color == "light magenta") return GCOLOR_LIGHTMAGENTA;
    if(color == "yellow")        return GCOLOR_YELLOW;
    if(color == "white")         return GCOLOR_WHITE;
    return GCOLOR_WHITE;
}

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

int SGraphics::getBackgroundColor(GCOLOR col) {
  return getForegroundColor(col); // ainakin coniossa background on sama kuin foreground
}
