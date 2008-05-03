#include "./Config.h"
#include "./menu.h"
#include "./Ticker.h"

#include <iostream>
using namespace std;

/**
 * Main.cpp
 *
 * Main release entry point for Tetris game
 *
 * $Id$
 * $Revision$
 *
 */

int main(int argc, char** argv) {
  char * configfile = NULL;
  configfile = "Tetris.ini"; //default config file
  SConfig * settings = &SConfig::getInstance();
  settings->setFilename(configfile);
  settings->readFile();

  if(argc > 1) { //if user has added another config file as command line parameter we'll apply it's settings too
    configfile = argv[1];
    settings->setFilename(configfile);
    settings->readFile();
  }

  /**/
  STicker::getInstance().start();
  CTetrisMenu * menu = new CTetrisMenu(2, 2, 10, 3);
  menu->show();
  STicker::getInstance().start();

  delete menu;
  return 0;
}
