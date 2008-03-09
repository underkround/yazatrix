#ifndef __KEYBOARDINPUT_H__
#define __KEYBOARDINPUT_H__

/**
 * KeyboardListener.h
 *
 * $Revision$
 * $Id$
 *
 * Kuuntelee näppäimistösyötettä ja lähettää signaalit itselleen rekisteröityneille kuuntelijoille.
 *
 */

#include "Thread.h"
#include <string>
#include <process.h>
#include <windows.h>
#include <vector>
#include "CommandListener.h"

class TKeyboardInput : private CThread {

public:
  /**
   * Säikeen luontikutsu
   */
  static void TKeyboardInput::create(const char* inputName);

  /**
   * Varsinainen koodi joka suoritettaan säiettä ajaessa
   */
  void code();

  /**
   * registerCommandListener(VCommandListener *listener)
   *
   * Rekisteröi uuden komentokuuntelijan
   * @param listener    rekisteröityvä kuuntelija
   */
  static void registerCommandListener(VCommandListener *listener);

  /**
   * unregisterCommandListener(VCommandListener *listener)
   *
   * Poistaa rekisteröityneen kuuntelijan kuuntelijalistalta.
   * @param listener    poistettava kuuntelija
   */
  static void unregisterCommandListener(VCommandListener *listener);


private:

  static std::vector<VCommandListener*> listeners; // define listeners

  /**
   * Säikeen yksilöivä nimi
   */
  std::string name;


  /**
   * Onko säie käynnissä?
   */
  //bool m_boolRunning;

  /**
   * handleKeyPress(char key)
   *
   * Parsii näppäinpainalluksen näppäinkoodin mukaan
   *
   * @param key   näppäinkoodi
   */
  static void handleKeyPress(char key);

  /**
   * notifyCommand(COMMAND cmd)
   *
   * Lähettää näppäinpainallukseen assosioidun komennon
   * kuuntelijoille.
   * @param cmd   kuuntelijoille lähetettävä komento
   */
  static void notifyCommand(VCommandListener::COMMAND cmd);

  TKeyboardInput(const char* inputName) : name(inputName) {}

};

#endif //__KEYBOARDINPUT_H__
