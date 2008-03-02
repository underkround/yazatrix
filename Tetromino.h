#ifndef __TETRISBOARD_H__
#define __TETRISBOARD_H__

#include "TetrisBoard.h"

/**
 * Tetromino
 *

 TODO:
   ongelma:
    palikan muoto ja rotaatiot tulee antaa konstruktorissa (blockfactory antaa ne),
    mutta miten muoto pidetään? ja onko pivot point aina toinen piste x ja y-suunnassa?
    lähdetään siitä että annetaan ainoastaan rotaation 0 muoto, jota pyöritetään
    laskennallisesti, eli getRotation(int r)-metodi palauttaa halutun rotaation r
   metodit joihin tämä vaikuttaa:
    konstruktori
    getRotation(int r)

 * Palikka huolehtii seuraavista asioista:
 *  - palikka voi olla liitettynä yhteen pelilautaan kerrallaan
 *  - palikka tietää muotonsa ja mahdolliset rotaationsa
 *  - palikka tietää omat koordinaattinsa pelilaudalla
 *  - palikka osaa kääntää omaa rotaatiotaan, ja tietää uudet koordinaattinsa
 *    pelilaudalla
 *  - palikka osaa liikuttaa itseään eri suuntiin, ja tietää uudet
 *    koordinaattinsa pelilaudalla
 *  - palikka osaa muuttuessaan testata että sen ruudut ovat tyhjät
 *    pelilaudalla
 *  - palikka osaa "polttaa/maalata" itsensä pelilautaan kun sen tila on
 *    muuttunut
 *  - palikan tilan muuttuessa se osaa asettaa vanhat ruutunsa laudalla
 *    tyhjiksi
 *  - palikka osaa kertoa onko se laskeutunut (seuraava tiputus osuisi laudan
 *    maastoon)
 *
 */

class CTetromino {

public:

    /**
     * Konstruktori, jossa määritetään palikan muoto, sekä mitä se maalaa
     * pelilautaan kohdalleen, ja mitä se jättää jälkeensä (tyhjää yleensä)
     */
    CTetromino(int SLOT_TYPE slotType, SLOT_TYPE emptySlotType);

    ~CTetromino(void);



// ===========================================================================
// PRIVATE
// ===========================================================================

private:

    /**
     * Kenttä (TetrisBoard), johon tämä palikka on kiinnittyneenä.
     * NULL, jos palikka ei ole kiinni missään kentässä.
     */
    TetrisBoard board;

    /**
     * mySlotType = palikan oma tyyppi, jota se piirtää pelikenttään
     * omiin koordinaatteihinsa
     * EmptySlotType = tyhjä ruutu jota palikka piirtää vanhaan
     * sijaintiinsa, kun se liikkuu uusiin ruutuihin.
     */
    const SLOT_TYPE mySlotType;
    static const SLOT_TYPE emptySlotType;

    /**
     * Palikan koordinaatit nykyisessä kentässään.
     * Palikka tarkistaa kenttään kiinnittyessään, että sen sijainti
     * koordinaateissa on sallittu, tai kiinnittymistä ei tapahdu.
     */
    int m_intX;
    int m_intY;

    /**
     * Palikan nykyinen orientaatio
     *
     * Orientaatio on
     */
    short m_shortOrientation;

    /**
     * Palikan suurin sallittu orientaatio (0 -> maxOrientation)
     * Asetetaan constructorissa.
     */
    const short m_shortMaxOrientation

    // ================= METODIT =============================================

    /**
     * Testaa voiko palikka olla laudalla annetuissa koordinaateissa,
     * annetulla orientaatiolla.
     *
     * @return  false, jos joku palikan ruuduista ei ole tyhjä laudalla,
     *          tai jos palikka menee ohi laudasta sivusuunnassa (tai pohjasta)
     */
    bool canMoveTo(const int newX, const int newY, const int newOrientation);

//    bool getOrientationX... TODO!!

    /**
     * @return  nykyinen rotaatio (arvo väliltä 0..3)
     */
    short getRotation();

    /**
     * @return  nykyisestä seuraava rotaatio (pyöräytettäessä myötäpäivään)
     *          arvo väliltä 0..3
     */
    short getNextRotation();

    /**
     * @return  nykyisestä edellinen rotaatio (pyöräytettäessä vastapäivään)
     *          arvo väliltä 0..3
     */
    short getPreviousRotation();

    /**
     * "Polttaa" palikan pelilaudan kenttään, eli vaihtaa omat ruutunsa
     * pelilaudassa oman tyyppinsä mukaisiksi.
     */
    void insertToBoard();

    /**
     * Poistaa itsensä pelilaudalta, eli kirjoittaa tyhjän ruudun arvon
     * jokaiseen ruutuunsa pelilaudassa
     */
    void removeFromBoard();

};

#endif //__TETRISBOARD_H__
