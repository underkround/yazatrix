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

  enum VARIABLE_TYPE { VARIABLE_STRING, VARIABLE_INTEGER };

  union Value {
    int number;
    std::string * text;
  };

  struct Setting {
    std::string * name;
    VARIABLE_TYPE type;
    Value value;
  };

  bool isNumeric(const char merkki);

  void printSettings();

  private:
    //muuttujat ja vakiot
    string m_strFilename;
    vector<Setting> settingData;
    static const char CHAR_DELIMITER = '=';
    static const char CHAR_COMMENT   = '#';

    //metodit
    void addSetting(string in_name, string in_value);
    void addSetting(string in_name, int in_value);

};
#endif //__CONFIG_H__
