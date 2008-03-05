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

#include "CellType.h"
#include "TetrisBoard.h"

class CTetromino {

public:

  /**
   * Konstruktori, jossa määritetään palikan muoto, sekä mitä se maalaa.
   */
  CTetromino(int cellCoordsX[4], int cellCoordsY[4], int maxRotation, CELL_TYPE type);

  ~CTetromino(void);

  // ================= METODIT =============================================

  bool rotateRight(void);

  bool rotateLeft(void);
  bool isAttached(void);

  bool attach(CTetrisBoard *targetBoard);

  bool attach(CTetrisBoard *targetBoard, int offsetY);

  bool attach(CTetrisBoard *targetBoard, int offsetX, int offsetY);

  bool detach(bool clear);

  bool moveLeft(void);

  bool moveRight(void);

  bool moveUp(int n);

  bool moveDown(void);

  bool moveDown(int n);

  bool drop(void);

  bool hasLanded(void);

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

  bool setRotation(int r);

  bool canMoveTo(const int x, const int y, const int rotation);

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

  void insertToBoard();

  void removeFromBoard();

};

#endif //__TETROMINO_H__
