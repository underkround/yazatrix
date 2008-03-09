/**
 * windows/Thread.cpp
 *
 * $Revision$
 * $Id$
 *
 * @see Thread.h
 *
 */

#include <stdlib.h>
#include <process.h>
#include <windows.h>
#include "../Thread.h"

CThread::CThread() : running(0) , m_pid(0L) {}

void CThread::run()
{
    // Don't start two threads on the same object
    if (running) return;

    // Create an OS thread, using the static callback
    m_pid = _beginthread(CThread::dispatch, 0, this);
    running = 1;
}

void CThread::dispatch(void* thread_obj)
{
    // Call the actual OO thread code
    ((CThread*)thread_obj)->code();

    // After code() returns, kill the thread object
    delete (CThread*)thread_obj;
}
