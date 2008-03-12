#ifndef __MENU_H__
#define __MENU_H__

/**
 * Menu.h
 *
 * $Id$
 * $Revision$
 *
 * Huolehtii valikoista
 *
 */

#include "Panel.h"
#include "Graphics.h"
#include "CommandListener.h"
#include <queue>

class CTetrisMenu : VPanel, VCommandListener {
  public:
  CTetrisMenu(SGraphics *graphics);
  CTetrisMenu(SGraphics *graphics, int x_position, int y_position, int width, int height);
  virtual ~CTetrisMenu(void);

  /**
   * Show
   *
   * Näyttää menun
   */
  void Show();

  //Paneelista perityt
  inline virtual int getX(void) { return m_x; }
  inline virtual int getY(void) { return m_y; }
  inline virtual int getWidth(void) { return m_width; };
  inline virtual int getHeight(void) { return m_height; };
  inline virtual void setX(int newX) { m_x = newX; }
  inline virtual void setY(int newY) { m_y = newY; }

  /**
   * Commandlisteneriltä peritty
   *
   * @see CommandListener.h
   *
   * Eli mitä tehdään kun saadaan näppäimistökomentoja
   *
   */
  virtual void handleCommand(VCommandListener::COMMAND cmd);


  /*
   * Tickiltä peritty
   *
   * @see TickListener.h
   */
/*  virtual int handleTick();
  int handleTick(void);*/

  private:
  int m_menuLength;
  std::queue<char*> m_menuItems;
  int m_x, m_y, m_width, m_height;

  void createItems();

};

#endif //__MENU_H__
