#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int processos =0;

// void arquivo(char* nomeArquivo){
// 	FILE *pont;
// 	pont=fopen(nomeArquivo,"w");
    
//     int i;
//      for (i = 0; i < numAleatorio; i++)
//     {
//     /* gerando valores aleatórios entre zero e 100 */
//     fprintf(pont,"%d ", rand() % 100);
//      }
// 	//fprintf(pont,"%d",palavra);

// 	fclose(pont);

// }

void* Aleatorio(void*valor){
    int* limite= (int*)valor;
  	//printf("Olá! Sou a thread #%ld!\n", *limite);

	FILE *pont;
    char nomeArquivo[50];
        printf("Diga o nome do arquivo com .txt no final\n");
        scanf("%s",nomeArquivo);
	    pont=fopen(nomeArquivo,"w");
    
    int i;
     for (i = 0; i < *limite; i++)
    {
    /* gerando valores aleatórios entre zero e 100 */
    fprintf(pont,"%d\n ", rand() % 100);
     }
	//fprintf(pont,"%d",palavra);

	fclose(pont);
    return NULL;
}
int main(){
    int numAleatorio =0;
    char* nomeArquivo[20];
    int i;
    printf("Diga o numero de threads\n");
    scanf("%d",&processos);
     printf("Diga o numero de numeros aleatorios\n");
    scanf("%d",&numAleatorio);
 

    pthread_t thread[processos];

   	for(i=0;i<processos;i++){

       //arquivo(nomeArquivo);
		pthread_create(&thread[i],NULL,Aleatorio,(void*)&numAleatorio);
        pthread_join(thread[i],NULL);
	}

    // for(i=0;i<processos;i++){
           
    //     pthread_join(thread[i],NULL);
	// }
 

    
    return  EXIT_SUCCESS;
}