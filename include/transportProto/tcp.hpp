#ifndef TCP_HPP
#define TCP_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <transport.hpp>

class hex;
class byte;


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

            const hex &getSource() const;
            const hex &getDest() const;
            const hex &getSeqNumber() const;
            const hex &getAckNumber() const;
            const hex &getFlags() const;
            const byte &getHdrLen() const;
            const hex &getWindow() const;
            const hex &getCsum() const;
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

        std::string getSeqNumber() const;
        std::string getAckNumber() const;
        int getHdrLen() const;
        std::string getFlags() const;
        int getWindow() const;
};


#endif