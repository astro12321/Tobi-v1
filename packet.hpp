#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "network.hpp"
#include "layer.hpp"
#include "hex.hpp"
#include "defaults.hpp"


class Packet
{
    private:
        int index;
        bool valid;
        std::string status;
        std::string transportProto;
        std::string networkProto;
        hex h;
        Layer layer;
        
        std::string setStatus(int status);
        std::string setTransportProto(int proto);
        std::string setNetworkProto(int proto);
    
    public:
        Packet(int ind, hex &hex);

        hex &getHex();
        Layer &getLayer();
        std::string getStatus();
        int getIndex();
        std::string getTransportProto();
        std::string getNetworkProto();
        bool isValid();
};


#endif