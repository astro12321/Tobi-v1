#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
#include <DNS/authority.hpp>
#include <address.hpp>


namespace dns
{
    namespace authority
    {
        Frame::Frame(hex &aHex): hex(aHex)
        {
            int start = 0;

            this->name = FindDNSName(aHex);

            start += name.numberOfBytes();

            this->type = aHex.substr(start, 2);
            this->_class = aHex.substr(start + 2, 2);
            this->ttl = aHex.substr(start + 4, 4);

            start += 10; //We skiped 2 bytes (so we're at 10) that defined the length of the data, but we do not want to keep track of them

            int primNSLen = FindFQDN(aHex, start);
            this->primaryNameServer = aHex.substr(start, primNSLen);
            start += primNSLen;

            int authMailLen = FindFQDN(aHex, start);
            this->responsibleAuthorityMailbox = aHex.substr(start, authMailLen);
            start += authMailLen;

            this->serialNumber = aHex.substr(start, 4);
            this->refreshInterval = aHex.substr(start + 4, 4);
            this->retryInterval = aHex.substr(start + 8, 4);
            this->expireLimit = aHex.substr(start + 12, 4);
            this->minimumTtl = aHex.substr(start + 16, 4);
        }


        int Frame::FindFQDN(hex &aHex, int start) const
        {
            int i = start;
            
            while (true)
            {
                int len = aHex[i].to_dec(); //DNS names are separated in the packet by the length of the next word (the length replace the .(dot) that would be there)

                if (len == 0) { //If the length is of 0, then we're at the end of the FQDN
                    i++;
                    break;
                }
                else if (aHex[i].to_bits().substr(0, 2) == "11") { //Instead of writing the domain, the protocol can sometimes write a pointer to the domain in the packet
                    i += 2; //This pointer is 2 bytes long but we just need to check if the first one begin with '11' (in binary) to know it's a pointer
                    break;
                }

                i += len + 1;
            }

            return i - start; //Remove start because we want the length
        }


        hex Frame::FindDNSName(hex &aHex) const
        {
            byte firstByte = aHex[0];

            if (firstByte.to_bits().substr(0, 2) == "11") return aHex.substr(0, 2); //If the first 2 bit are '11', then this is a pointer to the real FQDN
            else if (firstByte.to_dec() == 0) return aHex.substr(0, 1); //<Root>
            return aHex.substr(0, FindFQDN(aHex, 0)); //This is the long FQDN
        }


        const hex &Frame::getName() const { return this->name; }
        const hex &Frame::getType() const { return this->type; }
        const hex &Frame::getClass() const { return this->_class; }
        const hex &Frame::getTtl() const { return this->ttl; }
        const hex &Frame::getPrimaryNameServer() const { return this->primaryNameServer; }
        const hex &Frame::getResponsibleAuthorityMailbox() const { return this->responsibleAuthorityMailbox; }
        const hex &Frame::getSerialNumber() const { return this->serialNumber; }
        const hex &Frame::getRefreshInterval() const { return this->refreshInterval; }
        const hex &Frame::getRetryInterval() const { return this->retryInterval; }
        const hex &Frame::getExpireLimit() const { return this->expireLimit; }
        const hex &Frame::getMinimumTtl() const { return this->minimumTtl; }
        

        //////////////////////////////////////////////


        Authority::Authority(hex &aHex)
        {
            this->frame = Frame(aHex);

            this->name = ParseName(frame.getName());
            this->type = frame.getType().to_dec();
            this->_class = frame.getClass().to_fstring();
            this->ttl = frame.getTtl().to_dec();
            this->primaryNameServer = frame.getPrimaryNameServer().convert_to_string();
            this->responsibleAuthorityMailbox = frame.getResponsibleAuthorityMailbox().convert_to_string();
            this->serialNumber = frame.getSerialNumber().to_dec();
            this->refreshInterval = frame.getRefreshInterval().to_dec();
            this->retryInterval = frame.getRetryInterval().to_dec();
            this->expireLimit = frame.getExpireLimit().to_dec();
            this->minimumTtl = frame.getMinimumTtl().to_dec();
        }


        const Address &Authority::getName() const { return this->name; }
        int Authority::getType() const { return this->type; }
        std::string Authority::getClass() const { return this->_class; }
        const int &Authority::getTtl() const { return this->ttl; }
        const Address &Authority::getPrimaryNameServer() const { return this->primaryNameServer; }
        const Address &Authority::getResponsibleAuthorityMailbox() const { return this->responsibleAuthorityMailbox; }
        const int Authority::getSerialNumber() const { return this->serialNumber; }
        const int Authority::getRefreshInterval() const { return this->refreshInterval; }
        const int Authority::getRetryInterval() const { return this->retryInterval; }
        const int Authority::getExpireLimit() const { return this->expireLimit; }
        const int Authority::getMinimumTtl() const { return this->minimumTtl; }

        std::string Authority::ParseName(const hex &aHex) const
        {
            byte firstByte = aHex[0];

            if (firstByte.to_bits().substr(0, 2) == "11") return aHex.to_fstring(); //If the first 2 bit are '11', then this is a pointer to the real FQDN
            else if (firstByte.to_dec() == 0) return "<Root>"; //<Root>
            else return aHex.convert_to_string(); //This is the long FQDN
        }

    }

}