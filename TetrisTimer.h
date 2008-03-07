#ifndef __TETRISTIMER_H__
#define __TETRISTIMER_H__

#include "TetrisBoard.h"

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

class CTetrisTimer {

public:

  // TODO: ilmoitetaanko viive millisekunteina ja levelin‰?
  // zemm prefers: level, koska viivelogiikka on
  CTetrisTimer(const int startValue, const int maxValue);

  ~CTetrisTimer(void);

  void setPause(bool pause);

  /**
   * resetTick()
   *
   * Resetoi ajan seuraavaan tickiin, eli jos tickin viive
   * olisi vaikkapa 500ms, josta olisi j‰ljell‰ 150ms, t‰m‰n
   * kutsumisen j‰lkeen seuraava tick tulee 500ms kuluttua.
   */
  void resetTick();

// ==================== PRIVATE =========================

private:

};

#endif // __TETRISTIMER_H__
