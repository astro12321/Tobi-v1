#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <hex.hpp>


class Transport 
{
    private:
        hex h;
        int proto;
        int source;
        int dest;
        std::string csum;

    public:
        Transport() = default;
        Transport(hex &hex, int proto);
        virtual ~Transport() = default;

        hex &getHex();
        int getProto();
        int getSource();
        int getDest();
        std::string getCsum();

        //ICMP
        virtual int getType();
        virtual int getCode();
        virtual std::string getData();

        //TCP
        virtual std::string getSeqNumber();
        virtual std::string getAckNumber();
        virtual int getHdrLen();
        virtual std::string getFlags();
        virtual int getWindow();

    protected:
        void setSource(int source);
        void setDest(int dest);
        void setCsum(std::string csum);
};


#endif