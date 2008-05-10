#ifndef GAMESTATELISTENER_H_INCLUDED
#define GAMESTATELISTENER_H_INCLUDED

/**
 * GameStateListener.h
 *
 * $Revision$
 * $Id$
 *
 * Listens to changes in game state.
 */

class VGameStateListener {

public:

  enum GAMESTATE {
    START,
    PAUSE,
    RESUME,
    GAMEOVER,
    EXIT
  };

  /**
   * handleGameState()
   *
   * Called when game state changes
   */
  virtual void handleGameState(VGameStateListener::GAMESTATE state) = 0;

};

#endif // GAMESTATELISTENER_H_INCLUDED
