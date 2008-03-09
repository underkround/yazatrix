#ifndef __COMMANDLISTENER_H__
#define __COMMANDLISTENER_H__

/**
 * CommandListener.h
 *
 * $Revision$
 * $Id$
 *
 * Abstrakti luokka / interface, jonka periv� luokka (esimerkiksi
 * pelilogiikka ja menu) voi vastaanottaa komentoja (esimerkiksi
 * n�pp�imist�kuuntelijalta).
 */

class VCommandListener {

public:

  /**
   * enum COMMAND
   *
   * Lista komennoista joita kuuntelija voi vastaanottaa
   */
  enum COMMAND {
    GAME_COMMAND_LEFT,        // liikuttaa palikkaa vasemmalle
    GAME_COMMAND_RIGHT,       // liikuttaa palikkaa oikealle
    GAME_COMMAND_ROTATE_CW,   // k��nt�� palikkaa my�t�p�iv��n
    GAME_COMMAND_ROTATE_CCW,  // k��nt�� palikkaa vastap�iv��n
    GAME_COMMAND_SOFTDROP,    // tiputtaa yhdell� rivill�, resetoi tickin
    GAME_COMMAND_HARDDROP,    // tiputtaa palikan alas, resetoi tickin
  //  GAME_COMMAND_SWAP,        // vaihtaa nykyisen ja seuraavan palikan kesken��n (vain kerran) --> implementoidaan joskus jos huvittaa
    GAME_COMMAND_PAUSE,       // pause (toggle, on/off)
    GAME_COMMAND_QUIT,        // lopettaa nykyisen pelin
    MENU_COMMAND_UP,
    MENU_COMMAND_DOWN,
    MENU_COMMAND_SELECT,
    MENU_COMMAND_BACK
  };

  /**
   * handleCommand(COMMAND cmd)
   *
   * Vastaanottaa komennon, ja toimii sen mukaan, miten sitten
   * toimiikaan.
   *
   * @param cmd   Annettu komento
   */
  virtual void handleCommand(VCommandListener::COMMAND cmd) = 0;

};

#endif // __COMMANDLISTENER_H__
