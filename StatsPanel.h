#ifndef __STATSPANEL_H__
#define __STATSPANEL_H__

/**
 * StatsPanel.h
 *
 * $Revision$
 * $Id$
 *
 *
 */
#include "StatsListener.h"
#include "Graphics.h"
#include "Panel.h"

class CStatsPanel : public VStatsListener, public VPanel {

public:

  CStatsPanel();
  virtual ~CStatsPanel();

  virtual inline int getWidth() {  return m_width + 2; }
  virtual inline int getHeight() { return m_height + 2; }
  virtual inline void setX(const int newX) { m_x = newX; }
  virtual inline void setY(const int newY) { m_y = newY; }
  virtual inline void setLocation(const int x, const int y) { m_x = x; m_y = y; }

  virtual void handleChangeInStats(const int score, const int level, const int reml, const int remll);

private:

  SGraphics               *g;
  SGraphics::BORDER_STYLE  m_borderStyle;
  int m_score;
  int m_level;
  int m_reml;
  int m_remll;

  void draw();

};

#endif // __STATSPANEL_H__
