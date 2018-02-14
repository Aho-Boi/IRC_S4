#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<err.h>
#include<netdb.h>
#include<unistd.h>
char* build_query(const char *url, size_t *len)
{
  char *str;
  if((asprintf(&str,"GET http://%s HTTP/1.0\n\r\n\r",url) == -1))
    errx(EXIT_FAILURE, "u fail");
  *len = sizeof(str);
  return str;
}

void get_page(const char *name, const char *url, const char *port)
{
  size_t len;
  char *query = build_query(url,&len);
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
  int addrinfo_error = getaddrinfo(name, port, &hints, &result);
 
  // Error management
  if ( addrinfo_error != 0 ) {
    errx(EXIT_FAILURE, "Fail getting address for %s on port %s: %s",
	 name, port, gai_strerror(addrinfo_error));
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
  if(write(cnx, query ,strlen(query)) == -1)
    err(3,"mdr ca marche ap");
  char buffer[256];
  int fd;
  while((fd = read(cnx,buffer,256)) != 0)
  {
    if(write(STDOUT_FILENO,buffer,fd) == -1)
      err(3,"mdr ca marche pas");
  }
  free(query);
}
int main(){
  get_page("perdu.com", "http://perdu.com", "80");
  return 0;

}
