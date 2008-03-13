#ifndef __PANEL_H__
#define __PANEL_H__
/**
 * Panel.h
 *
 * $Revision$
 * $Id$
 *
 * Containeri ruudulla, jolla on sijainti ja koko.
 */

class VPanel {

public:

  virtual void setLocation(const int x, const int y) = 0;

  virtual void setX(const int newX) = 0;

  virtual void setY(const int newY) = 0;

  virtual inline int getX() {
    return m_x;
  }

  virtual inline int getY() {
    return m_y;
  }

  virtual inline int getWidth() = 0;

  virtual inline int getHeight() = 0;

protected:

  int m_x;
  int m_y;
  int m_width;
  int m_height;

private:

};

#endif // __PANEL_H__
