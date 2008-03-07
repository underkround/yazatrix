#ifndef __TETRISBOARD_H__
#define __TETRISBOARD_H__
/**
 * TetrisBoard.h
 *
 * $Id$
 * $Revision$
 *
 * Y-koordinaatit alkavat alhaalta, eli alin rivi on y==0
 */

#include <vector>
#include "CellType.h"
#include "BoardChangeListener.h"
//#include "Tetromino.h"

class CTetrisBoard {

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

  inline int getRemovedLines(void) {
    return m_removedLines;
  }

  inline int getRemovedLinesLast(void) {
    return m_removedLinesLast;
  }

  /**
   * GetSlot
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
   * SetSlot
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
   * isEmpty
   *
   * Tarkistaa onko koko pelikenttä tyhjä (kaikki arvot EMPTY).
   *
   * @return  true, jos jokainen laudan ruutu on EMPTY
   */
  bool isEmpty(void); // koko lauta

  /**
   * isEmpty
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
   * isEmpty
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
   * isFull
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
   * reset
   *
   * Alustaa pelikentän taulukon (matrix) EMPTY-arvoilla, sekä nollaa
   * laskurit.
   */
  void reset(void);

  CELL_TYPE** getMatrix(void); // palauttaa koko matriksin

  /**
   * clearFullLines
   *
   * Käy pelilaudan rivit järjestyksessä (alhaalta ylöspäin) läpi, ja
   * poistaa kaikki täynnä olevat rivit. Päivittää poistettujen rivien
   * laskurit.
   *
   * @return puhdistuskerralla poistettujen rivien määrä
   */
  int clearFullLines(void); // käytetään joka tickillä

  /**
   * Lisää laudan tapahtumakuuntelijan kuuntelijavektoriin.
   * Ei vastaa kuuntelijaolioiden tuhoamisesta.
   */
  bool registerBoardChangeListener(VBoardChangeListener* bcl);

  /**
   * Poistaa laudan tapahtumakuuntelijan kuuntelijavektorista
   * Ei tuhoa kuuntelijaa.
   */
  bool unregisterBoardChangeListener(VBoardChangeListener* bcl);

  void update(void);

private:

  int m_width;
  int m_height;
  CELL_TYPE **m_matrix; // kentän sisältö CELL_TYPE vakioina
  int m_removedLines; // räjähtäneet rivit yhteensä
  int m_removedLinesLast; // viimeksi räjähtäneet rivit
  std::vector<VBoardChangeListener*> changeListeners; // laudan muutostapahtumakuuntelijat

  /**
   * removeLine
   *
   * Poistaa rivin kentästä, ja siirtää ylempiä rivejä alaspäin.
   * Alustaa ylimmäiseksi riviksi uuden tyhjän rivin.
   *
   * @param   y   poistettavan rivin koordinaatti y
   * @return  false, jos kentässä ei ole riviä y (yli rajojen)
   */
  bool removeLine(int y); // siirrä yläpuolen rivejä yhdellä

  void resetLine(const int y); // asettaa rivin alkiot EMPTY:n mukaiseksi

  /**
   * Ilmoittaa laudan rekisteröityneille tapahtumakuuntelijoille
   * muutoksesta pelilaudassa (matrixissa)
   */
  void notifyChange(void);

};

#endif //__TETRISBOARD_H__
