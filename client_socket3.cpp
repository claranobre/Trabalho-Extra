// programa cliente4.cp --> ler um vetor de caracter


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main( )
{
   int sockfd;
   int len;
   struct sockaddr_in address;
   int result, urlID = 3;
   string file = "t003";
   char vetor_ch[4] = {'A','B','C','D'};
   char answer_ch[1000000];

   //printf( "File = %s\n",file.c_str());
   strcpy(vetor_ch, file.c_str());

   sockfd  = socket(AF_INET, SOCK_STREAM,0);  // criacao do socket

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = inet_addr("127.0.0.1");
   address.sin_port = 8081;
   len = sizeof(address);

   result = connect(sockfd, (struct sockaddr *) &address, len);

   if (result == -1)
   {
      perror ("Houve erro no cliente");
      exit(1);
   }
  
  send(sockfd,  &vetor_ch,sizeof(vetor_ch),0);
  send(sockfd,  &urlID,sizeof(urlID),0);
  recv(sockfd, answer_ch,sizeof(answer_ch),0);

  //printf( "Caracter vindo do servidor = %c %c %c %c\n",vetor_ch[0],vetor_ch[1],vetor_ch[2],vetor_ch[3]);
  printf( "Texto vindo do servidor = %s\n",answer_ch);
  close(sockfd);
  exit(0);
}

