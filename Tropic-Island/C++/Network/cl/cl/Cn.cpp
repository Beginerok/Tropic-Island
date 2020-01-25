#include "Cn.h"
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
Cn::Cn()
{

}
Cn::Cn(int id)
{
   this->id = id;
}
#include <iostream>
int Cn::Init()
{
	WSADATA ws={0};
	if(WSAStartup(MAKEWORD(2,2),&ws)==0)
	{
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
			newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
			if (newsockfd < 0)
				error("ERROR on accept");
		}
	}
	return 0;
}
void Cn::error(const char *msg)
{
    perror(msg);
    close(sockfd);
	WSACleanup();	
	exit(1);
}
int Cn::Close()
{
    close(sockfd);
    if(this->id == 0)
        close(newsockfd);
    WSACleanup();
	return 0;
}
void Cn::Snd()
{
    if(this->id == 0)
        n = write(newsockfd,buffer,255);
    else
        n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
        bzero(buffer,256);
}
void Cn::Recv()
{
	if(this->id == 0)
		n = read(  newsockfd ,buffer,255);
	else
		n = read(  sockfd ,buffer,255);
    if (n < 0) error("ERROR reading from socket");
}
void Cn::SetBuf(char * s)
{
    bzero(buffer,256);
    unsigned int i;
    for(i = 0;i<strlen(s);i++)
        this->buffer[i] = s[i];
}
void Cn::ClearBuf()
{
    bzero(buffer,256);
}
char * Cn::GetBuf()
{
    return this->buffer;
}
void Cn::SetName(char *name)
{
    this->name = name;
}
void Cn::SetPrt(int portno)
{
    this->portno = portno;
}
Cn::~Cn()
{

}