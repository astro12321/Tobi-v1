#ifndef QUERY_HPP
#define QUERY_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

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

                hex &getName();
                hex &getType();
                hex &getClass();
        };


        class Query
        {
            private:
                Frame frame;
                std::string name;
                int type;
                std::string _class;

            public:
                Query() = default;
                Query(hex &hex);

                std::string getName();
                int getType();
                std::string getClass();
        };
    }

}


#endif