//for debug: https://hpd.gasmi.net/
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include <packet.hpp>
#include <network.hpp>
#include <hex.hpp>
#include <defaults.hpp>
#include <dns.hpp>
#include <layer.hpp>


int opentun(char *devname, int *fd)
{
    struct ifreq ifr;
    int err;

    if ((*fd = open("/dev/net/tun", O_RDWR)) == -1) { perror("Error opening /dev/net/tun"); return -1; }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    strncpy(ifr.ifr_name, devname, IFNAMSIZ); 

    if ((err = ioctl(*fd, TUNSETIFF, (void *) &ifr)) == -1) { perror("ioctl TUNSETIFF"); close(*fd); return -1; }

    return 0;
}


int main(int argc, char *argv[])
{
    int fd, bytesRead, ind;
    char devname[] = "tun0";
    unsigned char buffer[BUFFERSIZE];

    opentun(devname, &fd);

    ind = 0;

    while (true)
    {
        ind++;
        bytesRead = read(fd, buffer, sizeof(buffer));

        if (bytesRead < 0) perror("Error reading from tun interface");


        hex packetHex = hex(buffer, bytesRead);
        Packet pkt(ind, packetHex);

        if (pkt.getTransportProto() == "UDP" && pkt.getApplicationProto() == "DNS")
        {
            std::cout << "\n------------------------------------------------\n";

            std::cout << pkt.getIndex() << ". Packet read: " << pkt.getHex().to_string() << "\n";

            if (pkt.getLayer().networkIsValid()) {
                /*std::cout << "- Source IP: " << pkt.getLayer().getNetwork().getSource().to_string() << "\n";
                std::cout << "- Dest IP: " << pkt.getLayer().getNetwork().getDest().to_string() << "\n";
                std::cout << "- Network Protocol: " << pkt.getNetworkProto() << "\n";
                std::cout << "- Transport Protocol: " << pkt.getTransportProto() << "\n";*/

                if (pkt.getLayer().transportIsValid()) {
                    /*if (pkt.getTransportProto() == "ICMP") { //ICMP
                        std::cout << "- Transport code: " << pkt.getLayer().getTransport().getCode() << "\n";
                        std::cout << "- Transport type: " << pkt.getLayer().getTransport().getType() << "\n";
                        std::cout << "- Transport csum: " << pkt.getLayer().getTransport().getCsum() << "\n";
                        std::cout << "- Transport data: " << pkt.getLayer().getTransport().getData() << "\n";
                    }

                    if (pkt.getTransportProto() == "TCP") { //TCP
                        std::cout << "- Transport source: " << pkt.getLayer().getTransport().getSource() << "\n";
                        std::cout << "- Transport dest: " << pkt.getLayer().getTransport().getDest() << "\n";
                        std::cout << "- Transport csum: " << pkt.getLayer().getTransport().getCsum() << "\n";
                        std::cout << "- Transport seq: " << pkt.getLayer().getTransport().getSeqNumber() << "\n";
                        std::cout << "- Transport ack: " << pkt.getLayer().getTransport().getAckNumber() << "\n";
                        std::cout << "- Transport hdr length: " << pkt.getLayer().getTransport().getHdrLen() << "\n";
                        std::cout << "- Transport flags: " << pkt.getLayer().getTransport().getFlags() << "\n";
                        std::cout << "- Transport windows: " << pkt.getLayer().getTransport().getWindow() << "\n";
                    }
                    
                    if (pkt.getTransportProto() == "TCP") { //UDP
                        std::cout << "- Transport source: " << pkt.getLayer().getTransport().getSource() << "\n";
                        std::cout << "- Transport dest: " << pkt.getLayer().getTransport().getDest() << "\n";
                        std::cout << "- Transport csum: " << pkt.getLayer().getTransport().getCsum() << "\n";
                    }*/

                    if (pkt.getLayer().applicationIsValid()) {
                        if (pkt.getLayer().getApplication().getProto() == "DNS") {
                            std::cout << "- Application Protocol: " << pkt.getApplicationProto() << "\n";
                            std::cout << "- Status: " << pkt.getStatus() << "\n";
                            std::cout << "\n\n";
                            std::cout << "- DNS transaction ID: " << pkt.getLayer().getApplication().getTransactID() << "\n";
                            std::cout << "- DNS flags: " << pkt.getLayer().getApplication().getFlags() << "\n";
                            std::cout << "- DNS questions: " << pkt.getLayer().getApplication().getQuestions() << "\n";
                            std::cout << "- DNS answersRRs: " << pkt.getLayer().getApplication().getAnswerRRs() << "\n";
                            std::cout << "- DNS authorityRRs: " << pkt.getLayer().getApplication().getAuthorityRRs() << "\n";
                            std::cout << "- DNS AddRRs: " << pkt.getLayer().getApplication().getAdditionalRRs() << "\n";
                            std::cout << "\n";
                            std::cout << "- DNS Query name: " << pkt.getLayer().getApplication().getQuery().getName().to_string() << "\n";
                            std::cout << "- DNS Query type: " << pkt.getLayer().getApplication().getQuery().getType() << "\n";
                            std::cout << "- DNS Query class: " << pkt.getLayer().getApplication().getQuery().getClass() << "\n";

                            if (pkt.getLayer().getApplication().getAnswerRRs() >= 1)
                            {
                                for (size_t i = 0; i < pkt.getLayer().getApplication().getAnswers().size(); i++)
                                {
                                    std::cout << "---------\n";
                                    std::cout << "- DNS Answer name: " << pkt.getLayer().getApplication().getAnswers()[i].getName() << "\n";
                                    std::cout << "- DNS Answer type: " << pkt.getLayer().getApplication().getAnswers()[i].getType() << "\n";
                                    std::cout << "- DNS Answer class: " << pkt.getLayer().getApplication().getAnswers()[i].getClass() << "\n";
                                    std::cout << "- DNS Answer ttl: " << pkt.getLayer().getApplication().getAnswers()[i].getTtl() << "\n";
                                    std::cout << "- DNS Answer addr: " << pkt.getLayer().getApplication().getAnswers()[i].getAddress().to_string() << "\n";
                                }
                            }

                            if (pkt.getLayer().getApplication().getAuthorityRRs() >= 1)
                            {
                                std::cout << "- DNS Authority name: " << pkt.getLayer().getApplication().getAuthority().getName().to_string() << "\n";
                                std::cout << "- DNS Authority type: " << pkt.getLayer().getApplication().getAuthority().getType() << "\n";
                                std::cout << "- DNS Authority class: " << pkt.getLayer().getApplication().getAuthority().getClass() << "\n";
                                std::cout << "- DNS Authority ttl: " << pkt.getLayer().getApplication().getAuthority().getTtl() << "\n";
                                std::cout << "- DNS Authority primaryNameServer: " << pkt.getLayer().getApplication().getAuthority().getPrimaryNameServer().to_string() << "\n";
                                std::cout << "- DNS Authority responsibleAuthorityMailbox: " << pkt.getLayer().getApplication().getAuthority().getResponsibleAuthorityMailbox().to_string() << "\n";
                                std::cout << "- DNS Authority SN: " << pkt.getLayer().getApplication().getAuthority().getSerialNumber() << "\n";
                                std::cout << "- DNS Authority refreshInterval: " << pkt.getLayer().getApplication().getAuthority().getRefreshInterval() << "\n";
                                std::cout << "- DNS Authority retryInterval: " << pkt.getLayer().getApplication().getAuthority().getRetryInterval() << "\n";
                                std::cout << "- DNS Authority expireLimit: " << pkt.getLayer().getApplication().getAuthority().getExpireLimit() << "\n";
                                std::cout << "- DNS Authority minimumTtl: " << pkt.getLayer().getApplication().getAuthority().getMinimumTtl() << "\n";
                            }

                        }

                    }

                }

                std::cout << "\n";
            }

            std::cout << "------------------------------------------------\n\n";
        }


        if(write(fd, &pkt.getHex().getBytes()[0], bytesRead) < 0) perror("Error writing to tun interface");
    }

}