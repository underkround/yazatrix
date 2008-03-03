#ifndef __TETRISBOARD_H__
#define __TETRISBOARD_H__

#include "TetrisBoard.h"

/**
 * Tetromino
 *
 * $Id$
 * $Revision$
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
     * Konstruktori, jossa määritetään palikan muoto, sekä mitä se maalaa.
     */
    CTetromino(int cellCoordsX[], int cellCoordsY[], int maxRotation, CELL_TYPE type);

    ~CTetromino(void);

    // ================= METODIT =============================================

    /** Palauttaa nykyisen rotaation */
    int getRotation();

    /** Kääntää palikkaa myötäpäivään */
    bool rotateRight();

    /** Kääntää palikkaa vastapäivään */
    bool rotateRight();

    /** @return true jos palikka on kiinnitetty johonkin boardiin */
    bool isAttached();

    /**
     * Kiinnittää palikan lautaan jos ei tule collisionia (jolloin palauttaa
     * false).
     * Kiinnittyminen tapahtuu vaakasuunnassa keskelle, pystysuunnassa
     * palikan pivot-point/origo tulee kentän ylimpään riviin. Jos palikka
     * on ennestään toisessa laudassa, tehdään siihen ensin clean
     * detach.
     */
    bool attach(TetrisBoard board);

    /**
     * Kiinnittyy boardiin jos ei tule collisionia (collisionissa liitosta ei
     * tapahdu ja palautetaan false)
     * Kiinnittyminen tapahtuu vaakasuunnassa keskelle, pystysuunnassa laudan
     * ylimpään koordinaattiin + offset
     */
    bool attach(TetrisBoard board, int offsetY);

    /** Detachaa nykyisestä boardista, jos bool = true, tyhjää sijaintinsa laudassa */
    bool detach(bool clear);

    bool moveLeft();

    bool moveRight();

    bool moveUp(int n);

    bool moveDown();

    bool moveDown(int n);

    bool drop();

    bool contains(const int x, const int y);

    /**
     * Onko palikka laskeutunut:
     * a) seuraava tiputus olisi collision
     * b) palikka ei ole missään boardissa
     */
    void hasLanded();

    /**
     * Palikka on boardissa ja jokainen sen ruutu on laudan sisäpuolella
     * (palikka voi aluksi olla yläpuolelta boardin ulkopuolella)
     */
    bool isFullyVisible();

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
     * palikan oma tyyppi, jota se piirtää pelikenttään
     * omiin koordinaatteihinsa
     */
    const CELL_TYPE m_type;

    /**
     * Palikan koordinaatit nykyisessä kentässään.
     * Palikka tarkistaa kenttään kiinnittyessään, että sen sijainti
     * koordinaateissa on sallittu, tai kiinnittymistä ei tapahdu.
     */
    int m_x;
    int m_y;

    /**
     * Palikan muoto, eli koordinaatit joissa palikalla on solu
     * rotaatiossa 0 (oletus) pivot-pointtinsa suhteen
     * (eli negatiivisia ja positiivisia koordinaatteja).
     * Tetromino koostuu neljästä solusta/ruudusta, eli tetrominolla
     * tauluissa on aina neljä koordinaattiparia.
     */
    int m_cellCoordsX[4];
    int m_cellCoordsY[4];

    /**
     * Palikan nykyinen orientaatio
     *
     * Orientaatio on
     */
    int m_rotation;

    /**
     * Palikan suurin sallittu rotaatio (0 -> m_rotationMax)
     * Asetetaan constructorissa.
     */
    const int m_rotationMax;

    // ================= METODIT =============================================

    /**
     * Asettaa rotaaion r jos mahdollista
     * @return  asettamisen onnistuminen
     */
    bool setRotation(int r);

    /**
     * Testaa voiko palikka olla laudalla annetuissa koordinaateissa,
     * annetulla orientaatiolla.
     *
     * @return  false, jos joku palikan ruuduista ei ole tyhjä laudalla,
     *          tai jos palikka menee ohi laudasta sivusuunnassa (tai pohjasta)
     */
    bool canMoveTo(const int x, const int y, const int rotation);

    /**
     * @return  nykyinen rotaatio (arvo väliltä 0..3)
     */
    inline int getRotation() {
        return m_rotation;
    }

    /**
     * @return  nykyisestä seuraava rotaatio (pyöräytettäessä myötäpäivään)
     *          arvo väliltä 0..3
     */
    inline int getNextRotation() {
        return (m_rotation+1 > m_rotationMax) ? 0
            : m_rotation+1;
    }

    /**
     * @return  nykyisestä edellinen rotaatio (pyöräytettäessä vastapäivään)
     *          arvo väliltä 0..3
     */
    inline int getPreviousRotation() {
        return (m_rotation-1 < 0) ? m_rotationMax
            : m_rotation-1;
    }

    /**
     * Palauttaa halutun rotaation relatiivisen koordinaatin
     */
    int getRelativeX(const int x, const int rotation);
    int getRelativeY(const int y, const int rotation);

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
