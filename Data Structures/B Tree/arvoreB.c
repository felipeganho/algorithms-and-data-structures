#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "arvoreB.h"
#include "misc.h"

/* ====================================================
   INICIALIZA
   ==================================================== */
void initArvoreB(arvoreb_t *arv) {
	// apenas zera por completo a árvore
	memset(arv, 0, sizeof(arvoreb_t));
	if(file_exists(FILENAMEARVOREB)) {
		// se a árvore já existe, carrega ela do arquivo
		arv->fd = fopen(FILENAMEARVOREB, "r+");
		loadArvoreBFromFile(arv);
		return ;
	}
	debug("O arquivo da árvore não existe, criando o arquivo da árvore\n");
	arv->fd = fopen(FILENAMEARVOREB, "w+");
	// inicializa a árvore nessa função msmo
	// seta árvore vazia
	arv->root = -1;
	// no começo, não possui página vazia
	arv->empty_pages = -1;
	// agr salva no arquivo
	saveToFileArvoreB(arv);
}

/**
 * Cria a árvore B e inicializa a árvore B
 * @return precisa de free
 */
arvoreb_t *createArvoreB() {
	arvoreb_t *result = malloc(sizeof(arvoreb_t));
	initArvoreB(result);
	return result;
}

/**
 * Salva a árvore B no arquivo
 */
void saveToFileArvoreB(arvoreb_t *arv) {
	rewind(arv->fd);
	fwrite(&arv->root, sizeof(page_t), 1, arv->fd);
	fwrite(&arv->num_pages, sizeof(uint), 1, arv->fd);
	fwrite(&arv->empty_pages, sizeof(page_t), 1, arv->fd);
	fflush(arv->fd);
}

/**
 * Carrega a árvore B do arquivo
 */
void loadArvoreBFromFile(arvoreb_t *arv) {
	debug("Carregando a árvore da memória\n");
	rewind(arv->fd);
	fread(&arv->root, sizeof(page_t), 1, arv->fd);
	fread(&arv->num_pages, sizeof(uint), 1, arv->fd);
	fread(&arv->empty_pages, sizeof(page_t), 1, arv->fd);
}

page_t getNewPage(arvoreb_t *arv) {
    page_t result;
    // o valor da página é desconhecido, portanto, devemos criar uma página nova no disco
    if(arv->empty_pages != -1) {
        // obtem o primeiro nó da lista de vazios
        arvoreb_node_t *empty_node = loadNodeFromFile(arv, arv->empty_pages);
        // define a próxima página da lista de vazios
        arv->empty_pages = empty_node->filhos[0];
        // este nó será salvo no lugar do nó vazio
        result = empty_node->page_num;
        free(empty_node);
    } else {
        // cria uma nova página no arquivo
        debug("Criando uma página nova no disco\n");
        result = arv->num_pages+1; // 1, 2, 3, ...
    }
    arv->num_pages++; // aumenta o número de páginas
    saveToFileArvoreB(arv);
    return result;
}

/**
 * Salva um nó da árvore no arquivo
 * esta função altera o valor de node->page_num para a nova página alocada em disco
 */
void saveNodeToFile(arvoreb_t *arv, arvoreb_node_t *node) {
	if(node->page_num == 0) {
        node->page_num = getNewPage(arv);
	}
	if(node->num_chaves == 0) {
		// se este nó não possui nenhuma chave, inclui ele na lista de vazios
		// adiciona a próxima página a lista
		node->filhos[0] = arv->empty_pages;
		// define o primeiro da pilha
		arv->empty_pages = node->page_num;
		arv->num_pages--;
		if(arv->root == node->page_num) {
			arvoreb_node_t *nova_raiz = loadNodeFromFile(arv, arv->root);
			arv->root = nova_raiz->filhos[0];
			debug("Removeu a raiz! Nova raiz: %d\n", arv->root);
			free(nova_raiz);
		}
		saveToFileArvoreB(arv);
	}
	fseek(arv->fd, pageToOffset(node->page_num), SEEK_SET);
	fwrite(node, sizeof(arvoreb_node_t), 1, arv->fd);
	fflush(arv->fd);
	debug("Salvando página %d\n", node->page_num);
}

