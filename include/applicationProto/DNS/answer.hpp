#ifndef ANSWER_HPP
#define ANSWER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <address.hpp>

class hex;


namespace dns
{
    namespace answer
    {
        class Frame: public hex
        {
            private:
                hex name;
                hex type;
                hex _class;
                hex ttl;
                hex address;
            
            public:
                Frame() = default;
                Frame(hex &aHex);

                const hex &getName() const;
                const hex &getType() const;
                const hex &getClass() const;
                const hex &getTtl() const;
                const hex &getAddress() const;
        };


        class Answer
        {
            private:
                Frame frame;
                std::string name;
                int type;
                std::string _class;
                int ttl;
                Address address;

            public:
                Answer() = default;
                Answer(hex &aHex);

                const std::string &getName() const;
                int getType() const;
                std::string getClass() const;
                const int &getTtl() const;
                const Address &getAddress() const;
        };
    }

}


#endif