#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
#include <application.hpp>
#include <dns.hpp>
#include <query.hpp>
#include <answer.hpp>


namespace dns
{
    Frame::Frame(hex &aHex): hex(aHex)
    {
        this->transactID = aHex.substr(0, 2);
        this->flags = aHex.substr(2, 2);
        this->questions = aHex.substr(4, 2);
        this->answerRRs = aHex.substr(6, 2);
        this->authorityRRs = aHex.substr(8, 2);
        this->additionalRRs = aHex.substr(10, 2);
    }

    const hex &Frame::getTransactID() const { return transactID; }
    const hex &Frame::getFlags() const { return this->flags; }
    const hex &Frame::getQuestions() const { return this->questions; }
    const hex &Frame::getAnswerRRs() const { return this->answerRRs; }
    const hex &Frame::getAuthorityRRs() const { return this->authorityRRs; }
    const hex &Frame::getAdditionalRRs() const { return this->additionalRRs; }
}


DNS::DNS(hex &aHex): Application(aHex, "DNS")
{
    this->frame = dns::Frame(aHex);

    this->transactID = frame.getTransactID().to_fstring();
    this->flags = frame.getFlags().to_fstring();
    this->questions = frame.getQuestions().to_dec();
    this->answerRRs = frame.getAnswerRRs().to_dec();
    this->authorityRRs = frame.getAuthorityRRs().to_dec();
    this->additionalRRs = frame.getAdditionalRRs().to_dec();

    int queryLen = 0;

    if (questions >= 1) //Doesn't support multiple queries (which is super rare)
    {
        queryLen = FindQueryNameLength(aHex.substr(12, aHex.numberOfBytes() - 12));

        hex queryHex = aHex.substr(12, queryLen);

        this->query = dns::query::Query(queryHex);
    }

    if (answerRRs >= 1)
    {
        int i = 0;
        int answerLen = 0;
        int start = queryLen + 12; //skip query + DNS headers

        do {
            answerLen = aHex.substr(start + 10, 2).to_dec() + 12;

            hex answerHex = aHex.substr(start, answerLen);
            this->answers.push_back(dns::answer::Answer(answerHex));

            start += answerLen;
            i++;
        } while (i < answerRRs);

        /*for (size_t i = 0; i < answers.size(); i++)
        {
            std::cout << "\n";
            std::cout << "- DNS name: " << answers[i].getName() << "\n";
            std::cout << "- DNS type: " << answers[i].getType() << "\n";
            std::cout << "- DNS class: " << answers[i].getClass() << "\n";
            std::cout << "- DNS ttl: " << answers[i].getTtl() << "\n";
            std::cout << "- DNS addr: " << answers[i].getAddress().to_string() << "\n";
            std::cout << "\n";
        }*/
        
    }
    
}


//Find the name (FQDN) in the query fields from the whole packet hex (because it's length vary)
int DNS::FindQueryNameLength(hex hex) const
{
    int i = 0;
    
    while (true) 
    {
        int len = hex[i].to_dec(); //DNS names are separated in the packet by the length of the next word (the length replace the .(dot) that would be there)

        if (len == 0) { //If the length is of 0, then we're at the end of the FQDN
            i++;
            break;
        }

        i += len + 1;
    }

    return i + 4;
    //return hex.substr(0, i + 4); //Adding the 4 bytes of the end (DNS type and class)
}


std::string DNS::getTransactID() const { return this->transactID; }
std::string DNS::getFlags() const { return this->flags; }
int DNS::getQuestions() const { return this->questions; }
int DNS::getAnswerRRs() const { return this->answerRRs; }
int DNS::getAuthorityRRs() const { return this->authorityRRs; }
int DNS::getAdditionalRRs() const { return this->additionalRRs; }
const dns::query::Query &DNS::getQuery() const { return this->query; }
const std::vector<dns::answer::Answer> &DNS::getAnswers() const { return this->answers; }