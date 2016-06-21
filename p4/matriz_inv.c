#include "matriz_io.h"

void fila_pivote(void){ 
    unsigned char m; 
    for(m=0; m<10; m++) 
        if(m != i) 
            b[i][m]=a[i][m]/pivote; 
} 
 
void col_pivote(){ 
    unsigned char m; 
    for(m=0; m<10; m++) 
        if(m != j) 
            b[m][j]=-a[m][j]/pivote; 
} 
 
void otros(void){ 
    unsigned char x,y; 
    for(x=0 ;x<10; x++) 
        for(y=0; y<10; y++) 
            if(x!=i && y!=j) 
                b[x][y]=a[x][y]-(a[i][y]*a[x][j])/pivote; 
} 
 
void inversa(char matriz){
	unsigned char k,l;
	for(i = 0; i<10; i++){
		for(j = 0; j<10; j++){
			if(matriz == 1)
				a[i][j] = m1[i][j];
			else
				a[i][j] = m2[i][j];
		}
	}	
	for(i=0; i<10; i++){ 
        	j=i; 
		pivote=a[i][j]; 
		b[i][j]=1/pivote; 
		fila_pivote(); 
		col_pivote(); 
		otros(); 
		for(k=0; k<10; k++) 
		    for(l=0; l<10; l++) 
		        a[k][l]=b[k][l]; 
    	} 
}
 
void main(int argc,char*argv[]){
	init();
	leer(m1,argv[1]);
	leer(m2,argv[2]);
	inversa(1);
	guardarInv("inv1.txt");
	inversa(2);
	guardarInv("inv2.txt");
	exit(0);
}
