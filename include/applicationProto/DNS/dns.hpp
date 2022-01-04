#ifndef DNS_HPP
#define DNS_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <application.hpp>
#include <DNS/query.hpp>
#include <DNS/answer.hpp>
#include <DNS/authority.hpp>

class hex;


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

            const hex &getTransactID() const;
            const hex &getFlags() const;
            const hex &getQuestions() const;
            const hex &getAnswerRRs() const;
            const hex &getAuthorityRRs() const;
            const hex &getAdditionalRRs() const;
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
        dns::query::Query query;
        std::vector<dns::answer::Answer> answers;
        dns::authority::Authority authority;

        int FindQueryNameLength(hex hex) const;

    public:
        DNS() = default;
        DNS(hex &aHex);

        std::string getTransactID() const;
        std::string getFlags() const;
        int getQuestions() const;
        int getAnswerRRs() const;
        int getAuthorityRRs() const;
        int getAdditionalRRs() const;
        const dns::query::Query &getQuery() const;
        const std::vector<dns::answer::Answer> &getAnswers() const;
        const dns::authority::Authority &getAuthority() const;
};


#endif