#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>


void hilos(int nhilos,void*fun){
	int i;
	pthread_t* tid = (pthread_t*) malloc(sizeof(pthread_t)*nhilos);
	pthread_t id;
	char* cad = (char*)malloc(256);
	char* aux = (char*)malloc(10);
	sprintf(cad,"Hilos creados: ");
	for(i = 0;i<nhilos;i++){
		pthread_create(&id,NULL,fun,NULL);
		tid[i] = id;
		sprintf(aux,"%u ",tid[i]);
		strcat(cad,aux);
	}
	printf("%s\n",cad);
	for(i = 0;i<nhilos;i++){
		pthread_join(tid[i],NULL);
	}
	
}

void* hilo3(){
	printf("Práctica 5\n");
	pthread_exit((void*)0);
}

void* hilo2(){
	hilos(5,hilo3);
	pthread_exit((void*)0);
}

void* hilo1(){
	hilos(10,hilo2);
	pthread_exit((void*)0);
}

int main(){
	if(!fork()){
		hilos(15,hilo1);
	}
	else{
		wait(NULL);
	}
	exit(0);
}
