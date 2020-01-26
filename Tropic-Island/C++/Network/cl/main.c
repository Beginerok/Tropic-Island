#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32 || _W64
    #include <WinSock.h>
    #pragma comment (lib,"WS2_32.lib")
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <pthread.h>
#endif // _WIN32
        int sockfd
        , portno
        , n
        ,*newsockfd
        ,id
        ,clients
        ,currentclient=0;
        ;

#ifdef _WIN32 || _W64
        int clilen;
#else
        socklen_t clilen;
#endif // _WIN32
        struct sockaddr_in serv_addr
        ,cli_addr;
        struct hostent *server;
        char* name;
        char buffer[2][256];

#ifdef _WIN32 || _W64
void bzero(char * buf,int l)
{
	for(int i=0;i<l;i++)
		buf[i] = '\0';
}
int write(int sock,char * buf,int l)
{
	return send(sock,buf,l,0);
}
int read(int sock,char * buf,int l)
{
	return recv(sock,buf,l,0);
}
void close(int sock)
{
	shutdown(sock,0);
}
void bcopy(char * from, char *to, int l)
{
	for(int i=0;i<l;i++)
		to[i] = from[i];
}
#endif // _WIN32
int Init()
{
#ifdef _WIN32 || _W64
	WSADATA ws={0};
	if(WSAStartup(MAKEWORD(2,2),&ws)==0)
	{
#endif // _WIN32
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
	        error("ERROR opening socket");
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		if(id==0)
			serv_addr.sin_addr.s_addr = INADDR_ANY;
		else
			serv_addr.sin_addr.s_addr = inet_addr(name);
		serv_addr.sin_port = htons(portno);
		if(id==0)
		{
	        if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
				error("ERROR on binding");
		}
		else
		{
	        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		        error("ERROR connecting");
		}
		if(id == 0)
		{
	        listen(sockfd,5);

		    clilen = sizeof(cli_addr);
			newsockfd[currentclient] = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
			if (newsockfd < 0)
				error("ERROR on accept");
            currentclient++;
		}

#ifdef _WIN32 || _W64
	}
#endif // _WIN32
	return 0;
}
void error(const char *msg)
{
    perror(msg);
    close(sockfd);
#ifdef _WIN32 || _W64
	WSACleanup();
#endif // _WIN32
	exit(1);
}
int Close()
{
    close(sockfd);
    if(id == 0)
        close(newsockfd);
#ifdef _WIN32 || _W64
    WSACleanup();
#endif // _WIN32
	return 0;
}
void Send(int numberclient,int numberbuf)
{
    if(id == 0)
        n = write(newsockfd[numberclient],buffer[numberbuf],255);
    else
        n = write(sockfd,buffer[numberbuf],strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
        bzero(buffer,256);
}
void Recv(int numberclient,int numberbuf)
{
	if(id == 0)
		n = read(  newsockfd[numberclient] ,buffer[numberbuf],255);
	else
		n = read(  sockfd ,buffer[numberbuf],255);
    if (n < 0) error("ERROR reading from socket");
}
void SetBuf(char * s,int numberbuf)
{
    bzero(buffer[numberbuf],256);
    unsigned int i;
    for(i = 0;i<strlen(s);i++)
        buffer[numberbuf][i] = s[i];
}
void ClearBuf(int numberbuf)
{
    bzero(buffer[numberbuf],256);
}
char * GetBuf(int numberbuf)
{
    return buffer[numberbuf];
}
void SetName(char *name_)
{
    name = name_;
}
void SetPort(int portno_)
{
    portno = portno_;
}
const int length = 256;
char *text;
typedef struct
{
    int numberclient;
    int numberbuf;
}clientdata;
void s(void *numbers)
{
    clientdata *data = (clientdata*)numbers;
    data->numberbuf = 1;
    while(1)
    {
        ClearBuf(data->numberbuf);
        //Sleep(1);
        //scanf("%s",text);
        SetBuf(text,data->numberbuf);
        Send(data->numberclient,data->numberbuf);
        //if(text[0] == '0')
          //  break;
    }
}
void r(void *numbers)
{
    clientdata *data = (clientdata*)numbers;
    data->numberbuf = 0;
    while(1)
    {
        ClearBuf(data->numberbuf);
        //Sleep(1);
        Recv(data->numberclient,data->numberbuf);
        printf("%s",GetBuf(data->numberbuf));
        //if(GetBuf(data->numberbuf)[0] == '0')
           // break;
    }
}
int main()
{
    id = 1;
	printf("input ip address\n");
	char *name = (char*)malloc(sizeof(char)*15);
	//name = "127.0.0.1";
	scanf("%s",name);
	SetName(name);
	printf("input port number\n");
	int port;//=15000;
	scanf("%d",&port);
	SetPort(port);

    text = (char*)malloc(sizeof(char)*n);
	Init();
	printf("0 - for exit!\n");
    clientdata *d;
    d->numberclient = 0;
    pthread_t threadsend,threadreceive;
    pthread_create(&threadreceive,NULL,r,(void*)d);
    pthread_create(&threadsend,NULL,s,(void*)d);
	Close();
	free(name);
	free(text);
    return 0;
}
