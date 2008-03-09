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

class TKeyboardInput : private CThread {

  public:
  /**
   * Varsinainen koodi joka suoritettaan säiettä ajaessa
   */
  void code();

  private:
  /**
   * Säikeen yksilöivä nimi
   */
  std::string name;
  /**
   * Onko säie käynnissä?
   */
  bool m_intIsRunning;

};

#endif //__KEYBOARDINPUT_H__