/**
 * verifica se a árvore está vazia
 * @return     true or false
 */
bool isEmptyArvoreB(arvoreb_t *arv) {
	return arv->root == -1;
}

/**
 * Verifica se a página está vazia
 * @param  page um inteiro que identifica a página no disco
 * @return      true or false
 */
bool isPageFull(arvoreb_t *arv, page_t page) {
	bool result;
	arvoreb_node_t *node = loadNodeFromFile(arv, page);
	result = node->num_chaves == ORDEM-1;
	free(node);
	return result;
}

/**
 * retorna o offset da página no arquivo de dados
 * @param  page um inteiro que identifica a página no disco
 */
offset_t pageToOffset(page_t page) {
	// anda o número de páginas
	offset_t result = ((page - 1) * sizeof(arvoreb_node_t));
	result += sizeof(page_t) * 2; // anda a raiz e o empty_pages
	result += sizeof(uint); // anda o num_pages
	return result;
}

/**
 * Carrega a página no disco e devolve o ponteiro do nó
 * @param  page um inteiro que identifica a página no disco
 * @return      precisa de free
 */
arvoreb_node_t *loadNodeFromFile(arvoreb_t *arv, page_t page) {
	if(page == -1) {
		return NULL;
	}
	arvoreb_node_t *result = createNodeArvoreB();
	fseek(arv->fd, pageToOffset(page), SEEK_SET);
	fread(result, sizeof(arvoreb_node_t), 1, arv->fd);
	return result;
}

/**
 * Carrega o filho de node do disco para a memória
 * @param  filho idx do filho no nó
 * @return       precisa de fre
 */
arvoreb_node_t *loadFilhoFromFile(arvoreb_t *arv, arvoreb_node_t *node, int filho) {
	return loadNodeFromFile(arv, node->filhos[filho]);
}

/* ====================================================
   BUSCA
   ==================================================== */
/**
* Função que realiza a busca binária em uma página
* @param page é a página em que é feita a bsca, id é o ID buscado, offset_page é um ponteiro para a página
*        em que o ID deveria estar, ideal_pos é um ponteiro para a posição em que o ID deveria estar na página identificada
*        por offset_page.
* @return a função retorna true se o elemento foi encontrado na página e false, caso contrário.
*/
bool b_search(arvoreb_t *arv, arvoreb_node_t *page, id_type id, page_t *offset_page, int *ideal_pos)
{
    if(isEmptyArvoreB(arv))
        return false;

    int left, right, middle;
    left = -1;
    right = page->num_chaves;
    *offset_page = -1;

    if(isEmptyArvoreB(arv))
        return false;

    while(left < right-1)
    {
        middle = (left + right)/2;

        if (page->chaves[middle].id < id)
        {
            (*offset_page) = page->filhos[middle+1];
            (*ideal_pos) = middle+1;
            left = middle;
        }

        else
        {
            if (page->chaves[middle].id > id)
            {
                *offset_page = page->filhos[middle];
                *ideal_pos = middle;
                right = middle;
            }

            else
            {
                if (page->chaves[middle].id == id)
                {
                    *offset_page = page->page_num;
                    *ideal_pos = middle;
                    return true;
                }
            }
        }
    }
    return false;
}


/**
* Função que realiza a busca por um ID na árvore B
* @param id é o ID buscado
* @return a função retorna o byte offset do registro do arquivo de dados identificado por id
*/
offset_t searchArvoreB(arvoreb_t *arv, id_type id)
{
    file_log("Execucao de operacao de PESQUISA de %d\n", id);
    if(isEmptyArvoreB(arv))
        return -1;

    page_t offset;      	                        //Byte offset a ser usado na busca binária
    bool busca = false;                             //Variável de controle da busca
    arvoreb_node_t *page = createNodeArvoreB();
    int i;

    //Lendo página raiz
    page = loadNodeFromFile(arv, arv->root);


    //Enquanto a busca não for bem sucedida
    while(!busca)
    {
        busca = b_search(arv, page, id, &offset, &i);

        if (!busca && offset != -1)
        {
            free(page);
            page = loadNodeFromFile(arv, offset);
        }
        else
            break;
    }


    if(busca)
        return page->chaves[i].offset;

    else
    	file_log("Chave %d nao encontrada\n", id);
        return -1;
}

