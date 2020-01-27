#include <stdio.h>
#include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <pthread.h>
        int sockfd
        , portno
        , n
        ,*newsockfd
        ,id
        ;
        socklen_t clilen;
        struct sockaddr_in serv_addr
        ,cli_addr;
        /*struct hostent *server;*/
        char* name;
        char buffer[2][256];

int roundr = 0;
int rounds = 0;
void error(const char *msg)
{
    perror(msg);
    close(sockfd);
	exit(1);
}
int Init()
{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
	        error("ERROR opening socket");
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;

			serv_addr.sin_addr.s_addr = inet_addr(name);
		serv_addr.sin_port = htons(portno);

		{
	        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		        error("ERROR connecting");
		}
	return 0;
}

int Close()
{
    close(sockfd);
	return 0;
}
void Send(int numberbuf)
{
    n = write(sockfd,buffer[numberbuf],256);
    if (n < 0)
	{
        char*str=(char*)malloc(sizeof(char)*3);
        sprintf(str,"%d",rounds);
        perror(str);
        error("ERROR writing to socket");
  //      free(str);
	}
	//bzero(buffer,256);
}
void Recv(int numberbuf)
{
    n = read(sockfd,buffer[numberbuf],256);
	if (n < 0)
    {
        char*str=(char*)malloc(sizeof(char)*3);
        sprintf(str,"%d",roundr);
        perror(str);
        error("ERROR reading from socket");
  //      free(str);
    }
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
#include <stdbool.h>
typedef struct
{
    //int numberclient;
    int numberbuf;
    bool exit;
}data;
void s(void *numbers)
{
    data *data_ = (data*)numbers;
    data_->numberbuf = 1;
    //int round=0
    while(rounds++<10)
    {
        ClearBuf(data_->numberbuf);
        //Sleep(1);
        //scanf("%s",text);
        SetBuf(text,data_->numberbuf);
        Send(/*data->numberclient,*/data_->numberbuf);
        printf("%s",GetBuf(data_->numberbuf));
        //if(text[0] == '0')
          //  break;
    }
    data_->exit=true;
}
void r(void *numbers)
{
    data *data_ = (data*)numbers;
    data_->numberbuf = 0;
    //int round = 0;
    while(roundr++<10)
    {
        ClearBuf(data_->numberbuf);
        //Sleep(1);
        Recv(data_->numberbuf);
        printf("%s",GetBuf(data_->numberbuf));
        //if(GetBuf(data->numberbuf)[0] == '0')
           // break;
    }
    data_->exit=true;
}
int main()
{
	printf("input ip address\n");
	char *name = (char*)malloc(sizeof(char)*15);
	name = "127.0.0.1";
	//scanf("%s",name);
	SetName(name);
	printf("input port number\n");
	int port=15000;
	//scanf("%d",&port);
	SetPort(port);
    text = (char*)malloc(sizeof(char)*length);   
    text = "1111111111111111\n";
    SetBuf(text,1);
    data *datareceive = (data*)malloc(sizeof(data));
    data*datasend=(data*)malloc(sizeof(data));
    /*
    datareceive->numberclient = 0;
    datasend->numberclient = 0;
    */
    pthread_t threadsend,threadreceive;
    datareceive->exit = false;
    datasend->exit = false;
	Init();
    pthread_create(&threadreceive,NULL,r,(void*)datareceive);
    pthread_create(&threadsend,NULL,s,(void*)datasend);
    while(!(datareceive->exit && datasend->exit))
        sleep(1);
	Close();
	free(text);
	//free(name);
    return 0;
}