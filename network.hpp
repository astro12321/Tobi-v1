#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "hex.hpp"


class Network 
{       
    private:
        hex h;
        int networkProto;
        int transportProto;
        std::string source;
        std::string dest;
    
    public:
        Network() = default;
        Network(hex &hex);
        virtual ~Network() = default;

        std::string getSource();
        std::string getDest();
        int getTransportProto();
        int getNetworkProto();
        hex &getHex();
        
        virtual int getTTL();
    
    protected:
        void setTransportProto(int transportProto);
        void setNetworkProto(int networkProto);//////////////////////////
        void setSource(std::string source);
        void setDest(std::string dest);
};


#endif