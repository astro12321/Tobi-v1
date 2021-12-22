#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "transport.hpp"

//using namespace std;


Transport::Transport(std::string hex, std::string protocol)
{
    this->protocol = protocol;
    this->hex = hex;
}