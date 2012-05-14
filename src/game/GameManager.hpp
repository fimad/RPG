#ifndef _GAME_MANAGER_HPP_
#define _GAME_MANAGER_HPP_

#include <list>
using namespace std;

class GameState;
class ViewContext;

class GameManager{
  public:
    GameManager(ViewContext* context);
    ViewContext* getContext();
    void pushState(GameState* state);
    void popState();
    GameState* peekState();
    void run();
    void stop();
  private:
    bool _shouldRun;
    ViewContext* _context;
    list<GameState*> _states;
};

#endif

