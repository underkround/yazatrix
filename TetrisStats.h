#ifndef __TETRISSTATS_H__
#define __TETRISSTATS_H__

/**
 * TetrisStats.h
 *
 * $Revision$
 * $Id$
 *
 * TetrisStatus sis‰lt‰‰ logiikan levelin, pisteiden ja viiveen laskemiseen
 * r‰j‰ytettyjen rivien ja peliss‰ olleiden palikoiden perusteella.
 */

#include "StatsListener.h"
#include "Observable.h"

class CTetrisStats : public VObservable<VStatsListener> {

public:

  CTetrisStats();
  ~CTetrisStats();

  void linesRemoved(const int lines);
  void tetrominoAdded(); // ilmoittaa ett‰ uusi palikka on laudalla

  int getLevel();
  int getScore();
  int getRemovedLines();
  int getRemovedLinesLast();
  int getDropDelay();

private:

  static const int LEVEL_MAX = 15;
  int m_tetrominoCounter;
  int m_score;
  int m_level;
  int m_removedLines;
  int m_removedLinesLast;
  int m_dropDelay;
  int m_currentLevelTetrominoCounter;

  void update();
  void notifyChangeInStats();

};

#endif // __TETRISSTATS_H__
