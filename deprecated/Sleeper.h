#ifndef __SLEEPER_H__
#define __SLEEPER_H__

/**
 * Sleeper.h
 *
 * $Revision$
 * $Id$
 *
 * Sleeper on ajastin, joka nukkuu s‰‰detyn ajan ja kutsuu
 * jokaisen nukkumisen j‰lkeen annettua tick-kuuntelijaa.
 * Ajastimen viivett‰ voidaan s‰‰t‰‰ eri tavoin, ja se voidaan
 * pys‰ytt‰‰.
 */

#include "TickListener.h"

class {

public:

  Sleeper(VTickListener tickListener);

  virtual ~Sleeper();

  virtual void setDelayMillis(int msDelay);

  /**
   * pause(bool pauseState)
   *
   * Keskeytt‰‰ timerin.
   *
   * @param pauseState  true pys‰ytt‰‰ timerin, false k‰ynnist‰‰ sen uudestaan
   */
  virtual void pause(bool pauseState);

  /**
   * start();
   *
   * K‰ynnist‰‰ sleeperin.
   */
  virtual void start();

  /**
   * stop()
   *
   * Pys‰ytt‰‰ sleeperin.
   */
  virtual void stop();

  /**
   * resetTick()
   *
   * Aloittaa tickin laskemisen alusta.
   * Esim:  Jos viive olisi vaikkapa 500ms, ja resetTick() metodia
   *        kutsutaan kun viiveest‰ on kulunut 300ms, tulee seuraava
   *        tick 800ms kuluttua edellisest‰.
   */
  virtual void resetTick(void);

  /**
   * skipTick(int skips)
   *
   * J‰tt‰‰ parametrina annetun m‰‰r‰n tickej‰ v‰list‰.
   *
   * @param skips   v‰liin j‰tett‰vien tickien lukum‰‰r‰
   */
  virtual void skipTick(int skips);

private:

  bool            m_paused;
  VTickListener   *listener; // kenen ticki‰ kutsutaan


};

#endif // __SLEEPER_H__
