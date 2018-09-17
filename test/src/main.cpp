#include "header.h"
#include "functest.h"
#include "fileman.h"

#include <string>
#include <vector>

const char* FILENAME = "data";
std::string VALUE_READ;
std::string VALUE_WRITE;

bool running;



void print_random_key(){
	for(int i = 0 ; i< 10; i++)
		std::cout << key_gen() << std::endl;
}

void foo(int x){
	std::cout << x << std::endl;
}

int main(){
	running = true;

	std::thread fst (reader,FILENAME);
	std::thread sec (writer,FILENAME);

	sleep(1);
	running = false;

	fst.join();
	sec.join();

	std::cout << "Exiting main thread..." << std::endl;
	return 0;
}