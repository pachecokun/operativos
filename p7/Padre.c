#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "matriz.h"
#include "semaforo.h"

/*Función para guardar las matrices en un archivo*/
void guardaMatriz(Matriz m, char* archName){
	int i, j;
	FILE *f;
	f = fopen(archName, "w");
	for(i=0; i<10; i++){
		for(j=0; j<10; j++){
			fprintf(f, "    %0.4f", m->filas[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

int main(){
	init(); //inicializa operaciones

	int i, j, n;

	int shmid1,shmid2;
	key_t llave1,llave2;
	float *shm1;
	float *shm2;
	llave1 = 5677;
	llave2 = 5678;

	pid_t pid;
	char *argv[2];
	argv[0] = "Hijo";
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
	printf("shmid1: %d\n", shmid1);
	printf("shmid2: %d\n", shmid2);
	
	reset(0); //ponemos en 0 el semáforo
	reset(1); //ponemos en 0 el semáforo
	bloquear(0); //suma
	bloquear(1); //mult
	
	
	/*Valores de las matrices para el proceso hijo*/
	srand(time(NULL));
	for(i=0; i<100; i++){
		*(shm1+i) = rand() % 11;
	}
	for(i=0; i<100; i++){
		*(shm2+i) = rand() % 11;
	}
	
	/*Creación del proceso hijo*/
	if((pid= fork())==-1)
		printf("Error al crear el proceso hijo\n");
	if(pid == 0){
		execv(argv[0], argv);
	}
	else{	
	
		esperar(1); //esperamos operaciones
		/*Obtención de los resultados de la suma y producto*/
		Matriz mult = crear(10, 10);
		Matriz sum = crear(10, 10);
		for(i=0; i<10; i++){
			for(j=0; j<10; j++){
				n= (i*10) + j;
				mult->filas[i][j] = *(shm1+n);
				sum->filas[i][j] = *(shm2 + n);
			}
		}
		printf("Calculando inversas...\n");
		/*Matrices Inversas*/
		Matriz invMult = inv(mult);
		Matriz invSum = inv(sum);
		printf("\nMatriz inversa de la MULTIPLICACIÓN realizada por el HIJO:\n");
		printMatriz(invMult);
		printf("\nMatriz inversa de la SUMA realizada por el NIETO:\n");
		printMatriz(invSum);
		printf("\n");

		guardaMatriz(invMult, "multiplicacion.txt");
		guardaMatriz(invSum, "suma.txt");

		printf("Terminado.\n");

		exit(0);
	}
}
