#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/times.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define TAILLE_TAMPON 256
 
#define IP "198.100.148.10"
#define PORT 6969

int socket_creer(void)
{
    int sock;
 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	return -1;
 
    return sock;
}
 
int socket_connecter(int sock, char* ip, int port)
{
    struct sockaddr_in serveur;
    socklen_t taille = sizeof(struct sockaddr);
 
    serveur.sin_family = AF_INET;
    serveur.sin_addr.s_addr = inet_addr(ip);
    serveur.sin_port = htons(port);
 
    if (connect(sock, (struct sockaddr*) &serveur, taille) == -1)
	return -1;
 
    return 1;
}
 
void fdset_initialiser(fd_set* rfds, int sock)
{
    FD_ZERO(rfds);
    FD_SET(STDIN_FILENO, rfds);
    FD_SET(sock, rfds);
}
 
int main(void)
{
    int sock;
    int taille;
    int continuer = 1;
    char tampon[TAILLE_TAMPON];
    fd_set rfds;
   
    if ((sock = socket_creer()) == -1)
	return -1;
 
    if (socket_connecter(sock, IP, PORT) == -1)
	return -1;
 
 
    while (continuer)
    {
	fdset_initialiser(&rfds, sock);
	select(sock + 1, &rfds, NULL, NULL, NULL);
	if (FD_ISSET(STDIN_FILENO, &rfds))
	{
	  // fgets(tampon, TAILLE_TAMPON - 1, stdin);
	    if(fgets(tampon, TAILLE_TAMPON - 1, stdin) == NULL)
      {
        errx(3,"exit_fget");
      }
	    if ((taille = send(sock, tampon, strlen(tampon), 0)) == -1)	
		return -1;
	    if (strcmp("/quitter", tampon) == 0)
		continuer = 0;
	}
	else if (FD_ISSET(sock, &rfds))
	{
	    if ((taille = recv(sock, 
			       tampon, 
			       TAILLE_TAMPON - 1, 
			       0)) == -1)
		return -1;
	    else
	    {
		tampon[taille] = '\0';
		printf("%s\n", tampon);
	    }
	}
    }
 
    close(sock);
 
    return 0;
}
