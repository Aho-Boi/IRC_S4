#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>     
  
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    char buffer[256];
     
    struct sockaddr_in serv_addr;
    struct hostent *server;
     
     
    if (argc < 3)
    {
        fprintf(stderr,"Spécifiez les arguments SVP %s nom_hôte No_Port\n", argv[0]);
        exit(0);
     }
     
    portno = atoi(argv[2]); // converti une chaine de caractére a un entier
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
    if (sockfd < 0)
        {
            perror("Erreur dans l'ouverture de socket");
            exit(-1);
        }
     
    server = gethostbyname(argv[1]);
     
    if (server == NULL)
    {
        fprintf(stderr,"Erreur, Nom d'hôte incorrect\n");
        exit(0);
    }
     
    memset((char *) &serv_addr,0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);// rempli la structure host
     
    serv_addr.sin_port = htons(portno);//converti un entiercourt(short)hostshort depuisl'ordre des octets de l'hôte vers celui du réseau.
 
    unsigned int size_addr = sizeof(serv_addr);
     
    if (connect(sockfd,(struct sockaddr *)&serv_addr,size_addr)< 0)
        {
            perror("Erreur de connexion");
            exit(-1);
        }
//n = write(sockfd,"bonjour",7);
     
    /*if (n < 0)
        {
            perror("Erreur d'écriture dans le socket");
            exit(-1);
        }*/
                 
 
    memset(buffer,0,256);
    n = read(sockfd,buffer,255);
     
    if (n < 0)
        {
            perror("Erreur de lecture du  socket");
            exit(-1);
        }      
 
    //printf("%s\n",buffer);
       // sleep(1);
   do{
     printf("Entrez le message à envoyer : ");
    memset(buffer,0,256);
    fgets(buffer,255,stdin);
        int len =strlen(buffer);
    n = write(sockfd,buffer,len);
    if(n<0)
        {
	 puts("mdr2");
         exit(-1);         
        }
    if (send(sockfd,buffer,len,0) < 0)
        {
            perror("lmdr");
            exit(-1);
        }
    memset(buffer,0,256);
    n = read(sockfd,buffer,255);
     
    if (n < 0)
        {
            perror("Erreur de lecture du  socket");
            exit(-1);
        }
    if((recv(sockfd, buffer , 2000,0)) <  0)
        {
           puts("recv failed");
           break;
        }      
 
    printf("%s\n",buffer);
  }while(buffer!=NULL);
return 0;
}
