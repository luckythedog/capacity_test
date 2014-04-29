#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <semaphore.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <netdb.h>
#include <fcntl.h>
#include <cstdio>
#include <stdlib.h>
#include <ctime>
#define SEND_BUFFER true
unsigned int PORT_SPECIFIED;
unsigned int clientNumber = 1;
unsigned int failedConnections = 0;
unsigned int failedSends = 0;
struct LMSPacket{
    int randomNumber;
};

void* spawn_client(void*){
    unsigned int localSocket = socket(AF_INET, SOCK_STREAM, 0);
    clientNumber++;
    struct sockaddr_in serv_addr;
    serv_addr.sin_port = htons(PORT_SPECIFIED);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(localSocket, (struct sockaddr*)&serv_addr, sizeof serv_addr) <0){
        perror("connect");
        std::cout << "Something fucking wrong " << clientNumber++ << std::endl;
        failedConnections++;
    }else{
    }
    LMSPacket newPacket;
    newPacket.randomNumber = rand()%10000;
    if(SEND_BUFFER){
    if((send(localSocket, (char*)&newPacket, sizeof newPacket, 0)) < 0){
        failedSends++;
    }else{
    }
    }
    return NULL;
}

int main()
{
    std::cout << "Please enter the port of the server: ";
    std::cin >> PORT_SPECIFIED;
    unsigned int numberOfClients;
    std::cout << "Please enter the number of clients you would like to spawn." << std::endl;
    while(std::cin >> numberOfClients){
        for(unsigned int i=0; i<numberOfClients; i++){
        pthread_t thread_to_spawn;
        pthread_create(&thread_to_spawn, NULL, spawn_client, NULL);
        pthread_tryjoin_np(thread_to_spawn, NULL);
        poll(0,0,50);
        if(i==numberOfClients-1){
            std::cout << "Done!" << std::endl;
        }
        }
    }
    return 0;
}
