#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <ip.hpp>
#include <hex.hpp>


class Network 
{
    private:
        hex h;
        int networkProto;
        int transportProto;
        int status;
        IP source;
        IP dest;
    
    public:
        Network() = default;
        Network(hex &hex, int proto);
        virtual ~Network() = default;

        const hex &getHex() const;

        IP getSource() const;
        IP getDest() const;
        int getStatus() const;
        int getTransportProto() const;
        int getNetworkProto() const;
        
        virtual int getTTL() const;
    
    protected:
        void setTransportProto(int transportProto);
        void setSource(IP source);
        void setDest(IP dest);
        void setStatus(int status);
};


#endif