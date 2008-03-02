#ifndef __TETRISBOARD_H__
#define __TETRISBOARD_H__

#include "TetrisBoard.h"

/**
 * Tetromino
 *

 TODO:
   ongelma:
    palikan muoto ja rotaatiot tulee antaa konstruktorissa (blockfactory antaa ne),
    mutta miten muoto pidet��n? ja onko pivot point aina toinen piste x ja y-suunnassa?
    l�hdet��n siit� ett� annetaan ainoastaan rotaation 0 muoto, jota py�ritet��n
    laskennallisesti, eli getRotation(int r)-metodi palauttaa halutun rotaation r
   metodit joihin t�m� vaikuttaa:
    konstruktori
    getRotation(int r)

 * Palikka huolehtii seuraavista asioista:
 *  - palikka voi olla liitettyn� yhteen pelilautaan kerrallaan
 *  - palikka tiet�� muotonsa ja mahdolliset rotaationsa
 *  - palikka tiet�� omat koordinaattinsa pelilaudalla
 *  - palikka osaa k��nt�� omaa rotaatiotaan, ja tiet�� uudet koordinaattinsa
 *    pelilaudalla
 *  - palikka osaa liikuttaa itse��n eri suuntiin, ja tiet�� uudet
 *    koordinaattinsa pelilaudalla
 *  - palikka osaa muuttuessaan testata ett� sen ruudut ovat tyhj�t
 *    pelilaudalla
 *  - palikka osaa "polttaa/maalata" itsens� pelilautaan kun sen tila on
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
     * Konstruktori, jossa m��ritet��n palikan muoto, sek� mit� se maalaa
     * pelilautaan kohdalleen, ja mit� se j�tt�� j�lkeens� (tyhj�� yleens�)
     */
    CTetromino(int SLOT_TYPE slotType, SLOT_TYPE emptySlotType);

    ~CTetromino(void);



// ===========================================================================
// PRIVATE
// ===========================================================================

private:

    /**
     * Kentt� (TetrisBoard), johon t�m� palikka on kiinnittyneen�.
     * NULL, jos palikka ei ole kiinni miss��n kent�ss�.
     */
    TetrisBoard board;

    /**
     * mySlotType = palikan oma tyyppi, jota se piirt�� pelikentt��n
     * omiin koordinaatteihinsa
     * EmptySlotType = tyhj� ruutu jota palikka piirt�� vanhaan
     * sijaintiinsa, kun se liikkuu uusiin ruutuihin.
     */
    const SLOT_TYPE mySlotType;
    static const SLOT_TYPE emptySlotType;

    /**
     * Palikan koordinaatit nykyisess� kent�ss��n.
     * Palikka tarkistaa kentt��n kiinnittyess��n, ett� sen sijainti
     * koordinaateissa on sallittu, tai kiinnittymist� ei tapahdu.
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
     * @return  false, jos joku palikan ruuduista ei ole tyhj� laudalla,
     *          tai jos palikka menee ohi laudasta sivusuunnassa (tai pohjasta)
     */
    bool canMoveTo(const int newX, const int newY, const int newOrientation);

//    bool getOrientationX... TODO!!

    /**
     * @return  nykyinen rotaatio (arvo v�lilt� 0..3)
     */
    short getRotation();

    /**
     * @return  nykyisest� seuraava rotaatio (py�r�ytett�ess� my�t�p�iv��n)
     *          arvo v�lilt� 0..3
     */
    short getNextRotation();

    /**
     * @return  nykyisest� edellinen rotaatio (py�r�ytett�ess� vastap�iv��n)
     *          arvo v�lilt� 0..3
     */
    short getPreviousRotation();

    /**
     * "Polttaa" palikan pelilaudan kentt��n, eli vaihtaa omat ruutunsa
     * pelilaudassa oman tyyppins� mukaisiksi.
     */
    void insertToBoard();

    /**
     * Poistaa itsens� pelilaudalta, eli kirjoittaa tyhj�n ruudun arvon
     * jokaiseen ruutuunsa pelilaudassa
     */
    void removeFromBoard();

};

#endif //__TETRISBOARD_H__
