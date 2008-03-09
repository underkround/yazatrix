#ifndef __COMMANDLISTENER_H__
#define __COMMANDLISTENER_H__

/**
 * CommandListener.h
 *
 * $Revision$
 * $Id$
 *
 * Abstrakti luokka / interface, jonka perivä luokka (esimerkiksi
 * pelilogiikka ja menu) voi vastaanottaa komentoja (esimerkiksi
 * näppäimistökuuntelijalta).
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
    GAME_COMMAND_ROTATE_CW,   // kääntää palikkaa myötäpäivään
    GAME_COMMAND_ROTATE_CCW,  // kääntää palikkaa vastapäivään
    GAME_COMMAND_SOFTDROP,    // tiputtaa yhdellä rivillä, resetoi tickin
    GAME_COMMAND_HARDDROP,    // tiputtaa palikan alas, resetoi tickin
  //  GAME_COMMAND_SWAP,        // vaihtaa nykyisen ja seuraavan palikan keskenään (vain kerran) --> implementoidaan joskus jos huvittaa
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
