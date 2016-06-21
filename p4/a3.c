#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int i,n;

int hijos(int n){
	for(i=1;i<n+1;i++){
		if(!fork()){
			return i;
		}
	}
	return 0;
}

int linea(int n){
	for(i=0;i<n;i++){
		if(fork()){
			return 0;
		}
	}
	return 1;
}

int main(){
	n = hijos(3);
	
	if(n==1){
		if(linea(2)){
			n = hijos(4);
			if(n==1){
				if(linea(1)){
					hijos(3);
				}
			}
			else if(n==2){
				if(linea(2)){
					hijos(2);
				}
			}
			else if(n==3){
				if(linea(3)){
					hijos(4);
				}
			}
			else if(n==4){
				hijos(1);
			}
		}			
	}
	else if(n==2){
		if(linea(1)){
			n=hijos(3);
			if(n==1){
				if(linea(4)){
					hijos(2);
				}
			}
			else if(n==2){
				if(linea(4)){
					hijos(3);
				}
			}
			else if(n==3){
				if(linea(4)){
					hijos(2);
				}
			}
		}
	}
	else if(n==3){
		if(linea(3)){
			n=hijos(4);
			if(n==1){
				hijos(3);
			}
			else if(n==2){
				hijos(1);
			}	
			else if(n==3){
				hijos(1);
			}	
			else if(n==4){
				n=hijos(2);
				if(n==1){
					if(linea(1)){
						hijos(3);
					}
				}
				else if(n==2){
					if(linea(1)){
						hijos(4);
					}
				}
			}	
		}
	}
	exit(0);
}
