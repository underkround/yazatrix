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

  virtual void setX(int newX) = 0;

  virtual void setY(int newY) = 0;

  virtual int getX() = 0;

  virtual int getY() = 0;

  virtual int getWidth() = 0;

  virtual int getHeight() = 0;

private:

};

#endif // __PANEL_H__
