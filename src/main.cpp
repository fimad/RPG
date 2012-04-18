#include <iostream>
#include "Errors.hpp"
using namespace std;

int main(int argc, char* argv[]){
  try{
    //...
  }catch(exception &e){
    cout << e.what() << endl;
  }
}

