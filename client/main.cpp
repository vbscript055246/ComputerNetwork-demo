#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
int main() {
    int fd;
    struct sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(8080);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");

    if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket error");
    }

    if(connect(fd, (struct sockaddr*) &srv, sizeof(srv)) < 0){
        perror("connect fail");
    }

    int nbytes;
    char buf[] = "Helloworld";
    char buff[1024];
    clock_t t1, t2;
    t1 = clock();
    if((nbytes = send(fd, buf, sizeof(buf), 0)) < 0){
        perror("send fail");
    }

    if((nbytes = recv(fd, buff, sizeof(buff), 0)) < 0){
        perror("recv error");
    }
    else{
        t2 = clock();
        std::cout << (t2-t1)/(double)(CLOCKS_PER_SEC) << std::endl;
    }

}
