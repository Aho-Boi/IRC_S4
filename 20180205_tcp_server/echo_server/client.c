#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<err.h>
#include<netdb.h>
#include<unistd.h>

#define PORT "4242"

int main(void)
{
 
    
}

/*int main(void)
{
  struct sockaddr_in serverinfo;
  struct hostent *he;
  char buffer[1024];
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  // hints describes what we want
  // first fill the structure with 0s
  memset(&hints, 0, sizeof (struct addrinfo));
  // We only want IPv4, use AF_UNSPEC if you don't care which one
  hints.ai_family = AF_INET;
  // We want TCP
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;
 
  // name and port are strings (domaine name and port, obviously)
  // result will contain the result
  int addrinfo_error = getaddrinfo(argv[0], PORT, &hints, &result);
  
  // Error management
  if (argc != 3)
    errx(EXIT_FAILURE, "arg");
  if ((he = gethostbyname(argv[1])) == NULL)
    errx(EXIT_FAILURE, "host name");

  if ( addrinfo_error != 0 ) {
    errx(EXIT_FAILURE, "Fail getting address");
  }
  int cnx;
  for(rp = result; rp != NULL; rp = rp->ai_next){
    cnx = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if(cnx == -1) continue;
    if(connect(cnx, rp->ai_addr, rp->ai_addrlen) != -1){
       break;
    }
    close(cnx);
  }
  freeaddrinfo(result);
  if(rp == NULL){
    errx(EXIT_FAILURE,"Couldn't connect");
  }
  if(write(cnx, argv[2] ,strlen(buffer)) == -1)
    err(3,"mdr ca marche ap");
  int fd;
  while((fd = read(cnx,buffer,256)) != 0)
  {
    if((send(cnx, buffer, strlen(buffer),0)) == -1)
    {
      errx(EXIT_FAILURE,"lol send");
      close(cnx);
    }
    if(write(STDOUT_FILENO,buffer,fd) == -1)
      err(3,"mdr ca marche pas");
  }
}*/
