#ifndef _DIE_HPP_
#define _DIE_HPP_

#include <list>
#include <tuple>
#include <string>
#include <unordered_map>
#include "Errors.hpp"
using namespace std;

class DieException : public Exception{
  public:
    DieException(const string& roll, const string& what);
    ~DieException() throw();
    virtual string description() const throw();
  private:
    string _roll;
    string _what;
};

class Die{
  public:
    static Die* parse(const string& roll); //each type of roll will correspond to the same instanece of die, DON'T DELETE THEM!
    static void clear();
    int roll();
    const string& str();
  private:
    Die(const string& roll);

    //the tuple contains the sign(-1 or 1), the number of this die type to roll, and the die type
    list<tuple<int,int,int>> _components;
    string _roll;
    static unordered_map<string,Die*> _createdDie;
};

#endif

