#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <layer.hpp>


class Packet
{
    private:
        int index;
        std::string status;
        std::string applicationProto;
        std::string transportProto;
        std::string networkProto;
        hex h;
        Layer layer;
        
        std::string setStatus(int status) const;
        std::string setTransportProto(int proto) const;
        std::string setNetworkProto(int proto) const;
    
    public:
        Packet(int ind, hex &hex);

        const hex &getHex() const;
        const Layer &getLayer() const;
        std::string getStatus() const;
        int getIndex() const;
        std::string getApplicationProto() const;
        std::string getTransportProto() const;
        std::string getNetworkProto() const;
};


#endif