/* ====================================================
   INSERÇÃO
   ==================================================== */
/**
* Função que insere uma nova chave na árvore B
* @param id e offset são os campos da nova chave a ser inserida
* @return true, caso a inserção seja bem sucedida e false, caso contrário
*/
bool insertArvoreB(arvoreb_t *arv, id_type id, offset_t offset)
{
    //Elemento existente
    if(searchArvoreB(arv, id) != -1)
    {
        file_log("Chave %d duplicada\n", id);
        return false;
    }

    arvoreb_node_t *new_page;
    page_t pai;

    // Ávore vazia
    if (arv->root == -1)
    {
        //Alocando espaço para raiz
        new_page = createNodeArvoreB();

        //Preencehndo raiz
        new_page->chaves[0].id = id;
        new_page->chaves[0].offset = offset;
        new_page->num_chaves = 1;
        new_page->is_folha = true;

        saveNodeToFile(arv, new_page);

        arv->root = new_page->page_num;
        saveToFileArvoreB(arv);

        free(new_page);

        file_log("Chave %d inserida com sucesso\n", id);
        return true;
    }

   //Caso a árvore não esteja vazia
    else
    {
        //Lendo a raiz
        new_page = loadNodeFromFile(arv, arv->root);

        //Caso a raiz esteja cheia
        if (new_page->num_chaves == ORDEM-1)
        {
            //Criando nova raiz
           free(new_page);
           new_page = createNodeArvoreB();

           new_page->is_folha = false;
           new_page-> page_num = getNewPage(arv);
           pai = new_page->page_num;


           //Tornando antiga raiz filha da nova raiz
           new_page->filhos[0] = arv->root;

           //Mudando a raiz
           arv->root = pai;
           fseek(arv->fd, pageToOffset(new_page->page_num), SEEK_SET);
           fwrite(new_page, sizeof(arvoreb_node_t), 1, arv->fd);

           saveToFileArvoreB(arv);

           //Lendo antiga raiz
           fseek(arv->fd, pageToOffset(new_page->filhos[0]), SEEK_SET);
           free(new_page);
           new_page = createNodeArvoreB();

           fread(new_page, sizeof(arvoreb_node_t), 1, arv->fd);

            //Realizando o split na antiga raiz e promovendo um elemento para a nova raiz
            split(arv, 0, pai, new_page);
           debug("new_page->num_chaves = %d\n", new_page->num_chaves);

            saveNodeToFile(arv, new_page);
            free(new_page);

            //Lendo a nova raiz
            new_page = loadNodeFromFile(arv, arv->root);

            //Qual dos dois filhos da nova raiz irá receber a nova chave
            int i = 0;
            if (new_page->chaves[0].id < id)
                i++;

            saveNodeToFile(arv, new_page);
            saveToFileArvoreB(arv);

            fseek(arv->fd, pageToOffset(new_page->filhos[i]), SEEK_SET);
            free(new_page);

            new_page = createNodeArvoreB();
            fread(new_page, sizeof(arvoreb_node_t), 1, arv->fd);

            insertion(arv, id, offset, new_page);
            file_log("Chave %d inserida com sucesso\n", id);

            return true;
        }

        //Caso a raiz não esteja cheia
        else
        {
            insertion(arv, id, offset, new_page);
            file_log("Chave %d inserida com sucesso\n", id);
            return true;
        }
    }
}

