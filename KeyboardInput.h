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
 *
 * Changelog
 *   - vaihdettiin vektori pointteritaulukkoon
 */

#include "Singleton.h"
#include "TickListener.h"
#include "CommandListener.h"
#include <stdio.h>

//class SKeyboardInput : public Singleton<SKeyboardInput>, public VTickListener {

class SKeyboardInput : VTickListener {

//friend class Singleton<SKeyboardInput>;

public:

static SKeyboardInput& getInstance() {
  static SKeyboardInput theSingleInstance;  // assumes T has a protected default constructor
  return theSingleInstance;
}

  /**
   * @see TickListener.h
   */
  virtual int handleTick();

  /**
   * registerCommandListener(VCommandListener *listener)
   *
   * Rekister�i uuden komentokuuntelijan
   * @param listener  rekister�ityv� kuuntelija
   * @return          true, jos kuuntelijoihin mahtui ja rekister�inti onnistui
   */
  bool registerCommandListener(VCommandListener *listener);

  /**
   * unregisterCommandListener(VCommandListener *listener)
   *
   * Poistaa rekister�ityneen kuuntelijan kuuntelijalistalta.
   * @param listener  poistettava kuuntelija
   * @return          true, jos poistettava l�ytyi listasta ja poisto onnistui
   */
  bool unregisterCommandListener(VCommandListener *listener);

private:

//  std::vector<VCommandListener*> listeners;
  static const int LISTENERS_MAX = 10;
  int m_tickDelay;

  VCommandListener *listeners[LISTENERS_MAX];
  int m_listenerCount;

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
