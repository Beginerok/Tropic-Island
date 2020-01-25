#include "example\c.h"
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
Con::Con()
{

}
int Con::GetSession()
{
	return countsession;
}
Con::Con(int id_)
{
    id = id_;
    FileReader *filereader = new FileReader();
	filereader->FileReader__("simple.conf", "r");
	address = new char[16];
	strcpy(address,filereader->GetNumber().c_str());
	portno = atoi(filereader->GetNumber().c_str());
	countsession = atoi(filereader->GetNumber().c_str());
    cr = (bool)atoi(filereader->GetNumber().c_str());
	pl = atoi(filereader->GetNumber().c_str());
	filereader->~FileReader();
	countclient = 0;
	changeport = false;
	//if(id == 1)
    {
		if(id==0)
        {
			if(!cr)
				ssl = (SSL**)malloc(sizeof(SSL*)*(countsession));
			sockfd = (int*)malloc(sizeof(int)*(countsession));
			newsockfd = (int*)malloc(sizeof(int)*(countsession));
			closeflag = (bool*)malloc(sizeof(bool)*(countsession));
			buffer = (char**)(malloc(sizeof(char)*pl*countsession));//new char[pl];
			for(int i=0;i<countsession;i++)
			{
				closeflag[i] = false;
				buffer[i] = (char*)malloc(sizeof(char)*pl);
				for(int j=0;j<pl;j++)
					buffer[i][j] = '-';
			}
			clilen = sizeof(cli_addr);
			udpsocket = new int[1];
			udpbuffer = new char[pl];
		}
		else
		{
			ssl = (SSL**)malloc(sizeof(SSL*)*(countclient+1));
			sockfd = (int*)malloc(sizeof(int)*(countclient+1));
			newsockfd = (int*)malloc(sizeof(int)*(countclient+1));
			closeflag = (bool*)malloc(sizeof(bool)*(countclient+1));
			closeflag[0] = false;
			buffer = (char**)(malloc(sizeof(char)*pl*(countclient+1)));//new char[pl];
			buffer[0] = (char*)malloc(sizeof(char)*pl);
			for(int j=0;j<pl;j++)
				buffer[0][j] = '-';
			servlen = sizeof(serv_addr);
		}
	}
    #if HANDSHAKE == 0
    if(fcntl(sockfd,F_SETFL,fcntl(sockfd,F_GETFL,0) | O_NONBLOCK)<0)
        std::cout<<"some wrong"<<errno;
    type = SOCK_DGRAM;
    sockfd[currentclient] = socket(AF_INET, type, IPPROTO_UDP);
    flag =  MSG_DONTWAIT;
    #endif
}
bool Con::Closed(int currentclient)
{
	return 0;
}
volatile bool Con::AllClose()
{
    int i=-1,count=0;
    while(++i<countclient)
        if(closeflag[i] == true)
            count++;
    if(countclient == count)
        return true;
    else
        return false;
}
void Con::End(int currentclient)
{
	strcpy(buffer[currentclient],"End");
    //this->buffer[currentclient][0] = '0';
    Snd(currentclient);
}
void Con::SetPort(int port)
{
    this->portno = port;
};
int Con::InitSecure(int currentclient)
{
    if(id == 0)
    {
        //sbuf = (SSL**)realloc(ssl,countclient*sizeof(SSL*));
        //if(!sbuf)
        //    std::cout<<"error sreal"<<'\n';
        //else
        //    ssl = sbuf;
        SSL_load_error_strings();
        SSLeay_add_ssl_algorithms();
        meth = (SSL_METHOD *)SSLv23_server_method();
    }
    else
    {
        SSL_load_error_strings();
        SSLeay_add_ssl_algorithms();
        meth = (SSL_METHOD *)SSLv23_client_method();
    }
    ctx = SSL_CTX_new (meth);
    //if(id == 0)
    {
        if (!ctx)
        {
            ERR_print_errors_fp(stderr);
            exit(2);
        }
        if (SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM) <= 0)
        {
            ERR_print_errors_fp(stderr);
            exit(3);
        }
        if (SSL_CTX_use_PrivateKey_file(ctx, KEYF, SSL_FILETYPE_PEM) <= 0)
        {
            ERR_print_errors_fp(stderr);
            exit(4);
        }
        if (!SSL_CTX_check_private_key(ctx))
        {
            fprintf(stderr,"Private key does not match the certificate public key\n");
            exit(5);
        }
    }
    CHK_NULL(ctx);
    CHK_SSL(err);
    ssl[currentclient] = SSL_new (ctx);
    CHK_NULL(ssl[currentclient]);
    if(id == 0)
        SSL_set_fd (ssl[currentclient], newsockfd[currentclient]);
    else
        SSL_set_fd (ssl[currentclient], sockfd[currentclient]);
    if(id == 0)
        err = SSL_accept (ssl[currentclient]);
    else
        err = SSL_connect (ssl[currentclient]);
    CHK_SSL(err);
    //printf ("SSL connection using %s\n", SSL_get_cipher (ssl));
    //SSL_CTX_add_client_CA()
    ////////
    if(id ==0)
    {
        client_cert = SSL_get_certificate (ssl[currentclient]);
        CHK_NULL(client_cert);
    }
    else
    {
        server_cert = SSL_get_peer_certificate (ssl[currentclient]);
        CHK_NULL(server_cert);
    }
    if(id == 0)
        str = X509_NAME_oneline (X509_get_subject_name (client_cert),0,0);
    else
        str = X509_NAME_oneline (X509_get_subject_name (server_cert),0,0);
    CHK_NULL(str);
    //printf ("\t subject: %s\n", str);
    OPENSSL_free(str);
    if(id == 0)
        str = X509_NAME_oneline(X509_get_issuer_name(client_cert),0,0);
    else
        str = X509_NAME_oneline(X509_get_issuer_name(server_cert),0,0);
    CHK_NULL(str);
    //printf ("\t issuer: %s\n", str);
    OPENSSL_free(str);
    /* We could do all sorts of certificate verification stuff here before deallocating the certificate. */
    if(id == 0)
        X509_free(client_cert);
    else
        X509_free(server_cert);
    return 0;
}
int Con::Init(int currentclient)
{
	WSADATA ws = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &ws) == 0)
	{
			
		if (!gethostname(hostname, 128))
		{
			if (server = gethostbyname(hostname))
			{
				std::cout << "Your address>";
				std::cout << (inet_ntoa(*((in_addr*)server->h_addr_list[0]))) << std::endl;
			}
			else
			{
				std::cout << "Please connect to Internet or change(check) your (DNS server or Gateaway) or Your computer name is very long(last is little possibility) ;)" << '\n';
				std::cout << "Your address>";
				server = gethostbyname("localhost");
				std::cout << (inet_ntoa(*((in_addr*)server->h_addr_list[0]))) << std::endl;
			}
		}
		if (id == 1)
		{
			udpport = 15000;
			sockfd[currentclient] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			if (sockfd[currentclient] < 0)
				error("ERROR opening socket");
			///////////////////////////////////////////////////////////////////here
			//////////////////////////////////////////////////////////////////here
			bzero((char *)&serv_addr, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET;		
			/*
			server = gethostbyname(name);
			if (server == NULL )
				error("ERROR no such host\n");
			*/
			//bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
			serv_addr.sin_addr.s_addr = inet_addr(address);//    
	
			std::cout << "Connect to " << address << ":" << portno << " ";
			if (cr)
				std::cout << "Not Secure";
			else
				std::cout << "Secure";
			std::cout << '\n';
			serv_addr.sin_port = htons(udpport);
			//////////////////////////////////////////////////////////////////here
			bool flagg = false;
			while (!flagg)
			{
				if (sendto(sockfd[currentclient], buffer[currentclient], pl, 0, (struct sockaddr*)&serv_addr, servlen) == -1)
					/*error("ERROR sendto")*/;
				else
					flagg = true;
			}
			flagg = false;
			while (!flagg)
			{
				if (recvfrom(sockfd[currentclient], buffer[currentclient], pl, 0, (struct sockaddr*)&serv_addr, &servlen) == -1)
					/*error("ERROR recvfrom")*/;
				else
				{
					portno = atof(buffer[currentclient]);
					flagg = true;
				}
			}
			close(sockfd[currentclient]);
		}
		/*
		int no = 1;
		if (setsockopt(sockfd[currentclient], SOL_SOCKET, SO_REUSEADDR, (char*)&no, sizeof(no)) < 0)
			error("ERROR on sockopt");
		*/
		sockfd[currentclient] = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd[currentclient] < 0)
			error("ERROR opening socket");
		bzero((char *)&serv_addr, sizeof(serv_addr));
		bzero((char *)&cli_addr, sizeof(cli_addr));
		serv_addr.sin_family = AF_INET;
		//////////////////////////////////////////////////////////////////here
		if (id == 0)
			serv_addr.sin_addr.s_addr = INADDR_ANY;//htonl(INADDR_ANY);
		else
		{	/*
			server = gethostbyname(name);
			if (server == NULL )
				error("ERROR no such host\n");
			*/
			//bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
			serv_addr.sin_addr.s_addr = inet_addr(address);//    
		}
		/////////////////////////////////////////////////////////////here
		if (id == 1)
			std::cout << "Connect to " << address << ":" << portno << " ";
		else
			std::cout << "Listen " << address << ":" << portno << " ";
		if (cr)
			std::cout << "Not Secure";
		else
			std::cout << "Secure";
		std::cout << '\n';
		serv_addr.sin_port = htons(portno);
		if (id == 0)
		{
			while (!changeport)
				;
			if (bind(sockfd[currentclient], (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
				error("ERROR on binding");
		}
		else
		{
			int n = connect(sockfd[currentclient], (struct sockaddr*)&serv_addr, servlen/*sizeof(serv_addr)*/);
			while (n < 0)
			{
				/*std::cout<<*/portno++/*<<std::endl*/;
				serv_addr.sin_port = htons(portno);
				n = connect(sockfd[currentclient], (struct sockaddr*)&serv_addr, servlen/*sizeof(serv_addr)*/);
			}
			//std::cout << portno << std::endl;
			//error("ERROR connecting");
		}
		//////////////////////////////////////////////////////////////////here
		if (id == 0)
		{
			if (listen(sockfd[currentclient], 10/*5*/) < 0)
				error("ERROR listen");
			//clilen = sizeof(cli_addr);
			newsockfd[currentclient] = accept(sockfd[currentclient], (struct sockaddr *) &cli_addr, &clilen);
			std::cout << inet_ntoa(cli_addr.sin_addr) << " connected" << std::endl;
			server = gethostbyaddr((char*)&cli_addr.sin_addr, clilen, cli_addr.sin_family);
			std::cout << (*server).h_name << std::endl;
			if (newsockfd[currentclient] < 0)
				error("ERROR on accept");
			shutdown(sockfd[currentclient], 0);
			countclient++;
			//sprintf(buffer,"%i",nextport);
			/*
			fd_set rfd, wfd, exceptfd;
			FD_ZERO(&rfd);
			FD_SET(newsockfd[currentclient], &rfd);
			timeval time;
			time.tv_sec = 1;
			time.tv_usec = 0;
			int n = select(sockfd[currentclient], &rfd, &wfd, &exceptfd, &time);
			int cnt = 0;
			if ((n == 1) && (FD_ISSET(newsockfd[currentclient], &rfd)))
			{
				cnt=0;
			}
			*/
		}
		time(&datetime);
		strftime(datetimebuf, sizeof datetimebuf, "%A %b %d %H:%M:%S %Y\n", localtime(&datetime));
		std::cout << datetimebuf;
		////////
		if (!cr)
			InitSecure(currentclient);
		closeflag[currentclient] = false;
	}
    return 0;
}
#include <iostream>
int Con::InitOnce()
{
	WSADATA ws = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &ws) == 0)
	{
		if (id == 0)
		{
			//buf = (int*)realloc(sockfd,(countclient+1)*sizeof(int));
			//sockfd = buf;
			//nbuf = (int*)realloc(newsockfd,(countclient+1)*sizeof(int));
			//newsockfd = nbuf;
			//fbuf = (bool*)realloc((void*)closeflag,(countclient+1)*sizeof(bool));
			//closeflag = fbuf;
			//bbuf = (char**)realloc(buffer,(countclient+1)*sizeof(char)*pl);
			//buffer = bbuf;
			//bbuf[currentclient] = (char*)realloc(buffer[currentclient],sizeof(char)*pl);
			//buffer[currentclient] = bbuf[currentclient];
		}
		udpport = 15000;
		if (!changeport)
		{
			udpsocket[0] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			if (udpsocket[0] < 0)
				error("ERROR opening socket");
			bzero((char *)&serv_addr, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_port = htons(udpport);
			std::cout << "Listen " << address << ":" << portno << " ";
			if (cr)
				std::cout << "Not Secure";
			else
				std::cout << "Secure";
		}
		if (id == 0)
		{
			if (!changeport)
			{
				serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
				if (bind(udpsocket[0], (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
					error("ERROR on binding");
			}
			int recv_len;
			bool flagg = false;
			while (!flagg)
			{	
				if ((recv_len = recvfrom(udpsocket[0], udpbuffer, pl, 0, (struct sockaddr*)&cli_addr, &clilen)) == -1)
					/*error("ERROR recvfrom")*/;
				else
				{
					flagg = true;
					std::cout << inet_ntoa(cli_addr.sin_addr) << " need a free port." << std::endl;
					srand(time(NULL));
					portno = ((int)((float)rand() / RAND_MAX*(65536 - 1024) + 1024));
					std::cout << "Give a port:" << portno << std::endl;
					sprintf(udpbuffer, "%d", portno);
					changeport = true;
				}
			}
			flagg = false;
			while (!flagg)
			{
				if (sendto(udpsocket[0], udpbuffer, pl, 0, (struct sockaddr*)&cli_addr, clilen) == -1)
					/*error("ERROR sendto")*/;
				else
				{
					flagg = true;
				}
			}
		}
	}
	return 0;
}
void Con::error(const char *msg)
{
	
    perror(msg);
	std::cout<<'\n'<<"Exit with error>Press any key + Enter"<<std::endl;
    char c;
    std::cin>>c;
	WSACleanup();
	exit(1);
}
int Con::Close(int currentclient)
{
    ClearBuf(currentclient);
    if(this->id == 0)
        shutdown(newsockfd[currentclient],0);
    else
        shutdown(sockfd[currentclient],0);
    if(!cr)
    {
    //    int i = -1;
      //  while(++i<countclient)

            SSL_free(ssl[currentclient]);
        //SSL_CTX_free (ctx);
        //SSL_shutdown (ssl);  /* send SSL/TLS close_notify */
    }
	WSACleanup();
    return 0;
}
int Con::Snd(int currentclient)
{
    if(!cr)
    {
        if(strlen(buffer[currentclient])!=0)
            err = SSL_write (ssl[currentclient], buffer[currentclient],pl);
        //else
        //    buffer[currentclient][0] = '0';
            CHK_SSL(err);
        //std::cout<<'\n'<<err<<" Send this>"<<buffer[currentclient]<<std::endl;
			ClearBuf(currentclient);
    }
    else
    {
        if(this->id == 0)
            if(HANDSHAKE)
                n = write(newsockfd[currentclient],buffer[currentclient],pl);
            else
            {
                bzero((char*)&cli_addr,sizeof(struct sockaddr_in));
                cli_addr.sin_family = AF_INET;
                cli_addr.sin_addr.s_addr = inet_addr(address);
                cli_addr.sin_port = portno;
                clilen = sizeof(struct sockaddr_in);
                n = sendto(sockfd[currentclient],buffer[currentclient],pl,flag,(struct sockaddr*)&cli_addr,clilen);
            }
        else
            if(HANDSHAKE)
                n = write(sockfd[currentclient],buffer[currentclient],pl/*strlen(buffer[currentclient])*/);
            else
            {
                bzero((char*)&serv_addr,sizeof(struct sockaddr_in));

                serv_addr.sin_family = AF_INET;
                serv_addr.sin_addr.s_addr = inet_addr(address);
                serv_addr.sin_port = portno;
                servlen = sizeof(struct sockaddr_in);
                //n = recvfrom(sockfd,buffer,255,flag,(struct sockaddr*)&serv_addr,&servlen);

                n = sendto(newsockfd[currentclient],buffer[currentclient],pl,flag,(struct sockaddr*)&serv_addr,servlen);
             }
        if (n < 0)
            error("ERROR writing to socket");
        ClearBuf(currentclient);
    }
    return 0;
}
int Con::Recv(int currentclient)
{
    //ClearBuf(currentclient);
    if(!cr)
    {
        //if(strlen(buffer[currentclient])!=0)
			int eror = SSL_get_error(ssl[currentclient],0);
	       err = SSL_read (ssl[currentclient], buffer[currentclient], pl);
        //else
            CHK_SSL(err);
        //buffer[currentclient][err] = '\0';
        //printf ("Got %d chars:'%s'\n", err, buffer[currentclient]);
    }
    else
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
                if(HANDSHAKE)
                    n = read(newsockfd[currentclient],buffer[currentclient],pl);
                else
                {
                    bzero((char*)&cli_addr,sizeof(struct sockaddr_in));
                    cli_addr.sin_family = AF_INET;
                    cli_addr.sin_addr.s_addr = inet_addr(address);
                    cli_addr.sin_port = portno;
                    clilen = sizeof(struct sockaddr_in);
                    //setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,(char*)1,sizeof(int));
                    n = recvfrom(sockfd[currentclient],buffer[currentclient],pl,flag,(struct sockaddr*)&cli_addr,&clilen);
                }
                //printf("Here is the message: %s\n",buffer);
            }
        }
        else
            //if(!FD_ISSET(sockfd,&input))
        {
            if(HANDSHAKE)
            n = read(  sockfd[currentclient],buffer[currentclient],pl);
            else
            {
                bzero((char*)&serv_addr,sizeof(struct sockaddr_in));
                serv_addr.sin_family = AF_INET;
                serv_addr.sin_addr.s_addr = inet_addr(address);
                serv_addr.sin_port = portno;
                servlen = sizeof(struct sockaddr_in);
                //n = sendto(sockfd,buffer,255,flag,(struct sockaddr*)&serv_addr,servlen);
                //setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,(char*)1,sizeof (int));
                n = recvfrom(sockfd[currentclient],buffer[currentclient],pl,flag,(struct sockaddr*)&serv_addr,&servlen);
            }

        }
        if (n < 0)
            error("ERROR reading from socket");
    }
	if(strncmp(buffer[currentclient],"End",3)==0)
	{
		closeflag[currentclient] = true;
		return 0;
	}
	else
	{
		return 1;
	}
}
int Con::SetBuf(char * s,int currentclient)
{
    for(int i=0,j = 0;i<pl, j<pl; i++,j++)
        buffer[currentclient][i] = s[j];
    return 0;
}
void Con::ClearBuf(int currentclient)
{
    bzero(buffer[currentclient],pl);
}
char * Con::GetBuf(int currentclient)
{
    return this->buffer[currentclient];
}
Con::~Con()
{
    delete address;
    //free(buf);
    //free(sbuf);
    //free(nbuf);
    //free(fbuf);
    free((void*)closeflag);
    free(sockfd);
	free(newsockfd);
    free(ssl);
    int i=-1;
    while(++i<countsession)
    {
        //free(bbuf[i]);
        free(buffer[i]);
    }
    //free(bbuf);
    free(buffer);

	delete udpsocket;
	delete udpbuffer;

}
