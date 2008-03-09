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

class CTetrisTimer : private CThread {
  public:
  void code();
  private:
  std::string name;
};

#endif //__KEYBOARDINPUT_H__
