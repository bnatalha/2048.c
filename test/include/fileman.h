#ifndef FILEMAN_HEADER
#define FILEMAN_HEADER

#include <fstream> 

void write_value(const char* filename, char value);

std::string read_value(const char* filename);

#endif