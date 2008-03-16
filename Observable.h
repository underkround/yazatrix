#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__
/**
 * Observable.h
 *
 * $Revision$
 * $Id$
 *
 * Observable antaa toteutuksen yhteiseen toiminnallisuuteen luokille,
 * jotka ottavat kuuntelijoita.
 * Observable hoitaa kuuntelijoiden rekisteröitymisen ja kuuntelijalistasta
 * poistamisen.
 *
 */

//template<typename T> class VObservable {
template <class T> class VObservable {

public:

  /**
   * registerCommandListener(VCommandListener *listener)
   *
   * Rekisteröi uuden komentokuuntelijan
   * @param listener  rekisteröityvä kuuntelija
   * @return          true, jos kuuntelijoihin mahtui ja rekisteröinti onnistui
   */
  bool registerListener(T *listener);

  /**
   * unregisterCommandListener(VCommandListener *listener)
   *
   * Poistaa rekisteröityneen kuuntelijan kuuntelijalistalta.
   * @param listener  poistettava kuuntelija
   * @return          true, jos poistettava löytyi listasta ja poisto onnistui
   */
  bool unregisterListener(T *listener);

protected:

  VObservable(void);

  static const int LISTENERS_MAX = 10;
  T *listeners[LISTENERS_MAX];
  int m_listenerCount;

private:

};


template <class T> VObservable<T>::VObservable() {
  m_listenerCount = 0;
}


template <class T> bool VObservable<T>::registerListener(T *listener) {
  if(m_listenerCount >= LISTENERS_MAX)
    return false;
  listeners[m_listenerCount] = listener;
  m_listenerCount++;
  return true;
}


template <class T> bool VObservable<T>::unregisterListener(T *listener) {
  int index = -1;
  for(int i=0; i<m_listenerCount; i++) {
    if(listeners[i] == listener) {
      index = i;
      i = m_listenerCount;
      break;
    }
  }
  if(index >= 0) {
    // poistettava löytyi
    listeners[index] = 0;
    m_listenerCount--;
    for(int i=index; index<m_listenerCount; i++) {
      listeners[i] = listeners[i+1]; // siirretään poistetusta seuraavia yhdellä alaspäin
    }
    listeners[m_listenerCount] = 0; // tyhjätään viimeinen alkio, joka olisi nyt kaksi kertaa listassa
    return true;
  }
  return false;
}

#endif // __OBSERVABLE_H__
