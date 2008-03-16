#include "../Config.h"

int main(void) {
  SConfig * settings = &SConfig::getInstance();
  settings->printSettings();
  return 0;
}
