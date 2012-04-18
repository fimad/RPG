#ifndef _ERRORS_HPP_
#define _ERRORS_HPP_

#include <exception>
#include <string>
using namespace std;

#define raise(e,...) {e a = e(__VA_ARGS__); a.setWhere(__FILE__,__LINE__); throw a;}

class Exception : public exception{
  public:
    ~Exception() throw();
    void setWhere(string file, int line);
    string where() const throw();
    virtual string description() const throw();
    virtual const char* what() const throw();
  private:
    string file;
    int line;
};

#endif

