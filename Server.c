//SERVER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
int on = 1;
int main(int argc,char *argv[]) {
    int sockc, newsockc;
    int p = 1000;
    char buffer[1024] = {0};
    char *hello = "SERVER SAYS: HELLO!";
    struct sockaddr_in address;
    if ((sockc = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket couldn't be made");
        exit(1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(p);
    int addrslen = sizeof(address);
    if (bind(sockc, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("Failed to bind port to socket");
        exit(1);
    }
    if (listen(sockc, 3) > 0) {
        perror("Can't listen");
        exit(1);
    }
    if ((newsockc = accept(sockc, (struct sockaddr *) &address, (socklen_t*)& addrslen)) < 0) {
        perror("Server can't accept");
        exit(1);
    }
    int vr = read(newsockc,buffer,1024);
    printf("%s\n",buffer);
    send(newsockc,hello,strlen(hello),0);
    printf("Enter your message\n");
    printf("Send to Client> ");
    char newbuffer[1024] = {0};
    char s[1024];
    fgets(s,1024,stdin);
    while(on == 1){
        send(newsockc,s,strlen(s),0);
        s[1024] = "";
        printf("Send to Client> ");
        fgets(s,1024,stdin);
    }
    return 0;
}
