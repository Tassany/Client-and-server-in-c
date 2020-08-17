#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
// forma de entrada:  ./emissor arquivo.txt X.X.X.X 9990
int main(int argc, char *argv[]) {
    if(argc == 4){

        FILE *arquivo = fopen(argv[1],"r");
        if(arquivo == NULL){
            printf("ei ta certo esse arquivo ai?\n");
        }else{


            int emissor_fd, port; 
            char buffer[100]; // buffer que armazenara mensagem recebida
            struct sockaddr_in receptor_addr; 
            char* IP = argv[2];//"127.0.0.1"
            port = atoi(argv[3]);
            //port = 9000;
            
            emissor_fd = socket(AF_INET, SOCK_DGRAM, 0); 

            receptor_addr.sin_family = AF_INET;  
            receptor_addr.sin_port = htons(port); 
            inet_aton(IP, &receptor_addr.sin_addr);  



            fgets(buffer, 100, arquivo); //le string do usuario
            printf("Copiar para o arquivo receptor: %s\n", buffer);
             //sendto(emissor_fd, buffer, 100, 0, (struct sockaddr*) &receptor_addr,(unsigned int) sizeof(receptor_addr));
            write(emissor_fd, buffer, strlen(buffer)+1);
        
            return 0;
        }
        fclose(arquivo);
    }else{
        printf("eita faltou parametro em boy\n");
    }//else
}
