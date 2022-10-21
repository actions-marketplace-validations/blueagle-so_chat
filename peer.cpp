//DEBUG

#include "peer.h"
using namespace net;
void Peerrunclient(){
        self->crt_sock(self); 
        printf("client fd %i \n", self->sock);
        self->cnt_to_sock(self);
        dprintf(self->sock,s);
        for(;;)
        {
                memset(self->buffer, 0, sizeof(self->buffer));
                FD_ZERO(&self->read_fd);
                FD_SET(0, &self->read_fd);
                FD_SET(self->sock, &self->read_fd);
                self->sel_conn(self);
                if (FD_ISSET(0, &self->read_fd)){read(0,self->buffer,sizeof(self->buffer));dprintf(self->sock, self->buffer);}  
                if(FD_ISSET(self->sock, &self->read_fd)){read(self->sock, self->buffer, sizeof(self->buffer));dprintf(0,self->buffer);}
        }   
        self->cls_sock(self);




}



void Peerrunserver(){
	//socket creation
	self->crt_sock(self);
	//output socket file descriptor
	printf("server fd %i \n", self->sock);
	//initialisation
	self->bnd_sock(self);
	//waiting for connection
	self->lsn_sock(self);

	self->nicknames.insert({0,s});
	
        for(;;){
        FD_ZERO(&self->read_fd);      
        //comm->max_sd = comm->sock; 
      //  for (auto it1 = self->nicknames.begin(); it1!=self->nicknames.end();  ++it1)
    //std::cout << it1->first << "->" << it1->second << std::endl;  
	for (auto itr = self->nicknames.begin(); itr != self->nicknames.end(); ++itr)FD_SET(itr->first, &self->read_fd);
        FD_SET(self->sock, &self->read_fd);  
	//wait for connection/recive message
        self->sel_conn(self);
	
	if (FD_ISSET(self->sock, &self->read_fd)) 
                {	
			//acepting connection	
       			self->acpt_conn(self);
			self->acpt_conn(self);
			char g[80]={0};
			read(self->new_socket,g,1024);
			self->nicknames.insert({self->new_socket,g});
			printf("New connection %s\n",self->nicknames.find(self->new_socket)->second);
			dprintf(self->new_socket,"welcome %d\n",self->new_socket);  
                }
		//for (auto it2 = self->nicknames.begin(); it2!=self->nicknames.end();  ++it2)
    //std::cout << it2->first << "->" << it2->second << std::endl; 
		for (auto itr2 = self->nicknames.begin(); itr2 != self->nicknames.end(); ++itr2)
                { 
			self->sd = itr2->first; 
			if (FD_ISSET(self->sd , &self->read_fd)) 
                        { 
				if ((read( self->sd , self->buffer, 1024))==0)//man read 
				{ 
                                        printf("Host disconnected %s \n" ,itr2->second); 
                                        close(self->sd); 
					self->nicknames.erase(itr2); 
                                	break;				
				} 
                                else
				{ 
	  				self->buffer[self->valread] = '\0';
					for (auto itr1 = self->nicknames.begin(); itr1 != self->nicknames.end(); ++itr1)
					dprintf(itr1->first,"%s says: %s\n",itr2->second,self->buffer);
					
                                 }  
                        } 
                } 
        
	          //  for (auto it3 = self->nicknames.begin(); it3!=self->nicknames.end();  ++it3)
   // std::cout << it3->first << "->" << it3->second << std::endl; 

	}
        close(self->sd2);
	//closing socket
	self->cls_sock(self);


}
//funkcii visokogo urovnya

void create_socket(struct Peer *self){
        self->sock=socket(AF_INET, SOCK_STREAM, 0);
}
void close_socket(struct Peer *self){
        close(self->sock);
}
void connect_to_socket(struct Peer * self){
        connect(self->sock, (struct sockaddr*)&self->addres, sizeof(self->addres));
}
void bind_socket(struct Peer* self){
        bind(self->sock, (struct sockaddr*)&self->addres, sizeof(self->addres));
}
void listen_socket(struct Peer * self){
        listen(self->sock, 300);
}
void accept_connection(struct Peer * self){
        self->new_socket = accept(self->sock,NULL,NULL);
}
void select_connection(struct Peer *self){
        select(300, &self->read_fd, NULL, NULL, NULL);
}

void init(struct Peer *self){

        self->crt_sock=create_socket;
        self->cls_sock=close_socket;
        self->sel_conn=select_connection;
        self->addres.sin_family = AF_INET;
        self->addres.sin_port = htons(PORT);
        self->lsn_sock=listen_socket;
        self->bnd_sock=bind_socket;
        self->acpt_conn=accept_connection;
        self->cnt_to_sock=connect_to_socket;
        self->sel_conn=select_connection;
        self->addres.sin_addr.s_addr = htonl(INADDR_ANY); 
        //comm->Client::addres.sin_addr.s_addr = inet_addr(CLIIP);
}

void connector( args *argz) {
args* q=(args*)argz;

 int socke = socket(AF_INET, SOCK_STREAM, 0);
 
addr.sin_family = AF_INET;
 addr.sin_port = htons(PORT);
 char a[256] = "192.168.1.";
 char b[10];
 sprintf(b,"%d",q->x);
 strcat(a,b);
 addr.sin_addr.s_addr =  inet_addr(a);
 
 if(connect(socke, (struct sockaddr*)&addr, sizeof(addr))==0){sprintf(q->y,"%s",a);q->isServer=Client;}

}


args ar[256]={};



void spawnThreads()
{

    for (int i = 0; i < 255; i++) {
        ar[i].x=i;
        ar[i].tid = std::thread(connector,&ar[i]);
        qq.push(&ar[i]); 
   }


}

enum  PeerType isserver=Server;
args *pclient;



void wait()
{
while(!qq.empty()){
pclient=qq.front();
if((pclient!=NULL)&&(pclient->tid.joinable())){
pclient->tid.join();}
if(pclient)if(pclient->isServer==Client){isserver=Client;break;}
qq.pop();
}

}











void start(enum PeerType chat){
switch (chat){
        case Client:
	{peers->client=new Peer;
	init(peers->client);
	self=peers->client;
	Peerrunclient();}
        case Server:
	{
	peers->server=new Peer;
        init(peers->server);
        self=peers->server;
        Peerrunserver();}
 }
}




void check(){


//  init(self);

if(isserver==Client){
char a[256] = "192.168.1.";
 char b[10];
 sprintf(b,"%d",pclient->x);
  strcat(a,b);
 self->addres.sin_addr.s_addr = inet_addr(a);}

std::cout << "nick:";
std::cin >> s;

start(isserver);


}