#ifndef QUERY_HPP
#define QUERY_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <address.hpp>

class hex;


namespace dns
{
    namespace query
    {
        class Frame: public hex
        {
            private:
                hex name;
                hex type;
                hex _class;
            
            public:
                Frame() = default;
                Frame(hex &aHex);

                const hex &getName() const;
                const hex &getType() const;
                const hex &getClass() const;
        };


        class Query
        {
            private:
                Frame frame;
                Address name;
                int type;
                std::string _class;

            public:
                Query() = default;
                Query(hex &hex);

                const Address &getName() const;
                int getType() const;
                std::string getClass() const;
        };
    }

}


#endif