/**
* Função que insere uma nova chave em uma página que não está cheia
* @param id e off são os campos da nova chave, page é um ponteiro para a página na qual a chave será inserida
*/
void insertion(arvoreb_t *arv, id_type id, offset_t off, arvoreb_node_t *page)
{

    int i = page->num_chaves-1;

    page_t offset;
    int ideal_pos;
    arvoreb_node_t *new_page;

    //Caso page seja uma folha
    if (page->is_folha == true)
    {
        //Encontrando a posição da chave ao mesmo tempo em que se move as posteriores para a direita, alocando espaço
        while (i >= 0 && page->chaves[i].id > id)
        {
            page->chaves[i+1].id =  page->chaves[i].id;
            page->chaves[i+1].offset =  page->chaves[i].offset;
            i--;
        }

        //Inserindo a nova chave
        page->chaves[i+1].id = id;
        page->chaves[i+1].offset = off;     
        page->num_chaves ++;

        saveNodeToFile(arv, page);
    }

    //Caso page não seja uma folha
    else
    {
        //Buscando o nó filho que ira receber a nova chave
        b_search(arv, page, id, &offset, &ideal_pos);

        new_page = loadNodeFromFile(arv, offset);

        //Verificando se o nó filho está cheio
        if (new_page->num_chaves == ORDEM-1)
        {
            //Se o filho está cheio, ele sofre split
            split(arv, ideal_pos, page->page_num, new_page);

            //Relendo a página depois do split
            fseek(arv->fd, pageToOffset(page->page_num), SEEK_SET);

            free (page);

            page = createNodeArvoreB();
            fread(page, sizeof(arvoreb_node_t), 1, arv->fd);

            //Verificando qual das duas páginas resultantes do split irá receber a chave
            if (page->chaves[ideal_pos].id < id)
                ideal_pos++;
        }

        saveNodeToFile(arv, new_page);
        free(new_page);

        new_page = loadNodeFromFile(arv, page->filhos[ideal_pos]);

        insertion(arv, id, off, new_page);
    }
}

/**
* Função auxiliar que realiza o split de um nó
* @param filho é o nó que sofrerá o split, pai é o nó pai deste
*/
void split(arvoreb_t *arv, int i, page_t pai, arvoreb_node_t *filho)
{
    int j;
    int k = ORDEM/2;
    arvoreb_node_t *father;
    page_t num_aux;

    file_log("Divisao de no - página %d\n", filho->page_num);

    //Criando uma nova página que vai receber os k-1 elementos de filho
    arvoreb_node_t *new_page = createNodeArvoreB();
    new_page->page_num = getNewPage(arv);
    new_page->is_folha = filho->is_folha;
    new_page->num_chaves = MIN_CHAVES;

    //Copiando os elementos
    for (j = 0; j < k -1; j++)
    {
        new_page->chaves[j].id = filho->chaves[j+k].id;
        new_page->chaves[j].offset = filho->chaves[j+k].offset;
        filho->chaves[j+k].id = 0;
        filho->chaves[j+k].offset = 0;
    }

    //Copiando o último filho de um nó a outro
    if (filho->is_folha == false)
    {
        for (j = 0; j < k; j++)
            new_page->filhos[j] = filho->filhos[j+k];
    }

    //Decrementando o número de chaves de filho
    filho->num_chaves -= MIN_CHAVES;

    saveNodeToFile(arv, new_page);
    num_aux = new_page->page_num;
    free(new_page);

    //Criando espaço no nó pai para o nó criado
    father = loadNodeFromFile(arv, pai);

    for (j = father->num_chaves; j >= i+1; j--)
        father->filhos[j+1] = father->filhos[j];

    //Referenciando o novo filho no nó pai
    father->filhos[i+1] = num_aux;

    //Encontrando espaço para a chave promovida
    for (j = father->num_chaves-1; j >= i; j--)
    {
        father->chaves[j+1].id = father->chaves[j].id;
        father->chaves[j+1].offset = father->chaves[j].offset;
    }

    father->chaves[i].id = filho->chaves[k - 1].id;
    father->chaves[i].offset = filho->chaves[k - 1].offset;
    filho->chaves[k - 1].id = 0;
    filho->chaves[k - 1].offset = 0;

    file_log("Chave %d promovida\n", father->chaves[i].id);

    //Incrementando o número de chaves no nó pai
    father->num_chaves = father->num_chaves + 1;
    filho->num_chaves = filho->num_chaves -1;

    saveNodeToFile(arv, father);
    saveNodeToFile(arv, filho);
    free(father);
}


/* ====================================================
   REMOÇÃO
   ==================================================== */
/**
 * Remove o elemento que possui o ID infromado por parâmetro
 * @return     true se foi encontrado
 */
