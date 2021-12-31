#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <hex.hpp>


class Network 
{
    private:
        hex h;
        int networkProto;
        int transportProto;
        int status;
        std::string source;
        std::string dest;
    
    public:
        Network() = default;
        Network(hex &hex, int proto);
        virtual ~Network() = default;

        hex &getHex();

        std::string getSource();
        std::string getDest();
        int getStatus();
        int getTransportProto();
        int getNetworkProto();
        
        virtual int getTTL();
    
    protected:
        void setTransportProto(int transportProto);
        void setSource(std::string source);
        void setDest(std::string dest);
        void setStatus(int status);
};


#endif