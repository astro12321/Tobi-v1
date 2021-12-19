//g++ -o tobi *.cpp && sudo ./tobi
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include "packet.hpp"
#include "network.hpp"

#define BUFFERSIZE 4096

//using namespace std;


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

        Packet pkt(ind, buffer, bytesRead);

        std::cout << "\n------------------------------------------------\n";
        std::cout << pkt.index << ". Packet read: " << pkt.hex << "\n";
        std::cout << "- Network part: " << pkt.layer.network.hex << "\n";
        std::cout << "- Source IP: " << pkt.layer.network.ipv4.source << "\n";
        std::cout << "- Dest IP: " << pkt.layer.network.ipv4.dest << "\n";
        std::cout << "- TTL: " << pkt.layer.network.ipv4.ttl << "\n";
        std::cout << "- Protocol: " << pkt.layer.network.ipv4.protocol << "\n";
        std::cout << "- Packet length: " << pkt.length << "\n";
        std::cout << "------------------------------------------------\n\n";

        if(write(fd, pkt.bytes, bytesRead) < 0) perror("Error writing to tun interface");
    }

}