#ifndef __PANEL_H__
#define __PANEL_H__
/**
 * Panel.h
 *
 * $Revision$
 * $Id$
 *
 * Containeri ruudulla, jolla on sijainti, koko ja mahdollisesti
 * border.
 */

#include "Graphics.h"

class VPanel {

public:

  // asetetaan jonkunlaiset defaultit
  VPanel();

//  virtual ~VPanel();

  virtual void setLocation(const int x, const int y);
  virtual int getX();
  virtual int getY();
  virtual void setX(const int newX);
  virtual void setY(const int newY);
  virtual int getWidth(void);
  virtual int getHeight(void);

  // TODO: t‰m‰ ei ole viel‰ kokonaan tuettu, pidet‰‰n borderit toistaiseksi p‰‰ll‰..
//  virtual void setBorderVisible(bool visible);
  void setBorderColor(const SGraphics::GCOLOR fg, const SGraphics::GCOLOR bg);
  void setBorderStyle(const SGraphics::BORDER_STYLE bs);

  // panelin tulee piirt‰‰ itsens‰ kun t‰t‰ kutsutaan
  virtual void draw(void);

protected:

  SGraphics::BORDER_STYLE m_borderStyle;
  SGraphics::GCOLOR       m_borderBG;
  SGraphics::GCOLOR       m_borderFG;
  SGraphics::GCOLOR       m_foreground;
  SGraphics::GCOLOR       m_background;
  bool    m_border;
  int     m_x;
  int     m_y;
  int     m_width;
  int     m_height;

  // piirret‰‰n borderi
  void drawBorder(void);

private:

};

#endif // __PANEL_H__
