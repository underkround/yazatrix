#include "Menu.h"
#include "Graphics.h"
#include "Ticker.h"
#include "KeyboardInput.h"
#include <list>
#include <string>
#include <iostream>

#define MENU_TICKDELAY 10

using namespace std;

CTetrisMenu::CTetrisMenu(){
  //rekisteröidytään tickerille
  STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), MENU_TICKDELAY);
  //rekisteröidytään näppäimistölle
  SKeyboardInput::getInstance().registerCommandListener( dynamic_cast<VCommandListener*>(this) );
  //käytetään grafiikkaa
  g = &SGraphics::getInstance();
  setX(2);
  setY(2);
  //TODO: causes wtf
  //m_height = graphics->getHeight;
  //m_width = graphics->getWidth;
  m_height = 25;
  m_width = 80;
  setColorSet(SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, SGraphics::GCOLOR_BLACK, SGraphics::GCOLOR_WHITE);
  createItems();
}

CTetrisMenu::CTetrisMenu(int x_position, int y_position, int width, int height) {
  //rekisteröidytään tickerille
  STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), MENU_TICKDELAY);
  //rekisteröidytään näppäimistölle
  SKeyboardInput::getInstance().registerCommandListener( dynamic_cast<VCommandListener*>(this) );
  //käytetään grafiikkaa
  g = &SGraphics::getInstance();
  setX(x_position);
  setY(y_position);
  m_width = width;
  m_height = height;
  setColorSet(SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, SGraphics::GCOLOR_BLACK, SGraphics::GCOLOR_WHITE);
  createItems();
}

CTetrisMenu::~CTetrisMenu(void) {
}

void CTetrisMenu::show() {
  list<string>::iterator iter = m_listMenuItems.begin();
  for(int i=0;i<m_intMenuLength;i++,iter++) {
    //printf("m_x: %d  m_y: %d\n temp: %s", m_x, m_y+i, &iter);
    if((i+1) != m_intSelectedItem) {
      g->drawString(m_x, (m_y+i), selected_fg, selected_bg, *iter);
    }
    else {
      g->drawString(m_x, (m_y+i), menu_fg, menu_bg, *iter);
    }
  }
}

void CTetrisMenu::setColorSet(const SGraphics::GCOLOR in_menu_fg, const SGraphics::GCOLOR in_menu_bg, const SGraphics::GCOLOR in_selected_fg, const SGraphics::GCOLOR in_selected_bg) {
  menu_fg = in_menu_fg;
  menu_bg = in_menu_bg;
  selected_fg = in_selected_fg;
  selected_bg = in_selected_bg;
}

void CTetrisMenu::handleCommand(VCommandListener::COMMAND cmd) {
      switch(cmd) {
      case MENU_COMMAND_UP: {
        selectionUp();
        //printf("up to %d\n", m_intSelectedItem);
        show();
        break;
      }
      case MENU_COMMAND_DOWN: {
        selectionDown();
        //printf("down to %d\n", m_intSelectedItem);
        show();
        break;
      }
      case MENU_COMMAND_SELECT: {
        selectionSelect();
        break;
      }
      case MENU_COMMAND_BACK: {
        break;
      }
      default:
        break;
    }
}

int CTetrisMenu::handleTick(void) {
  return MENU_TICKDELAY;
}

void CTetrisMenu::createItems(void) {
  m_intSelectedItem = 1;
  m_listMenuItems.push_back("Game start");
  m_listMenuItems.push_back("About");
  m_listMenuItems.push_back("Quit");
  m_intMenuLength = 3;
}

void CTetrisMenu::selectionUp() {
  //piirretään nykyinen menun väreillä
  m_intSelectedItem--;
  if(m_intSelectedItem < 1) {
    m_intSelectedItem = m_intMenuLength;
  }
  //piirretään uusi valintaväreillä
}

void CTetrisMenu::selectionDown() {
  //piirretään nykyinen menun väreillä
  m_intSelectedItem++;
  if(m_intSelectedItem > m_intMenuLength) {
    m_intSelectedItem = 1;
  }
  //piirretään uusi valintaväreillä
}

bool CTetrisMenu::selectionSelect(const int item_number) {
}
