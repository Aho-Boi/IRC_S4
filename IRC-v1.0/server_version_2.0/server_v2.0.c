#define _GNU_SOURCE
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <stdio.h>
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include "ascii.c"
    
#define TRUE   1 
#define FALSE  0 
#define PORT 6969 

char* namelist(char* tab[]);
 
int main()  
{  
    int opt = TRUE;  
    int master_socket , addrlen , new_socket , client_socket[30] , 
          max_clients = 30 , activity, i , valread , sd;  
    int max_sd;  
    struct sockaddr_in address;
    char* tab[30];
    namelist(tab);
    char buffer[1025];  //data buffer      
    //set of socket descriptors 
    fd_set readfds;  
        
    //a message 
    print();
    char *message = "RETARDED_IRC.exe v2.0 \r\n ┌∩┐(◣_◢)┌∩┐ \n";  
    
    //initialise all client_socket[] to 0 so not checked 
    for (i = 0; i < max_clients; i++)  
    {  
        client_socket[i] = 0;  
    }  
        
    //create a master socket 
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
    
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
    
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  
        
    //bind the socket to localhost port 8888 
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
    // 3 connection for test    
    if (listen(master_socket, 30) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
        
    //accept the incoming connection 
    addrlen = sizeof(address);  
    puts("Waiting for connections ...");  
        
    while(TRUE)  
    {  
        //clear the socket set 
        FD_ZERO(&readfds);  
    
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
            
        //add child sockets to set 
        for ( i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
    
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
      
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
            
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, 
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
            
            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket is %d , ip is : %s , port : %d \n", new_socket , inet_ntoa(address.sin_addr) , ntohs
                  (address.sin_port));  
          
            //send new connection greeting message 
            if( send(new_socket, message, strlen(message), 0) != (int)strlen(message) )  
            {  
                perror("send");  
            }  
  
            puts("Welcome message sent successfully");  
                
            //add new socket to array of sockets 
            for (i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket;  
                    printf("Adding to list of sockets as %d\n" , i);  
                        
                    break;  
                }  
            }  
        }  
            
        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)  
        {  
            sd = client_socket[i];  
                
            if (FD_ISSET( sd , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                if ((valread = read( sd , buffer, 1024)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                        
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    client_socket[i] = 0;  
                }  
                    
                //Echo back the message that came in 
                else
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    buffer[valread] = '\0';
                    int fd;
                    char *id = "";
                    for(int k = 0 ; k < max_clients ; k++){
                    fd = client_socket[k];
                    if(sd != fd){ 
                      int trash = asprintf(&id,"<%s>: %s",tab[sd],buffer); 
                      if(trash == -1)
                        perror("S_thé_banc tu craint");
                      send(fd , id , strlen(id) , 0 );
                      free(id);
                      
                      }
                    }
                    
                }  
            }
        }
    }
    return 0;  
}  


char* namelist(char* tab[])
{
   tab[4] = "David";
   tab[5] = "Finn";
   tab[6] = "Sham";
   tab[7] = "Philémon";
   tab[8] = "S_Thé_banc";
   tab[9] = "Ken Le Survivant";
   tab[10] = "BMO";
   tab[11] = "Jake The Dog";
   tab[12] = "Princess Bubblegum";
   tab[13] = "Marceline";
   tab[14] = "Reznov";
   tab[15] = "Just Monika";
   tab[16] = "420_Blaze_It";
   tab[17] = "XxX_Dark_SaSuKe_du_77_xXx";
   tab[18] = "Qu1cksc0p3r_Xtr3m";
   tab[19] = "Uganda Knucles";
   tab[20] = "Anime is fucking trash";
   return *tab;
}


