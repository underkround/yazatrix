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
#include "TetrisStats.h"
#include "TickListener.h"
#include "Config.h"
#include <sstream>

class CStatsPanel : public VStatsListener, public VPanel, public VTickListener {

public:

  CStatsPanel(const CTetrisStats *stats, const int x, const int y);

  virtual ~CStatsPanel();

  virtual void draw(void);

  virtual void handleChangeInStats(const int score, const int level, const int reml, const int remll);

  virtual int handleTick();

private:

  SGraphics               *g;
  SConfig                 *s;
  SGraphics::GCOLOR m_foreground2;
  int m_score;
  int m_level;
  int m_reml;
  int m_remll;

  int m_flashCount;
  static const int m_flashDelay = 400;
  bool m_flashOn;

  std::string intToString(const int i);

  // temporary for effect
  void drawBackground();

};

#endif // __STATSPANEL_H__
