#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <application.hpp>
#include <DNS/query.hpp>
#include <DNS/answer.hpp>
#include <DNS/authority.hpp>
#include <defaults.hpp>


Application::Application(hex &hex, std::string proto) 
{
    this->h = hex; 
    this->proto = proto;
}


const hex &Application::getHex() const { return this->h; }

std::string Application::getProto() const { return this->proto; }


//virtual DNS
std::string Application::getTransactID() const { return UNDEF; }
std::string Application::getFlags() const { return UNDEF; }
int Application::getQuestions() const { return -1; }
int Application::getAnswerRRs() const { return -1; }
int Application::getAuthorityRRs() const { return -1; }
int Application::getAdditionalRRs() const { return -1; }
const dns::query::Query &Application::getQuery() const { throw std::invalid_argument("No query fields in the packet"); }
const std::vector<dns::answer::Answer> &Application::getAnswers() const { throw std::invalid_argument("No answer fields in the packet"); }
const dns::authority::Authority &Application::getAuthority() const { throw std::invalid_argument("No authority fields in the packet"); }