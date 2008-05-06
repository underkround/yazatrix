
#include "Highscore.h"

CHighscore::CHighscore() {
  g = &SGraphics::getInstance();
  settings = &SConfig::getInstance();
}

CHighscore::~CHighscore() {
  for (vector<Score*>::iterator iter = scores.begin(); iter!=scores.end(); ++iter) {
    delete *iter;
  }
}

//alkaa kuulemma harkkatyö olla liian laaja kurssille muutenkin niin jätetään nämä hiscoret nyt sitten tekemättä
