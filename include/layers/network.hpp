#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <address.hpp>
#include <hex.hpp>


class Network 
{
    private:
        hex h;
        int networkProto;
        int transportProto;
        int status;
        Address source;
        Address dest;
    
    public:
        Network() = default;
        Network(hex &hex, int proto);
        virtual ~Network() = default;

        const hex &getHex() const;

        Address getSource() const;
        Address getDest() const;
        int getStatus() const;
        int getTransportProto() const;
        int getNetworkProto() const;
        
        virtual int getTTL() const;
    
    protected:
        void setTransportProto(int transportProto);
        void setSource(Address source);
        void setDest(Address dest);
        void setStatus(int status);
};


#endif