bool removeArvoreB(arvoreb_t *arv, id_type id) {
	file_log("Execucao de operacao de REMOCAO de %d.\n", id);
	if(isEmptyArvoreB(arv)) {
		file_log("Chave %d não cadastrada\n", id);
		return false;
	}
	arvoreb_node_t *root = loadNodeFromFile(arv, arv->root);
	bool result = removeNodeArvoreB(arv, root, id);
	free(root);
	if(result == false) {
		file_log("Chave %d não cadastrada\n", id);
	} else {
		file_log("Chave %d removida com sucesso\n", id);
	}
	return result;
}

/**
 * obtem um índice maior ou igual a devida posição da chave no Nó
 * @param  node nó que a chave será procurado
 * @param  id   id do elemento
 * @return      a posição do índice, sendo ela maior ou igual
 */
int getIndexNodeArvoreB(arvoreb_node_t *node, id_type id) {
	int i = 0;
	while(i < node->num_chaves && node->chaves[i].id < id) {
		i++;
	}
	return i;
}

bool nodeHasKey(arvoreb_node_t *node, id_type key) {
	int i;
	for(i=0; i<node->num_chaves; i++) {
		if(node->chaves[i].id == key) {
			return true;
		}
	}
	return false;
}

/**
 * remove um elemento do nó na árvore b
 * @param  node nó em que será procurado o elemento
 * @param  id   id do elemento
 * @return      true se foi removido com sucesso
 */
bool removeNodeArvoreB(arvoreb_t *arv, arvoreb_node_t *node, id_type id) {
	debug("Pesquisando a chave na página: %d\n", node->page_num);
	int idx = getIndexNodeArvoreB(node, id);
	debug("IDX: %d, Chave: %d, num_chaves: %d\n", idx, node->chaves[idx].id, node->num_chaves);
	if(idx < node->num_chaves && node->chaves[idx].id == id) {
		// o id está nesse nó
		debug("Chave %d encontrada na página: %d\n", id, node->page_num);
		if(node->is_folha) {
			removeFromFolha(arv, node, idx);
		} else {
			removeFromNonFolha(arv, node, idx);
		}
		return true;
	}
	// procura em outros nós
	debug("A página %d é folha? %d\n", node->page_num, node->is_folha);
	if(node->is_folha) {
		// chave não encontrada
		return false;
	}
	page_t prox_pagina = node->filhos[idx];
	// está em algum dos filhos
	bool estaNoUltimoFilho = (idx == node->num_chaves);
	arvoreb_node_t *filho_esquerdo = loadFilhoFromFile(arv, node, idx);
	if(filho_esquerdo) {
		if(filho_esquerdo->num_chaves < MIN_CHAVES+1) {
			// se o filho da chave que encontramos não possui o mínimo de chaves, vamos preencher este filhos
			debug("Preenche a página %d para a remoção.\n", filho_esquerdo->page_num);
			fillNodeArvoreB(arv, node, idx);
		}
		free(filho_esquerdo);
	}
	// continua procurando para os filhos desse idx
	debug("estaNoUltimoFilho? %d\n", estaNoUltimoFilho);
	if(estaNoUltimoFilho && idx > node->num_chaves) {
		// foi retirado um filho
		prox_pagina = node->filhos[idx-1];
	}
	debug("Próxima página: %d\n", prox_pagina);
	node = loadNodeFromFile(arv, prox_pagina);
	bool result = removeNodeArvoreB(arv, node, id);
	free(node);
	return result;
}

/**
 * remove um elemento de um nó folha
 * @param idx  índice do elemento no nó da árvore
 */
void removeFromFolha(arvoreb_t *arv, arvoreb_node_t *node, int idx) {
	debug("Removendo a chave %d de um nó folha\n", node->chaves[idx].id);
	// move todos os ídices a direita dele para a esquerda
	int i;
	for(i=idx+1; i<node->num_chaves; i++) {
		node->chaves[i-1] = node->chaves[i];
	}
	// reduz uma chave
	node->num_chaves--;
	// salva no arquivo
	saveNodeToFile(arv, node);
}

/**
 * remove um elemento do nó da árvore que não é folha
 * @param idx  índice do elemento no nó da árvore
 */
