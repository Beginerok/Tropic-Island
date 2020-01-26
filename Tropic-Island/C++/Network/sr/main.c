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
        ,clients
        ,currentclient=0;
        ;
        socklen_t clilen;
        struct sockaddr_in serv_addr
        ,cli_addr;
        struct hostent *server;
        char* name;
        char buffer[2][256];

int roundr = 0;
int rounds = 0;
int Init()
{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
	        error("ERROR opening socket");
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		if(id==0)
			serv_addr.sin_addr.s_addr = INADDR_ANY;

		serv_addr.sin_port = htons(portno);
		if(id==0)
		{
	        if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
				error("ERROR on binding");
		}

		if(id == 0)
		{
	        listen(sockfd,5);
		    clilen = sizeof(cli_addr);

			newsockfd[currentclient] = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
			if (newsockfd[currentclient] < 0)
				error("ERROR on accept");
            currentclient++;
		}
	return 0;
}
void *a(void *args)
{
    while(1)
    {
        newsockfd[currentclient] = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd[currentclient]< 0)
            error("ERROR on accept");
        currentclient++;
        printf("curr_cli",currentclient-1);
    }
}
void error(const char *msg)
{
    perror(msg);
    close(sockfd);
	exit(1);
}
int Close()
{
    close(sockfd);
    close(newsockfd);
	return 0;
}

void Send(int numberclient,int numberbuf)
{
    n = write(newsockfd[numberclient],buffer[numberbuf],256);
    if(n < 0)
    {
        char*str=(char*)malloc(sizeof(char)*3);
        sprintf(str,"%s",rounds);
        perror(str);
        error("ERROR writing to socket");
        free(str);
    }
    //bzero(buffer,256);
}
void Recv(int numberclient,int numberbuf)
{
    n = read(newsockfd[numberclient],buffer[numberbuf],256);
    if (n < 0)
    {
        char*str=(char*)malloc(sizeof(char)*3);
        sprintf(str,"%s",roundr);
        perror(str);
        error("ERROR reading from socket");
        free(str);
    }
}
void SetBuf(char * s,int numberbuf)
{
    //bzero(buffer[numberbuf],256);
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
    int numberclient;
    int numberbuf;
    bool exit;
}clientdata;
void s(void *numbers)
{
    clientdata *data = (clientdata*)numbers;
    data->numberbuf = 1;
    while(rounds++<100)
    {
        //ClearBuf(data->numberbuf);
        //Sleep(1);
        //scanf("%s",text);
        SetBuf(text,data->numberbuf);
        Send(data->numberclient,data->numberbuf);
        printf("%s",GetBuf(data->numberbuf));
        //if(text[0] == '0')
          //  break;
    }
    data->exit = true;
}
void r(void *numbers)
{
    clientdata *data = (clientdata*)numbers;
    data->numberbuf = 0;

    while(roundr++<100)
    {
        //ClearBuf(data->numberbuf);
        //Sleep(1);
        Recv(data->numberclient,data->numberbuf);
        printf("%s",GetBuf(data->numberbuf));
        //if(GetBuf(data->numberbuf)[0] == '0')
           // break;
    }
    data->exit = true;
}
int main()
{
    text = "0000000000000001\n";

    printf("Enter clients count\n");
    //scanf("%d",&clients);
    clients=1;
    newsockfd = (int*)malloc(sizeof(int)*clients);
    pthread_t threadsend,threadreceive,threadaccept;
    text = (char*)malloc(sizeof(char)*length);
	printf("input port number\n");
	int port=15000;
	//scanf("%d",&port);
	SetPort(port);
	Init();
	pthread_create(&threadaccept,NULL,a,NULL/*(void*)currentclient*/);
    clientdata *datareceive = (clientdata*)malloc(sizeof(clientdata));
    clientdata*datasend=(clientdata*)malloc(sizeof(clientdata));
	for(int i=0;i<clients;i++)
    {
        datareceive->numberclient = i;
        datareceive->exit = false;
        datasend->numberclient = i;
        datasend->exit = false;
        pthread_create(&threadreceive,NULL,r,(void*)datareceive);
        pthread_create(&threadsend,NULL,s,(void*)datasend);
        //pthread_join(threadreceive,NULL);
        //pthread_join(threadsend,NULL);
	}
	while(!(datareceive->exit && datasend->exit))
        sleep(1);

        //r(i);
	Close();
	//system("pause");
	free(text);
	free(newsockfd);
	//char c;
	//scanf("%c",&c);
    return 0;
}
