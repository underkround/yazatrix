#ifndef __TETRISSTATS_H__
#define __TETRISSTATS_H__

/**
 * TetrisStats.h
 *
 * $Revision$
 * $Id$
 *
 * TetrisStatus contains game's stats in realtime, and is
 * responsible for calculating level, scores and drop delay.
 *
 * Responsibilities:
 *  - count of removed lines
 *  - count of tetrominoes played
 *  - algorithm for calculating level from removed lines & tetrominoes
 *  - algorithm for calculating score from removed lines & tetrominoes
 *  - algorithm for calculating drop delay
 *
 * TetrisStats can have listeners that are notified when game stats
 * are changed. Listeners have to derive from VStatsListener.
 */

#include "StatsListener.h"
#include "Observable.h"
#include "Config.h"

class CTetrisStats : public VObservable<VStatsListener> {

public:

  CTetrisStats();
  ~CTetrisStats();

  /**
   * Notifies TetrisStats that there are new lines removed from
   * gameboard.
   *
   * @param lines   count of lines that were removed in last clear
   */
  void linesRemoved(const int lines);

  /**
   * Notifies TetrisStats of new Tetromino added to gameboard.
   */
  void tetrominoAdded(); // ilmoittaa että uusi palikka on laudalla

  /**
   * Public getters for current statistics.
   *
   * @return    requested stat's value
   */
  int getLevel();
  int getScore();
  int getRemovedLines();
  int getRemovedLinesLast();

  /**
   * Returns current time based drop delay for advancing tetromino
   * in game. Based on current game's statistics. Returned value is
   * milliseconds between drops.
   *
   * @return    milliseconds between drops of current tetromino
   */
  int getDropDelay();

private: // private class members

  static const int  LEVEL_MAX = 15;  // maximum level to reach
  int         m_tetrominoCounter;
  int         m_score;
  int         m_level;
  int         m_removedLines;
  int         m_removedLinesLast;
  int         m_dropDelay;
  int         m_currentLevelTetrominoCounter;
  SConfig     *settings;

private: // private methods

  /**
   * Updates drop-delay, level and score.
   * Called when new tetromino is added to board.
   */
  void update();

  /**
   * Notifies currently registered stats-listeners for update in
   * stats.
   */
  void notifyChangeInStats();

};

#endif // __TETRISSTATS_H__
