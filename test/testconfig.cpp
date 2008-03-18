#include "../Config.h"

int main(void) {
  SConfig * settings = &SConfig::getInstance();
  settings->printSettings();
  settings->setFilename("testi.ini");
  settings->readFile();
  return 0;
}
