#include <iostream>
#include "Logger.h"

Logger DEBUG_LOG("Logger.log", loglevel::debug);

int main()
{
       DEBUG_LOG("sourav");
       DEBUG_LOG<<"sourav append" << 123 <<" float=" <<123.432 <<  std::endl;
}
