#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include "game/GameManager.hpp"

class GameState{
  public:
    virtual void leaveFocus() = 0;
    virtual void gainFocus() = 0;
    virtual void update(double dt) = 0;
    virtual void draw() = 0;

    GameManager* getManager();
    friend class GameManager;

    static GameState* InitialState; //The main menu state, set by ViewContext implementer
  private:
    GameManager* _manager;
};

#endif

