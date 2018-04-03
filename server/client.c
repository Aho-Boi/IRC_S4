#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <resolv.h>
#include <netinet/in.h>

/*Client*/

/*┌∩┐(◣_◢)┌∩┐*/



int main(){
  int clientSocket, portNum, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  portNum = 8888;

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portNum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  while(1){
    printf("Type a sentence to send to server:\n");
    fgets(buffer,1024,stdin);
   // printf("You typed: %s",buffer);

    nBytes = strlen(buffer) + 1;

    if((recv(clientSocket, buffer, 1024, 0) < 0)&&(send(clientSocket,buffer,nBytes,0) < 0))
    {
      puts("lol fail");
      break;
    }

    //recv(clientSocket, buffer, 1024, 0);

   // puts(buffer);   
  }

  return 0;
}
