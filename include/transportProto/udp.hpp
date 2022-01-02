#ifndef UDP_HPP
#define UDP_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class hex;
class Transport;


namespace udp
{
    class Frame: public hex
    {
        private:
            hex source;
            hex dest;
            hex csum;

        public: //Could add checksum status support
            Frame() = default;
            Frame(hex &aHex);

            const hex &getSource() const;
            const hex &getDest() const;
            const hex &getCsum() const;
    };
}


class UDP : public Transport
{
    private:
        udp::Frame frame;
        int source;
        int dest;
        std::string csum;

    public:
        UDP() = default;
        UDP(hex &hex);
};


#endif