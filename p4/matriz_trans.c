#include "matriz_io.h"

void transpuesta(char matriz){
	for(i = 0; i<10; i++){
		for(j = 0; j<10; j++){
			if(matriz == 1)
				aux[i][j] = m1[j][i];
			else
				aux[i][j] = m2[j][i];
		}
	}
}
 

 
void main(int argc,char*argv[]){
	init();
	leer(m1,argv[1]);
	leer(m2,argv[2]);
	transpuesta(1);
	guardar("trans1.txt");
	transpuesta(2);
	guardar("trans2.txt");
	exit(0);
}
