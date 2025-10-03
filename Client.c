//CLIENT
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
int on = 1;
int main(int argc,char *argv[]) {
    int sockc, newsockc;
    int p = 1000;
    char buffer[1024] = {0};
    char *message = "CLIENT CONNECTED";
    struct sockaddr_in address;
    if ((sockc = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket couldn't be made");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(p);
    int addrslen = sizeof(address);
    if(connect(sockc,(struct sockaddr*)&address,sizeof(address)) < 0){
        perror("COULDN'T CONNECT!");
        exit(1);
    }
    send(sockc,message,strlen(message),0);
    int vr = read(sockc,buffer,1024);
    printf("%s\n",buffer);
    int on = 1;
    char s[1024];
    char newbuffer[1024] = {0};
    while(on == 1){
        int v = read(sockc,newbuffer,1024);
        if(v != 0){
            if(newbuffer != "\n"){
                printf("Message from server: %s",newbuffer);
                char newbuffer[1024] = {0};
            }
        }
        v = 0;
    }
    return 0;
    pthread_exit(NULL);
}
