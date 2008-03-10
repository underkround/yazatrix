#include "Menu.h"
#include "Graphics.h"
#include <queue>

CTetrisMenu::CTetrisMenu(CGraphics *graphics){
  m_menuItems.push("Game start");
  m_menuItems.push("Quit");
}

CTetrisMenu::CTetrisMenu(CGraphics *graphics, int x_position, int y_position, int width, int height) {
}

CTetrisMenu::~CTetrisMenu(void) {

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

int CTetrisMenu::handleTick(void) {
}
