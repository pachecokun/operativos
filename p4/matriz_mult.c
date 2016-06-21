#include "matriz_io.h"

void multiplicacion(){
	unsigned char k;
	for(i = 0; i<10; i++){
		for(j=0; j<10; j++){
			for(k=0; k<10; k++){
				aux[i][j] += m1[i][k] * m2 [k][j];
			}
		}
	}
}

 
void main(int argc,char*argv[]){
	init();
	leer(m1,argv[1]);
	leer(m2,argv[2]);
	multiplicacion();
	guardar("mult.txt");
	exit(0);
}