void removeFromNonFolha(arvoreb_t *arv, arvoreb_node_t *node, int idx) {
	// não passei o id pelo argumento, mas é fácil resgatá-lo
	id_type id = node->chaves[idx].id;
	debug("Removendo a chave %d de uma não folha.\n", id);

	// para o filho esquerdo
	arvoreb_node_t *filho_esquerdo = loadFilhoFromFile(arv, node, idx);
	bool runExit = false;
	if(filho_esquerdo->num_chaves >= MIN_CHAVES+1) {
		runExit = true;
		arvoreb_elem_t pred = getPred(arv, node, idx);
		node->chaves[idx] = pred;
		saveNodeToFile(arv, node);
		removeNodeArvoreB(arv, filho_esquerdo, pred.id);
	}
	free(filho_esquerdo);
	if(runExit) {
		return ;
	}

	// para o filho direito
	arvoreb_node_t *filho_direito = loadFilhoFromFile(arv, node, idx+1);
	if(filho_direito->num_chaves >= MIN_CHAVES+1) {
		runExit = true;
		arvoreb_elem_t succ = getSucc(arv, node, idx);
		node->chaves[idx] = succ;
		saveNodeToFile(arv, node);
		removeNodeArvoreB(arv, filho_direito, succ.id);
	}
	free(filho_direito);
	if(runExit) {
		return ;
	}

	// se os filhos da direita e da esquerda possui menos de MIN_CHAVES
	mergeNodeArvoreB(arv, node, idx);
	filho_esquerdo = loadFilhoFromFile(arv, node, idx);
	removeNodeArvoreB(arv, filho_esquerdo, id);
	free(filho_esquerdo);
}

/**
 * obtém o maior elemento da subárvore da esquerda
 * @param  idx  índice do elemento no nó Node
 */
arvoreb_elem_t getPred(arvoreb_t *arv, arvoreb_node_t *node, int idx) {
	file_log("Chave %d rebaixada\n", node->chaves[idx].id);
	arvoreb_elem_t result;
	page_t next_page = node->filhos[idx];
	while(next_page != -1) {
		arvoreb_node_t *cur = loadNodeFromFile(arv, next_page);
		next_page = cur->filhos[cur->num_chaves];
		result = cur->chaves[cur->num_chaves-1];
		free(cur);
	}
	file_log("Chave %d promovida\n", result.id);
	return result;
}

/**
 * obtém o menor elemento da subárvore da direita
 * @param  idx  índice do elemento no nó Node
 */
arvoreb_elem_t getSucc(arvoreb_t *arv, arvoreb_node_t *node, int idx) {
	file_log("Chave %d rebaixada\n", node->chaves[idx].id);
	arvoreb_elem_t result;
	page_t next_page = node->filhos[idx+1];
	while(next_page != -1) {
		arvoreb_node_t *cur = loadNodeFromFile(arv, next_page);
		next_page = cur->filhos[0];
		result = cur->chaves[0];
		free(cur);
	}
	file_log("Chave %d promovida\n", result.id);
	return result;
}

/**
 * preenche o filho[idx] com algum dos filhos de Node que possui menos do que MIN_CHAVES
 * @param idx  um inteiro que identifica a página no disco
 */
void fillNodeArvoreB(arvoreb_t *arv, arvoreb_node_t *node, int idx) {
	debug("Fill da página %d\n", node->page_num);
	if(idx != 0) {
		arvoreb_node_t *filho_esquerdo = loadFilhoFromFile(arv, node, idx-1);
		if(filho_esquerdo->num_chaves >= MIN_CHAVES+1) {
			borrowFromPrev(arv, node, idx);
			free(filho_esquerdo);
			return ;
		}
		free(filho_esquerdo);
	}
	if(idx != node->num_chaves) {
		arvoreb_node_t *filho_direito = loadFilhoFromFile(arv, node, idx+1);
		if(filho_direito->num_chaves >= MIN_CHAVES+1) {
			borrowFromNext(arv, node, idx);
			free(filho_direito);
			return ;
		}
		free(filho_direito);
	}

	// se foi removido do meio da página, junta os filhos
	if(idx != node->num_chaves) {
		// último filho
		mergeNodeArvoreB(arv, node, idx);
	} else {
		// penúltimo filho
		mergeNodeArvoreB(arv, node, idx-1);
	}
}

