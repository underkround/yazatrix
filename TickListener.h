#ifndef __TICKLISTENER_H__
#define __TICKLISTENER_H__

/**
 * TickListener.h
 *
 * $Revision$
 * $Id$
 *
 * Abstrakti luokka / interface, josta perivä luokka voi saada
 * tickin sleeper/timer luokalta.
 */

class VTickListener {

public:

  /**
   * handleTick()
   *
   * Kutsutaan timerin/sleeperin viiveen mukaan.
   * Implementoija tekee ajastetun toimintansa tässä metodissa.
   */
  virtual void handleTick() = 0;

};

#endif // __TICKLISTENER_H__
