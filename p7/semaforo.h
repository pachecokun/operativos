#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define clave 5869

int semid = -1;
int sem_flags = IPC_CREAT|0777;
int nsems = 2;
int nops = 1;
struct sembuf* ops;

void init(){
	ops = (struct sembuf*)malloc(sizeof(struct sembuf));
	
	if((semid=semget(clave,nsems,sem_flags))==-1){
		printf("Error al obtener semáforo: %s\n",strerror(errno));
		exit(0);
	}
}

int getSemaforo(){
	return semid;
}

int opSemaforo(int sem,int oper){
	int sid = getSemaforo();
	ops[0].sem_num = sem;
	ops[0].sem_op = oper;
	ops[0].sem_flg = SEM_UNDO | (oper==-1 ? IPC_NOWAIT : 0);
	if(semop(sid,ops,1)){
		return 1;
	}
	return 0;
}

void esperar(int sem){
	opSemaforo(sem,0);
}

void bloquear(int sem){
	opSemaforo(sem,1);
}

void liberar(int sem){
	opSemaforo(sem,-1);
}


void reset(int sem){
	while(!opSemaforo(sem,-1));
}

