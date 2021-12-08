//////////////////////////////
//****************************
//1. Si le tun se connecte pas au serveur se reconnecter
//2. Si receiveFromServer le msgLength == -1, ne pas arreter, faire un compteur et arreter sur un certain nombre de fail
//****************************
//////////////////////////////
//gcc tun.c -o tun && sudo ./tun
#include <fcntl.h>  //O_RDWR
#include <string.h> //memset(), memcpy()
#include <stdio.h> //perror(), printf(), fprintf()
#include <stdlib.h> //exit(), malloc(), free() 
#include <sys/ioctl.h> //ioctl() 

//includes for struct ifreq, etc
#include <linux/if.h>
#include <linux/if_tun.h>

#include <unistd.h>

//Socket
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFERSIZE 4096


int openTUN(char *devname, int *fd)
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


int connectToServer(int *sock, struct sockaddr_in *server)
{
    *sock = socket(AF_INET , SOCK_DGRAM , 0);
    if (*sock == -1) { perror("Could not create socket"); close(*sock); return 1; }
    
    memset(server, 0, sizeof(*server));

    server->sin_addr.s_addr = inet_addr("127.0.0.1");
	server->sin_family = AF_INET;
	server->sin_port = htons(5000);

    if (connect(*sock, (struct sockaddr *) server , sizeof(*server)) < 0) { perror("connection error"); return 1; } 

    return 0;
}


int sendToServer(int *sock, struct sockaddr_in *server, unsigned char msg[])
{
    sendto(*sock, msg, strlen(msg), MSG_CONFIRM, (struct sockaddr *) server, sizeof(*server));

    return 0;
}


int receiveFromServer(int *sock, struct sockaddr_in *server, char *sockBuffer) //S'inspirer de bytesToString pour l'array pis le memcpy
{
    int len, msgLength;

    msgLength = recvfrom(*sock, (char*) sockBuffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr *) server, &len);
    
    if (msgLength == -1) { perror("No response from server"); return 1; } //Si un paquet drop toute arrete...

    sockBuffer[msgLength] = '\0';

    return 0;
}


int helloServer(int *sock, struct sockaddr_in *server, char *sockBuffer)
{
    sendToServer(sock, server, "SYN");

    if ((receiveFromServer(sock, server, sockBuffer)) != 0) return 1;

    if (strcmp((char *)sockBuffer, "SYNACK") == 0) 
    { 
        printf("Connected to server !\n"); return 0; 
    }

    sendToServer(sock, server, "ACK");

    perror("Wrong return message from server..."); 
    return 1;
}


int bytesToString(int bytesRead, unsigned char *buffer, char *packet)
{
    char *p = packet;
    
    for (int i = 0; i < bytesRead; i++) 
    { 
        p += snprintf(p, sizeof(buffer[i]) + 2, "%02X", buffer[i]);
    }

    return 0;
}


int main(int argc, char *argv[])
{
    struct sockaddr_in server;
    char devname[] = "tun0";
    int fd, sock, bytesRead;
    int ind;
    unsigned char buffer[BUFFERSIZE];
    char sockBuffer[BUFFERSIZE];

    memset(&server, '\0', sizeof(server));

    if (openTUN(devname, &fd) == -1) return 1;

    printf("Device %s opened\n", devname);

    if (connectToServer(&sock, &server) == 1) return 1;
    if (helloServer(&sock, &server, sockBuffer) == 1) return 1;

    while(1) 
    {
        ind++;
        memset(buffer, 0, sizeof(buffer)); //Avoid junk in the buffer (dont know if slower, have to test)

        bytesRead = read(fd, buffer, sizeof(buffer)); 
    
        char packet[bytesRead * 2 + 1];

        bytesToString(bytesRead, buffer, packet);
        printf("String variable contains:\n%s\n\n", packet);

        sendToServer(&sock, &server, packet);

        if(write(fd, buffer, bytesRead) < 0) perror("Error writing to tun interface");

        //return 1;
    }

    return 0;
}