#include <sys/types.h>
#include <sys/ipc.h>	
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "matriz.h"
#include "semaforo.h"

int main(){
	printf("--INICIÓ PROCESO HIJO--\n");
	init();     //inicializa operaciones
	
	
	int i, j, n;

	int shmid1,shmid2;
	key_t llave1,llave2;
	float *shm1;
	float *shm2;
	llave1 = 5677;
	llave2 = 5678;

	pid_t pid;
	char *argv[2];
	argv[0] = "Nieto";
	argv[1] = NULL;

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
	
	/*Valores de las matrices para el proceso nieto*/
	srand(time(NULL));
	for(i=0; i<100; i++){
		*(shm1+i) = rand() % 11;
	}
	for(i=0; i<100; i++){
		*(shm2+i) = rand() % 11;
	}
	
	/*Creación del proceso hijo del hijo*/
	if((pid= fork())==-1)
		printf("Error al crear el proceso hijo del proceso hijo\n");
	if(pid == 0){
		execv(argv[0], argv);
	}
	else{
		Matriz m = mult(m1, m2);
	
		printf("\nMatriz 1 recibida del padre:\n");
		printMatriz(m1);
		printf("\nMatriz 2 recibida del padre:\n");
		printMatriz(m2);
		printf("\nM1*M2:\n");
		printMatriz(m);
	
		esperar(0); //esperamos que termine suma 
	
		printf("Hijo: Enviando mult a padre...\n");
		/*Guardando el producto en el bloque de memoria compartida*/
		for(i=0; i<10; i++){
			for(j=0; j<10; j++){
				n= (i*10) + j;
				*(shm1+n) = m->filas[i][j];
			}
		}
		printf("--FINALIZÓ PROCESO HIJO--\n");
		liberar(1); //termina multiplicación
		exit(0);
	}
	
}
