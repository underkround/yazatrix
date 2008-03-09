#ifndef __TETRISTIMER_H__
#define __TETRISTIMER_H__

/**
 * TetrisTimer.h
 *
 * $Revision$
 * $Id$
 *
 * Timer kutsuu TetrisBoard::tick() tasaisin v‰liajoin.
 * Jokaisella tickill‰ palikka tippuu.
 * Timerin viivett‰ voidaan lyhent‰‰ (timeria nopeuttaa)
 * m‰‰ritettyyn rajaan asti.
 *
 * TODO: tarkista oikeat viiveet tetrisconsept -wikist‰
 *
 */

#include "Thread.h"
#include <string>
#include <process.h>
#include <windows.h>

#define DEBUG

class CTetrisTimer : private CThread {

public:

  // TODO: ilmoitetaanko viive millisekunteina ja levelin‰?
  // zemm prefers: level, koska viivelogiikka on
  static void CTetrisTimer::create(const char* timerName);
  static CRITICAL_SECTION sync;

  void setPause();

  /**
   * resetTick()
   *
   * Resetoi ajan seuraavaan tickiin, eli jos tickin viive
   * olisi vaikkapa 500ms, josta olisi j‰ljell‰ 150ms, t‰m‰n
   * kutsumisen j‰lkeen seuraava tick tulee 500ms kuluttua.
   */
  void resetTick();

  inline bool isRunning() { return m_intIsRunning; }

  /**
   * adjust(int tetrominoCount, int level, int removedLines)
   *
   * K‰sket‰‰n timeria tarkistamaan viiveens‰ annettujen
   * parametrien perusteella.
   * Timerin asia on pit‰‰ algoritmi jolla viive lasketaan,
   * ja p‰‰tt‰‰ mink‰ perusteella se lasketaan..
   *
   * @param tetrominoCount  pelilaudalla olleiden palikoiden m‰‰r‰
   * @param level           pelin level
   * @param removedLines    r‰j‰ytettyjen rivien m‰‰r‰
   */
  void adjust(int tetrominoCount, int level, int removedLines);

// ==================== PRIVATE =========================

//private:
  /**
   * run()
   *
   * Timerin k‰ynnistys
   */
  void code();

  /**
   * tick();
   *
   * Tehd‰‰n ne asiat mit‰ tickatessa halutaan tehd‰.
   */
  void tick();

  CTetrisTimer(const char* timerName) : name(timerName) {}
  std::string name;
  bool m_intIsRunning;
  int m_intStartValue;
  int m_intMaxValue;
  #ifdef DEBUG
  int laskuri;
  #endif
};

#endif // __TETRISTIMER_H__
