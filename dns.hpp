#ifndef DNS_HPP
#define DNS_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "hex.hpp"
#include "application.hpp"


namespace dns
{
    class Frame: public hex
    {
        private:
            hex transactID;
            hex flags;
            hex questions;
            hex answerRRs;
            hex authorityRRs;
            hex additionalRRs;

        public: //Could add checksum status support
            Frame() = default;
            Frame(hex &aHex);

            hex &getTransactID();
            hex &getFlags();
            hex &getQuestions();
            hex &getAnswerRRs();
            hex &getAuthorityRRs();
            hex &getAdditionalRRs();
    };
}


class DNS : public Application
{
    private:
        dns::Frame frame;
        std::string transactID;
        std::string flags;
        int questions;
        int answerRRs;
        int authorityRRs;
        int additionalRRs;

    public:
        DNS() = default;
        DNS(hex &hex);

        std::string getTransactID();
        std::string getFlags();
        int getQuestions();
        int getAnswerRRs();
        int getAuthorityRRs();
        int getAdditionalRRs();
};


#endif