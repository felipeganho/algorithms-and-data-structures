/*
    Integrantes:
        Felipe Silva Ganho
        Leonardo Loureiro de Almeida
*/

//inclusao de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include "treeRN.h"

void main () {
    int op, id;
    arvoreRN aux;
    Artigo *artigo;

    iniciaRN();
    do{
        printf("\nMenu:\n1. Inserir um ID\n");
        printf("2. Deletar um ID da Arvore\n" );
        printf("3. Buscar um Artigo na Arvore\n" );
        printf("4. Imprimir\n");
        printf("0. Sair\n\n");
        printf(" Escolha a opcao: ");
        scanf ("%d", &op);
        switch (op) {
            case 1: //Inserir
                artigo = criaArtigo(artigo);
                raiz =  insereRN(raiz, artigo);
                //printf("ID cadastrado com sucesso!");
            break;
            case 2: //Remover
                printf (" Digite a ID que deseja remover da Arvore RN: ");
                scanf ("%d", &id);
                aux = buscaRN(raiz, id);
                removeRN(raiz, aux);
                if (aux != noNullRN)
                    printf ("\n ID removido com  com sucesso!\n");
                else
                    printf ("\n ID nao existe.\n");
            break;
            case 3: //Buscar
                printf ("\nSegue abaixo todos os ID cadastrados em Ordem\n");
                imprimeEmOrdemRN(raiz);
                printf("\n");
                printf (" Digite o ID de qual Artigo deseja buscar: ");
                scanf ("%d", &id);
                arvoreRN aux;
                aux = buscaRN (raiz, id);
                if (aux == noNullRN)
                    printf (" ID nao cadastrado.\n");
                else
                    mostrarArtigo(aux->artigo);
            break;
            case 4: //Imprimir
                if (raiz != noNullRN) {
                    imprimeNivelRN(raiz);
                }
                else
                    printf ("\nA arvore esta vazia.\n");
            break;
            default:
                printf ("Opcao Invalida!\n");
            break;
        }
        printf("\n");
    }while (op != 0);

}
