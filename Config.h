#ifndef __CONFIG_H__
#define __CONFIG_H__

/**
 * Config.h
 *
 * $Id$
 * $Revision$
 *
 */

/*
- palikoiden värit
- käytetty palikkasetti
- näppäimet
- previewpalikoiden määrä
- laudan koko?
- vaikeuteen liittyvät asetukset?
*/

#include "Singleton.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class SConfig {

  protected:
    SConfig(void);
    ~SConfig(void);

  public:

  static SConfig& getInstance() {
    static SConfig theSingleInstance;  // assumes T has a protected default constructor
    return theSingleInstance;
  }

  /**
   * Asetus tiedostossa käytetyt muuttujatyypit
   */
  enum VARIABLE_TYPE { VARIABLE_STRING, VARIABLE_INTEGER };

  struct Setting {
    string name;
    VARIABLE_TYPE type;
  };

  struct SettingInt : Setting {
    int value;
  };

  struct SettingString : Setting {
    string value;
  };

  /**
   * isNumeric
   *
   * Käytetään merkin numeerisuuden tarkistamiseen
   *
   * @param merkki tutkittava merkki
   * @return oliko merkki numeerinen
   */
  bool isNumeric(const char merkki);

  /**
   * printSettings
   *
   * Tulostaa kaikki asetukset ruudulle. @see printSetting(Setting * set)
   */
  void printSettings();

  /**
   * readFile
   *
   * Lukee asetukset tiedostosta
   */
  void readFile();

  inline void setFilename(string filename) { m_strFilename = filename; };

  int getValueAsInt(string name);

  bool getValueAsBool(string name);

  string getValueAsString(string name);

  private:
    //** muuttujat ja vakiot **
    string m_strFilename;
    vector<Setting*> settingData;
    static const char CHAR_DELIMITER = '=';
    static const char CHAR_COMMENT   = '#';

    //** metodit **

    /**
     * addSetting
     */
    void addSetting(string in_name, string in_value);
    void addSetting(string in_name, int in_value);

    /**
     * printSetting
     *
     * Tulostaa halutun asetuksen muotoiltuna ruudulle
     *
     * @param set tulostettava asetus
     */
    void printSetting(Setting * set);

    bool parseRow(string row);

};
#endif //__CONFIG_H__
