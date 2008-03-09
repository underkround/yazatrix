#ifndef __THREAD_H__
#define __THREAD_H__

/**
 * Thread.h
 *
 * $Revision$
 * $Id$
 *
 */

class CThread {
public:
    virtual ~CThread() {}
    void run();
    unsigned long pid() const { return m_pid; }

protected:
    CThread();
    virtual void code() = 0;

private:
    bool m_boolRunning;
    unsigned long m_pid;

    static void dispatch(void* thread_obj);
};
#endif //__THREAD_H__
