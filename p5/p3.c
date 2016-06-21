#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>

char*dest;
char*orig;


char* getruta(int d,char* ruta){
	char* raiz = d ? dest : orig;
	char* res = (char*)malloc(strlen(ruta)+strlen(raiz)+2);
	sprintf(res,"%s/%s",raiz,ruta);
	return res;
}
void* copiar(void*arg){
	char* ro = (char*)arg;
	char* roa = getruta(0,ro);
	struct dirent **nombres;
	int n = scandir(roa,&nombres,NULL,alphasort);
	pthread_t hilos[n];
	int i,j = 0;
	
	
	if(n>=0){
		for(i = 2;i<n;i++){
			char * fname = malloc(200);
			sprintf(fname,"%s/",ro);
			strcat(fname,nombres[i]->d_name);
			char * fnameo = getruta(0,fname);
			char * fnamed = getruta(1,fname);
			
			struct stat info;
			stat(fnameo,&info);
			if(S_ISDIR(info.st_mode)){
				printf("Copiando directorio %s",fname);
				mkdir(fnamed,0777);
				pthread_t hid;
				pthread_create(&hid,NULL,copiar,fname);
				hilos[j++] = hid;
			}
			else{
				printf("Copiando archivo %s\n",fname);
				FILE* fr = fopen(fnameo,"r");
				FILE* fw = fopen(fnamed,"w");
				char c;
				while((c = fgetc(fr))!=EOF){
					fputc(c,fw);
				}
				close(fr);
				close(fw);
			}
			
		}
		for(i = 0;i<j;i++){
			pthread_join(hilos[i],NULL);
		}
	}
	else{
		printf("Error al copiar %s",arg);
	}
	pthread_exit((void*)0);
}

int main(int argc, char* argv[]){
	if(argc<3){
		printf("argumentos: carpeta_origen carpeta_destino\n");
	}
	else{
		orig = argv[1];
		dest = argv[2];
		pthread_t pid;
		pthread_create(&pid,NULL,copiar,(void*)"");
		pthread_join(pid,NULL);
	}
	exit(0);
}
