#ifndef __TETRISBOARD_H__
#define __TETRISBOARD_H__

/**
 * TetrisBoard.h
 *
 * $Revision$
 * $Id$
 *
 * Y-koordinaatit alkavat alhaalta, eli alin rivi on y==0
 */

#include "TetrisCommon.h"
#include "Observable.h"
#include "BoardChangeListener.h"
#include <stack>

class CTetrisBoard : public VObservable<VBoardChangeListener> {

public:

  CTetrisBoard();

  CTetrisBoard(const int cols, const int rows);

  ~CTetrisBoard();

  inline int getWidth(void) {
    return m_width;
  }

  inline int getHeight(void) {
    return m_height;
  }

  /**
   * GetSlot(int x, int y)
   *
   * Palauttaa kentän solun sisältämän arvon
   *
   * @param   x     boardin x-koordinaatti
   * @param   y     boardin y-koordinaatti
   * @return  matrixin solun {x,y} arvon tai OFFGRID jos menee yli
   *          kentän rajojen
   */
  CELL_TYPE getSlot(const int x, const int y);

  /**
   * SetSlot(int x, int y, CELL_TYPE content)
   *
   * Asettaa kentän koordinaatin {x,y} annettuun arvoon, jos koordinaatti
   * on kentän rajojen sisäpuolella.
   *
   * @param   x     boardin x-koordinaatti
   * @param   y     boardin y-koordinaatti
   * @param   content   koordinaattiin asetettava arvo
   * @return  koordinaatin entinen arvo, tai OFFGRID jos koordinaatti oli
   *          yli kentän rajojen
   */
  CELL_TYPE setSlot(const int x, const int y, const CELL_TYPE content); // returns old content

  /**
   * isEmpty()
   *
   * Tarkistaa onko koko pelikenttä tyhjä (kaikki arvot EMPTY).
   *
   * @return  true, jos jokainen laudan ruutu on EMPTY
   */
  bool isEmpty(void); // koko lauta

  /**
   * isEmpty(int x, int y)
   *
   * Tarkistaa, onko yksittäinen koordinaatti tyhjä.
   *
   * @param   x     boardin x-koordinaatti
   * @param   y     boardin y-koordinaatti
   * @return  true, jos koordinaatti {x,y} on
   *          a) vapaa (< 1)
   *          b) kentän rajojen sisäpuolella sivusuunnassa ja pohjasta
   *             katsoen (sivusuunnassa kentällä, ylhäältä yli = true)
   */
  bool isEmpty(const int x, const int y); // haluttu ruutu, offgrid = false, paitsi ylhäällä

  /**
   * isEmpty(int y)
   *
   * Tarkistaa, onko yksittäinen rivi tyhjä.
   *
   * @param   y     rivin koordinaatti y (indeksit alhaalta ylöspäin)
   * @return  true, jos rivi y on kokonaan tyhjä (kaikkien rivin
   *          ruudut < 1)
   *          false, jos rivillä on jotain tai se on yli rajojen
   */
  bool isEmpty(const int y); // rivi

  /**
   * isFull(int y)
   *
   * Tarkistaa, onko yksittäisen rivin kaikki solut täysiä (muuta kuin
   * EMPTY).
   *
   * @param   y     rivin koordinaatti y (indeksit alhaalta ylöspäin)
   * @return  true, jos rivin y mikään koordinaatti ei ole tyhjä
   *          (jokainen ruutu > 0)
   */
  bool isFull(const int y); // rivi

  /**
   * reset()
   *
   * Alustaa pelikentän taulukon (matrix) EMPTY-arvoilla, sekä nollaa
   * laskurit.
   */
  void reset(void);

  /**
   * getMatrix()
   *
   * Palauttaa kutsujalle koko boardin solutaulukon.
   *
   * @return    kaksiulotteinen taulukko boardin soluista
   */
  CELL_TYPE** getMatrix(void); // palauttaa koko matriksin

  /**
   * clearFullLines()
   *
   * Käy pelilaudan rivit järjestyksessä (alhaalta ylöspäin) läpi, ja
   * poistaa kaikki täynnä olevat rivit. Päivittää poistettujen rivien
   * laskurit.
   *
   * @return puhdistuskerralla poistettujen rivien määrä
   */
  int clearFullLines(void); // käytetään joka tickillä

  /**
   * update()
   *
   * Public -näkyvyyden metodi, jolla boardia muokannut ilmoittaa
   * muokkauksen loppuneen, jolloin board voi lähettää muutokset
   * (flush) sen muutoskuuntelijoille.
   *
   * Määrittää changeBufferien perusteella, lähetetäänkö kuuntelijoille
   * muutokset vai käsketäänkö piirtämään koko lauta uudestaan
   */
  void update(void);

private:

  static const int TETRIS_GUIDELINE_WIDTH = 10;
  static const int TETRIS_GUIDELINE_HEIGHT = 22;

  int m_width;  // solujen määrä vaakasuunnassa
  int m_height; // solujen määrä pystysuunnassa
  CELL_TYPE **m_matrix;   // kentän sisältö CELL_TYPE vakioina
  bool m_firstReset;
  std::stack<int> m_changeBufferX;
  std::stack<int> m_changeBufferY;
  std::stack<CELL_TYPE> m_changeBufferCT;

  /**
   * removeLine
   *
   * Poistaa rivin kentästä, ja siirtää ylempiä rivejä alaspäin.
   * Alustaa ylimmäiseksi riviksi uuden tyhjän rivin.
   *
   * @param y   poistettavan rivin koordinaatti y
   * @return    false, jos kentässä ei ole riviä y (yli rajojen)
   */
  bool removeLine(const int y); // siirrä yläpuolen rivejä yhdellä

  /**
   * resetline(int y)
   *
   * Asettaa rivin y solujen arvoksi EMPTY
   *
   * @param y   nollattavan rivin indeksi
   */
  void resetLine(const int y); // asettaa rivin alkiot EMPTY:n mukaiseksi

  /**
   * notifyFreshBoard()
   *
   * Ilmoittaa boardin rekisteröityneille tapahtumakuuntelijoille
   * suuresta muutoksesta pelilaudassa (matrixissa), jolloin suositeltava
   * toimenpide kuuntelijoille on hakea koko matrixin tila uudestaan.
   */
  void notifyFreshBoard(void);

  /**
   * notifyChangeInCoord(int x, int y, CELL_TYPE ct)
   *
   * Ilmoittaa boardin kuuntelijoille muutoksesta yksittäisessä
   * koordinaatissa.
   * @param   x     muuttuneen solun x koordinaatti
   * @param   y     muuttuneen solun y koordinaatti
   * @param   ct    muuttuneen solun uusi sisältö
   */
  void notifyChangeInCoord(const int x, const int y, const CELL_TYPE ct);

};

#endif //__TETRISBOARD_H__
