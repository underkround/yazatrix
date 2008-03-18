#include "Config.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//*** Protected ***
SConfig::SConfig(void) {
  addSetting("asetus", 2);
  addSetting("toinen asetus", "ASETETTU");
  addSetting("setting 3", true);
  addSetting("setting 4", true);
}

SConfig::~SConfig(void) {
  for (vector<Setting*>::iterator iter = settingData.begin(); iter!=settingData.end(); ++iter) {
    delete *iter;
  }
}

void SConfig::readFile(void) {
  //TODO: tutustu voiko lukea tiedostosta jotenkin hienommin
  string rivi;
  ifstream kahva (m_strFilename.c_str());
  if (kahva.is_open())
  {
    while (! kahva.eof() )
    {
      getline(kahva, rivi);
      parseRow(rivi);
    }
    kahva.close();
  }
  else cout << "yhyy :("; //fail
}


//*** Public ***

bool SConfig::isNumeric(const char merkki) {
    switch(merkki) {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '0':
        return true;
      default:
        return false;
    }
}

void SConfig::printSettings() {
  for (vector<Setting*>::iterator iter = settingData.begin(); iter!=settingData.end(); ++iter) {
    printSetting(*iter);
  }
}

//*** Private ***

void SConfig::printSetting(Setting * set) {
  cout << "Nimi:\t" << set->name << endl;
  switch(set->type) {
    case VARIABLE_INTEGER:
      cout << "Tyyppi:\t" << "kokonaisluku" << endl;
      cout << "Arvo:\t" << static_cast<SettingInt*>(set)->value << endl << endl;
      break;
    case VARIABLE_STRING:
      cout << "Tyyppi:\t" << "merkkijono" << endl;
      cout << "Arvo:\t" << static_cast<SettingString*>(set)->value << endl << endl;
      break;
  }
}

void SConfig::addSetting(string in_name, string in_value) {
  VARIABLE_TYPE tyyppi = VARIABLE_STRING;
  Setting * set = new SettingString();
  static_cast<SettingString*>(set)->name = in_name;
  static_cast<SettingString*>(set)->type = tyyppi;
  static_cast<SettingString*>(set)->value = in_value;
  settingData.push_back(set);
}

void SConfig::addSetting(string in_name, int in_value) {
  VARIABLE_TYPE tyyppi = VARIABLE_INTEGER;
  Setting * set = new SettingString();
  static_cast<SettingInt*>(set)->name = in_name;
  static_cast<SettingInt*>(set)->type = tyyppi;
  static_cast<SettingInt*>(set)->value = in_value;
  settingData.push_back(set);
}

bool SConfig::parseRow(string row) {
  cout << "parse: " << row << endl;
  //JOS "" -> return true;
  //JOS substr(0) = '[' -> return true;
  //JOS substr(0) = '#' -> return true;
  //JOS muu
    //loop until =
      //alkupuoli = name
      //loppupuoli isNumeric?
        //loppupuoli = value
    //jos ei löydy = niin return false;
  //return true;
  return true;
}
