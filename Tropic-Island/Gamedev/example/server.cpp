#include <example\c.h>

struct arg_s
{
	bool debug;
    char * buffer;
    int * num;
    char * stroke;
    Con *Con_;
};
struct arg_sa
{
	struct arg_s *lalk;
	int current;
};
#define type struct arg_sa
void session_(LPVOID args)
{
	if(((type*)args)->lalk->debug)
        std::cout<<"create new session"<<std::endl;
    float min = 4;
    float max = 18;
	int count=0;
	/*
	DWORD
	 id_ =
	GetCurrentThreadId();
	std::cout<<"id = "<<id_<< " ";
	*/
	int current = ((type*)args)->current;
    while(((type*)args)->lalk->Con_->Recv(current))
    {
        if(((type*)args)->lalk->debug)
            std::cout<<"data receving "<<((type*)args)->current<<std::endl;
		int i=-1;
        int j=0;
        srand(time(NULL));
        while(++i!=30)
        {
            ((type*)args)->lalk->num[i] = ((int)((float)rand()/RAND_MAX*(max-min)+min));
            sprintf(((type*)args)->lalk->stroke,"%d|",((type*)args)->lalk->num[i]);
            if(((type*)args)->lalk->debug)
                std::cout<<((type*)args)->lalk->stroke;
            int k = 0;
            while(k<strlen(((type*)args)->lalk->stroke))
                ((type*)args)->lalk->buffer[j++] = ((type*)args)->lalk->stroke[k++];
        }
        ((type*)args)->lalk->Con_->SetBuf(((type*)args)->lalk->buffer,current);
        ((type*)args)->lalk->Con_->Snd(current);
        if(((type*)args)->lalk->debug)
            std::cout<<"\ndata sending "<<current<<std::endl;
        //((type*)args)->lalk->Con_->Recv(((type*)args)->current);
        count++;
	}
	if(((type*)args)->lalk->debug)
		std::cout<<"session end"<<std::endl;
	return;
}
int main(int argc,char *argv[])
{
    struct arg_sa *args = new struct arg_sa();
	args->lalk = new struct arg_s();
	args->lalk->debug = true;
	args->lalk->buffer = new char[90];
	args->lalk->num = new int[30]; 
	args->lalk->stroke = new char[3];
	args->lalk->Con_ = new Con(0);
	if(args->lalk->debug)
		std::cout<<"start serv"<<std::endl;
    int i=-1;
	int session = args->lalk->Con_->GetSession();
	HANDLE *thread = (HANDLE*)malloc(sizeof(HANDLE)*session);
	while(++i<session)
    {
		sleep(1);
		args->current = i;
		args->lalk->Con_->InitOnce();
		args->lalk->Con_->Init(i);
		//session_((LPVOID)args);
		thread[i] = CreateThread(0,0,(LPTHREAD_START_ROUTINE)(session_),args,0,0);
	}
    while(true)
    {
		if(args->lalk->Con_->AllClose())
			break;
	}
    i=-1;
    while(++i<session)
	{
		args->lalk->Con_->Close(i);
		TerminateThread(thread[i],0);
	}
	if(args->lalk->debug)
		std::cout<<"stop serv"<<std::endl;
	std::cout<<'\n'<<"Press any key+Enter to exit>"<<'\n';
	char c;
    std::cin>>c;
    delete args->lalk->Con_;
    //delete args->lalk->stroke;
    delete args->lalk->num;
    delete args->lalk->buffer;
	delete args->lalk;
	delete args;
	free(thread);
}
