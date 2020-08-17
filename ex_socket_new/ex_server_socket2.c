#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char** argv) {
	int sd;
	int port=8080;
	struct sockaddr_in addr;

	if ( argc != 2 )
		printf("usage: %s <portnum>\n...Using default port (%d).\n", argv[0], port);
	else { 
		printf("using port: %s\n",argv[1]);
		port = atoi(argv[1]);
	}
	sd = socket(PF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		printf("error bind");
	if ( listen(sd, 20) != 0 )
		printf("error listen");
	while (1)
	{
		printf("Entrei no while(1)\n");	
		char buffer[1024];
		char* buffer2; //= "MENSAGEM A SER EXIBIDA NO BROWSER\n";
		int client = accept(sd, 0, 0);
		printf("connected\n");
		send(client,"CONECTOU",8,0);
		recv(client,buffer,sizeof(buffer),0);
		printf("primeiro recv buffer: %s",buffer);	
		send(client, buffer, recv(client, buffer, sizeof(buffer), 0), 0);
		printf("segundo recv buffer: %s",buffer);
		close(client);
	}
	return 0;
}

