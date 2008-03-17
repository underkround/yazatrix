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
