#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <resolv.h>

/*Client*/

int main(int argc , char *argv[])
{   
    //getting hostname
    struct hostent* host;
    host = gethostbyname("127.0.0.1");
    printf("IP address = %s\n", inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));
  
    //get port number
    struct servent *srv;
    srv = getservbyname("http", "tcp");
    printf("%s: port=%d\n", srv->s_name, ntohs(srv->s_port));

    int sd;
    sd = socket(PF_INET, SOCK_STREAM, 0); /* create socket */
   

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));    /* create & zero struct */
    addr.sin_family = AF_INET;    /* select internet protocol */
    addr.sin_port = srv->s_port;         /* set the port # */
    addr.sin_addr.s_addr = *(long*)host->h_addr_list[0]; /* set the addr */
    connect(sd, &addr, sizeof(addr));         /* connect! */

    char s[200];
    FILE *fp;
    fp = fdopen(sd, "r+");         /* convert into stream */
    fprintf(fp, "GET / HTTP/1.0\n\n");      /* send request */
    fflush(fp);               /* ensure it got out */
    while ( fgets(s, sizeof(s), fp) != 0 )  /* while not EOF ...*/
      fputs(s, stdout);           /*... print the data */
    fclose(fp);
    /*int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2048];

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    //Bind
  if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client,(socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        write(client_sock , client_message , strlen(client_message));
    }

    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }*/

    return 0;
}
