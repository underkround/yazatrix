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
   * Rekisteröi uuden komentokuuntelijan
   * @param listener    rekisteröityvä kuuntelija
   */
  void registerCommandListener(VCommandListener *listener);

  /**
   * unregisterCommandListener(VCommandListener *listener)
   *
   * Poistaa rekisteröityneen kuuntelijan kuuntelijalistalta.
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
