#ifndef __TETRISTIMER_H__
#define __TETRISTIMER_H__

#define DEBUG

//#include "TetrisBoard.h"
#include "Thread.h"
#include <string>
#include <process.h>
#include <windows.h>

/**
 * TetrisTimer
 *
 * Timer kutsuu TetrisBoard::tick() tasaisin v‰liajoin.
 * Jokaisella tickill‰ palikka tippuu.
 * Timerin viivett‰ voidaan lyhent‰‰ (timeria nopeuttaa)
 * m‰‰ritettyyn rajaan asti.
 *
 * TODO: tarkista oikeat viiveet tetrisconsept -wikist‰
 *
 */

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
