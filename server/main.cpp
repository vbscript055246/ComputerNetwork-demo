#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main() {
    struct sockaddr_in srv;
    struct sockaddr_in cli;
    int fd, newfd, cli_len = sizeof(cli);
    srv.sin_family = AF_INET;
    srv.sin_port = htons(8080);
    srv.sin_addr.s_addr = htonl(INADDR_ANY);

//    srv.sin_addr.s_addr = inet_addr("140.122.123.123");
//    if(srv.sin_addr.s_addr == (in_addr_t) - 1){
//        std::cout << "轉換失敗!!" << std::endl;
//    }


    if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket error");
    }
    else{
        std::cout << "socket" << std::endl;
    }

    if(bind(fd, (struct sockaddr*) &srv, sizeof(srv)) < 0){
        perror("bind error");
        exit(1);
    }
    else{
        std::cout << "bind" << std::endl;
    }

    if(listen(fd, 8080) < 0){
        perror("listen error");
    }
    else{
        std::cout << "listen" << std::endl;
    }

    while(1){
        newfd = accept(fd, (struct sockaddr*) &cli, &cli_len);
        if(newfd < 0){
            continue;
            //perror("accept error");
        }
        int nbytes;
        char buf[1024];
        if((nbytes = recv(newfd, buf, sizeof(buf), 0)) < 0){
            perror("recv error");
        }
        else{
            while (nbytes >0){
                std::cout << buf[nbytes-1];
                nbytes--;
            }
            std::cout << std::endl;
        }
        if((nbytes = send(newfd, buf, sizeof(buf), 0)) < 0){
            perror("send fail");
        }

    }

    return 0;
}