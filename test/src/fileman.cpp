#include "header.h"
#include "fileman.h"

void write_value(const char* filename, char value){
  std::fstream outData;
  outData.open(filename, std::fstream::out);
  if (outData.is_open()){
    outData << value;
    outData.close();
  }
  else throw std::runtime_error("[write_value]: could not open file.");
}

std::string read_value(const char* filename){
  std::fstream inData;
  inData.open(filename, std::fstream::in);
  if (inData.is_open()){
    std::string str;
    inData >> str;
    inData.close();
    return str;
  }
  throw std::runtime_error("[read_value]: could not open file.");
}