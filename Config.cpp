#include "Config.h"

//*** Protected ***
SConfig::SConfig(void) {
  //tähän heti tiedoston luku ok?
  addSetting("asetus", 1);
  addSetting("toinen asetus", "ASETETTU");
  addSetting("setting 3", "this is setting number three");
  addSetting("setting 4", true);
}

SConfig::~SConfig(void) {
  for (vector<Setting*>::iterator iter = settingData.begin(); iter!=settingData.end(); ++iter) {
    delete *iter;
  }
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
