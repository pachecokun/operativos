#include <stdio.h>
#include <stdlib.h>

unsigned char i,j;
char** m1;
char** m2;
short int** aux;
float pivote, a[10][10], b[10][10];
unsigned char i,j;

void init(){
	m1 = (char**)malloc(10*sizeof(char*));
	for(i = 0;i<10;i++){
		m1 [i] = (char*)malloc(10);
	}
	m2 = (char**)malloc(10*sizeof(char*));
	for(i = 0;i<10;i++){
		m2 [i] = (char*)malloc(10);
	}
	aux = (short int**)malloc(10*sizeof(short int*));
	for(i = 0;i<10;i++){
		aux [i] = (short int*)malloc(10*sizeof(short int));
	}
}

void leer(char** res,char*cad){
	char c;
	char aux[5];
	int pa = 0,p = 0;
	i = j = 0;
	
	aux[0] = 0;
	
	for(p = 0;(c = cad[p])!=0;p++){
		if(c!=' '){
			aux[pa++] = c;
			aux[pa] = 0;
		}
		else{
			res[i][j++] = atoi(aux);
			j %= 10;
			i = j ? i : i+1;
			pa = 0;
			if(i==10){
				break;
			}
		}
	}
}

void guardar(char* file){
	FILE* f = fopen(file,"w");
	for(i = 0; i<10; i++){
		for(j = 0; j<10; j++){
			fprintf(f,"%5.2hd ",aux[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}

void guardarInv(char* file){
	FILE* f = fopen(file,"w");
	for(i = 0; i<10; i++){
		for(j = 0; j<10; j++){
			fprintf(f,"%7.3f",a[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}
