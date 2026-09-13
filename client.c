#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == - 1)
    {
        printf("failed to create socket \n");
        return -1;
    }
    else
    {
        printf("successfully created socket\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    int c = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(c == - 1)
    {
        printf("failed to connect  \n");
        return -1;
    }
    else
    {
        printf("successfully connected\n");
    }
    char msg[] = "{\"text\":\"hi\"}";

    int s = send(sockfd, msg, strlen(msg), 0);
    
    if(s == -1)
    {
        printf("sending failed\n");
    }
    else
    {
        printf("data sent successfully\n");
    }
    
    char buffer[1024];
    
    int rec = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    
    if(rec > 0)
    {
        buffer[rec] = '\0';
        printf("data received: %s\n", buffer);
    }
    else if(rec == 0)
    {
        printf("server closed connection\n");
    }
    else
    {
        printf("receiving failed\n");
    }
    
    close(sockfd);
}