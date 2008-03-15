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
#include <sstream>

class CStatsPanel : public VStatsListener, public VPanel {

public:

  CStatsPanel(const CTetrisStats *stats, const int x, const int y);

  virtual ~CStatsPanel();

  virtual void draw(void);

  virtual void handleChangeInStats(const int score, const int level, const int reml, const int remll);

private:

  SGraphics               *g;
//  SGraphics::BORDER_STYLE  m_borderStyle;
  int m_score;
  int m_level;
  int m_reml;
  int m_remll;

  std::string intToString(const int i);

};

#endif // __STATSPANEL_H__
