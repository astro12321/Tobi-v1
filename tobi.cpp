//g++ -o tobi *.cpp && sudo ./tobi
//sudo valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./tobi
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include "packet.hpp"
#include "network.hpp"
#include "hex.hpp"
#include "defaults.hpp"


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


        std::cout << "\n------------------------------------------------\n";

        hex packetHex = hex(buffer, bytesRead);
        Packet pkt(ind, packetHex);

        std::cout << pkt.getIndex() << ". Packet read: " << pkt.getHex().to_string() << "\n";

        if (pkt.getTransportProto() == "TCP" || pkt.getTransportProto() == "ICMP")
        {
            if (pkt.getLayer().networkIsValid()) {
                std::cout << "- Network part: " << pkt.getLayer().getNetwork().getHex().to_string() << "\n";
                std::cout << "- Source IP: " << pkt.getLayer().getNetwork().getSource() << "\n";
                std::cout << "- Dest IP: " << pkt.getLayer().getNetwork().getDest() << "\n";
                std::cout << "- TTL: " << pkt.getLayer().getNetwork().getTTL() << "\n";
                std::cout << "- Network Protocol: " << pkt.getNetworkProto() << "\n";
                std::cout << "- Transport Protocol: " << pkt.getTransportProto() << "\n";
                std::cout << "- Status: " << pkt.getStatus() << "\n";
                std::cout << "\n";

                if (pkt.getLayer().transportIsValid()) {
                    //ICMP
                    /*std::cout << "- Transport code: " << pkt.getLayer().getTransport().getCode() << "\n";
                    std::cout << "- Transport type: " << pkt.getLayer().getTransport().getType() << "\n";
                    std::cout << "- Transport checksum: " << pkt.getLayer().getTransport().getCsum() << "\n";
                    std::cout << "- Transport data: " << pkt.getLayer().getTransport().getData() << "\n";*/

                    //TCP
                    std::cout << "- Transport source: " << pkt.getLayer().getTransport().getSource() << "\n";
                    std::cout << "- Transport dest: " << pkt.getLayer().getTransport().getDest() << "\n";
                    std::cout << "- Transport csum: " << pkt.getLayer().getTransport().getCsum() << "\n";
                    std::cout << "- Transport seq: " << pkt.getLayer().getTransport().getSeqNumber() << "\n";
                    std::cout << "- Transport ack: " << pkt.getLayer().getTransport().getAckNumber() << "\n";
                    std::cout << "- Transport hdr length: " << pkt.getLayer().getTransport().getHdrLen() << "\n";
                    std::cout << "- Transport flags: " << pkt.getLayer().getTransport().getFlags() << "\n";
                    std::cout << "- Transport windows: " << pkt.getLayer().getTransport().getWindow() << "\n";
                }
            }
        }
        
        std::cout << "------------------------------------------------\n\n";


        if(write(fd, &pkt.getHex().getBytes(), bytesRead) < 0) perror("Error writing to tun interface");
    }


}