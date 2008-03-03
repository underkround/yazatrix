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
     * Konstruktori, jossa m��ritet��n palikan muoto, sek� mit� se maalaa.
     */
    CTetromino(int cellCoordsX[], int cellCoordsY[], int maxRotation, CELL_TYPE type);

    ~CTetromino(void);

    // ================= METODIT =============================================



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
     * palikan oma tyyppi, jota se piirt�� pelikentt��n
     * omiin koordinaatteihinsa
     */
    const CELL_TYPE m_type;

    /**
     * Palikan koordinaatit nykyisess� kent�ss��n.
     * Palikka tarkistaa kentt��n kiinnittyess��n, ett� sen sijainti
     * koordinaateissa on sallittu, tai kiinnittymist� ei tapahdu.
     */
    int m_x;
    int m_y;

    /**
     * Palikan muoto, eli koordinaatit joissa palikalla on solu
     * rotaatiossa 0 (oletus) pivot-pointtinsa suhteen
     * (eli negatiivisia ja positiivisia koordinaatteja).
     * Tetromino koostuu nelj�st� solusta/ruudusta, eli tetrominolla
     * tauluissa on aina nelj� koordinaattiparia.
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
     * Testaa voiko palikka olla laudalla annetuissa koordinaateissa,
     * annetulla orientaatiolla.
     *
     * @return  false, jos joku palikan ruuduista ei ole tyhj� laudalla,
     *          tai jos palikka menee ohi laudasta sivusuunnassa (tai pohjasta)
     */
    bool canMoveTo(const int x, const int y, const int rotation);

    /**
     * @return  nykyinen rotaatio (arvo v�lilt� 0..3)
     */
    inline int getRotation() {
        return m_rotation;
    }

    /**
     * @return  nykyisest� seuraava rotaatio (py�r�ytett�ess� my�t�p�iv��n)
     *          arvo v�lilt� 0..3
     */
    inline int getNextRotation() {
        return (m_rotation+1 > m_rotationMax) ? 0
            : m_rotation+1;
    }

    /**
     * @return  nykyisest� edellinen rotaatio (py�r�ytett�ess� vastap�iv��n)
     *          arvo v�lilt� 0..3
     */
    inline int getPreviousRotation() {
        return (m_rotation-1 < 0) ? m_rotationMax
            : m_rotation-1;
    }

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
