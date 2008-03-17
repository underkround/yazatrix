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
 *   - vaihdettiin vektori pointteritaulukkoon
 */

#include "Singleton.h"
#include "TickListener.h"
#include "CommandListener.h"
#include "Observable.h"
#include <stdio.h>

class SKeyboardInput : public VObservable<VCommandListener>, public Singleton<SKeyboardInput>, public VTickListener {
//class SKeyboardInput : public VObservable<VCommandListener>, public VTickListener {

friend class Singleton<SKeyboardInput>;
friend class VObservable<VCommandListener>;

public:

/*  static SKeyboardInput& getInstance() {
    static SKeyboardInput theSingleInstance;  // assumes T has a protected default constructor
    return theSingleInstance;
  }*/

  /**
   * @see TickListener.h
   */
  virtual int handleTick();

private:

//  std::vector<VCommandListener*> listeners;

  int m_tickDelay;



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
   * pakotetaan käyttämään Instance() -metodia
   *
   * Rekisteröidytään konstruktorissa STickerille tick-listeneriksi,
   * että saadaan prosessoriaikaa näppäimistöbufferin lukuun.
   */
  SKeyboardInput();

  virtual ~SKeyboardInput();

};

#endif // __KEYBOARDINPUT_H__
