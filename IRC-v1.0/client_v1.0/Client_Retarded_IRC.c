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
#include "../RSA_version_2.0/rsa.h"
#include <pthread.h>

#define TAILLE_TAMPON 2072
 

#define IP "127.0.0.1"
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



    

    pthread_t tid;
    size_t *keys = malloc(2 * sizeof(size_t));
    pthread_create(&tid, NULL, myThread, keys);
      
    while(pthread_join(tid, NULL)){
      pthread_create(&tid, NULL, myThread, keys);
    }
    

    
    if (socket_connecter(sock, IP, PORT) == -1){
      free(keys);
      return -1;
    }
 
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

	    
	    size_t len = 1;
	    for(; tampon[len]; len++){
	      continue;
	    }
	    lnb *public0 = lutolnb(keys[0]);	    
	    lnb *public1 = lutolnb(keys[1]);
	    lnb **encrypted = malloc(len * sizeof(lnb));
	    for(size_t i = 0; i < len - 1; i++){
	      *(encrypted + i) = lutolnb(ncrypt(tampon[i], keys[0], 65537));
	    }
	    for(size_t k = 0; k < 8; k++){
	      tampon[k] = public0->bytes[k];
	    }
	    for(size_t k = 0; k < 8; k++){
	      tampon[8 + k] = public1->bytes[k];
	    }
	    for(size_t i = 0; i < len - 1; i++){
	      for(size_t k = 0; k < 8; k++){
		tampon[16 + i * 8 + k] = encrypted[i]->bytes[k];
	      }
	    }
	    
	    for(size_t k = 0; k < 8; k++){
	      tampon[16 + len * 8 + k] = 0;
	    }

	    /*
	    /////////////////////////////
	    
	    lnb *tmp = lnbtolu(0);
	    char *res = malloc(256);
	    for(size_t k = 0; k < 8; k++){
	      tmp->bytes[k] = tampon[k];
	    }
	    size_t pub0 = lnbtolu(tmp);

	    for(size_t k = 0; k < 8; k++){
	      tmp->bytes[k] = tampon[8 + k];
	    }
	    size_t pub1 = lnbtolu(tmp);
	    
	    size_t prov;
	    for(size_t i = 0; i < 256; i++){
	      for(size_t k = 0; k < 8; k++){
		tmp->bytes[k] = tampon[16 + i * 8 + k];
	      }
	      prov = lnbtolu(tmp);
	      prov = decrypt(prov, pub0, pub1);
	      res[i] = prov;
	      if (!prov){
		break;
	      }
	    }

	    //////////////////////////////
	    */
	    
	    if ((taille = send(sock, tampon, 8 * len, 0)) == -1)	
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
    free(keys);
    return 0;
}
