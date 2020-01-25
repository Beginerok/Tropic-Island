#ifndef CN_H
#define CN_H

#include <stdio.h>
//#include <WinSock.h>
#include <WS2tcpip.h>
#pragma comment (lib,"ws2_32.lib")//(lib,"msvcurt.lib")
class Cn
{
    public:
        Cn();
        Cn(int id);
        int Init();
        int Close();
        void Snd();
        void Recv();
        void SetBuf(char * s);
        void ClearBuf();
        char * GetBuf();
        void error(const char *msg);
        void SetName(char * name);
        void SetPrt(int portno);
        virtual ~Cn();
    protected:
    private:
        int sockfd
        , portno
        , n
        ,newsockfd
        ,id;
        /*socklen_t*/ int clilen;
        struct sockaddr_in serv_addr
        ,cli_addr;
        struct hostent *server;
        char* name;

        char buffer[256];
};

#endif // CN_H
