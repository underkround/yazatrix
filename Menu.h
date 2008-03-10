#ifndef __MENU_H__
#define __MENU_H__

#include "Panel.h"
#include "Graphics.h"
#include "CommandListener.h"
#include <queue>

class CTetrisMenu : VPanel, VCommandListener {
  public:
  CTetrisMenu(CGraphics *graphics);
  CTetrisMenu(CGraphics *graphics, int x_position, int y_position, int width, int height);
  virtual ~CTetrisMenu(void);

  //Paneelista perityt
  inline virtual int getX(void) { return m_x; }
  inline virtual int getY(void) { return m_y; }
  inline virtual int getWidth(void) { return m_width; };
  inline virtual int getHeight(void) { return m_height; };
  inline virtual void setX(int newX) { m_x = newX; }
  inline virtual void setY(int newY) { m_y = newY; }

  //Commandlisteneristä perityt
  virtual void handleCommand(VCommandListener::COMMAND cmd);

  //Tickiltä perityt
  int handleTick(void);

  private:
  int m_menuLength;
  std::queue<char*> m_menuItems;
  int m_x, m_y, m_width, m_height;

};

#endif //__MENU_H__
