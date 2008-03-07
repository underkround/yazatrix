#ifndef __TETROMINO_H__
#define __TETROMINO_H__

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

#include "TetrisCommon.h"
#include "TetrisBoard.h"

class CTetromino {

public:

  /**
   * Konstruktori, jossa määritetään palikan muoto, sekä mitä se "maalaa"
   * boardiin sijaintiinsa.
   */
  CTetromino(int cellCoordsX[4], int cellCoordsY[4], int maxRotation, CELL_TYPE type);

  ~CTetromino(void);

  // ================= METODIT =============================================

#ifdef __DEBUG
  inline int getX() { return m_x; }
  inline int getY() { return m_y; }
#endif // __DEBUG

  /**
   * Kääntää palikkaa myötäpäivään
   */
  bool rotateRight(void);

  /**
   * Kääntää palikkaa vastapäivään
   */
  bool rotateLeft(void);

  /**
   * @return true, jos palikka on kiinnitetty johonkin boardiin
   */
  bool isAttached(void);

  /**
   * Kiinnittää palikan lautaan jos ei tule collisionia (jolloin palauttaa
   * false).
   * Kiinnittyminen tapahtuu vaakasuunnassa keskelle, pystysuunnassa
   * palikan pivot-point/origo tulee kentän ylimpään riviin. Jos palikka
   * on ennestään toisessa laudassa, tehdään siihen ensin clean detach.
   */
  bool attach(CTetrisBoard *targetBoard);

  /**
   * Kiinnittyy boardiin jos ei tule collisionia (collisionissa liitosta ei
   * tapahdu ja palautetaan false)
   * Kiinnittyminen tapahtuu vaakasuunnassa keskelle, pystysuunnassa laudan
   * ylimpään koordinaattiin + offset
   */
  bool attach(CTetrisBoard *targetBoard, int offsetY);

  bool attach(CTetrisBoard *targetBoard, int offsetX, int offsetY);

  /**
   * Detachaa nykyisestä boardista, jos clear = true, tyhjää sijaintinsa laudassa
   */
  bool detach(bool clear);

  /**
   * Detachaa nykyisestä boardista, ei tyhjää sijaintinsa laudassa
   */
  bool detach();

  bool moveLeft(void);

  bool moveRight(void);

  bool moveUp(int n);

  bool moveDown(void);

  bool moveDown(int n);

  /**
   * Tiputtaa palikkaa niinkauan alas kuin se ei törmää mihinkään
   */
  bool drop(void);

  /**
   * Onko palikka laskeutunut:
   * a) seuraava tiputus olisi collision
   * b) palikka ei ole missään boardissa
   */
  bool hasLanded(void);

  /**
   * Palikka on boardissa ja jokainen sen ruutu on laudan sisäpuolella
   * (palikka voi aluksi olla yläpuolelta boardin ulkopuolella)
   */
  bool isFullyVisible(void);

// ===========================================================================
// PRIVATE
// ==

private:

  /**
   * Kenttä (TetrisBoard), johon tämä palikka on kiinnittyneenä.
   * NULL, jos palikka ei ole kiinni missään kentässä.
   */
  CTetrisBoard *board;

  /**
   * palikan oma tyyppi, jota se piirtää pelikenttään
   * omiin koordinaatteihinsa
   */
  CELL_TYPE m_type;

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
  int m_rotationMax;

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

  /** Ylläoleva omalla laudalla */
  bool canMoveTo(const int x, const int y, const int rotation, CTetrisBoard *targetBoard);

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
      return (m_rotation+1 > m_rotationMax) ? 0 : m_rotation+1;
  }

  /**
   * @return  nykyisestä edellinen rotaatio (pyöräytettäessä vastapäivään)
   *          arvo väliltä 0..3
   */
  inline int getPreviousRotation() {
      return (m_rotation-1 < 0) ? m_rotationMax : m_rotation-1;
  }

  /**
   * Palauttaa halutun rotaation relatiivisen koordinaatin
   */
  int getRelativeX(const int x, const int rotation);
  int getRelativeY(const int y, const int rotation);

  /** Laske mikä on boardin keski-x -koordinaatti */
  int getBoardCenterX(CTetrisBoard *targetBoard);

  /** Testaa onko boardin koordinaatti {x,y} tämän palikan */
  bool containsBoardCoord(int x, int y);

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

#endif //__TETROMINO_H__
