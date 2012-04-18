#include "Errors.hpp"
#include <cstdio>

Exception::~Exception() throw(){
}

void Exception::setWhere(string file, int line){
  this->file = file;
  this->line = line;
}

string Exception::where() const throw(){
  char buffer[64];
  buffer[63] = 0;
  snprintf(buffer,63,"%d",line);
  return file+":"+buffer+": ";
}

string Exception::description() const throw(){
  return "an exception occurred...";
}

const char* Exception::what() const throw(){
  return (where()+description()).c_str();
}
