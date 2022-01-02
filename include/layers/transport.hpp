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

        const hex &getHex() const;
        int getProto() const;
        int getSource() const;
        int getDest() const;
        std::string getCsum() const;

        //ICMP
        virtual int getType() const;
        virtual int getCode() const;
        virtual std::string getData() const;

        //TCP
        virtual std::string getSeqNumber() const;
        virtual std::string getAckNumber() const;
        virtual int getHdrLen() const;
        virtual std::string getFlags() const;
        virtual int getWindow() const;

    protected:
        void setSource(int source);
        void setDest(int dest);
        void setCsum(std::string csum);
};


#endif