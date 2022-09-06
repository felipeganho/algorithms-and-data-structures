#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "arvoreB.h"
#include "misc.h"

#define MAX_USR_NM 50
#define MAX_REG 70
#define FILE_REG "registro.reg"

typedef struct REGISTRO {
	int id;
    int ano;
	char titulo[MAX_USR_NM];
    char autor[200];
    char revista[200];
    char DOI[20];
    char palavraChave[200];
} usr_t;

//Funcao que imprime o menu principal
void main_menu(void);

/*
Funcao que insere um usuario na btree e no arquivo de registro, se necessario
Variaveis:
	btree- arvore binária
	id- numero da id a ser inserida
	pos- posicao do registro no arquivo de registros
	reg- arquivo de registros
	tu- tipo de usuario a ser inserido
	buff- guarda o tamanho da string a ser armazenada no arquivo de registros
	usr_name- nome do usuario a ser inserido
	buffer- string que guarda todo o registro
*/
void Insere_usuario (arvoreb_t *btree);

/*
Funcao que remove um usuario da btree e do arquivo de registro
Variaveis:
	btree- arvore binaria
	id- numero da id a ser removida
	pos- posicao da id no arquivo de registros
	reg- arquivo de registros
	buff- guarda o tamanho da string do registro
	buffer- string que guarda todo o registro
*/
void Remove_usuario (arvoreb_t *btree);

/*
Funcao que busca um usuario na btree
Variaveis:
	btree- arvore binaria
	usr- struct que representa e guarda as informações do usuário a ser buscado
	pos- posicao da id no arquivo de registros
	reg- arquivo de registros
	buff- guarda o tamanho da string do registro
	buffer- string que guarda todo o registro
*/
void Busca_usuario(arvoreb_t *btree);

/*
Funcao que carrega um arquivo de registros ja existente para uma btree
Variaveis:
	reg- arquivo de registros
	btree- arvore binaria
	usr- struct que representa um determinado usuário
	pos- posicao da id no arquivo de registros
	reg- arquivo de registros
	buff- guarda o tamanho da string a ser armazenada no arquivo de registros
	buffer- string que guarda um registro inteiro
*/
void Load_reg(FILE *reg, arvoreb_t *btree);

/*
Função que altera uma string de um registro para que ela passe a indicar que o registro foi apagado
Variáveis:
	str- string a ser alterada
	i- contador
Retorno:
	0- a string foi alterada com sucesso
	-3- a string não foi gravada corretamente
*/
int altera_srt(char *str);

/*
Função que passa uma string com um registro para uma struct que representará o registro em memória
Variáveis:
	str- string com o registro
	usr- string para representar o registro
	i, j- contadores
	buffer- usado para gravar temporáriamente cada informação do registro separadamente
*/
void strTOstruct(char *str, usr_t *usr);
