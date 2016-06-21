#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct matriz{
	float**filas;
	int w;
	int h;	
}* Matriz;

Matriz crear(int h,int w){
	Matriz res = (Matriz)malloc(sizeof(struct matriz));
	res->filas = (float**)malloc(sizeof(float*)*h);
	int i;
	for(i = 0;i<h;i++){
		res->filas[i] = (float*)malloc(sizeof(float)*w);
	}
	res->w = w;
	res->h = h;
	return res;
}


void printMatriz(Matriz m){
	int i,j;
	for(i = 0;i<m->h;i++){
		for(j = 0;j<m->w;j++){
			printf("%f\t",m -> filas[i][j]);
		}
		printf("\n");
	}
}

void saveMatriz(Matriz m,FILE*f){
	int i,j;
	fprintf(f,"%d\n%d\n",m->h,m->w);
	for(i = 0;i<m->h;i++){
		for(j = 0;j<m->w;j++){
			fprintf(f,"%f\t",m -> filas[i][j]);
		}
		fprintf(f,"\n");
	}
}

void sendMatriz(Matriz m,int f){
	int i,j;
	char msg[1300];
	char num[13];
	sprintf(msg,"%d\n%d\n",m->h,m->w);
	for(i = 0;i<m->h;i++){
		for(j = 0;j<m->w;j++){
			sprintf(num,"%f\t",m -> filas[i][j]);
			strcat(msg,num);
		}
		strcat(msg,"\n");
	}
	write(f,msg,strlen(msg)+1);
}

Matriz readMatriz(int f){
	char msg[1300];
	char c;
	int i = 0;
	read(f,msg,1300);
	int w,h;
	
	char*ptr = &msg[0];
	h = (int)strtof(ptr,&ptr);
	w = (int)strtof(ptr,&ptr);	
	Matriz m = crear(h,w);
	int j;
	for(i = 0;i<m->h;i++){
		for(j = 0;j<m->w;j++){
			m -> filas[i][j] = strtof(ptr,&ptr);
		}
		sscanf(msg,"\n");
	}
	return m;
}

Matriz suma(Matriz m1, Matriz m2){
	Matriz res = crear(m1->h,m1->w);
	int i,j;
	for(i = 0;i<m1->h;i++){
		for(j = 0;j<m1->w;j++){
			res -> filas[i][j] = m1 -> filas[i][j] + m2 -> filas[i][j];
		}
	}
	return res;
}

Matriz resta(Matriz m1, Matriz m2){
	Matriz res = crear(m1->h,m1->w);
	int i,j;
	for(i = 0;i<m1->h;i++){
		for(j = 0;j<m1->w;j++){
			res -> filas[i][j] = m1 -> filas[i][j] - m2 -> filas[i][j];
		}
	}
	return res;
}

Matriz mult(Matriz m1, Matriz m2){
	Matriz res = crear(m1->h,m2->w);
	int i,j,k;
	for(i = 0;i<m1->h;i++){
		for(j = 0;j<m1->w;j++){
			float mult = 0;
			for(k = 0;k<m1->w;k++){
				mult += m1 -> filas[i][k] * m2 -> filas[k][j];
			}
			res -> filas[i][j] = mult;
		}
	}
	return res;
}

Matriz multN(Matriz m1, float n){
	Matriz res = crear(m1->h,m1->w);
	int i,j;
	for(i = 0;i<m1->h;i++){
		for(j = 0;j<m1->w;j++){
			res -> filas[i][j] = m1 -> filas[i][j]*n;
		}
	}
	return res;
}

Matriz trans(Matriz m1){
	Matriz res = crear(m1->h,m1->w);
	int i,j;
	for(i = 0;i<m1->h;i++){
		for(j = 0;j<m1->w;j++){
			res -> filas[i][j] = m1 -> filas[j][i];
		}
	}
	return res;
}

void limpiar(Matriz m){
	int i;
	for(i=0;i<m->h;i++){
		free(m->filas[i]);
	}
	free(m->filas);
	free(m);
}


Matriz menor(Matriz m, int fila, int col){
	Matriz res = crear(m->h-1,m->w-1);
	int i,j,k,l;
	for(i = 0;i<m->h;i++){
		for(j = 0;j<m->w;j++){
			if(i<fila){
				if(j<col){
					res -> filas[i][j] = m -> filas[i][j];
				}
				else if(j>col){
					res -> filas[i][j-1] = m -> filas[i][j];
				}
			}
			else if(i>fila){
				if(j<col){
					res -> filas[i-1][j] = m -> filas[i][j];
				}
				else if(j>col){
					res -> filas[i-1][j-1] = m -> filas[i][j];
				}
			}
		}
	}
	return res;
}
float det(Matriz m);

float cofactor(Matriz m, int i,int j){
	int n = (i+j)%2 ? -1 : 1;
	Matriz men = menor(m,i,j);
	float f =n*det(men);
	limpiar(men);
	return f;
}

float det(Matriz m){
	if(m->w == 1){
		return m->filas[0][0];
	}
	else{
		int i,j;
		float res = 0;
		j = 0;
		for(i = 0;i<m->h;i++){
			res += m->filas[i][j]*cofactor(m,i,j);
		}
		return res;
	}
}

Matriz adjunta(Matriz m1){
	int i,j;
	Matriz res = crear(m1->h,m1->w);
	for(i = 0;i<m1->h;i++){
		for(j = 0;j<m1->w;j++){
			res -> filas[i][j] = cofactor(m1,i,j);
		}
	}
	return trans(res);
}

Matriz inv(Matriz m){
	Matriz adj = adjunta(m);
	float d = det(m);
	Matriz inv = multN(adj,1/det(m));
	limpiar(adj);
	return inv;
}

