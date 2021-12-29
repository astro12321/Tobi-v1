#ifndef TCP_HPP
#define TCP_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "hex.hpp"
#include "transport.hpp"


namespace tcp
{
    class Frame: public hex
    {
        private:
            hex source;
            hex dest;
            hex seqNumber;
            hex ackNumber;
            byte hdrLen;
            hex flags;
            hex window;
            hex csum;

        public: //Could add checksum status support
            Frame() = default;
            Frame(hex &aHex);

            hex &getSource();
            hex &getDest();
            hex &getSeqNumber();
            hex &getAckNumber();
            hex &getFlags();
            byte &getHdrLen();
            hex &getWindow();
            hex &getCsum();
    };
}


class TCP : public Transport
{
    private:
        tcp::Frame frame;
        int source;
        int dest;
        std::string seqNumber;
        std::string ackNumber;
        int hdrLen;
        std::string flags;
        int window;
        std::string csum;

    public:
        TCP() = default;
        TCP(hex &hex);

        std::string getSeqNumber();
        std::string getAckNumber();
        int getHdrLen();
        std::string getFlags();
        int getWindow();
};


#endif