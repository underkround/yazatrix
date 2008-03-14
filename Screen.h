#ifndef __SCREEN_H__
#define __SCREEN_H__

/**
 * Screen.h
 *
 * $Revision$
 * $Id*
 *
 * Screen pit‰‰ sis‰ll‰‰n ruudulla n‰kyv‰t containerit, ja se piirt‰‰
 * containerien takana n‰kyv‰‰n alueeseen
 */

#include "Panel.h"
#include "TickListener.h"
#include "StatsListener.h"
#include <vector>

class CScreen : public VTickListener, public VStatsListener {

public:

  enum STATE {
    INTRO, MENU, SETUP, INGAME
  };

  CScreen();

  virtual ~CScreen();

  void setState(STATE newState);

  void add(VPanel *panel);

  virtual int handleTick();

  virtual void handleChangeInStats(const int score, const int level, const int reml, const int remll);

private:

  static const int TICKDELAY = 100;
  STATE m_state;

  // containerit t‰ll‰, t‰m‰ tuhoaa ne
  std::vector<VPanel*> m_panels;
//	vector<CAnimal*>	m_arrAnimals;

  void paint(void);

};

#endif // __SCREEN_H__
