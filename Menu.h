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
#include "TickListener.h"
#include <queue>

class CTetrisMenu : VPanel, VCommandListener, VTickListener {
  public:
  CTetrisMenu();
  CTetrisMenu(int x_position, int y_position, int width, int height);
  virtual ~CTetrisMenu(void);

  /**
   * Show
   *
   * Näyttää menun
   */
  void show();

  //Paneelista perityt
  inline virtual int getX(void) { return m_x; }
  inline virtual int getY(void) { return m_y; }
  inline virtual int getWidth(void) { return m_width; };
  inline virtual int getHeight(void) { return m_height; };
  inline virtual void setX(int newX) { m_x = newX; }
  inline virtual void setY(int newY) { m_y = newY; }
  inline void setLocation(const int x, const int y) { m_x = x; m_y = y; };

  /**
   * Commandlisteneriltä peritty
   *
   * @see CommandListener.h
   *
   * Eli mitä tehdään kun saadaan näppäimistökomentoja
   *
   */
  virtual void handleCommand(VCommandListener::COMMAND cmd);


  /**
   * TickListeneriltä peritty
   *
   * @see TickListener.h
   */
  virtual int handleTick();
  //int handleTick(void);

  private:
  int m_menuLength;
  int selectedItem;
  std::queue<char*> m_menuItems;
  int m_x, m_y, m_width, m_height;

  /**
   * CreateItems
   *
   * Lisää kovakoodatut menuitemit menuun.
   */
  void createItems();

  /**
   * selectionUp
   *
   * Siirretään valintaa ylös ja ympäri.
   */
  void selectionUp();

  /**
   * selectionDown
   *
   * Siirretään valintaa alas ja ympäri.
   */
  void selectionDown();

  /**
   * moveToSelection
   *
   * Siirretään valinta suoraan johonkin tiettyyn indeksiin.
   */
  void moveToSelection(const int item_number);

  /**
   *
   *
   */
   inline bool selectionSelect() { return selectionSelect(selectedItem); }

  /**
   *
   *
   */
   bool selectionSelect(const int item);
};

#endif //__MENU_H__
