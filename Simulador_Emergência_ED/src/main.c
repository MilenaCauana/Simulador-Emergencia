#include <stdio.h>
#include <stdlib.h>

int main(){

    Descritor* fila;
    cria_fila(&fila);
    enfileirando(&fila);
    free_fila(fila->ultimo);

    return 0;

}
