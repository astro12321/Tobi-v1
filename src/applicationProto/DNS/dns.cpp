#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
#include <application.hpp>
#include <dns.hpp>
#include <query.hpp>


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

    hex &Frame::getTransactID() { return this->transactID; }
    hex &Frame::getFlags() { return this->flags; }
    hex &Frame::getQuestions() { return this->questions; }
    hex &Frame::getAnswerRRs() { return this->answerRRs; }
    hex &Frame::getAuthorityRRs() { return this->authorityRRs; }
    hex &Frame::getAdditionalRRs() { return this->additionalRRs; }
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

    if (questions >= 1) //Doesn't support multiple queries (which is super rare)
    { 
        hex hex = FindQueryHex(aHex.substr(12, aHex.numberOfBytes() - 12));
        
        this->query = dns::query::Query(hex);
    }
    
}


hex DNS::FindQueryHex(hex hex)
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

    return hex.substr(0, i + 4); //Adding the 4 bytes of the end (DNS type and class)
}


std::string DNS::getTransactID() { return this->transactID; }
std::string DNS::getFlags() { return this->flags; }
int DNS::getQuestions() { return this->questions; }
int DNS::getAnswerRRs() { return this->answerRRs; }
int DNS::getAuthorityRRs() { return this->authorityRRs; }
int DNS::getAdditionalRRs() { return this->additionalRRs; }
dns::query::Query DNS::getQuery() { return this->query; }