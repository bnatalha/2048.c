#ifndef COMMON_VARIABLE_HEADER
#define COMMON_VARIABLE_HEADER

#include <thread> // for threads
#include <mutex>
#include <condition_variable>

extern std::mutex mtx;
extern std::condition_variable can_play;
extern std::condition_variable can_read;

extern bool SHARED_PLAYING;

extern bool SHARED_RUNNING;
extern char SHARED_KEY_OUTPUT;

#endif