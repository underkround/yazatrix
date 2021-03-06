#ifndef __KEYBOARDINPUT_H__
#define __KEYBOARDINPUT_H__
/**
 * KeyboardInput.h
 *
 * $Revision$
 * $Id$
 *
 * Lukee tickillä näppäinbufferin, ja parsii sen komennoiksi,
 * jotka lähetetään komentokuuntelijoille (VCommandListener)
 * KeyboardInput on singleton, koska vain yksi luokka vaaditaan
 * kuunteluun (yksi näppäimistöbufferi jota lukea..)
 *
 * Changelog
 *   - korvattiin Singleton-templaten käyttö paikallisella getInstance:lla
 *   - vaihdettiin vektori pointteritaulukkoon
 */

#include "TickListener.h"
#include "CommandListener.h"
#include "Observable.h"
#include <stdio.h>

class SKeyboardInput : public VObservable<VCommandListener>, public VTickListener {

friend class VObservable<VCommandListener>;

public:

  /** Access to this singleton class */
  static SKeyboardInput& getInstance() {
    static SKeyboardInput theSingleInstance;
    return theSingleInstance;
  }

  /**
   * @see TickListener.h
   */
  virtual int handleTick();

private:

//  std::vector<VCommandListener*> listeners;

  static const int m_tickDelay = 5;

  inline void dump(char key) {
    printf(" %d ", key);
  }

  /**
   * handleKeyPress(char key)
   *
   * Parsii näppäinpainalluksen näppäinkoodin mukaan
   *
   * @param key   näppäinkoodi
   */
  void handleKeyPress(char key);

  /**
   * notifyCommand(COMMAND cmd)
   *
   * Lähettää näppäinpainallukseen assosioidun komennon
   * kuuntelijoille.
   * @param cmd   kuuntelijoille lähetettävä komento
   */
  void notifyCommand(VCommandListener::COMMAND cmd);

protected:

  /**
   * Konstruktori määritellään näkyvyydellä protected, jolloin
   * pakotetaan käyttämään getInstance() -metodia
   *
   * Rekisteröidytään konstruktorissa STickerille tick-listeneriksi,
   * että saadaan prosessoriaikaa näppäimistöbufferin lukuun.
   */
  SKeyboardInput();

  virtual ~SKeyboardInput();

};

#endif // __KEYBOARDINPUT_H__
