#ifndef __BOARDCHANGELISTENER_H__
#define __BOARDCHANGELISTENER_H__

/**
 * Abstrakti luokka / interface
 * jolle voidaan v‰litt‰‰ tieto kun laudan sis‰ltˆ muuttuu.
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

class VBoardChangeListener {
  public:

    /**
     * T‰t‰ kutsutaan kun boardissa on tapahtunut suuri muutos,
     * ja sen uudelleenpiirt‰mist‰ kokonaan suositellaan.
     */
    virtual void handleFreshBoard() = 0;

    /**
     * Vastaanottaa listan boarissa muuttuneista koordinaateista.
     * Kaksi listaa pit‰v‰t sis‰ll‰‰n koordinaattiparit, eli
     * x-koordinaatit toisessa ja y- toisessa.
     * Apumuuttuja numCoords kertoo helpottaa kertomalla montako
     * koordinaattia on muuttunut.
     * Kuuntelija voi hakea boardilta muuttuneet koordinaatit, tai
     * j‰tt‰‰ hakematta.
     *
     * Ilmoituksen l‰hett‰j‰ vastaa taulun tuhoamisesta.
     */
    virtual void handleChangeInCoords(int *changedCoordsX[], int *changedCoordsY[], int numCoords) = 0;

    /**
     * Vastaanottaa tiedon, boardin muuttuneista riveist‰.
     * Parametrina tuotu taulukko kertoo muuttuneet rivit, jotka tulisi
     * hakea ja n‰ytt‰‰ uudestaan. Taulukko sis‰lt‰‰ y-koordinaatteja.
     *
     * Ilmoituksen l‰hett‰j‰ vastaa taulun tuhoamisesta.
     */
    virtual void handleChangeInLines(int *changedLines[], int numLines) = 0;

    /**
     * Tehd‰‰np‰ nyt muutoksia silm‰ll‰pit‰en myˆs yhden koordinaatin
     * muuttuminen, vaikkei sit‰ ehk‰ k‰ytett‰isik‰‰n. Vaikkapa
     * nopeustestien varalle.
     * Ei pit‰isi olla suuri homma implementoida =)
     */
    virtual void handleChangeInCoord(int x, int y) = 0;

};

#endif // __BOARDCHANGELISTENER_H__
