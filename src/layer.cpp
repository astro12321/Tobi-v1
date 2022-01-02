#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <memory>

#include <layer.hpp>
#include <ipv4.hpp>
#include <hex.hpp>
#include <icmp.hpp>
#include <tcp.hpp>
#include <udp.hpp>
#include <dns.hpp>


Layer::Layer(hex &pktHex)
{
    this->network = findNetworkProto(pktHex);

    if (network != nullptr)
    {
        this->networkValid = true;

        this->transport = findTransportProto(pktHex, getNetwork().getHex().numberOfBytes(), getNetwork().getTransportProto());

        if (transport != nullptr)
        {
            this->transportValid = true;

            int hdrsLen = getNetwork().getHex().numberOfBytes() + getTransport().getHex().numberOfBytes();
            this->application = findApplicationProto(pktHex, hdrsLen);

            applicationValid = (application != nullptr) ? true : false;
        }
        else { this->transportValid = false; }
    }
    else { this->networkValid = false; } //If the packet is invalid (a protocol that we don't parse)
}


const Network &Layer::getNetwork() const { return *(this->network); }
const Transport &Layer::getTransport() const { return *(this->transport); }
const Application &Layer::getApplication() const { return *(this->application); }

bool Layer::networkIsValid() const { return this->networkValid; }
bool Layer::transportIsValid() const { return this->transportValid; }
bool Layer::applicationIsValid() const { return this->applicationValid; }


//Gotta use pointers because polymorphism requires it (smart pointers)
std::unique_ptr<Network> Layer::findNetworkProto(hex &pktHex) const
{
    int ipVersion = pktHex[0].first().to_dec();
    
    if (ipVersion == 4) {
        hex networkHex = pktHex.substr(0, 20);
        return std::make_unique<Ipv4>(networkHex); //make_unique avoid using "new"
    }
    
    return std::unique_ptr<Network>(nullptr);
}


std::unique_ptr<Transport> Layer::findTransportProto(hex &pktHex, int networkLength, int proto) const
{
    switch (proto)
    {
        case 1: //ICMP
        {
            hex transportHex = pktHex.substr(networkLength, pktHex.numberOfBytes() - networkLength);

            return std::make_unique<ICMP>(transportHex);
        }

        case 6: //TCP
        {
            int tcpHeaderLen = pktHex[networkLength + 12].first().to_dec();
            hex transportHex = pktHex.substr(networkLength, tcpHeaderLen * 4);

            return std::make_unique<TCP>(transportHex);
        }

        case 17: //UDP
        {
            hex transportHex = pktHex.substr(networkLength, 8);

            return std::make_unique<UDP>(transportHex);
        }

        default: //Other
            return std::unique_ptr<Transport>(nullptr);
    }

}


std::unique_ptr<Application> Layer::findApplicationProto(hex &pktHex, int headersLen) const
{
    hex appHex = pktHex.substr(headersLen, pktHex.numberOfBytes() - headersLen);

    if (isDNS()) return std::make_unique<DNS>(appHex); //DNS

    return std::unique_ptr<Application>(nullptr); //Other
}


bool Layer::isDNS() const {
    if (this->getTransport().getDest() == 53 || this->getTransport().getSource() == 53) return true;
    return false;
}