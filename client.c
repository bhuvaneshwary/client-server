#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

struct Student
{
    int roll_no;
    char name[20];
    float marks;
};

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;

    printf("Creating socket...\n");

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

    printf("Connecting to server...\n");

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

    // SEND STUDENT STRUCTURE

    struct Student student;

    student.roll_no = 101;
    strcpy(student.name, "Bhuvan");
    student.marks = 85.5;

    printf("Sending student data...\n");

    int s = send(sockfd, &student, sizeof(student), 0);
    
    if(s == -1)
    {
        printf("sending failed\n");
    }
    else
    {
        printf("student data sent successfully\n");
    }

    close(sockfd);

    printf("Client closed.\n");
}