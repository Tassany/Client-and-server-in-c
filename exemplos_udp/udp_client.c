#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(void) {

	int client_fd, port; //file descriptor do socket, porta 
	char buffer[100]; //buffer que armazena mensagem a ser enviada
	char* host = "127.0.0.1"; //string com endereco para quem a mensagem sera enviada via UDP
	struct sockaddr_in server_addr;

	port = 9000;
	
	client_fd = socket(AF_INET, SOCK_DGRAM, 0); //crio o socket 

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_aton(host, &server_addr.sin_addr); //passo para a estrutura o endereco para quem sera enviada a mensagem

	while(1) {
		printf("Digite algo: ");
		fgets(buffer, 100, stdin); //le string do usuario
		printf("Enviar para o servidor UDP: %s\n", buffer);
		sendto(client_fd, buffer, 100, 0, (struct sockaddr*) &server_addr, 
			(unsigned int) sizeof(server_addr));  //envia para o servidor via UDP 
							      // (passa a estrutura sockaddr na propria funcao)
	}
	
	return 0;
}
