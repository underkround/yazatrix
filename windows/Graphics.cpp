/**
 * Grafiikkaluokka windowsissa piirtämiseen implementaatio
 *
 * $Id$
 * $HeadURL$
 *
 */
#define DEFAULT_FOREGROUND_COLOR 7
#define DEFAULT_BACKGROUND_COLOR 0

#include "../graphics.h"
#include <conio2.h>
#include <iostream>

using namespace std;

//*** public ***
/**
 * Piirtotilan initialisoinnit
 */
CGraphics::CGraphics(void) {
  //piilotetaan kursori (asettamalla sen korkeudeksi 0%)
  _setcursortype(0);
  //tyhjennetään ruutu
  clrscr();
}

/**
 * Piirtotilan sulkeminen
 */
CGraphics::~CGraphics(void) {
  //varmistetaan että käyttäjä palaa konsoliin perusväreissä
  //resetColors();
  normvideo();
  //clrscr();
}

void CGraphics::drawChar(const int x, const int y, const char c) {
  putchxy(x, y, c);
}

void CGraphics::drawChar(const int x, const int y, const int fg, const int bg, const char c) {
  setColors(fg, bg);
  putchxy(x, y, c);
}

void CGraphics::drawSquare(const int x, const int y, const int color) {
  setColors(0, color);
  putchxy(x, y, ' '); //'█'
}

void CGraphics::drawString(const int x, const int y, const char* str) {
  moveCursor(y, x);
  cout << str;
}

void CGraphics::drawString(const int x, const int y, const int fg, const int bg, const char* str) {
  moveCursor(y, x);
  setColors(fg, bg);
  cout << str;
}

void CGraphics::drawBox(const int from_x, const int from_y, const int to_x, const int to_y, const int borderstyle) {
  char n,e,w,s,se,nw,ne,sw;
  switch(borderstyle) {
    case 0:
      n  = '-';
      s  = '-';
      w  = '|';
      e  = '|';
      nw = '+';
      ne = '+';
      sw = '+';
      se = '+';
      break;
    case 1:
      n  = 205;
      s  = 205;
      w  = 186;
      e  = 186;
      nw = 201;
      ne = 187;
      sw = 200;
      se = 188;

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

int CGraphics::getX() {
  return wherex();
}

int CGraphics::getY() {
  return wherey();
}

/**
 * @return käytössä olevan ruudun korkeus
 */
int CGraphics::getHeight() {
  text_info *x = new text_info;
  gettextinfo(x);
  int out = 0;
  out = x->screenheight;
  delete x;
  return out;
}

/**
 * @return käytössä olevan ruudun leveys
 */
int CGraphics::getWidth() {
  text_info *x = new text_info;
  gettextinfo(x);
  int out = 0;
  out = x->screenwidth;
  delete x;
  return out;
}

//*** private ***
void CGraphics::moveCursor(const int x, const int y) {
  gotoxy(y, x);
}

void CGraphics::resetColors(void) {
  textcolor(DEFAULT_FOREGROUND_COLOR);
  textbackground(DEFAULT_BACKGROUND_COLOR);
}

void CGraphics::setForegroundColor(const int fg) {
  textcolor(fg);
}

void CGraphics::setBackgroundColor(const int bg) {
  textbackground(bg);
}

void CGraphics::setColors(const int fg, const int bg) {
  textcolor(fg);
  textbackground(bg);
}
