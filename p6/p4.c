#include "matriz.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define size 10

int main(){
	int pipe1[2]; //padre-hijo
	int pipe2[2]; //hijo-nieto
	int pipe3[2]; //hijo-padre
	int pipe4[2]; //nieto-padre
	if(pipe(pipe1)||pipe(pipe2)||pipe(pipe3)||pipe(pipe4)){
		printf("Padre: Error al crear pipelines\n");
		exit(0);
	}
		
	if(fork()){ //padre
		Matriz m1 = crear(size,size);
		Matriz m2 = crear(size,size);
	
		int i,j;
		srand(time(NULL));
		for(i = 0;i<m1->h;i++){
			for(j = 0;j<m1->w;j++){
				m1 -> filas[i][j] = 5-rand()%11;
			}
		}
		for(i = 0;i<m2->h;i++){
			for(j = 0;j<m2->w;j++){
				m2 -> filas[i][j] = 5-rand()%11;
			}
		}		
		
		printf("m1:\n\n");
		printMatriz(m1);
		printf("m2:\n\n");
		printMatriz(m2);
		
		sendMatriz(m1,pipe1[1]);
		usleep(1000); //para evitar problemas con pipelines
		sendMatriz(m2,pipe1[1]);
		
		close(pipe1[1]);
		
		
		printf("Padre: Matrices enviadas a hijo\n");
		
		wait(NULL);
		printf("Padre: Leyendo repuestas...\n");
		
		
		Matriz res1 = readMatriz(pipe3[0]);
		Matriz res2 = readMatriz(pipe4[0]);
						
		printf("multiplicación:\n\n");
		printMatriz(res1);
		printf("suma:\n\n");
		printMatriz(res2);
			
		printf("Padre: Calculando inversas...\n");
					
		Matriz inv1 = inv(res1);
		Matriz inv2 = inv(res2);
		
		printf("Padre: Guardando matrices...\n");
		FILE*f1 = fopen("mult_inv.txt","w");
		saveMatriz(inv1,f1);
		fclose(f1);
		FILE*f2 = fopen("suma_inv.txt","w");
		saveMatriz(inv2,f2);
		fclose(f2);
		
		printf("Padre: Finalizado.\n\n");
	}
	else{
		if(fork()){ //hijo
			Matriz m1 = readMatriz(pipe1[0]);
			Matriz m2 = readMatriz(pipe1[0]);
			close(pipe1[0]);
			
			sendMatriz(m1,pipe2[1]);
			usleep(1000); //para evitar problemas con pipelines
			sendMatriz(m2,pipe2[1]);
			close(pipe2[1]);
			
			Matriz r = mult(m1,m2);
			
			wait(NULL);
			sendMatriz(r,pipe3[1]);
			close(pipe3[1]);
			
		}
		else{ //nieto
			Matriz m1 = readMatriz(pipe2[0]);
			Matriz m2 = readMatriz(pipe2[0]);
			close(pipe2[0]);
			
			Matriz r = suma(m1,m2);
			
			sendMatriz(r,pipe4[1]);
			close(pipe4[1]);
		}
	}
	exit(0);
	return 0;
}
