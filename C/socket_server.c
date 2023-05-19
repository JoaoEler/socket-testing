#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>

#define SERVER_PORT	8888	
#define BUF_SIZE	1024	
#define QUEUE_SIZE	10	

#define SERVER_MSG	"Server online"

int fatal(char *str1, char *str2) {
    fprintf(stderr, str1, str2);
    exit(-1);
}

int main(int argc, char *argv[])
{
  int server_socket,
  	  var_return,
  	  socket_connection,
  	  on,
      flag;

  char buf[BUF_SIZE];	
  struct sockaddr_in	channel;	
  struct sockaddr_in channel_client;
  socklen_t slen = sizeof(channel_client);

  memset(&channel, 0, sizeof(channel));	
  channel.sin_family = AF_INET;
  channel.sin_addr.s_addr = htonl(INADDR_ANY);
  channel.sin_port = htons(SERVER_PORT);

  server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(server_socket < 0)
    fatal("%s: socket() failed\n", argv[0]);

  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

  var_return = bind(server_socket, (struct sockaddr *)&channel, sizeof(channel));
  if(var_return < 0)
    fatal("%s: bind() failed\n", argv[0]);

  var_return = listen(server_socket, QUEUE_SIZE);
  if(var_return < 0)
    fatal("%s: listen() failed\n", argv[0]);

  flag = 1;
  while(flag){
    printf("%s\n", SERVER_MSG);
    socket_connection = accept(server_socket, (struct sockaddr *)&channel_client, &slen);
    if(socket_connection < 0)
      fatal("%s: accept() failed\n", argv[0]);

    printf("Connection established: %s, %d\n", inet_ntoa(channel_client.sin_addr),ntohs(channel_client.sin_port));

    read(socket_connection, buf, BUF_SIZE);

    printf("%s received: %s\n", argv[0], buf);

    close(socket_connection);
    if(strcmp(buf, "over") == 0) {
      close(server_socket);
      flag = 0;
    }
  }
}