void borrowFromPrev(arvoreb_t *arv, arvoreb_node_t *node, int idx) {
	// debug("borrowFromPrev da página %d com pg: %d e pg: %d\n", node->page_num, node->filhos[idx], node->filhos[idx-1]);
	file_log("Redistribuicao de chaves - entre as páginas irmas %d e %d\n", node->filhos[idx], node->filhos[idx-1]);
	arvoreb_node_t *filho_direito = loadFilhoFromFile(arv, node, idx);
	arvoreb_node_t *filho_esquerdo = loadFilhoFromFile(arv, node, idx-1);

	int i;
	for(i=filho_direito->num_chaves-1; i>=0; i--) {
		filho_direito->chaves[i+1] = filho_direito->chaves[i];
	}
	if(!filho_direito->is_folha) {
		for(i=filho_direito->num_chaves; i>=0; i--) {
			filho_direito->filhos[i+1] = filho_direito->filhos[i];
		}
	}
	filho_direito->chaves[0] = node->chaves[idx-1];
	if(!node->is_folha) {
		filho_direito->filhos[0] = filho_esquerdo->filhos[filho_esquerdo->num_chaves];
	}
	node->chaves[idx-1] = filho_esquerdo->chaves[filho_esquerdo->num_chaves-1];

	filho_direito->num_chaves++;
	filho_esquerdo->num_chaves--;

	saveNodeToFile(arv, node);
	saveNodeToFile(arv, filho_esquerdo);
	saveNodeToFile(arv, filho_direito);
	free(filho_esquerdo);
	free(filho_direito);
}

void borrowFromNext(arvoreb_t *arv, arvoreb_node_t *node, int idx) {
	// debug("borrowFromNext da página %d com pg: %d e pg: %d\n", node->page_num, node->filhos[idx], node->filhos[idx+1]);
	file_log("Redistribuicao de chaves - entre as páginas irmas %d e %d\n", node->filhos[idx], node->filhos[idx+1]);
	arvoreb_node_t *filho_esquerdo = loadFilhoFromFile(arv, node, idx);
	arvoreb_node_t *filho_direito = loadFilhoFromFile(arv, node, idx+1);

	filho_esquerdo->chaves[filho_esquerdo->num_chaves] = node->chaves[idx];
	if(!filho_esquerdo->is_folha) {
		filho_esquerdo->filhos[filho_esquerdo->num_chaves+1] = filho_direito->filhos[0];
	}
	node->chaves[idx] = filho_direito->chaves[0];
	int i;
	for(i=1; i<filho_direito->num_chaves; i++) {
		filho_direito->chaves[i-1] = filho_direito->chaves[i];
	}
	if(!filho_direito->is_folha) {
		for(i=0; i<=filho_direito->num_chaves; i++) {
			filho_direito->filhos[i-1] = filho_direito->filhos[i];
		}
	}
	filho_esquerdo->num_chaves++;
	filho_direito->num_chaves--;

	saveNodeToFile(arv, node);
	saveNodeToFile(arv, filho_esquerdo);
	saveNodeToFile(arv, filho_direito);
	free(filho_esquerdo);
	free(filho_direito);
}

/**
 * função que une idx com idx+1
 * @param idx  um inteiro que identifica a página no disco
 */
