#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

//$ ./cliente 127.0.0.1 22000 Fulano

char *nomeCliente;
void* recebe(void* param){
	int client_fd = (int)param;
	int teste;
	while (1){
		char msg[1000] ;
		bzero( msg, 1000);
		read(client_fd, msg, 1000);
	    printf("\n Recebi do servidor: %s\n",msg );
	}
}

void* envia(void* param){
	int client_fd = (int) param;
	while(1) {
		char send_msg[1000]; 
		bzero( send_msg, 1000);
		printf("Digite algo %s: ",nomeCliente);
		fgets(send_msg, 1000, stdin);
		send_msg[strcspn(send_msg, "\n")] = '\0';
		send(client_fd,send_msg,strlen(send_msg)+1,0);

	} 

}

int main(int argc, char *argv[]) {

	if(argc == 4){
		int client_fd; 
		char nomeBatePapo[1000]; 
		int port = atoi(argv[2]) ;
		char* IPservidor = argv[1];//"127.0.0.1" 
		pthread_t t1,t2; 
		struct sockaddr_in server_addr; 

		bzero(nomeBatePapo, 1000);

		nomeCliente = argv[3];

		client_fd = socket(AF_INET, SOCK_STREAM, 0); 

		bzero(&server_addr, sizeof(server_addr)); 

		server_addr.sin_family = AF_INET; 
		server_addr.sin_port = htons(port); 
		inet_aton(IPservidor, &server_addr.sin_addr); 
		printf("Conectando-se a porta %d do servidor %s\n", port, IPservidor);
		
		if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){ 
			printf("Falha de conexao\n"); 
			return -1; 
		}

		read(client_fd, nomeBatePapo, 1000);
		printf("Bem vindo ao bate-papo %s\n",nomeBatePapo); 

		send(client_fd,nomeCliente,strlen(nomeCliente)+1,0);
		pthread_create(&t1, NULL, (void*)recebe, (void*)client_fd);
		pthread_create(&t2, NULL,(void*) envia, (void*)client_fd);
		pthread_join(t1,NULL);
		pthread_join(t2,NULL);

	}else{
		printf("numeros de argumentos incorreto!\n");
	}
	return 0;
}