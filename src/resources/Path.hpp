#ifndef _PATH_HPP_
#define _PATH_HPP_

#include <list>
#include <string>
using namespace std;

class Path{
  public:
    static const Path Any; //a wildcard

    Path(const string& path); 
    Path(const Path& path);
    ~Path();
    void operator=(const Path& path);

    list<string> split() const;
    Path up() const;
    Path down(const string& path) const;
    Path down(const Path& path) const;
    Path operator/(const Path& path) const; //path composition root/Quest
    Path operator/(const string& path) const; //path composition root/"Quest"

    bool matches(const Path& path) const;
    bool operator==(const Path& path) const; //alias to matches
    bool operator<(const Path& path) const; //used for equivalence in std::map

    string toString() const;
  private:
    Path(); //default constructor creates the any path
    static bool isValidName(const string& name); //does the name contain illegal chars, '/', etc
    Path* bottom(); //returns the bottom of the tree/list

    string name;
    Path* child;
    bool isAny;
};

#endif

