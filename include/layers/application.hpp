#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
namespace dns { namespace query { class Query; } }
namespace dns { namespace answer { class Answer; } }


class Application 
{
    private:
        hex h;
        std::string proto;

    public:
        Application() = default;
        Application(hex &hex, std::string proto);
        virtual ~Application() = default;

        const hex &getHex() const; 
        std::string getProto() const;

        //DNS
        virtual std::string getTransactID() const;
        virtual std::string getFlags() const;
        virtual int getQuestions() const;
        virtual int getAnswerRRs() const;
        virtual int getAuthorityRRs() const;
        virtual int getAdditionalRRs() const;
        const virtual dns::query::Query &getQuery() const;
        const virtual std::vector<dns::answer::Answer> &getAnswers() const;
};


#endif