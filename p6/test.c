#include "matriz.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	Matriz m1 = crear(10,10);
	Matriz m2 = crear(2,2);

	int i,j;
	srand(time(NULL));
	for(i = 0;i<m1->h;i++){
		for(j = 0;j<m1->w;j++){
			m1 -> filas[i][j] = 10-rand()%21;
		}
	}
	for(i = 0;i<m2->h;i++){
		for(j = 0;j<m2->w;j++){
			m2 -> filas[i][j] = 10-rand()%21;
		}
	}	
	
	printMatriz(m1);
	printMatriz(m2);
	printMatriz(inv(m1));
	printMatriz(inv(m2));
	exit(0);
}
