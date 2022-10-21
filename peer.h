//DEBUG
#include <arpa/inet.h>  //inet_addr define
#include <stdio.h>  //printf()
#include <sys/socket.h> //socket(), connect(), bind(), listen(), accept(), select(); 
#include <unistd.h>  //close(), fread()
#include <string>  //string type
#include <map>
#include <cstring>
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#define MAXLINE 1024
#define PORT 3111 

namespace net {

typedef std::map<int,char*> nmap;
//enimeration for ip scaner
enum PeerType{
        Server,
        Client
};
char s[80];
struct arg{
        std::thread tid;
        int x;
        char y[256];
        enum PeerType isServer;
};


typedef struct arg args;
std::queue<args*> qq;
struct sockaddr_in addr;

using Func = void (*)(struct Peer *self);

struct Server{
        int sock;
        struct sockaddr_in addres;
        char* message;
        char buffer[MAXLINE];
        fd_set read_fd;
        Func crt_sock, cls_sock, sel_conn;
        Func bnd_sock, lsn_sock, acpt_conn, cnt_to_sock;
        int  sd, sd2, new_socket, client_socket[30], max_clients=30, activity, i, max_sd;
        int valread;
        nmap nicknames;
        int run(void);
        

};

struct Client : Server{
        int run(void);


};


struct Self : Client{};

struct Peer{
        int sock;
        struct sockaddr_in addres;
        char* message;
        char buffer[MAXLINE];
        fd_set read_fd;
        Func crt_sock, cls_sock, sel_conn;
        Func bnd_sock, lsn_sock, acpt_conn, cnt_to_sock;
        int  sd, sd2, new_socket, client_socket[30], max_clients=30, activity, i, max_sd;
        int valread;
        nmap nicknames;
        int run(void);
};

struct Peers{

        
        struct Peer *server;
        struct Peer *client;



};
struct Peers _peers;
struct Peers *peers=&_peers;



struct Peer _self;
struct Peer *self=&_self;


}