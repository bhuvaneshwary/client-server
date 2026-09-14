#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct Student
{
    int roll_no;
    char name[20];
    float marks;
};

int main()
{
    int sockfd;
    int clientfd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t size;
    size = sizeof(client_addr);

    // char buffer[1024];   // Not needed for integer

    printf("Creating socket...\n");

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    if(sockfd == -1)
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
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Binding socket...\n");

    int b = bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));

    if(b == -1)
    {
        printf("error\n");
        return -1;
    }
    else
    {
        printf("socket bound successfully\n");
    }

    printf("Listening for connections...\n");

    int l = listen(sockfd,10);

    if(l == -1)
    {
        printf("error\n");
        return -1;
    }
    else
    {
        printf("server is listening\n");
    }

    printf("Waiting for client...\n");

    clientfd = accept(sockfd,(struct sockaddr *)&client_addr,&size);

    if(clientfd == -1)
    {
        printf("connection failed\n");
    }
    else
    {
        printf("connection succeeded\n");
    }

    // OLD STRING RECEIVE
    /*
    int rec = recv(clientfd, buffer, sizeof(buffer), 0);

    if(rec > 0)
    {
        buffer[rec] = '\0';
        printf("data received: %s\n", buffer);
    }
    else if(rec == 0)
    {
        printf("client closed connection\n");
    }
    else
    {
        printf("receiving failed\n");
    }
    */


    // NEW: RECEIVE STUDENT STRUCTURE

    printf("Waiting for student data...\n");

    struct Student student;

    int rec = recv(clientfd, &student, sizeof(student), 0);

    if(rec > 0)
    {
        printf("Student data received successfully\n");
        printf("Roll No: %d\n", student.roll_no);
        printf("Name: %s\n", student.name);
        printf("Marks: %.2f\n", student.marks);
    }
    else if(rec == 0)
    {
        printf("client closed connection\n");
    }
    else
    {
        printf("receiving failed\n");
    }


    // OLD STRING SEND
    /*
    char msg[] = "hello client";

    int s = send(clientfd, msg, strlen(msg), 0);

    if(s == -1)
    {
        printf("sending failed\n");
    }
    else
    {
        printf("data sent successfully\n");
    }
    */


    printf("Closing server...\n");

    close(clientfd);
    close(sockfd);
}