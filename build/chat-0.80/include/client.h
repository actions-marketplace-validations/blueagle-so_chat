#include <arpa/inet.h>  //inet_addr define
#include <sys/socket.h> //socket(), connect(), bind(), listen(), accept(), select(); 
#include <ext/stdio_filebuf.h>
#include <stdio.h>  //printf()
#include <unistd.h>  //close(), fread()
#include <iostream>
#include <typeinfo>
#include <cstring>
#include "abspeer.h"
#define MAXLINE 1024
#define PORT 8080 

#if 0
<клиент>
		  |
		  |
	connect() to server
		 \|/
	 send nick to server 
		 \|/
 _____________\	loop(infinite)
 |	      /	  |
 |		  |
 |		 \|/
 |	set sockets to listen(stdin and self (client))
 |		  |
 |		  |
 |		 \|/
 |	select() wait for messages(0 fd is stdin, and other fd is connection descriptor)
 |					|				|
 |					|				|
 |		      		       \|/			       \|/
 |				stdin - send messg to server	  recive mess from server
 |					|				|
 |______________________________________|_______________________________|



#endif







//вводим определение клиента и сервера
class Client:public Peer{
        public:
	Client(){};
	//Client(int _sock, struct sockaddr_in _addres):AbstractPeer(_sock, _addres){}
	//int sock;
        //struct sockaddr_in addres;
        //char buffer[MAXLINE]={0};
        //fd_set read_fd={0};
	//template<class T> T *conn(T *);
	//auto *init(auto *);
	//template<class T> T *sel(T *);
	//template<class T> T *init1(T *);
	//auto *selinit(auto *);
	//template<class T> T *sendmes(T *);

void createSocket() override{
	sock=socket(AF_INET, SOCK_STREAM, 0);
	std::cout << typeid(this).name() << " fd " << sock << std::endl;
}

void connectInit() override ///<клиентская часть
        {

	addres.sin_family = AF_INET;
        addres.sin_port = htons(PORT);
        addres.sin_addr.s_addr = inet_addr("127.0.0.1");

        connect(sock, (struct sockaddr*)&addres, sizeof(addres));
        //dprintf(peer->sock, s);
	//std::cout <<"test" <<std::endl;

        }


void selinit() override{

                memset(buffer, 0, sizeof(buffer));
                FD_ZERO(&read_fd);
                FD_SET(0, &read_fd);
                FD_SET(sock, &read_fd);

}






void sel() override{
//                select(300, &peer->read_fd, NULL, NULL, NULL);

	return this;
}



void conn() override{
read(sock, buffer, sizeof(buffer));dprintf(0, buffer);//}
return this;
}


void sendmes() override{

if(FD_ISSET(0, &read_fd)){read(0, buffer,sizeof(buffer));dprintf(sock, buffer);}  
//if(FD_ISSET(sock, &read_fd)){read(sock, buffer, sizeof(buffer));dprintf(0, buffer);}

return this;



}

};

