#ifndef __HIGHSCORE_H_INCLUDED__
#define __HIGHSCORE_H_INCLUDED__

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Graphics.h"

#define SCORE_AMOUNT 10 //topten

//miten on, mahtaako näiden using lauseiden yksitellen määrittäminen vaikuttaa käännöksen lopputulokseen?
using std::vector;
using std::cout;
using std::string;

class CHighscore {
  struct Score {
    string name;
    int score;
  };

public:
  CHighscore(void);
  virtual ~CHighscore(void);

  /**
   * loadScores
   *
   * Ladataan pistedata tiedostosta.
   */
  void loadScores();

  /**
   * saveScore
   *
   * Lisää pistedatan listaan. Sorttaa listan ja tallentaa SCORE_AMOUNT määrän parhaita pisteitä tiedostoon.
   */
  void saveScore(string playerName, int playerScore);
  //std::sort(scores->begin, scores->end, vertailuehto)
  //vertailuehto(x, y) 	The ordered pair (x,y) 	  Returns true if x precedes y, and false otherwise

  inline void setFilename(string filename) { m_strFilename = filename; };
  inline string getFilename() { return m_strFilename; };

private:
  SGraphics * g;
  vector<Score*> scores;
  string m_strFilename;
};


#endif // __HIGHSCORE_H_INCLUDED__
