#ifndef MAINCONTROLLER_H_INCLUDED
#define MAINCONTROLLER_H_INCLUDED

/**
 * MainController.h
 *
 * $Id$
 * $Revision$
 *
 * State machine running the application.
 */

class CMainController {

public:

  /**
   * States handled
   */
  enum STATE {
    INIT,
    MAINMENU,
    INGAME,
    HIGHSCORE,
    CONFIG,
    ABOUT
  };

  static CMainController& getInstance() {
    static CMainController theSingleInstance;
    return theSingleInstance;
  }

protected:

  CMainController();
  ~CMainController();

private:

  void changeState(CMainController::STATE);
  void closeCurrentState();
  void openState(CMainController::STATE);

};

#endif // MAINCONTROLLER_H_INCLUDED
