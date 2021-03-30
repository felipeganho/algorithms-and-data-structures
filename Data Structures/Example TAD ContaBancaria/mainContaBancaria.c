// ************ mainContaBancaria.c *********
// Implementação da main

#include <stdio.h>
#include <stdlib.h>
#include "ContaBancaria.c"

int main(int argc, char *argv[]){
    ContaBancaria *conta;
    conta=(ContaBancaria *)malloc(sizeof(ContaBancaria));
    Inicializa(conta,2,2);
    Deposito(conta,500);
    printf("Deu certo!\n");
    Imprime(conta);
    return 10;
}
