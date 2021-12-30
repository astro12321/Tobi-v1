#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "hex.hpp"
namespace dns { namespace query { class Query; } }


class Application 
{
    private:
        hex h;
        std::string proto;

    public:
        Application() = default;
        Application(hex &hex, std::string proto);
        virtual ~Application() = default;

        hex &getHex();
        std::string getProto();

        //DNS
        virtual std::string getTransactID();
        virtual std::string getFlags();
        virtual int getQuestions();
        virtual int getAnswerRRs();
        virtual int getAuthorityRRs();
        virtual int getAdditionalRRs();
        virtual dns::query::Query getQuery(); /////////
};


#endif