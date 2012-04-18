#include "resources/DirectoryProvider.hpp"
#include "resources/Path.hpp"
#include "Errors.hpp"
#include <fstream>
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

string DirectoryProvider::getBuffer(const Path& path){
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

  return buffer;
}

void DirectoryProvider::putBuffer(const Path& path, string buffer){
  string fullPath = rootDirectory+"/"+path.toString();
  ofstream file(fullPath.c_str());
  if(!file)
    raise(NoSuchPathException,path);
  file << buffer;
}

