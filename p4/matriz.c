#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h> 

int n;
FILE *f;
char*args[3];
char aux [10];
int i,j;
 
void generaMatrices(){
	args[1] = (char*)malloc(200);
	args[2] = (char*)malloc(200);
	sprintf(args[1],"");
	sprintf(args[2],"");
	srand(time(NULL));
	
	printf("-----m1-----\n");
	
	for(i = 0; i<10; i++){
		for(j=0; j<10; j++){
			n = rand() % 10;
			sprintf(aux,"%d ",n);
			strcat(args[1],aux);
			printf("%5.2hd ",n);
		}
		printf("\n");
	}
	
	printf("-----m2-----\n");
	
	for(i = 0; i<10; i++){
		for(j=0; j<10; j++){
			n= rand() % 10;
			sprintf(aux,"%d ",n);
			strcat(args[2],aux);
			printf("%5.2hd ",n);
		}
		printf("\n");
	}
}


int main(){
	struct timeval t0, tf;
	gettimeofday(&t0,NULL);
	
	generaMatrices();
	
	
	args[0] = (char*)malloc(20);
	if(!fork()){
		sprintf(args[0],"matriz_suma");
		execv("matriz_suma",args);
	}
	else if(!fork()){
		sprintf(args[0],"matriz_resta");
		execv("matriz_resta",args);
	}
	else if(!fork()){
		sprintf(args[0],"matriz_mult");
		execv("matriz_mult",args);
	}
	else if(!fork()){
		sprintf(args[0],"matriz_trans");
		execv("matriz_trans",args);
	}
	else if(!fork()){
		sprintf(args[0],"matriz_inv");
		execv("matriz_inv",args);
	}
	else{
		for(i = 0; i<5;i++){
			wait(NULL);
		}
		if(!fork()){
			sprintf(args[0],"matriz_print");
			execv("matriz_print",NULL);
		}
		else{
			wait(NULL);
			gettimeofday(&tf,NULL);
			int tiempo = (int)((tf.tv_sec*1000)+(tf.tv_usec/1000))-((t0.tv_sec*1000)+(t0.tv_usec/1000));
			printf("Tiempo de ejecución: %d ms\n\n",tiempo);
		}
	}
	exit(0);
}
