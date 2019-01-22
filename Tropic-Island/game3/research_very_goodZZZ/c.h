#ifndef CON_H
#define CON_H
#include <iostream>
#include <stdlib.h>
#include <string.h>

#ifndef  _W64 || _WIN32 ||_WINDOWS_2
	#include <unistd.h>
#endif
#include <sys/types.h>
#ifdef _W64 || _WIN32 || _WINDOWS_2 
	#include <WinSock.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
#endif

#include <time.h>
#define HOME "./"
#define HANDSHAKE 1
#define CERTF  HOME "cert.pem"
#define KEYF  HOME  "cert.pem"

#define CHK_NULL(x) if ((x)==NULL) {printf("chk_null\n");char c; std::cin>>c;exit (1);}
#define CHK_ERR(err,s) if ((err)==-1) { printf("chk_err\n"); perror(s);char c; std::cin>>c; exit(1); }
#define CHK_SSL(err) if ((err)==-1) {printf("chk_ssl\n"); ERR_print_errors_fp(stderr);char c; std::cin>>c; exit(2); }

#include <openssl/crypto.h>
#include <openssl/rsa.h>       /* SSLeay stuff */
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#ifdef  _W64 || _WIN32 || _WINDOWS_2
#define socklen_t int
#define sleep(a) Sleep(a*1000)
	#pragma comment (lib,"ssleay32.lib")
	#pragma comment (lib,"libeay32.lib")
	#pragma comment (lib,"WS2_32.lib")
#endif
#include "FileReader.h"

#if HANDSHAKE == 0
    #include <fcntl.h>
#endif
class Con
{
public:
    Con();
    Con(int id);
    int Init(int currentclient);
	int InitOnce();
    int InitSecure(int currentclient);
    int Close(int currentclient);
    int Snd(int currentclient);
    int Recv(int currentclient);
    int SetBuf(char * s,int currentclient);
    void ClearBuf(int currentclient);
    char * GetBuf(int currentclient);
    void error(const char *msg);
    bool Closed(int currentclient);
    void End(int currentclient);
    void SetPort(int port);
    int GetSession();
    volatile bool AllClose();
    virtual ~Con();
protected:
private:
    int *sockfd,*udpsocket
    , portno,udpport
               , n
               ,*newsockfd
               ,id;
	socklen_t clilen,servlen;
    struct sockaddr_in serv_addr
            ,cli_addr;
    struct hostent *server;
    char *address;
    char **buffer,**bbuf,*udpbuffer;
    int err;
    SSL_CTX *ctx;
    SSL     **ssl;
    X509    *server_cert,*client_cert;
    SSL_METHOD *meth;
    char    *str;
    bool cr;
    time_t datetime;
    char datetimebuf[127];
    char hostname[128];
    int countclient;
    int flag;
    int type;
    int *buf;
    int *nbuf;
    SSL **sbuf;
    bool *closeflag,*fbuf,changeport;
    int pl;
    int countsession;
};
#endif // CON_H