void mergeNodeArvoreB(arvoreb_t *arv, arvoreb_node_t *node, int idx) {
	debug("Merge de %d e %d\n", node->filhos[idx], node->filhos[idx+1]);
	arvoreb_node_t *filho_esquerdo = loadFilhoFromFile(arv, node, idx);
	arvoreb_node_t *filho_direito = loadFilhoFromFile(arv, node, idx+1);

	filho_esquerdo->chaves[MIN_CHAVES] = node->chaves[idx];
	int i;
	for(i=0; i<filho_direito->num_chaves; i++) {
		filho_esquerdo->chaves[i+MIN_CHAVES+1] = filho_direito->chaves[i];
	}
	if(!filho_esquerdo->is_folha) {
		for(i=0; i<=filho_direito->num_chaves; i++) {
			filho_esquerdo->filhos[i+MIN_CHAVES+1] = filho_direito->filhos[i];
		}
	}
	for(i=idx+1; i<node->num_chaves; i++) {
		node->chaves[i-1] = node->chaves[i];
	}

	for(i=idx+2; i<=node->num_chaves; i++) {
		node->filhos[i-1] = node->filhos[i];
	}
	filho_esquerdo->num_chaves += filho_direito->num_chaves+1;
	node->num_chaves--;
	filho_direito->num_chaves = 0; // esvazia o filho direito


	saveNodeToFile(arv, node);
	saveNodeToFile(arv, filho_esquerdo);
	saveNodeToFile(arv, filho_direito);
	free(filho_esquerdo);
	free(filho_direito);
}

/* ====================================================
   NÓS
   ==================================================== */
void initNodeArvoreB(arvoreb_node_t *node) {
	// zera completamente
	memset(node, 0, sizeof(arvoreb_node_t));
	// seta os filhos para -1
	int i;
	for(i=0; i<ORDEM; i++) {
		node->filhos[i] = -1;
	}
}

/**
 * cria e inicializa um Nó da árvore
 * @return precisa de free
 */
arvoreb_node_t *createNodeArvoreB() {
	arvoreb_node_t *result = malloc(sizeof(arvoreb_node_t));
	initNodeArvoreB(result);
	return result;
}

/* ====================================================
   DESALOCA DA MEMÓRIA
   ==================================================== */
void freeArvoreB(arvoreb_t *arv) {
	fclose(arv->fd);
	arv->fd = NULL;
	free(arv);
}

/* ====================================================
   IMPRIME A ÁRVORE
   ==================================================== */
void printArvoreB(arvoreb_t *arv) {
	file_log("Execucao de operacao para mostrar a arvore-B gerada:\n");
	section("IMPRIMINDO A ÁRVORE B");
	printf("       root => %d\n", arv->root);
	printf("  num_pages => %d\n", arv->num_pages);
	printf("empty_pages => ");
	// imprimindo lista de vazios
	page_t next_page = arv->empty_pages;
	while(next_page != -1) {
		printf("%d, ", next_page);
		arvoreb_node_t *node = loadNodeFromFile(arv, next_page);
		next_page = node->filhos[0];
		free(node);
	}
	printf("FIM\n");
	// imrpimindo nós
	printPagesArvoreB(arv, arv->root);
	printf("/* =============================	 */\n\n");
}

/**
 * imprime um nó da árvore recebendo a página no arquivo
 */
void printPagesArvoreB(arvoreb_t *arv, page_t page) {
	if(page == -1) {
		return ;
	}
	printf("\n");
	arvoreb_node_t *node = loadNodeFromFile(arv, page);
	// copia os filhos
	int i;
	printf("PAGINA: %d\n", node->page_num);
	printf("NUM_CHAVES: %d\n", node->num_chaves);
	printf("%s\n", (node->is_folha) ? "É FOLHA!" : "nao é folha");
	printf("\t\tFILHO ESQUERDO: %d\n", node->filhos[0]);
	for(i=0; i<node->num_chaves; i++) {
		printf("\t\tChave: %-2d => offset: %-2ld | FILHO: %d\n", node->chaves[i].id, node->chaves[i].offset, node->filhos[i+1]);
	}
	for(i=0; i<node->num_chaves+1; i++) {
		printPagesArvoreB(arv, node->filhos[i]);
	}
	free(node);
}

void deleteFileArvoreB() {
	remove(FILENAMEARVOREB);
}

/**
 * Use-a como se fosse dar um printf na tela
 * já salva no arquivo automaticamente
 * se DEBUG está ativado, imprime na tela também
 */
void file_log(char *str, ...) {
	debug("ARQUIVO LOG: ");
	FILE *fd = _fopen(FILENAMELOG, "a");
	va_list args;
	va_start(args, str);
	vfprintf(fd, str, args);
	#ifdef DEBUG
		vfprintf(stdout, str, args);
	#endif // DEBUG
	va_end(args);
	fclose(fd);
}
