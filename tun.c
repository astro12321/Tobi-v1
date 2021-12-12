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

#include <errno.h>
#include <sys/select.h>


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


int receiveFromServer(int *sock, struct sockaddr_in *server, char *sockBuffer)
{
    int len, msgLength;

    msgLength = recvfrom(*sock, (char*) sockBuffer, BUFFERSIZE, MSG_WAITALL, (struct sockaddr *) server, &len);
    
    //if (msgLength == -1) { perror("No response from server"); return 1; } //Si un paquet drop toute arrete... (cause probleme)

    sockBuffer[msgLength] = '\0';

    return 0;
}


int bytesToHex(int bytesRead, unsigned char *buffer, char *packet)
{
    char *p = packet;
    
    for (int i = 0; i < bytesRead; i++) 
    { 
        p += snprintf(p, sizeof(buffer[i]) + 2, "%02X", buffer[i]);
    }

    return 0;
}


int HexToBytes(const char *buffer)
{
    int ret = 0;

    for(int i = 0; i < 2; i++)
    {
        char c = *buffer++;
        int n = 0;

        if('0' <= c && c <= '9')
            n = c - '0';
        else if('a' <= c && c <= 'f')
            n = 10 + c-'a';
        else if( 'A' <= c && c <= 'F')
            n = 10 + c - 'A';

        ret = n + ret * 16;
    }
    
    return ret;
}


int main(int argc, char *argv[])
{
    struct sockaddr_in server;
    char devname[] = "tun0";
    int fd, sock, bytesRead, nwrite, nread;
    int ind = 0;
    unsigned char buffer[BUFFERSIZE];
    char sockBuffer[BUFFERSIZE];

    memset(&server, 0, sizeof(server));

    if (openTUN(devname, &fd) == -1) return 1;

    printf("Device %s opened\n", devname);

    if (connectToServer(&sock, &server) == 1) return 1;



    //////////////////////////////////
    int maxfd;


    maxfd = (fd > sock)?fd:sock;
    //////////////////////////////////


    while(1) 
    {
        ind++;
        memset(buffer, 0, sizeof(buffer)); //Avoid junk in the buffer (dont know if slower, have to test)


        //////////////////////////////////

        /*int ret;
        fd_set rd_set;

        FD_ZERO(&rd_set);
        FD_SET(fd, &rd_set); 
        FD_SET(sock, &rd_set);

        ret = select(maxfd + 1, &rd_set, NULL, NULL, NULL);

        if (ret < 0 && errno == EINTR)
        {
            continue;
        }

        if (ret < 0) 
        {
            perror("select()");
            exit(1);
        }*/





        
    
        //////////////////////////////////

        //if(FD_ISSET(fd, &rd_set))
        //{
            ///////////////////////////////////////////////////////////////Read
            printf("\n%d. Reading card and sending to socket", ind);

            bytesRead = read(fd, buffer, sizeof(buffer)); 
        
            char packet[bytesRead * 2 + 1];
            bytesToHex(bytesRead, buffer, packet);

            nwrite = write(sock, packet, sizeof(packet));
            ///////////////////////////////////////////////////////////////
        //}

        //if(FD_ISSET(sock, &rd_set)) 
        //{
            ///////////////////////////////////////////////////////////////Write
            printf("\n%d. Reading socket and writing on card...", ind);

            nread = read(sock, sockBuffer, BUFFERSIZE);

            //////////////////

            const char *in = sockBuffer;
            char out[bytesRead];

            for(int i = 0; i < bytesRead; i++)
            {
                out[i] = HexToBytes(in);
                in += 2;
            }

            //memset(sockBuffer, 0, sizeof(sockBuffer));

            if(write(fd, out, bytesRead) < 0) perror("Error writing to tun interface");
            ///////////////////////////////////////////////////////////////
        //}

        

        



    }

    return 0;
}