#include "Menu.h"
#include "Graphics.h"
#include "Ticker.h"
#include "KeyboardInput.h"
#include <queue>

#define MENU_TICKDELAY 10

CTetrisMenu::CTetrisMenu(SGraphics *graphics){
  //rekisteröidytään tickerille
  STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), MENU_TICKDELAY);
  //rekisteröidytään näppäimistölle
  SKeyboardInput::getInstance().registerCommandListener( dynamic_cast<VCommandListener*>(this) );
  m_x = 0;
  m_y = 0;
  //TODO: causes wtf
  //m_height = graphics->getHeight;
  //m_width = graphics->getWidth;
  m_height = 25;
  m_width = 80;
  createItems();
}

CTetrisMenu::CTetrisMenu(SGraphics *graphics, int x_position, int y_position, int width, int height) {
  //rekisteröidytään tickerille
  STicker::getInstance().registerListener(dynamic_cast<VTickListener*>(this), MENU_TICKDELAY);
  m_x = x_position;
  m_y = y_position;
  m_width = width;
  m_height = height;
  createItems();
}

CTetrisMenu::~CTetrisMenu(void) {
}

void CTetrisMenu::Show() {

}

void CTetrisMenu::handleCommand(VCommandListener::COMMAND cmd) {
      switch(cmd) {
      case GAME_COMMAND_LEFT:
      case GAME_COMMAND_RIGHT:
      case GAME_COMMAND_ROTATE_CW:
      case GAME_COMMAND_ROTATE_CCW:
      case GAME_COMMAND_SOFTDROP:
      case GAME_COMMAND_HARDDROP:
        break;
      case GAME_COMMAND_QUIT:
        break;
      default:
        break;
    }
}

//int CTetrisMenu::handleTick(void) {
//}

void CTetrisMenu::createItems(void) {
  m_menuItems.push("Game start");
  m_menuItems.push("Quit");
}
