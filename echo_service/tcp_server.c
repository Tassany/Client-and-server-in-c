#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
char msg[100];
void* responde_cliente(void* param) {

	int client_fd = (int) param;

	//char msg[100];
	
	while(1) {
		bzero(msg, 100); // inicializa a mensagem com 0
                read(client_fd, msg, 100); // le mensagem do socket cliente associado
                printf("Recebi do cliente: %s\n",msg); // exibe o que recebeu do cliente
                 // envia de volta a mesma mensgem
	}

}


/* Um servidor de eco. Tudo que este servidor receber de um cliente, ele enviara de volta */

int main(void) {

	

	int server_port = 22000;

	int listen_fd, client_fd; // dois file descriptors, 1 para ouvir solicitacoes, outro para o cliente

	struct sockaddr_in server_addr; // struct com informacoes para o server socket
	struct sockaddr_in client_addr; // struct que armazenara informacoes do cliente conectado

	pthread_t threads[10]; // array que armazenara 10 threads (MAXIMO DE CLIENTES)
 
	int thread_count = 0; // contador de threads (de clientes)

	printf("Loading...\n");

	listen_fd = socket(AF_INET, SOCK_STREAM, 0); // listen_fd representa o socket que aguardara requisicoes

	bzero(&server_addr, sizeof(server_addr)); // Inicializa a estrutura do servidor sockaddr_in com 0
	bzero(&client_addr, sizeof(client_addr)); // Inicializa a estrutura do cliente sockaddr_in com 0

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY; // Constante sinaliza que o socket sera um servidor
	server_addr.sin_port = htons(server_port); // Porta a ser associada ao socket servidor criado

	bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)); // associa parametros definidos

	listen(listen_fd, 10); // sinaliza que aguardara conexoes na porta associada

	printf("Aguardando conexoes na porta %d\n",server_port);

	while (1) {
		client_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL); // funcao bloqueante, gera novo socket 
		pthread_create(&threads[thread_count++], NULL, (void*) responde_cliente, (void*) client_fd);
		write(client_fd, msg, strlen(msg)+1);
	}

	return 0;
}
