#ifndef AUTHORITY_HPP
#define AUTHORITY_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <address.hpp>

class hex;


namespace dns
{
    namespace authority
    {
        class Frame: public hex
        {
            private:
                hex name;
                hex type;
                hex _class;
                hex ttl;
                hex primaryNameServer;
                hex responsibleAuthorityMailbox;
                hex serialNumber;
                hex refreshInterval;
                hex retryInterval;
                hex expireLimit;
                hex minimumTtl;

                int FindFQDN(hex &aHex, int start) const;
                hex FindDNSName(hex &aHex) const;
            
            public:
                Frame() = default;
                Frame(hex &aHex);

                const hex &getName() const;
                const hex &getType() const;
                const hex &getClass() const;
                const hex &getTtl() const;
                const hex &getPrimaryNameServer() const;
                const hex &getResponsibleAuthorityMailbox() const;
                const hex &getSerialNumber() const;
                const hex &getRefreshInterval() const;
                const hex &getRetryInterval() const;
                const hex &getExpireLimit() const;
                const hex &getMinimumTtl() const;
        };


        class Authority
        {
            private:
                Frame frame;
                Address name;
                int type;
                std::string _class;
                int ttl;
                Address primaryNameServer;
                Address responsibleAuthorityMailbox;
                int serialNumber;
                int refreshInterval;
                int retryInterval;
                int expireLimit;
                int minimumTtl;

                std::string ParseName(const hex &aHex) const;

            public:
                Authority() = default;
                Authority(hex &aHex);

                const Address &getName() const;
                int getType() const;
                std::string getClass() const;
                const int &getTtl() const;
                const Address &getAddress() const;
                const Address &getPrimaryNameServer() const;
                const Address &getResponsibleAuthorityMailbox() const;
                const int getSerialNumber() const;
                const int getRefreshInterval() const;
                const int getRetryInterval() const;
                const int getExpireLimit() const;
                const int getMinimumTtl() const;
        };
    }

}


#endif