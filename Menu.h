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
#include "Config.h"
#include <vector>
#include <string>

class CTetrisMenu : public VPanel, VCommandListener, VTickListener {
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

  /**
   * drawMenuItem
   *
   * Piirtää yhden rivin menua
   */
  void drawMenuItem(const int line, const std::string text);
  void drawMenuItem(const int line, const std::string text, const bool isSelected);

  /**
   * setColorSet
   *
   * Asettaa menun käyttämät värit
   *
   * @param in_menu_fg      menun tekstin väri
   * @param in_menu_bg      menun taustaväri
   * @param in_selected_fg  valitun tekstin väri
   * @param in_selected_bg  valitun taustan väri
   */
  void setColorSet(
                    const SGraphics::GCOLOR in_menu_fg,
                    const SGraphics::GCOLOR in_menu_bg,
                    const SGraphics::GCOLOR in_selected_fg,
                    const SGraphics::GCOLOR in_selected_bg
                  );

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
  //Luokan omat muuttujat
  int m_intMenuLength;
  int m_intSelectedItem;
  std::vector<std::string> m_listMenuItems;
  //int m_x, m_y, m_width, m_height;
  SGraphics::GCOLOR menu_fg, menu_bg, selected_fg, selected_bg;
  SGraphics *g;
  SConfig *s;

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
   * selectionSelect
   *
   * Suorittaa nykyisen valitun menu itemin toiminnon.
   *
   * @return palauttaa tiedon toiminnon onnistumisesta
   */
   inline bool selectionSelect() { return selectionSelect(m_intSelectedItem); }

  /**
   * selectionSelect
   *
   * Suorittaa halutun menu itemin toiminnon
   *
   * @param item_number haluttu menu item
   * @return palauttaa tiedon toiminnon onnistumisesta
   */
   bool selectionSelect(const int item_number);
};

#endif //__MENU_H__
