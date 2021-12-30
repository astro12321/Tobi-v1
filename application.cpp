#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "application.hpp"
#include "query.hpp"
#include "defaults.hpp"


Application::Application(hex &hex, std::string proto) 
{
    this->h = hex; 
    this->proto = proto;
}


hex &Application::getHex() { return this->h; }

std::string Application::getProto() { return this->proto; }


//virtual DNS
std::string Application::getTransactID() { return UNDEF; }
std::string Application::getFlags() { return UNDEF; }
int Application::getQuestions() { return -1; }
int Application::getAnswerRRs() { return -1; }
int Application::getAuthorityRRs() { return -1; }
int Application::getAdditionalRRs() { return -1; }
dns::query::Query Application::getQuery() { throw std::invalid_argument("No query fields in the packet"); }