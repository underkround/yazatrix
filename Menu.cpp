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
  //rekister�idyt��n n�pp�imist�lle
  SKeyboardInput::getInstance().registerListener(static_cast<VCommandListener*>(this));
  //k�ytet��n asetuksia
  s = &SConfig::getInstance();
  //k�ytet��n grafiikkaa
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
  //rekister�idyt��n n�pp�imist�lle
  SKeyboardInput::getInstance().registerListener(static_cast<VCommandListener*>(this));
  //k�ytet��n asetuksia
  s = &SConfig::getInstance();
  //k�ytet��n grafiikkaa
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
  drawLogo();
  draw();
  vector<string>::iterator iter = m_listMenuItems.begin();
  for(int i=0;i<m_intMenuLength;i++,iter++) {
    drawMenuItem(i, *iter);
  }
}

void CTetrisMenu::drawLogo() {
  const int xOffset = 2;
  const int yOffset = 12;
  const int maxHeight = 8;
  const int maxWidth = 56;
  int temp[maxHeight][maxWidth] = {
    {1,2,3,4,0,0,1,2,3,4,0,1,2,3,4,0,1,1,1,1,1,2,3,4,0,1,2,3,4,0,1,1,1,1,1,2,3,1,1,1,1,2,3,4,1,2,3,1,2,3,4,1,2,3,4,0 },
    {0,1,2,3,4,1,2,3,4,0,1,2,1,2,3,4,0,0,0,0,1,2,3,4,1,2,1,2,3,4,0,0,1,2,3,4,0,1,2,3,4,1,2,3,1,2,3,1,2,3,4,1,2,3,4,0 },
    {0,0,1,2,1,2,3,4,0,1,2,3,4,1,2,3,4,0,0,1,2,3,4,1,2,3,4,1,2,3,4,0,1,2,3,4,0,1,2,3,4,1,2,3,1,2,3,4,1,2,1,2,3,4,0,0 },
    {0,0,0,1,2,3,4,0,0,1,1,1,1,1,2,3,4,0,1,2,3,4,0,1,1,1,1,1,2,3,4,0,1,2,3,4,0,1,1,1,1,2,3,4,1,2,3,4,0,1,2,3,4,0,0,0 },
    {0,0,0,1,2,3,4,0,0,1,2,0,0,1,2,3,4,1,2,3,4,0,0,1,2,3,4,1,2,3,4,0,1,2,3,4,0,1,2,1,2,3,4,0,1,2,3,4,1,2,1,2,3,4,0,0 },
    {0,0,0,1,2,3,4,0,0,1,2,3,4,1,2,3,1,2,3,4,0,0,0,1,2,3,4,1,2,3,4,0,1,2,3,4,0,1,2,3,1,2,3,4,1,2,3,1,2,3,4,1,2,3,4,0 },
    {0,0,0,1,2,3,4,0,0,1,2,3,4,1,2,3,1,1,1,1,1,2,3,1,2,3,4,1,2,3,4,0,1,2,3,4,0,1,2,3,4,1,2,3,1,2,3,1,2,3,4,1,2,3,4,0 },
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
  };
  for(int i=0;i<maxWidth;i++) {
    for(int j=0;j<maxHeight;j++) {
      switch(temp[j][i]) {
        case 1:
          g->drawChar(i+yOffset, j+xOffset, SGraphics::GCOLOR_LIGHTMAGENTA, SGraphics::GCOLOR_BLACK, 219);
          break;
        case 2:
          g->drawChar(i+yOffset, j+xOffset, SGraphics::GCOLOR_MAGENTA, SGraphics::GCOLOR_BLACK, 178);
          break;
        case 3:
          g->drawChar(i+yOffset, j+xOffset, SGraphics::GCOLOR_MAGENTA, SGraphics::GCOLOR_BLACK, 177);
          break;
        case 4:
          g->drawChar(i+yOffset, j+xOffset, SGraphics::GCOLOR_MAGENTA, SGraphics::GCOLOR_BLACK, 176);
          break;
      }
    }
  }
  g->drawString(yOffset, (xOffset+maxHeight), SGraphics::GCOLOR_DARKGRAY, SGraphics::GCOLOR_BLACK, "y e t   a n o t h e r   z e m m - a n t s y   t e t r i x");
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
  //m_listMenuItems.push_back("View config");
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
        // Toinen tapa olisi laittaa flag jolloin menu ei reagoisi komentoihin kun peli on k�ynniss�,
        // mutta t�ll� tapaa s��stet��n turhia kutsuja. Menu rekister�id��n uudelleen kuuntelijaksi
        // kun peli on ohi (handleGameState-metodissa).
        SKeyboardInput::getInstance().unregisterListener(static_cast<VCommandListener*>(this));

        // jos aiemmin on luotu peli, vapautetaan sen viem� muisti ensin.
        // TODO:  t�m� ei ole paras paikka muistin vapautukselle, mutta oikeammassa paikassa tuli erin�isi� ongelmia,
        //        johtuen pelin rakenteesta ja monesta sis�kk�isest� kutsusta.
        m_game_logic = new CTetrisLogic();
        m_game_gbg = new CBoardGraphics(m_game_logic->getGameBoard(), 18, 2);
        m_game_pbg = new CBoardGraphics(m_game_logic->getPreviewBoard(), (m_game_gbg->getWidth()+24), 4);
        m_game_stats = new CStatsPanel(m_game_logic->getStats(), 3, 5);

        // rekister�id��n menu vastaanottamaan tieto pelin loppumisesta
        m_game_logic->registerListener(static_cast<VGameStateListener*>(this));
        // rekister�id��n stats-paneeli vastaanottamaan statsit
        m_game_logic->getStats()->registerListener(static_cast<VStatsListener*>(m_game_stats));
        // rekister�id��n pelilautapaneeli vastaanottamaan pelitilat
        m_game_logic->registerListener(m_game_gbg);
        // rekister�id��n peli vastaanottamaan komentoja
        SKeyboardInput::getInstance().registerListener(static_cast<VCommandListener*>(m_game_logic));
        // ulkoasuhifistely�
        m_game_gbg->setBorderStyle(g->getBorder(s->getValueAsString("board border style")));
        m_game_pbg->setBorderColor(g->getColor(s->getValueAsString("preview border color front")),
                                   g->getColor(s->getValueAsString("preview border color back"))
                                  );
        m_game_pbg->setBorderStyle(g->getBorder(s->getValueAsString("preview border style")));
        if(!m_game_logic->isRunning())
          m_game_gbg->handleGameState(VGameStateListener::PAUSE);

        // peli on k�ynnistetty, ja se rupeaa py�rim��n seuraavalla tickill�
        // merkit��n pelioliot tuhottavaksi uuden pelin k�ynnistyksess�, tai ohjelman lopussa
        m_game_cleanup = true;
      break; }

    /** About */
    case 1: {
      g->setColors(SGraphics::GCOLOR_LIGHTGREEN, SGraphics::GCOLOR_BLACK);
      g->drawBox((g->getWidth()/2-15), (g->getHeight()/2+8), (g->getWidth()/2+15), (g->getHeight()/2+11), g->getBorder("groove"));
      g->drawString((g->getWidth()/2-13), (g->getHeight()/2+9), SGraphics::GCOLOR_LIGHTGRAY, SGraphics::GCOLOR_BLACK, "  made by antti and jussi");
      g->drawString((g->getWidth()/2-13), (g->getHeight()/2+10), SGraphics::GCOLOR_DARKGRAY, SGraphics::GCOLOR_BLACK, "        IIO6S 2008");
      break; }

    /** Quit */
    case 2: {
      g->clearScreen();
      g->drawString(1, 1, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, "Bye!");
      STicker::getInstance().stop();
      break; }

    /** Configuration *
    case 3: {
      g->drawString(0, 0, SGraphics::GCOLOR_WHITE, SGraphics::GCOLOR_BLACK, "Configuration:\n\n");
      s->printSettings();
      break; }
    */
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

      // muistin vapautus kuuluisi t�h�n, mutta johtuen monimutkaisista kutsujonoista, n�m�
      // deletet aiheuttavata kaatumisen, joten tilap�isesti on siirrytty k�ytt�m��n m_game_cleanup
      // flagia ja cleanup-metodia pelin luonnissa sek� destructorissa.
      //delete m_game_gbg;
      //delete m_game_pbg;
      //delete m_game_stats;
      //delete m_game_logic;

      // rekister�idyt��n takaisin n�pp�imist�kuuntelijaksi
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
