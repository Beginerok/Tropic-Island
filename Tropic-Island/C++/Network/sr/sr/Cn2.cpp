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
void bcopy(char * to, char *from, int l)
{
	for(int i=0;i<l;i++)
		to[i] = from[i];
}
Cn::Cn()
{
    //ctor
}
Cn::Cn(int id)
{
    //ctor
    this->id = id;
}
int Cn::Init()
{
    //countbuf  = 0;
	WSADATA ws={0};
	WORD mw= MAKEWORD(2,2); 
	if(WSAStartup(mw,&ws)==0)
	{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
   ///////////////////////////////////////////////////////////////////here
   if(id != 0)
   {
        server = gethostbyname(name);
        if (server == NULL)
        {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
   }
    //////////////////////////////////////////////////////////////////here
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    //////////////////////////////////////////////////////////////////here
    if(id==0)
        serv_addr.sin_addr.s_addr = INADDR_ANY;
    else
        bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    /////////////////////////////////////////////////////////////here
    serv_addr.sin_port = htons(portno);
    //////////////////////////////////////////////////////////////////here
    if(id==0)
    {
        if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
    }
    else
    {
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            error("ERROR connecting");;
    }
    //////////////////////////////////////////////////////////////////here
    if(id == 0)
    {
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
          error("ERROR on accept");
       close(sockfd);
    }
	}
	else
	{
		printf("nu pizdec!\n");
	}
    return 0;
}
void Cn::error(const char *msg)
{
    perror(msg);
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

    //printf("Please enter the message: ");
    //fgets(buffer,255,stdin);
    if(this->id == 0)
        n = write(newsockfd,buffer,255);
    else
        n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
        bzero(buffer,256);
}
void Cn::Recv()
{
    //ClearBuf();
    {
        /*
        fd_set input;
        FD_ZERO(&input);
        if(this->id == 0)
            FD_SET(newsockfd,&input);
        else
            FD_SET(sockfd,&input);
        struct timeval timeout;
        int sec = 0;
        timeout.tv_sec = sec;
        int msec = 10;
        timeout.tv_usec = msec*1000;
        int n;
        if(this->id == 0)
            n = select(newsockfd,&input,NULL,NULL,&timeout);
        else
            n = select(sockfd,&input,NULL,NULL,&timeout);
        */
        if(this->id == 0)
        {
            //if(!FD_ISSET(newsockfd,&input))
            {
                n = read(  newsockfd ,buffer,255);
                //printf("Here is the message: %s\n",buffer);
            }
        }
        else
        //if(!FD_ISSET(sockfd,&input))
        {
                n = read(  sockfd ,buffer,255);
        }
        if (n < 0) error("ERROR reading from socket");
    }
}
void Cn::SetBuf(char * s)
{
    bzero(buffer,256);
    unsigned int i;
    for(i = 0;i<strlen(s);i++)
    {
        this->buffer[i] = s[i];
    }
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
    //dtor
}
