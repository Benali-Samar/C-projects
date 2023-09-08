#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <strings.h> //bzero()
#include <sys/socket.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func (int sockfd)
{
  char buff[MAX];
  int n;
  for(;;)
  {
    bzero(buff,sizeof(buff));
    printf("Enter the string: ");
    n =0;
    while((buff[n++] = getchar()) != '\n')
      ;
    write(sockfd, buff,sizeof(buff));
    bzero(buff,sizeof(buff));
    read(sockfd,buff,sizeof(buff));
    printf("From server: %s",buff);
    if((strncmp(buff,"exit",4)) == 0)
      {
        printf("Client Exit...\n");
        break;
      }
    
  }
}

int main()
{
  int sockfd,connfd;
  struct sockaddr_in servaddr,cli;

  //create socket and verif
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if (sockfd == -1)
  {
    printf("|+|Socket creation failed!...\n");
    exit(0);
  }
  else {
    printf("|+|Socket successfully created...\n");
  }
  bzero(&servaddr,sizeof(servaddr));

  //assign IP,PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(PORT);

  //connect client socket to server socket ;)
  if (connect(sockfd,(SA*)&servaddr,sizeof(servaddr)) != 0)
  {
    printf("|+|Connection with the server failed!...\n");
    exit(0);
  }
  else {
    printf("|+|Connected to the server...\n");
  }

  //func to chat
  func(sockfd);

  //close the socket
  close(sockfd);

  return 0;
}



