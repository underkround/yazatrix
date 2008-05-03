#include "Menu.h"
#include "Graphics.h"
#include "Ticker.h"
#include "KeyboardInput.h"
#include <vector>
#include <string>
#include <iostream>

#include "./BoardGraphics.h"
#include "./TetrisLogic.h"
#include "./TickListener.h"
#include "./Ticker.h"
#include "./StatsPanel.h"
#include "./StatsListener.h"

#define MENU_TICKDELAY 10

using namespace std;

CTetrisMenu::CTetrisMenu(){
  //rekisteröidytään tickerille
  STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), MENU_TICKDELAY);
  //rekisteröidytään näppäimistölle
  SKeyboardInput::getInstance().registerListener( dynamic_cast<VCommandListener*>(this) );
  //käytetään asetuksia
  s = &SConfig::getInstance();
  //käytetään grafiikkaa
  g = &SGraphics::getInstance();
  setX(1);
  setY(1);
  m_height = g->getHeight();
  m_width = g->getWidth();
  m_height = 25;
  m_width = 80;
  setColorSet(
              SGraphics::GCOLOR_WHITE,  //menu fg
              SGraphics::GCOLOR_BLACK,  //menu bg
              SGraphics::GCOLOR_BLACK,  //selection fg
              SGraphics::GCOLOR_WHITE); //selection bg
  createItems();
}

CTetrisMenu::CTetrisMenu(int x_position, int y_position, int width, int height) {
  //rekisteröidytään tickerille
  STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), MENU_TICKDELAY);
  //rekisteröidytään näppäimistölle
  SKeyboardInput::getInstance().registerListener( dynamic_cast<VCommandListener*>(this) );
  //käytetään asetuksia
  s = &SConfig::getInstance();
  //käytetään grafiikkaa
  g = &SGraphics::getInstance();
  //paneelille:
  {
    setX(x_position);
    setY(y_position);
    m_width = width;
    m_height = height;
  }
  setColorSet(
              SGraphics::GCOLOR_WHITE,  //menu fg
              SGraphics::GCOLOR_BLACK,  //menu bg
              SGraphics::GCOLOR_BLACK,  //selection fg
              SGraphics::GCOLOR_WHITE); //selection bg
  createItems();
}

CTetrisMenu::~CTetrisMenu(void) {
}

void CTetrisMenu::show() {
  vector<string>::iterator iter = m_listMenuItems.begin();
  for(int i=0;i<m_intMenuLength;i++,iter++) {
    drawMenuItem(i, *iter);
  }
}

void CTetrisMenu::drawMenuItem(const int line, const string text) {
  drawMenuItem(line, text, (line == m_intSelectedItem));
}

void CTetrisMenu::drawMenuItem(const int line, const string text, const bool isSelected) {
  if(isSelected) {
    g->drawString(m_x, (m_y+line), selected_fg, selected_bg, text);
  }
  else {
    g->drawString(m_x, (m_y+line), menu_fg, menu_bg, text);
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
      //show();
      break;
    }
    case MENU_COMMAND_DOWN: {
      selectionDown();
      //show();
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
  m_intSelectedItem = 0; //indeksi alkaa tietenkin nollasta
  m_listMenuItems.push_back("Game start");
  m_listMenuItems.push_back("About");
  m_listMenuItems.push_back("Quit");
  m_listMenuItems.push_back("View config");
  m_intMenuLength = m_listMenuItems.size();
}

void CTetrisMenu::selectionUp() {
  drawMenuItem(m_intSelectedItem, m_listMenuItems.at(m_intSelectedItem), false);
  m_intSelectedItem--;
  if(m_intSelectedItem < 0) {
    m_intSelectedItem = (m_intMenuLength-1);
  }
  drawMenuItem(m_intSelectedItem, m_listMenuItems.at(m_intSelectedItem), true);
}

void CTetrisMenu::selectionDown() {
  drawMenuItem(m_intSelectedItem, m_listMenuItems.at(m_intSelectedItem), false);
  m_intSelectedItem++;
  if(m_intSelectedItem >= m_intMenuLength) {
    m_intSelectedItem = 0;
  }
  drawMenuItem(m_intSelectedItem, m_listMenuItems.at(m_intSelectedItem), true);
}

bool CTetrisMenu::selectionSelect(const int item_number) {
  switch(item_number) {
    case 0:
      //
        //SKeyboardInput::getInstance().unregisterListener( dynamic_cast<VCommandListener*>(this) );
        SKeyboardInput *input = &SKeyboardInput::getInstance();
        input->unregisterListener(dynamic_cast<VCommandListener*>(this));

        CTetrisLogic *logic = new CTetrisLogic();
        CBoardGraphics *gbg = new CBoardGraphics(logic->getGameBoard(), 18, 2);
        CBoardGraphics *pbg = new CBoardGraphics(logic->getPreviewBoard(), 34, 4);
        CStatsPanel *stats = new CStatsPanel(logic->getStats(), 3, 5);

        logic->getStats()->registerListener(dynamic_cast<VStatsListener*>(stats));

        input->registerListener( dynamic_cast<VCommandListener*>(logic) );
        gbg->setBorderStyle(SGraphics::BORDER_BLOCK);
        pbg->setBorderColor(SGraphics::GCOLOR_LIGHTGREEN, SGraphics::GCOLOR_GREEN);
        pbg->setBorderStyle(SGraphics::BORDER_SQUARE);

        STicker::getInstance().start();
        logic->start();

        delete gbg;
        delete pbg;
        input->unregisterListener(dynamic_cast<VCommandListener*>(logic));
        delete logic;
        input->registerListener(dynamic_cast<VCommandListener*>(this)); //TODO: miksi tämä ei palauta kontrollia käyttäjälle?

      break;
    case 1:
      g->drawString(2, 10, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, "tehnyt antti ja jussi");
      break;
    case 2:
      g->drawString(2, 6, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, "Bye!");
      STicker::getInstance().stop();
      break;
    case 3:
      g->drawString(0, 0, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, "Configuration:\n\n");
      s->printSettings();
      break;
    default:
      g->drawString(2, 10, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, "lol xiit wallhack    ");
      return false;
  }
  return true;
}
