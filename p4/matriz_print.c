#include<stdio.h>
#include<stdlib.h>

void printfile(char*file){
	FILE* f = fopen(file,"r");
	char c;
	while((c=fgetc(f))!= EOF){
		printf("%c",c);
	}
}


int main(int argc, char*argv[]){
	printf("-----m1+m2-----\n");
	printfile("suma.txt");
	printf("\n\n");
	printf("-----m1-m2-----\n");
	printfile("resta.txt");
	printf("\n\n");
	printf("-----m1m2-----\n");
	printfile("mult.txt");
	printf("\n\n");
	printf("-----trans(m1)-----\n");
	printfile("trans1.txt");
	printf("\n\n");
	printf("-----trans(m2)-----\n");
	printfile("trans2.txt");
	printf("\n\n");
	printf("-----inv(m1)-----\n");
	printfile("inv1.txt");
	printf("\n\n");
	printf("-----inv(m2)-----\n");
	printfile("inv2.txt");
	printf("\n\n");
	exit(0);
}
