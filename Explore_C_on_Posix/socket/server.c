#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <unistd.h> //for the read() , write() .. functions

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int confd)
{
  char buff[MAX];
  int n;
  for (;;) //infinite loop for chat
  {
    //erases the data in buff bytes of the memory starting at the location pointed to by MAX
    bzero(buff, MAX);
    read(confd,buff,sizeof(buff));
    printf("From client: %s\t To client: ", buff);
    bzero(buff,MAX);
    n =0;
    //copy server msg in the buffer
    while ((buff[n++] = getchar()) != '\n');
    ;

    //send the buffer to client
    write(confd,buff,sizeof(buff));

    if (strncmp("exit",buff,4) == 0)
    {
    printf("|+|Server exit...\n");
    break;
    }
  }
}

int main()
{
int sockfd, confd, len;
struct sockaddr_in servaddr, cli;

//create socket
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd == -1)
{
  printf("|+|Socket creation failed...\n");
  exit(0);
  }
else
  printf("|+| Socket successfully created...\n");
   
bzero(&servaddr, sizeof(servaddr));

  //assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);
  
  //binding created socket to given IP and verification
  if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
  {
    printf("|+|Socket bind failed!...\n");
    exit(0);
  }
  else
    printf("|+|Socket successfully binded...\n");

  //listen and verification
  if((listen(sockfd,5)) != 0)
  {
    printf("|+|Listen failed!...\n");
    exit(0);
  }
  else
    printf("|+|Server listening...\n");
  len = sizeof(cli);

  //accept the data packet from client and verifications
  confd = accept(sockfd,(SA*)&cli, &len);
  if(confd <0)
  {
    printf("|+|Server accept data failed!...\n");
    exit(0);
  }
  else
    printf("|+|Server accept the client data...\n");

  //chat between client  and server
  func(confd);

  //after chatting close socket
  close(sockfd);
  
  return 0;
}
