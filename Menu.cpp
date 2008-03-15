#include "Menu.h"
#include "Graphics.h"
#include "Ticker.h"
#include "KeyboardInput.h"
#include <queue>

#define MENU_TICKDELAY 10

CTetrisMenu::CTetrisMenu(){
  //rekisteröidytään tickerille
  STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), MENU_TICKDELAY);
  //rekisteröidytään näppäimistölle
  SKeyboardInput::getInstance().registerCommandListener( dynamic_cast<VCommandListener*>(this) );
  setX(0);
  setY(0);
  //TODO: causes wtf
  //m_height = graphics->getHeight;
  //m_width = graphics->getWidth;
  m_height = 25;
  m_width = 80;
  createItems();
}

CTetrisMenu::CTetrisMenu(int x_position, int y_position, int width, int height) {
  //rekisteröidytään tickerille
  STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), MENU_TICKDELAY);
  setX(x_position);
  setY(y_position);
  m_width = width;
  m_height = height;
  createItems();
}

CTetrisMenu::~CTetrisMenu(void) {
}

void CTetrisMenu::show() {
}

void CTetrisMenu::handleCommand(VCommandListener::COMMAND cmd) {
      switch(cmd) {
      case MENU_COMMAND_UP: {
        printf("painoit ylös");
        break;
      }
      case MENU_COMMAND_DOWN: {
        printf("painoit alas");
        break;
      }
      case MENU_COMMAND_SELECT: {
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
  m_menuItems.push("Game start");
  m_menuItems.push("Quit");
}
