#include "game/Die.hpp"
#include <regex>
#include <cstdlib>

#include <iostream>

unordered_map<string,Die*> Die::_createdDie;

//originall I implemented this with regexes but then I found out that libstdc++ don't have any :(
//also this doesn't allow spaces, so if you want spaces, FUCK YOU
Die::Die(const string& roll)
  : _roll(roll)
{
  const char* cur=roll.c_str();
  const char* start;
  while( *cur != 0 ){
    int sign = 1;
    int num = 1;
    int die = 1;

    //find the sign
    if( *cur == '+' ){
      sign = 1;
      cur++;
    }
    if( *cur == '-' ){
      sign = -1;
      cur++;
    }

    //some error checking...
    if( *cur == 0 )
      raise(DieException,roll,"Unexpected end of string after sign");

    //find the amount
    start = cur;
    while( *cur != 0 && *cur != 'd' ){
      if( *cur < '0' ||  *cur > '9' ){
        raise(DieException,roll,"Expected integer for number component");
      }
      cur++;
    }
    //if we have a size, let's decode it, ow the default is 1
    if( start != cur ){
      string str(start,cur-start);
      num = atoi(str.c_str());
      if( num <= 0 ){
        raise(DieException,roll,"Number component must be a positive integer");
      }
    }

    //find the 'd'
    if( *cur != 'd' )
      raise(DieException,roll,"Expected 'd' after number component");
    cur++;

    //some more error checking...
    if( *cur == 0 )
      raise(DieException,roll,"Unexpected end of string after number component");

    //find the die type
    start = cur;
    while( *cur != 0 && *cur != '-' && *cur != '+' ){
      if( *cur < '0' ||  *cur > '9' ){
        raise(DieException,roll,"Expected integer for die component");
      }
      cur++;
    }
    if( start != cur ){
      string str(start,cur-start);
      int die = atoi(str.c_str());
      if( die < 2 ){
        raise(DieException,roll,"Die component must be greater than 1");
      }
    }else{
      raise(DieException,roll,"Expected die component");
    }

    //add this roll to the list
    _components.push_back(make_tuple(sign,num,die));
  }
}

void Die::clear(){
  //delete all created die, hope nothing still references them!
  for(auto i : _createdDie){
    Die* d = i.second;
    delete d;
  }
  _createdDie.clear();
}

Die* Die::parse(const string& roll){
  if(_createdDie.count(roll) == 0){
    _createdDie[roll] = new Die(roll);
  }
  return _createdDie[roll];
}

int Die::roll(){
  int value = 0;
  for(auto t : _components){
    int sign = get<0>(t);
    for(int i=0; i < get<1>(t); i++){
      value += sign*( (rand()%(get<2>(t)))+1 );
    }
  }
  return value;
}
const string& Die::str(){
  return _roll;
}

DieException::DieException(const string& roll, const string& what)
  : _roll(roll)
  , _what(what)
{}
DieException::~DieException() throw(){}
string DieException::description() const throw(){
  return "Invalid dice roll: '"+_roll+"' : "+_what;
}

