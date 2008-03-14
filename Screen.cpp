#include "Screen.h"
#include "Ticker.h"

CScreen::CScreen() {
  m_state = INTRO;
}

CScreen::~CScreen() {
}

void CScreen::setState(STATE newState) {
  if(newState != m_state) {
    // tuhoa vanhat containerit
    for(unsigned int i=0; i<m_panels.size(); i++) {
      VPanel* panel = m_panels[i];
      delete panel;
    }
    m_panels.clear();
    // aseta uusi state
    switch(newState) {
      case INTRO:
        m_state = INTRO;
        break;
      case INGAME:
        m_state = INGAME;
//        STicker::getInstance().registerListener( dynamic_cast<VTickListener*>(this) );
        break;
      default:
        break;
    }
  }
}

void CScreen::add(VPanel *panel) {
}

void CScreen::handleChangeInStats(const int score, const int level, const int reml, const int remll) {
}

int CScreen::handleTick() {
  return -1;
}
