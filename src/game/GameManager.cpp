#include "game/GameManager.hpp"
#include "game/GameState.hpp"
#include <cstdlib>

GameManager::GameManager(ViewContext* context)
  : _context(context)
  , _shouldRun(true)
{}

ViewContext* GameManager::getContext(){
  return _context;
}

void GameManager::pushState(GameState* state){
  if( _states.size() ){
    _states.front()->leaveFocus();
  }
  state->_manager = this;
  _states.push_front(state);
  state->gainFocus();
}

void GameManager::popState(){
  if( _states.size() > 1 ){
    _states.front()->leaveFocus();
    _states.pop_front();
    _states.front()->gainFocus();
  }
}

GameState* GameManager::peekState(){
  return (_states.size()) ? _states.front() : NULL;
}

void GameManager::run(){
  while( _shouldRun ){
    if( _states.size() ){
      //TODO: add timing code here!
      _states.front()->update(0);
      _states.front()->draw();
    }
  }
}

void GameManager::stop(){
  _shouldRun = false;
}

