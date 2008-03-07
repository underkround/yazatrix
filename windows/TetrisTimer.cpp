
/**
 * TetrisTimer
 *
 * Timer kutsuu TetrisBoard::tick() tasaisin väliajoin.
 * Jokaisella tickillä palikka tippuu.
 * Timerin viivettä voidaan lyhentää (timeria nopeuttaa)
 * määritettyyn rajaan asti.
 *
 * $Id$
 *
 * Unhandled exception at 0x7c918fea in testtimer.exe: 0xC0000005: Access violation writing location 0x00000010.
 *
 */
#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif

#include "../TetrisTimer.h"
#include "../Thread.h"
#include <string>
#include <process.h>
#include <windows.h>

CRITICAL_SECTION CTetrisTimer::sync;

void CTetrisTimer::create(const char* timerName)
{
  (new CTetrisTimer(timerName))->run();
  #ifdef DEBUG
  printf("Ajastin konstruktori.\n");
  #endif
}

void CTetrisTimer::setPause() {
  m_intIsRunning = !m_intIsRunning;
}

void CTetrisTimer::resetTick() {
  /**
   * Resetoi ajan seuraavaan tickiin, eli jos tickin viive
   * olisi vaikkapa 500ms, josta olisi jäljellä 150ms, tämän
   * kutsumisen jälkeen seuraava tick tulee 500ms kuluttua.
   */
}

void CTetrisTimer::code() {
  setPause();
  laskuri = 1;
  while(isRunning()) {
    Sleep(1000);
    //EnterCriticalSection(&sync);
    tick();
    //LeaveCriticalSection(&sync);
  }
}

void CTetrisTimer::tick() {
  #ifdef DEBUG
  printf("TIK! (%d).\n", laskuri++);
  #endif
}
