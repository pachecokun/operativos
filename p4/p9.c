#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
 
char m1 [10][10];
char m2 [10][10];
short int aux[10][10];
unsigned char i,j;
FILE *f;
 
void generaMatrices(){
	srand(time(NULL));
	for(i = 0; i<10; i++){
		for(j=0; j<10; j++){
			m1[i][j] = rand() % 10;
			m2[i][j] = rand() % 10;
		}
	}
}
 
void suma(){
	for(i = 0; i<10; i++){
		for(j=0; j<10; j++){
			aux[i][j] = m1[i][j] + m2[i][j];
		}
	}
}
 


void resta(){
	for(i = 0; i<10; i++){
		for(j=0; j<10; j++){
			aux[i][j] = m1[i][j] - m2[i][j];
		}
	}
}
 
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
 
float pivote, a[10][10], b[10][10];
 
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
 
void lee(char proceso){
	char archivo[20];
	switch(proceso){
		case 1:
			sprintf(archivo,"%s","suma.txt");
			break;
		case 2:
			sprintf(archivo,"%s","resta.txt");
			break;
		case 3:
			sprintf(archivo,"%s","multiplicacion.txt");
			break;
		case 4:
			sprintf(archivo,"%s","inversa.txt");
			break;
		case 5:
			sprintf(archivo,"%s","transpuesta.txt");
	}
	f = fopen(archivo, "r");
	char linea[100];
	while(feof(f)==0){
		fgets(linea,100,f);
		printf("%s",linea);
	}
	fclose(f);
}
 
void main(){
	struct timeval t0, tf;
	gettimeofday(&t0,NULL);
	generaMatrices();
	printf("Matriz 1: \n");
	for(i = 0; i<10; i++){
		for(j = 0; j<10; j++){
			printf("%d ",m1[i][j]);
		}
		puts("");
	}
	puts("");
	printf("Matriz 2: \n");
	for(i = 0; i<10; i++){
		for(j = 0; j<10; j++){
			printf("%d ",m2[i][j]);
		}
		puts("");
	}
	if(fork() == 0){
		for(i = 1; i <= 5; i++){
			if(fork()==0){
				switch(i){
					case 1:
						f = fopen("suma.txt","w");
						suma();
						fprintf(f,"\nm1 + m2: \n");
						for(i = 0; i<10; i++){
							for(j = 0; j<10; j++){
								fprintf(f,"%.2hd ",aux[i][j]);
							}
							fprintf(f,"\n");
						}
						fclose(f);
						exit(0);
						break;
					case 2:
						f = fopen("resta.txt","w");
						resta();
						fprintf(f,"\n\nm1 - m2:");
						for(i = 0; i<10; i++){
							for(j = 0; j<10; j++){
								if(aux[i][j] >= 0)
									fprintf(f,"%.2hd ",aux[i][j]);
								else
									fprintf(f,"%hd ",aux[i][j]);
							}
							fprintf(f,"\n");
						}
						fclose(f);
						exit(0);
						break;
					case 3:
						f = fopen("multiplicacion.txt","w");
						multiplicacion();
						fprintf(f,"\nm1 * m2: \n");
						for(i = 0; i<10; i++){
							for(j = 0; j<10; j++){
								fprintf(f,"%.3hd ",aux[i][j]);
							}
							fprintf(f,"\n");
						}
						fclose(f);
						exit(0);
						break;
					case 4:
						f=fopen("inversa.txt","w");
						inversa(1);
						fprintf(f,"\nInversa de m1: \n");
						for(i = 0; i<10; i++){
							for(j = 0; j<10; j++){
								if(a[i][j] < 0)
									fprintf(f,"%.3f ",a[i][j]);
								else
									fprintf(f,"%.4f ",a[i][j]);
							}
							fprintf(f,"\n");
						}
						inversa(2);
						fprintf(f,"\nInversa de m2: \n");
						for(i = 0; i<10; i++){
							for(j = 0; j<10; j++){
								if(a[i][j] < 0)
									fprintf(f,"%.3f ",a[i][j]);
								else
									fprintf(f,"%.4f ",a[i][j]);
							}
							fprintf(f,"\n");
						}
						fclose(f);
						exit(0);
						break;
					case 5:
						f=fopen("transpuesta.txt","w");
						transpuesta(1);
						fprintf(f,"\nTranspuesta de m1: \n");
						for(i = 0; i<10; i++){
							for(j = 0; j<10; j++){
								fprintf(f,"%hd ",aux[i][j]);
							}
							fprintf(f,"\n");
						}
						transpuesta(2);
						fprintf(f,"\nTranspuesta de m2: \n");
						for(i = 0; i<10; i++){
							for(j = 0; j<10; j++){
								fprintf(f,"%hd ",aux[i][j]);
							}
							fprintf(f,"\n");
						}
						fprintf(f,"\n");
						fclose(f);
						exit(0);
				}
			}
		}
	}else{
		for(i = 1; i<=5; i++){
			wait(0);
		}
 
		for(i = 1; i<=5; i++){
			lee(i);
		}
		gettimeofday(&tf,NULL);
		int tiempo = (int)((tf.tv_sec*1000)+(tf.tv_usec/1000))-((t0.tv_sec*1000)+(t0.tv_usec/1000));
		printf("Tiempo de ejecución: %d milisegundos\n",tiempo);
	}
}
