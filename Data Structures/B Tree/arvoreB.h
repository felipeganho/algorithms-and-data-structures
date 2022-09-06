#ifndef __ARVOREB_H__
#define __ARVOREB_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#define FILENAMEARVOREB "arvoreB.btree"
#define FILENAMELOG     "log_lbastiani.txt"

#define ORDEM 6
#define MIN_CHAVES (ORDEM/2 - 1)

typedef uint      id_type;
typedef long int  offset_t;
typedef uint      page_t;

typedef struct {
	id_type id;
	offset_t offset;
} arvoreb_elem_t;

typedef struct {
	page_t root;
	uint num_pages;
	page_t empty_pages;
	FILE *fd; // arquivo da árvore que fica constantemente aberto
} arvoreb_t;

typedef struct arvoreb_node_t {
	uint page_num; // é o número da página no disco, começa no 1
	arvoreb_elem_t chaves[ORDEM-1];
	page_t filhos[ORDEM];
	uint8_t num_chaves;
	bool is_folha;
} arvoreb_node_t;

/* ====================================================
   INICIALIZA
   ==================================================== */
void initArvoreB(arvoreb_t *arv);

/**
 * Cria a árvore B e inicializa a árvore B
 * @return precisa de free
 */
arvoreb_t *createArvoreB();

/**
 * Salva a árvore B no arquivo
 */
void saveToFileArvoreB(arvoreb_t *arv);

/**
 * Carrega a árvore B do arquivo
 */
void loadArvoreBFromFile(arvoreb_t *arv);

/**
 * Carrega o filho de node do disco para a memória
 * @param  filho idx do filho no nó
 * @return       precisa de fre
 */
arvoreb_node_t *loadFilhoFromFile(arvoreb_t *arv, arvoreb_node_t *node, int filho);

/**
 * Salva um nó da árvore no arquivo
 * esta função altera o valor de node->page_num para a nova página alocada em disco
 */
void saveNodeToFile(arvoreb_t *arv, arvoreb_node_t *node);

/**
 * verifica se a árvore está vazia
 * @return     true or false
 */
bool isEmptyArvoreB(arvoreb_t *arv);

/**
 * Verifica se a página está vazia
 * @param  page um inteiro que identifica a página no disco
 * @return      true or false
 */
bool isPageFull(arvoreb_t *arv, page_t page);

/**
 * retorna o offset da página no arquivo de dados
 * @param  page um inteiro que identifica a página no disco
 */
offset_t pageToOffset(page_t page);

/**
 * Carrega a página no disco e devolve o ponteiro do nó
 * @param  page um inteiro que identifica a página no disco
 * @return      precisa de free
 */
arvoreb_node_t *loadNodeFromFile(arvoreb_t *arv, page_t page);

/* ====================================================
   BUSCA
   ==================================================== */
offset_t searchArvoreB(arvoreb_t *arv, id_type id);
/**
* Função que realiza a busca por um ID na árvore B
* @param id é o ID buscado
* @return a função retorna o byte offset do registro do arquivo de dados identificado por id
*/

bool b_search(arvoreb_t *arv, arvoreb_node_t *page, id_type id, page_t *offset_page, int *ideal_pos);
/**
* Função que realiza a busca binária em uma página
* @param page é a página em que é feita a bsca, id é o ID buscado, offset_page é um ponteiro para a página
*        em que o ID deveria estar, ideal_pos é um ponteiro para a posição em que o ID deveria estar na página identificada
*        por offset_page.
* @return a função retorna true se o elemento foi encontrado na página e false, caso contrário.
*/

/* ====================================================
   INSERÇÃO
   ==================================================== */
bool insertArvoreB(arvoreb_t *arv, id_type id, offset_t offset);
/**
* Função geral que insere uma nova chave na árvore B
* @param id e offset são os campos da nova chave a ser inserida
* @return true, caso a inserção seja bem sucedida e false, caso contrário
*/

void insertion(arvoreb_t *arv, id_type id, offset_t off, arvoreb_node_t *page);
/**
* Função que insere uma nova chave em uma página que não está cheia
* @param id e off são os campos da nova chave, page é um ponteiro para a página na qual a chave será inserida
*/

void split(arvoreb_t *arv, int i, page_t pai, arvoreb_node_t *filho);
/**
* Função auxiliar que realiza o split de um nó
* @param filho é o nó que sofrerá o split, pai é o nó pai deste
*/

/* ====================================================
   REMOÇÃO
   ==================================================== */
/**
 * Remove o elemento que possui o ID infromado por parâmetro
 * @return     true se foi encontrado
 */
bool removeArvoreB(arvoreb_t *arv, id_type id);

/**
 * obtem um índice maior ou igual a devida posição da chave no Nó
 * @param  node nó que a chave será procurado
 * @param  id   id do elemento
 * @return      a posição do índice, sendo ela maior ou igual
 */
int getIndexNodeArvoreB(arvoreb_node_t *node, id_type id);

/**
 * remove um elemento do nó na árvore b
 * @param  node nó em que será procurado o elemento
 * @param  id   id do elemento
 * @return      true se foi removido com sucesso
 */
bool removeNodeArvoreB(arvoreb_t *arv, arvoreb_node_t *node, id_type id);

/**
 * remove um elemento de um nó folha
 * @param idx  índice do elemento no nó da árvore
 */
void removeFromFolha(arvoreb_t *arv, arvoreb_node_t *node, int idx);

/**
 * remove um elemento do nó da árvore que não é folha
 * @param idx  índice do elemento no nó da árvore
 */
void removeFromNonFolha(arvoreb_t *arv, arvoreb_node_t *node, int idx);

/**
 * obtém o maior elemento da subárvore da esquerda
 * @param  idx  índice do elemento no nó Node
 */
arvoreb_elem_t getPred(arvoreb_t *arv, arvoreb_node_t *node, int idx);

/**
 * obtém o menor elemento da subárvore da direita
 * @param  idx  índice do elemento no nó Node
 */
arvoreb_elem_t getSucc(arvoreb_t *arv, arvoreb_node_t *node, int idx);

/**
 * preenche o filho[idx] com algum dos filhos de Node que possui menos do que MIN_CHAVES
 * @param idx  um inteiro que identifica a página no disco
 */
void fillNodeArvoreB(arvoreb_t *arv, arvoreb_node_t *node, int idx);

void borrowFromPrev(arvoreb_t *arv, arvoreb_node_t *node, int idx);

void borrowFromNext(arvoreb_t *arv, arvoreb_node_t *node, int idx);

/**
 * função que une idx com idx+1
 * @param idx  um inteiro que identifica a página no disco
 */
void mergeNodeArvoreB(arvoreb_t *arv, arvoreb_node_t *node, int idx);

/* ====================================================
   NÓS
   ==================================================== */
void initNodeArvoreB(arvoreb_node_t *node);

/**
 * cria e inicializa um Nó da árvore
 * @return precisa de free
 */
arvoreb_node_t *createNodeArvoreB();

/* ====================================================
   DESALOCA DA MEMÓRIA
   ==================================================== */
void freeArvoreB(arvoreb_t *arv);

/* ====================================================
   IMPRIME A ÁRVORE
   ==================================================== */
void printArvoreB(arvoreb_t *arv);

/**
 * imprime um nó da árvore recebendo a página no arquivo
 */
void printPagesArvoreB(arvoreb_t *arv, page_t page);

void deleteFileArvoreB();

/**
 * Use-a como se fosse dar um printf na tela
 * já salva no arquivo automaticamente
 * se DEBUG está ativado, imprime na tela também
 */
void file_log(char *str, ...);

#endif //__ARVOREB_H__
