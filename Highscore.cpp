#include "Highscore.h"

CHighscore::CHighscore() {
  g = &SGraphics::getInstance();
}

CHighscore::~CHighscore() {
  for (vector<Score*>::iterator iter = scores.begin(); iter!=scores.end(); ++iter) {
    delete *iter;
  }
}
