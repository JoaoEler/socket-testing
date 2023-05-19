#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>

#define SERVER_PORT	8888		
#define BUF_SIZE	1024		
#define _WIN32_WINNT 0x501

int fatal(char *str1, char *str2) {
  fprintf(stderr, str1, str2);
  exit(-1);
}


int main(int argc, char *argv[]) {
  int var_return,
  	  socket_client;
  char buf[BUF_SIZE];	
  struct hostent	*host;		
  struct sockaddr_in channel;	

  if(argc < 3)
    fatal("Uso: %s <server-IP> <message>\n", argv[0]);

  host = gethostbyname(argv[1]);	
  if(!host)
    fatal("%s: gethostbyname() failed\n", argv[0]);

  socket_client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(socket_client < 0)
    fatal("%s: socket() failed\n", argv[0]);

  memset(&channel, 0, sizeof(channel));
  channel.sin_family = AF_INET;
  memcpy(&channel.sin_addr.s_addr, host->h_addr, host->h_length);
  channel.sin_port = htons(SERVER_PORT);

  var_return = connect(socket_client, (struct sockaddr *)&channel, sizeof(channel));
  if(var_return < 0)
    fatal("%s: connect() failed\n", argv[0]);

  write(socket_client, argv[2], (strlen(argv[2]) + 1));

  close(socket_client);
}
