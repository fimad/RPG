#include "resources/DirectoryProvider.hpp"
#include "resources/Path.hpp"
#include "Errors.hpp"
#include <fstream>
#include <cstring>
using namespace std;

//deal in 4k chunks
#define IO_SIZE (1024*4)

DirectoryProvider::DirectoryProvider(string root){
  rootDirectory = root;
}

bool DirectoryProvider::provides(const Path& path){
  string fullPath = rootDirectory+"/"+path.toString();
  ifstream file(fullPath.c_str());
  return !(!file);
}

char* DirectoryProvider::getBuffer(const Path& path){
  string fullPath = rootDirectory+"/"+path.toString();
  ifstream file(fullPath.c_str());

  //for now, die if the full path doesn't exist
  if(!file)
    raise(NoSuchPathException,path);

  //read the file in chunks at a time
  char read_buffer[IO_SIZE];
  string buffer = "";
  while( !file.eof() ){
    int numRead = file.readsome(read_buffer,IO_SIZE-1);
    if( numRead == 0 )
      break;
    read_buffer[numRead] = 0;
    buffer += read_buffer;
  }

  //copy it into a modifiable c string
  char* c_buffer = (char*)malloc(buffer.size()+1);
  memcpy(c_buffer,buffer.c_str(),buffer.size());
  c_buffer[buffer.size()] = 0;

  return c_buffer;
}

void DirectoryProvider::putBuffer(const Path& path, string buffer){
  string fullPath = rootDirectory+"/"+path.toString();
  ofstream file(fullPath.c_str());
  if(!file)
    raise(NoSuchPathException,path);
  file << buffer;
}

