// gcc -O2 bomba.c -o bomba -no-pie

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 60 	   // segundos que tarda en explotar la bomba

void boom(void){

	printf("\n"
"     .-^^---....,,--		\n"      
" _--                  --_  \n"
"<                        >)\n"
"|          BOOM!           |\n"
" \\._                   _./ \n" 
"    ```--. . , ; .--'''    \n"   
"          | |   |          \n"   
"       .-=||  | |=-.   	\n"
"       `-=#$$$$$#=-'   	\n"
"          | ;  :|     		\n"
" _____.,-#########~,._____	\n");
	exit(-1);
}

void defused(void){
	printf(	"\n"
		"·························\n"
		"··· bomba desactivada ···\n"
		"·························\n"
		"\n");
	exit(0);
}

// Contraseña real: fuhvcty?!\n
// PIN real: 5270\n
char password[]="hcufvyt\n!?";	// contraseña de entre 8 y 10 caracteres
char passcode[]  = "7\n250";			// pin de entre 3 y 6 dígitos
int shuffle[] = {2, 4, 1, 0, 3, 6, 5, 9, 8, 7, 10};

void encriptar(char a_encriptar[], char encriptado[]){

	char cp[strlen(encriptado)];
	strcpy(cp, a_encriptar);
	for (int i=0; i<strlen(encriptado); i++)
		a_encriptar[i] = cp[shuffle[i]];
}

int main(){
	char pw[SIZE];
	char  pc[SIZE];

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);

	do	printf("\nIntroduce la contraseña: ");
	while (	fgets(pw, SIZE, stdin) == NULL );
	encriptar(pw, password);
	

	if    (	strncmp(pw,password,sizeof(password)) )
	    boom();

	gettimeofday(&tv2,NULL);
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    boom();


	do	printf("\nIntroduce el pin: ");
	while (	fgets(pc, SIZE, stdin) == NULL );
	encriptar(pc, passcode);

	if    (	strncmp(pc,passcode,sizeof(passcode)) )
	    boom();

	gettimeofday(&tv1,NULL);
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    boom();

	defused();
}
