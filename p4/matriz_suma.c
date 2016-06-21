#include "matriz_io.h"
 
void suma(){
	for(i = 0; i<10; i++){
		for(j=0; j<10; j++){
			aux[i][j] = m1[i][j] + m2[i][j];
		}
	}
}

void main(int argc,char*argv[]){
	init();
	leer(m1,argv[1]);
	leer(m2,argv[2]);
	suma();
	guardar("suma.txt");
	exit(0);
}
