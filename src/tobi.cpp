#include <fcntl.h>
#include <iostream>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iomanip>
#include <sstream>
#include <string>
#include <thread>

#include <GUI.cpp>

#include <IPv4Layer.h>
#include <Packet.h>
#include <RawPacket.h>

#define BUFFERSIZE 4096


int opentun(char *devname, int *fd) {
    struct ifreq ifr;
    int err;

    if ((*fd = open("/dev/net/tun", O_RDWR)) == -1) {
        perror("Error opening /dev/net/tun");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    strncpy(ifr.ifr_name, devname, IFNAMSIZ);

    if ((err = ioctl(*fd, TUNSETIFF, (void *)&ifr)) == -1) {
        perror("ioctl TUNSETIFF");
        close(*fd);
        return -1;
    }

    return 0;
}

//Only for testing
std::string hexStr(const uint8_t *data, int len) {
    std::stringstream ss;
    ss << std::hex;

    for (int i(0); i < len; ++i)
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}

int main(int argc, char *argv[]) {
    int fd, bytesRead, ind;
    char devname[] = "tun0";
    unsigned char buffer[BUFFERSIZE];

    opentun(devname, &fd);

    ind = 0;

	std::thread guiThread(&startGUI);

    while (true) {
        ind++;
        bytesRead = read(fd, buffer, sizeof(buffer));

        if (bytesRead < 0)
            perror("Error reading from tun interface");

        ///////////////////////This slows down the program because it gotta wait on the terminal to proceeds with packets
        timeval tm;
        gettimeofday(&tm, NULL);

        pcpp::RawPacket rawPacket((uint8_t *)buffer, bytesRead, tm, false, pcpp::LinkLayerType::LINKTYPE_RAW);
        pcpp::Packet parsedPacket(&rawPacket);
        pcpp::IPv4Address srcIP = parsedPacket.getLayerOfType<pcpp::IPv4Layer>()->getSrcIPv4Address();
        pcpp::IPv4Address destIP = parsedPacket.getLayerOfType<pcpp::IPv4Layer>()->getDstIPv4Address();

        std::cout << "\nPacket " << ind << ": " << std::endl << "srcIP: " << srcIP << std::endl << "dstIP: " << destIP << std::endl;
        ///////////////////////

        // std::cout << "\nPacket " << ind << "." << std::endl << hexStr(buffer, bytesRead) << std::endl;

        if (write(fd, buffer, bytesRead) < 0)
            perror("Error writing to tun interface");
    }

	guiThread.join();
}
