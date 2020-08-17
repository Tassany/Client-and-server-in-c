#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <errno.h>


// $ ./servidorbp 9990 BATEPAPO

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 int client_socket[10];

 void trava(char* mensagem) {
	pthread_mutex_lock(&mutex);
	
	FILE *arquivo;

	arquivo = fopen("conversas.txt","a");

	fprintf(arquivo, "%s\n",mensagem); 

	fclose(arquivo);
	
	pthread_mutex_unlock(&mutex);

}
void* modifica_cliente(void* param) {

	int client_fd = (int) param;

	int i;	
	char nome[1000]; 
	char msg[1000];
	char aux[1000] = " Cliente conectado: ";

	bzero(nome, 1000);
	
	read(client_fd, nome, sizeof(nome));
	
	strcat(aux,nome);
	trava(aux);
	printf("> > %s\n",aux);

	while(1) {
		bzero(msg, 1000);
		read(client_fd, msg, sizeof(msg));

		strcat(msg,nome);
		printf("%s\n",msg);
		trava(msg);

		for(i = 0; i < 10; i++){
			if(client_socket[i] != 0){
					
				send(client_socket[i],msg,strlen(msg)+1,0);
					
			}
		}		
	}
}


int main(int argc, char *argv[]) {

	if(argc == 3){
		int i,ip;
		for (i = 0; i < 30; i++){   
        	client_socket[i] = 0;   
    	}  
		char* cliente_ip;
		char msg[1000];
		char* nomeSala = argv[2];
		int porta = atoi( argv[1]);
		

		int listen_fd, client_fd; 

		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr; 

		socklen_t client_size = sizeof(client_addr);
		pthread_t threads[10];
	
		int thread_count = 0;

		printf("Carregando...\n");

		listen_fd = socket(AF_INET, SOCK_STREAM, 0);

		bzero(&server_addr, sizeof(server_addr));
		bzero(&client_addr, sizeof(client_addr));

		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = INADDR_ANY;
		server_addr.sin_port = htons(porta); 

	
	   	bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));

		listen(listen_fd, 10); 

		printf("Aguardando conexoes na porta %d\n",porta);
		
		while (1) {
			
			//client_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
			client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_size);
			ip =  inet_ntoa(client_addr.sin_addr);
			printf("O ip do cliente é: %d\n", ip);
			if (client_fd < 0) {
				perror("Erro ao receber conexao\n");
				return -1;
        	}

		 
			send(client_fd,nomeSala,strlen(nomeSala)+1,0);
			pthread_create(&threads[thread_count++], NULL, (void*) modifica_cliente, (void*) client_fd);
	 		
			for (i = 0; i < 10; i++){   
				
				if( client_socket[i] == 0 ){   
					client_socket[i] = client_fd;                            
					break;   
				}   
			} 
	
		}

		
	}else{
		printf("numeros de argumentos incorreto!\n");
	}
	return 0;
}
