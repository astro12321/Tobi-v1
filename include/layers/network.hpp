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

        const hex &getHex() const;

        std::string getSource() const;
        std::string getDest() const;
        int getStatus() const;
        int getTransportProto() const;
        int getNetworkProto() const;
        
        virtual int getTTL() const;
    
    protected:
        void setTransportProto(int transportProto);
        void setSource(std::string source);
        void setDest(std::string dest);
        void setStatus(int status);
};


#endif