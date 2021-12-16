#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "packet.hpp"
#include "transport.hpp"

#define BUFFERSIZE 4096

//using namespace std;


Packet::Packet(int ind, unsigned char *buffer, int bytesRead)
{
    memcpy(bytes, buffer, BUFFERSIZE);
    index = ind;
    length = bytesRead;

    this->hex = bytesToHex(bytes, length);
    this->layer = Layer(hex);
}


std::string Packet::bytesToHex(unsigned char *bytes, int len)
{
    std::stringstream ss;
    ss << std::hex;

    for (int i = 0; i < len; ++i)
        ss << std::setw(2) << std::setfill('0') << (int)bytes[i];

    return ss.str();
}