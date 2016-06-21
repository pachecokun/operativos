#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int pid,mypid,fatherpid;
char cad[100];
char aux[20];

int hijos(int n){
	int i;
	sprintf(cad, "[%d] Hijos (%d): ",mypid,n);
	for(i=1;i<n+1;i++){
		pid = fork();
		mypid = getpid();
		if(!pid){
			return i;
		}
		else{
			sprintf(aux,"%d ",pid);
			strcat(cad,aux);
		}
	}
	printf("%s\n",cad);
	return 0;
}

int linea(int n){
	int i;
	sprintf(cad,"[%d] Línea tamaño %d : ",mypid,n);
	for(i=0;i<n;i++){
		pid = fork();
		mypid = getpid();
		if(pid){
			return 0;
		}
		else{
			sprintf(aux,"%d ",mypid);
			strcat(cad,aux);
		}
	}
	printf("%s\n",cad);
	return 1;
}

int main(){
	int i;
	int n;
	mypid = getpid();
	printf("Proceso principal: %d\n",mypid);
	
	
	i = hijos(10);
	if(i){
		if(linea(11-i)){
			fatherpid = mypid;
			n = hijos(11-i);
			if(n){
				printf("[%d] --Proceso padre: %d\n",mypid,fatherpid);
			}
		}
	}
	exit(0);
}
