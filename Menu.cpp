/**
 * Menu.cpp
 *
 * $Revision$
 * $Id$
 *
 * @see Menu.h
 *
 */

#include "Menu.h"
#include "Graphics.h"
#include "Ticker.h"
#include "KeyboardInput.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

CTetrisMenu::CTetrisMenu(){
  //rekisteröidytään näppäimistölle
  SKeyboardInput::getInstance().registerListener(static_cast<VCommandListener*>(this));
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
              g->getColor(s->getValueAsString("menu front color")),              //menu fg
              g->getColor(s->getValueAsString("menu back color")),               //menu bg
              g->getColor(s->getValueAsString("menu selected front color")),     //selection fg
              g->getColor(s->getValueAsString("menu selected back color")));     //selection bg
  createItems();
  m_game_cleanup = false;
}

CTetrisMenu::CTetrisMenu(int x_position, int y_position, int width, int height) {
  //rekisteröidytään näppäimistölle
  SKeyboardInput::getInstance().registerListener(static_cast<VCommandListener*>(this));
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
              g->getColor(s->getValueAsString("menu front color")),           //menu fg
              g->getColor(s->getValueAsString("menu back color")),            //menu bg
              g->getColor(s->getValueAsString("menu selected front color")),  //selection fg
              g->getColor(s->getValueAsString("menu selected back color")));  //selection bg
  createItems();
  m_game_cleanup = false;
}

CTetrisMenu::~CTetrisMenu(void) {
  m_listMenuItems.clear();
  delete &m_listMenuItems;
  if(m_game_cleanup)
    gameCleanup();
}

void CTetrisMenu::show() {
  draw();
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
    g->drawString(m_x+2, (m_y+line+2), selected_fg, selected_bg, text);
  }
  else {
    g->drawString(m_x+2, (m_y+line+2), menu_fg, menu_bg, text);
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

    /** Start game */
    case 0: {
        g->clearScreen();

        if(m_game_cleanup)
          gameCleanup();

        // Poistetaan menu komentokuuntelijoista.
        // Toinen tapa olisi laittaa flag jolloin menu ei reagoisi komentoihin kun peli on käynnissä,
        // mutta tällä tapaa säästetään turhia kutsuja. Menu rekisteröidään uudelleen kuuntelijaksi
        // kun peli on ohi (handleGameState-metodissa).
        SKeyboardInput::getInstance().unregisterListener(static_cast<VCommandListener*>(this));

        // jos aiemmin on luotu peli, vapautetaan sen viemä muisti ensin.
        // TODO:  tämä ei ole paras paikka muistin vapautukselle, mutta oikeammassa paikassa tuli erinäisiä ongelmia,
        //        johtuen pelin rakenteesta ja monesta sisäkkäisestä kutsusta.
        m_game_logic = new CTetrisLogic();
        m_game_gbg = new CBoardGraphics(m_game_logic->getGameBoard(), 18, 2);
        m_game_pbg = new CBoardGraphics(m_game_logic->getPreviewBoard(), 34, 4);
        m_game_stats = new CStatsPanel(m_game_logic->getStats(), 3, 5);

        // rekisteröidään menu vastaanottamaan tieto pelin loppumisesta
        m_game_logic->registerListener(static_cast<VGameStateListener*>(this));
        // rekisteröidään stats-paneeli vastaanottamaan statsit
        m_game_logic->getStats()->registerListener(static_cast<VStatsListener*>(m_game_stats));
        // rekisteröidään pelilautapaneeli vastaanottamaan pelitilat
        m_game_logic->registerListener(m_game_gbg);
        // rekisteröidään peli vastaanottamaan komentoja
        SKeyboardInput::getInstance().registerListener(static_cast<VCommandListener*>(m_game_logic));
        // ulkoasuhifistelyä
        m_game_gbg->setBorderStyle(g->getBorder(s->getValueAsString("board border style")));
        m_game_pbg->setBorderColor(g->getColor(s->getValueAsString("preview border color front")),
                                   g->getColor(s->getValueAsString("preview border color back"))
                                  );
        m_game_pbg->setBorderStyle(g->getBorder(s->getValueAsString("preview border style")));
        if(!m_game_logic->isRunning())
          m_game_gbg->handleGameState(VGameStateListener::PAUSE);

        // peli on käynnistetty, ja se rupeaa pyörimään seuraavalla tickillä
        // merkitään pelioliot tuhottavaksi uuden pelin käynnistyksessä, tai ohjelman lopussa
        m_game_cleanup = true;
      break; }

    /** About */
    case 1: {
      g->drawString(2, 10, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, "tehnyt antti ja jussi");
      break; }

    /** Quit */
    case 2: {
      g->clearScreen();
      g->drawString(1, 1, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, "Bye!");
      STicker::getInstance().stop();
      break; }

    /** Configuration */
    case 3: {
      g->drawString(0, 0, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, "Configuration:\n\n");
      s->printSettings();
      break; }

    default: {
      g->drawString(2, 10, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, "lol xiit wallhack    ");
      return false; }
  }
  return true;
}

void CTetrisMenu::handleGameState(VGameStateListener::GAMESTATE state) {
  switch(state) {
    case VGameStateListener::EXIT: {
      SKeyboardInput::getInstance().unregisterListener(static_cast<VCommandListener*>(m_game_logic));
      m_game_logic->getStats()->unregisterListener(static_cast<VStatsListener*>(m_game_stats));

      // muistin vapautus kuuluisi tähän, mutta johtuen monimutkaisista kutsujonoista, nämä
      // deletet aiheuttavata kaatumisen, joten tilapäisesti on siirrytty käyttämään m_game_cleanup
      // flagia ja cleanup-metodia pelin luonnissa sekä destructorissa.
      //delete m_game_gbg;
      //delete m_game_pbg;
      //delete m_game_stats;
      //delete m_game_logic;

      // rekisteröidytään takaisin näppäimistökuuntelijaksi
      SKeyboardInput::getInstance().registerListener(static_cast<VCommandListener*>(this));
      //STicker::getInstance().start();

      g->clearScreen();
      show();
      break;
    }

    default: {
      break;
    }
  }
}

void CTetrisMenu::gameCleanup() {
  if(m_game_cleanup) {
    delete m_game_gbg;
    delete m_game_pbg;
    delete m_game_stats;
    delete m_game_logic;
    m_game_cleanup = false;
  }
}
