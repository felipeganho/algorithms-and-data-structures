/*
    Estudantes:
        Felipe Silva Ganho
        Leonardo Loureiro de Almeida
*/

//inclusao de bibliotecas
#include "huffman.h"

void main(){
	int opcao = 0;
	do{
        //menu
		printf("***** MENU *****\n");
    	printf("1. Comprimir\n");
    	printf("2. Descomprimir\n");
    	printf("3. Sair\n");
    	scanf("%d", &opcao);

		//COMPRESSAO
    	if(opcao==1){
			//solicita o nome do arquivo que deseja comprimir
    		printf("Digite o nome do arquivo para ser comprimido sem sua extensao | Ex.: (exemplo.txt) -> digite apenas (exemplo): ");
    		char documento[100];
	        fflush(stdin);
	        //gets(documento);
	        scanf("%s", documento);
	        strcat(documento,".txt");

            //atribui estrutrua, realiza contagem de simbolos e ocorrencias
    		if(preProcessamento(documento)){
                printf("Erro ao abrir o arquivo\n");
                return;
	        }

            //recebe toda a estrutura de no
	        atribuiAux();
            //constroi arvore
	        arvHuffman();
            //realiza a codificacao de cada caracter
	        codificar();

			//solicita uma nome para o arquivo de saida comprimido
	        printf("Informe um nome para o arquivo comprimido de saida: ");
			char docComprimido[100];
	        fflush(stdin);
	        //gets(docComprimido);
	        scanf("%s", docComprimido);
	        strcat(docComprimido,".txt");

			//verificacao caso tenha conseguido escrever o cabecalho no arquivo
	        if(escreveCabecalho(docComprimido)){
	            printf("Erro ao abrir o arquivo\n");
	            return;
	        }

			//verificacao caso tenha conseguido comprimir
		 	if(comprimir(documento, docComprimido)){
            	printf("Erro ao abrir o arquivo\n");
            	return;
	        }

			//impressao do codigo binario e informacoes uteis
	        imprimeInfos();

		//DESCOMPRESSAO
		}else if(opcao==2){
			//solicita nome do arquivo para descomprimir
			printf("Digite o nome do arquivo para ser descomprimido sem sua extensao | Ex.: (exemplo.txt) -> digite apenas (exemplo): ");
    		char docToDescomprimir[100];
	        fflush(stdin);
	        //gets(docToDescomprimir);
	        scanf("%s", docToDescomprimir);
	        strcat(docToDescomprimir,".txt");

			//solicita nome para o arquivo de saida descomprimido
			printf("Informe um nome para o arquivo descomprimido de saida: ");
			char docSaidaDescomprimido[100];
	        fflush(stdin);
	        //gets(docSaidaDescomprimido);
	        scanf("%s", docSaidaDescomprimido);
	        strcat(docSaidaDescomprimido,".txt");

			//realiza verificacao se houve a descompressao
			if (descomprimir(docToDescomprimir, docSaidaDescomprimido)){
           		printf("Error ao abrir o arquivo\n");
            	return;
        	}

		//SAIDA
		}else if(opcao==3) break;
		//OUTRAS OPCOES
		else{
			printf("Opcao invalida! Informe umas das opcoes apresentadas\n");
		}

	} while(opcao!=3);
}
