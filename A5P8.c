#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf entorno;
void atrapa(int);

int main() {
	int valor;
	printf("longjmp y setjmp son una forma de simular el \'goto\'\n\n");
	signal(SIGUSR1, atrapa);
	valor=setjmp(entorno);
	if(valor==0){
		printf("Inicia el punto de interrupcion del proceso.\n");
		sleep (1);
	}
	printf("Regreso al punto de interrupcion del proceso.\n");
}

Void atrapa(int sig) {
	signal(SIGUSR1, atrapa);
	long jmp (entorno, sig);
}
