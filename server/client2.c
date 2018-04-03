#define _GNU_SOURCE
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<stdlib.h>
//#include<sys/socket.h>
#include<sys/types.h>
//#include<string.h>
#include<err.h>
#include<netdb.h>
#include<unistd.h>
 
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    /*46.105.160.121*/
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
     
    //keep communicating with server
    while(1)
    {
        if((recv(sock , server_reply , 2000,0)) ==  0)
        {
           puts(server_reply);
           
        }
        
        printf("Enter message : ");
        scanf("%s" , message);
         
        //Send some data
       // if(!strcmp(message,""))
       // {
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
       // }
        //Receive a reply from the server
        
       /* else
        {
          if((read(sock,server_reply,2000)) == 0)
          {
            puts(server_reply);
            
          }
        }*/
         
        //puts("Server reply :");
        //puts(server_reply);
    }
     
    close(sock);
    return 0;
}
