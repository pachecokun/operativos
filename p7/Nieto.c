#include <sys/types.h>
#include <sys/ipc.h>	
#include <sys/shm.h>
#include "matriz.h"
#include "semaforo.h"

int main(){
	printf("--INICIÓ PROCESO NIETO--\n");
	init();     //inicializa operaciones
	int i, j, n;

	int shmid1,shmid2;
	key_t llave1,llave2;
	float *shm1;
	float *shm2;
	llave1 = 5677;
	llave2 = 5678;

	/*Creación de bloque de memoria compartida*/
	if((shmid1 = shmget(llave1, sizeof(float)*100, IPC_CREAT | 0666)) < 0)
	{
		perror("Error al obtener memoria compartida: shmget\n");
		exit(0);
	}
	if((shmid2 = shmget(llave2, sizeof(float)*100, IPC_CREAT | 0666)) < 0)
	{
		perror("Error al obtener memoria compartida: shmget\n");
		exit(0);
	}
	if((shm1 = shmat(shmid1, NULL, 0)) == (float *) -1){
		perror("Error al enlazar la memoria compartida: shmat\n");
		exit(0);
	}
	if((shm2 = shmat(shmid2, NULL, 0)) == (float *) -1){
		perror("Error al enlazar la memoria compartida: shmat\n");
		exit(0);
	}

	/*Obtención de las matrices del proceso padre*/
	Matriz m1 = crear(10, 10);
	Matriz m2 = crear(10, 10);
	for(i=0; i<10; i++){
		for(j=0; j<10; j++){
			n= (i*10) + j;
			m1->filas[i][j] = *(shm1+n);
			m2->filas[i][j] = *(shm2+n);
		}
	}
	
	
	Matriz m= suma(m1, m2);

	printf("\nMatriz 1 recibida del hijo:\n");
	printMatriz(m1);
	printf("\nMatriz 2 recibida del hijo:\n");
	printMatriz(m2);
	printf("\nM1 + M2:\n");
	printMatriz(m);
	printf("\n");

	printf("Enviando suma a padre...\n");
	/*Guardando la suma en el bloque de memoria compartido*/
	for(i=0; i<10; i++){
		for(j=0; j<10; j++){
			n= (i*10) + j;
			*(shm2+n) = m->filas[i][j];
		}
	}	
	liberar(0); //termina suma
	printf("--FINALIZÓ PROCESO NIETO--\n");
	exit(0);
}
