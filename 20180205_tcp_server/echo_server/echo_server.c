# define _GNU_SOURCE
# define _POSIX_C_SOURCE 201112L
# include <err.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <netdb.h>
# include <signal.h>
# include <errno.h>

void echo(int fdin , int fdout)
{
  //errno = 0;
  char boi[256];
  int fd = 0;
  while((fd = read(fdin ,boi,256)) != 0)
  {
   //if(errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
     //errx(EXIT_FAILURE,"mdr t'es null");
   if((write(fdout,boi,fd)) == -1)
     //if(errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
        err(3,"mdr t'es null"); 
     //err(3,"mdr t'es nul");
  }
}
int fdaccept_register(int fd) {
  static int fdaccept = -1;
  if (fdaccept == -1 && fd != -1) {
      fdaccept = fd;
   }
   return fdaccept;
  }

void sigint_handler(int sig) {
  (void)sig;
  int fd = fdaccept_register(-1);
  if (fd != -1)
    close(fd);
  _exit(0);
}
void server(const char *portname)
{
  int info_err = 0;
  struct addrinfo hints, *resinfo = NULL;
  struct addrinfo *rp;
 
  // setup hints and get local info
  memset(&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;                 // IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;             // TCP
  hints.ai_protocol = 0;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; // server mode
  // let's go !
  info_err = getaddrinfo(NULL, portname, &hints, &resinfo);
  // Error management
  if (info_err != 0) {
    errx(EXIT_FAILURE, "Server setup fails on port %s: %s", portname,
	 gai_strerror(info_err));
  }
  int cnx = 0;
  int reuse_err;
  int reuse = 1;
  for(rp = resinfo; rp != NULL; rp = rp->ai_next)
  {
   cnx = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
   if(cnx == -1) continue;
   reuse_err = setsockopt(cnx, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof (reuse));
   if(reuse_err != -1)
      break;
   if((connect(cnx, rp->ai_addr, rp->ai_addrlen)) != -1 ) 
     break;
   //close(cnx);

  }
  freeaddrinfo(resinfo);
  if(rp == NULL)
  {
    errx(EXIT_FAILURE,"mdr no connect");
  }
  
  
         
  // Error management
  if (reuse_err == -1)
      errx(EXIT_FAILURE, "Fail to set socket options");
  int fd_server = fdaccept_register(cnx);
  if(bind(fd_server, rp->ai_addr, rp->ai_addrlen) == -1)
    err(3,"bind");
  if(listen(fd_server,42) == -1)
    err(3,"listen !");
  int fdcnx;
  for(;;)
    {
      if((fdcnx = accept(fd_server,NULL,NULL)) == -1)
        err(3,"mdr lol whole infini");
      echo(fdcnx,fdcnx);
      close(fdcnx);
    }
}

int main(int argc, char* argv[]){
  (void)argc;
  struct sigaction sigint;
 
  // Handle terminaison through Ctrl-C
  memset(&sigint, 0, sizeof (struct sigaction));
  sigint.sa_handler = sigint_handler;
  sigfillset(&sigint.sa_mask);
  sigint.sa_flags = SA_NODEFER;
  if ( sigaction(SIGINT, &sigint, NULL) == -1)
    err(EXIT_FAILURE, "can't change SIGINT behavior");
  struct sigaction sigchld;
 
  // Avoid zombies and don't get notify about children
  memset(&sigchld, 0, sizeof (struct sigaction));
  sigchld.sa_handler = SIG_DFL;
  sigemptyset(&sigchld.sa_mask);
  sigchld.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT;
  if ( sigaction(SIGCHLD, &sigchld, NULL) == -1 )
    err(EXIT_FAILURE, "can't change SIGCHLD behavior");
  server(argv[1]);
  return 0;
}
