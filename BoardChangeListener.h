#ifndef __BOARDCHANGELISTENER_H__
#define __BOARDCHANGELISTENER_H__

/**
 * BoardChangeListener.h
 *
 * $Revision$
 * $Id$
 *
 * Abstrakti luokka / interface
 * jonka implementoivalle luokalle voidaan v‰litt‰‰ tieto
 * muutoksista laudan sis‰llˆss‰.
 *
 * Kuuntelijan tulee itse rekisterˆity‰ TetrisBoardilleen
 * kuuntelijaksi myBoard->registerChangeListener(this);
 * Kuuntelija on myˆs vastuussa itsens‰ kuuntelijoista poistamisesta
 * myBoard->unregisterChangeListener(this) jos se ei aio
 * en‰‰n kuunnella syyst‰ tai toisesta.
 *
 * Kuuntelija reagoi (tai j‰tt‰‰ reagoimatta) ilmoituksiin
 * haluamallaan tavalla. Luultavasti se haluaa kysy‰ muuttuneet
 * asiat boardin metodeilla: getMatrix() ja getSlot(x, y);
 */

#include "TetrisCommon.h"

class VBoardChangeListener {

public:

  /**
   * T‰t‰ kutsutaan kun boardissa on tapahtunut suuri muutos,
   * ja sen uudelleenpiirt‰mist‰ kokonaan suositellaan.
   */
  virtual void handleFreshBoard() = 0;

  /**
   * handleChangeInLines(int *changedLines[], int numLines)
   *
   * Vastaanottaa tiedon, boardin muuttuneista riveist‰.
   * Parametrina tuotu taulukko kertoo muuttuneet rivit, jotka tulisi
   * hakea ja n‰ytt‰‰ uudestaan. Taulukko sis‰lt‰‰ y-koordinaatteja.
   *
   * Ilmoituksen l‰hett‰j‰ vastaa taulun tuhoamisesta.
   *
   * @param   changedLines[]    taulukko muuttuneista riveist‰
   * @param   numLines          apumuuttuja joka kertoo muuttuneiden
   *                            rivien m‰‰r‰n
   */
  virtual void handleChangeInLines(const int *changedLines[], const int numLines) = 0;

  /**
   * handleChangeInCoord(int x, int y)
   *
   * Tehd‰‰np‰ nyt muutoksia silm‰ll‰pit‰en myˆs yhden solun
   * muuttuminen, vaikkei sit‰ ehk‰ k‰ytett‰isik‰‰n. Vaikkapa
   * nopeustestien varalle.
   * Ei pit‰isi olla suuri homma implementoida =)
   *
   * @param   x     muuttuneen solun x-koordinaatti
   * @param   y     muuttuneen solun y-koordinaatti
   * @param   ct    muuttuneen solun uusi arvo
   */
  virtual void handleChangeInCoord(const int x, const int y, const CELL_TYPE ct) = 0;

  /**
   * handleChangeInStats(int points, int removedLines, int removedTotal, int level)
   *
   * Vastaanottaa tiedon muuttuneista statseista. Ilmoitetaan yleens‰
   * kun pelikentt‰ on poistanut tyhj‰t rivit.
   *
   * @param   score   pistem‰‰r‰ yhteens‰
   * @param   reml    poistetut rivit yhteens‰
   * @param   remll   viimeksi r‰j‰ht‰neet rivit
   * @param   level   pelitaso
   */
  virtual void handleChangeInStats(const int score, const int reml, const int remll, const int level) = 0;

};

#endif // __BOARDCHANGELISTENER_H__
