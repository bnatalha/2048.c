#include "header.h"
#include "functest.h"
#include "fileman.h"

std::mutex mtx;
std::condition_variable can_write, can_read;

bool writing = false;


void reader(const char* filename){
	while(running){
		std::unique_lock<std::mutex> lck(mtx);
		while(writing) can_read.wait(lck);
		
		// do 
		try{
			std::string str = read_value(filename);
			//value = str[0];
			std::cout << "just read: " << str << std::endl;
			//sleep(1);
			std::this_thread::sleep_for (std::chrono::milliseconds(100));
		}
		catch (std::exception &e){
			std::cout << e.what() << std::endl;
		}

		//sleep(1);

		writing = true;
		can_write.notify_one();
	}
}

void writer(const char* filename){
	while(running){
		std::unique_lock<std::mutex> lck(mtx);
		while(!writing) can_write.wait(lck);

		write_value(filename,key_gen());
		std::cout << "done writing." << std::endl;
		//sleep(1);

		writing = false;
		can_read.notify_one();
	}
}

char key_gen(){
	srand(time(NULL));
	int number = 97 + rand() % 20;
	return char(number);
}