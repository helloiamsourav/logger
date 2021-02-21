#include <iostream>
#include "Logger.h"
#include <thread>
#include <unistd.h>

Logger DEBUG_LOG("Logger.log", loglevel::debug);

void foo()
{
	for(int i=0; i<300; i++)
	{
		DEBUG_LOG<<"sourav"<<" foo1" << std::endl;
		sleep(0.001);
	}
}

void foo1()
{
	for(int i=0; i<200; i++)
	{
		DEBUG_LOG<<"sourav"<<" foo2" << std::endl;
		sleep(0.001);
	}
}

int main()
{
	std::thread th1(foo);
	std::thread th2(foo1);
	th1.join();
	th2.join();
}
