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

                const hex &getName() const;
                const hex &getType() const;
                const hex &getClass() const;
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

                std::string getName() const;
                int getType() const;
                std::string getClass() const;
        };
    }

}


#endif