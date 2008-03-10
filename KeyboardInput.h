#ifndef __KEYBOARDINPUT_H__
#define __KEYBOARDINPUT_H__
/**
 * KeyboardInput.h
 *
 * $Revision$
 * $Id$
 *
 * Lukee tickill� n�pp�inbufferin, ja parsii sen komennoiksi,
 * jotka l�hetet��n komentokuuntelijoille (VCommandListener)
 * KeyboardInput on singleton, koska vain yksi luokka vaaditaan
 * kuunteluun (yksi n�pp�imist�bufferi jota lukea..)
 */

#include "Singleton.h"
#include "TickListener.h"
#include "CommandListener.h"
#include <vector>
#include <stdio.h>

class SKeyboardInput : public Singleton<SKeyboardInput>, public VTickListener {

friend class Singleton<SKeyboardInput>;

public:

  /**
   * @see TickListener.h
   */
  virtual int handleTick();

  /**
   * registerCommandListener(VCommandListener *listener)
   *
   * Rekister�i uuden komentokuuntelijan
   * @param listener    rekister�ityv� kuuntelija
   */
  void registerCommandListener(VCommandListener *listener);

  /**
   * unregisterCommandListener(VCommandListener *listener)
   *
   * Poistaa rekister�ityneen kuuntelijan kuuntelijalistalta.
   * @param listener    poistettava kuuntelija
   */
  void unregisterCommandListener(VCommandListener *listener);

private:

  std::vector<VCommandListener*> listeners;

  inline void dump(char key) {
    printf(" %d ", key);
  }

  /**
   * handleKeyPress(char key)
   *
   * Parsii n�pp�inpainalluksen n�pp�inkoodin mukaan
   *
   * @param key   n�pp�inkoodi
   */
  void handleKeyPress(char key);

  /**
   * notifyCommand(COMMAND cmd)
   *
   * L�hett�� n�pp�inpainallukseen assosioidun komennon
   * kuuntelijoille.
   * @param cmd   kuuntelijoille l�hetett�v� komento
   */
  void notifyCommand(VCommandListener::COMMAND cmd);

protected:

  /**
   * Konstruktori m��ritell��n n�kyvyydell� protected, jolloin
   * pakotetaan k�ytt�m��n Instance() -metodia
   *
   * Rekister�idyt��n konstruktorissa STickerille tick-listeneriksi,
   * ett� saadaan prosessoriaikaa n�pp�imist�bufferin lukuun.
   */
  SKeyboardInput();

  virtual ~SKeyboardInput();

};

#endif // __KEYBOARDINPUT_H__
