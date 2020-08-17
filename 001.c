#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 

int numAleatorio = 0;
int processos =0;

void arquivo(){
	FILE *pont;
      srand(time(NULL));

	//pont=fopen(nomeArquivo,"w");
    
    int i;
     for (i = 0; i < numAleatorio; i++)
    {
 
    printf("%d ", rand() % 100);
     }


	//fclose(pont);

}
int main(void)
{
  int i,pid;
    printf("Diga o numero de processos\n");
    scanf("%d",&processos);
     printf("Diga o numero de numeros aleatorios\n");
    scanf("%d",&numAleatorio);
 

    for(i=0;i<processos;i++){
    pid=getpid;
        if(pid!=0){
            fork();
            printf("numero de forks %d",i);
            arquivo();
        }
     
		
	}

  return 0;
}
