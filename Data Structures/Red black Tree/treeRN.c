/*
    Integrantes:
        Felipe Silva Ganho
        Leonardo Loureiro de Almeida
*/

//inclusao de bibliotecas
#include "treeRN.h"

//cria artigo com seus respectivos campos
Artigo *criaArtigo(Artigo *artigo){
    artigo = malloc(sizeof(Artigo));
    printf(" Preencha os campos do artigo: ");
    printf("\n ID: ");
    scanf("%d", &(artigo->id));
    printf(" Ano: ");
    scanf("%d", &(artigo->ano));
    printf(" Autor: ");
    scanf(" %[^\n]s", artigo->autor);
    printf(" Titulo: ");
    scanf(" %[^\n]s", artigo->titulo);
    printf(" Revista: ");
    scanf(" %[^\n]s", artigo->revista);
    printf(" DOI: ");
    scanf(" %s", artigo->DOI);
    printf(" Palavra Chave: ");
    scanf(" %[^\n]s", artigo->palavraChave);
    return artigo;
}

//mostra dados do artigo
void mostrarArtigo(Artigo *artigo){
    printf("\n ID: %d \n", artigo->id);
    printf(" Ano: %d \n", artigo->ano);
    printf(" Autor: %s \n", artigo->autor);
    printf(" Titulo: %s \n", artigo->titulo);
    printf(" Revista: %s \n", artigo->revista);
    printf(" DOI: %s \n", artigo->DOI);
    printf(" Palavra Chave: %s \n", artigo->palavraChave);
}

//aloca memoria para um novo no da arvore rubro-negra
arvoreRN criaNoRN(Artigo *artigo, arvoreRN esq, arvoreRN dir, arvoreRN pai){
    arvoreRN p = malloc (sizeof (*p));
    p->artigo = artigo;
    p->esq = esq;
    p->dir = dir;
    p->pai = pai;
    return p;
}

//aloca memoria para as variaveis globias
void iniciaRN(void){
    noNullRN = criaNoRN(NULL, NULL, NULL, NULL);
    noNullRN->cor = BLACK;
    raiz = noNullRN;
}

//realiza rotacao a esquerda na arvore rubro-negra
arvoreRN rotacaoEsquerda(arvoreRN T, arvoreRN w){
    //T é o pivô, onde vira a raiz
    //w é a raiz no momento
    arvoreRN y = w->dir;
    w->dir = y->esq;
    if (y->esq != noNullRN)
        y->esq->pai = w;
    y->pai = w->pai;
    if (w->pai == noNullRN)
        T = y;
    else if (w == w->pai->esq)
        w->pai->esq = y;
    else
        w->pai->dir = y;
    y->esq = w;
    w->pai = y;
    return T;
}

//realiza rotacao a esquerda na arvore rubro-negra
arvoreRN rotacaoDireita(arvoreRN T, arvoreRN w){
    //T é o pivô, onde vira a raiz
    //w é a raiz no momento
    arvoreRN y = w->esq;
    w->esq = y->dir;
    if(y->dir != noNullRN)
        y->dir->pai = w;
    y->pai = w->pai;
    if(w->pai == noNullRN)
        T = y;
    else if(w == w->pai->esq)
        w->pai->esq = y;
    else
        w->pai->dir = y;
    y->dir = w;
    w->pai = y;
    return T;
}

//realiza correcao das cores apos a insercao
arvoreRN consertaInsereRN(arvoreRN T, arvoreRN w){
    arvoreRN tio;
    while(w->pai->cor == RED ){
        //insere na sub-arvore esquerda
        if(w->pai == w->pai->pai->esq) {
            tio = w->pai->pai->dir;
           //CASO 1
           //cor a direita do avo eh vermelho
            if(tio->cor == RED){
                w->pai->cor = BLACK;
                tio->cor = BLACK;
                w->pai->pai->cor = RED;
                w = w->pai->pai;
                
            }
            else{
                //CASO 2 = esquerda->direita
                //cor a direita do avo eh preto
                //desbalanceio na subarvore a esquerda do filho a direita
                if(w == w->pai->dir){
                    w = w->pai;
                    T = rotacaoEsquerda(T, w);
                }

                //CASO 3 = esquerda->esquerda
                else{
                    w->pai->cor = BLACK;
                    w->pai->pai->cor = RED;
                    T = rotacaoDireita(T, w->pai->pai );
                }
            }
        }
        else{
            //insere na subarvore a direita
            tio = w->pai->pai->esq;

            //CASO 1
            //cor a direita do avo eh vermelho
            if(tio->cor == RED){
                w->pai->cor = BLACK;
                tio->cor = BLACK;
                w->pai->pai->cor = RED;
                w = w->pai->pai;
            }
            else{

                //CASO 2 = direita->esquerda
                //cor a direita do avo é preto
                //desbalanceio na subarvore direita do filho a esquerda
                if(w == w->pai->esq){
                    w = w->pai;
                    T = rotacaoDireita(T, w);
                }

                //CASO 3 = direita->direita
                else{
                    w->pai->cor = BLACK;
                    w->pai->pai->cor = RED;
                    T = rotacaoEsquerda(T, w->pai->pai);}
            }
        }
    }
    //cor preta na raiz
    T->cor = BLACK;
    return T;
}

//insere um no na arvore rubro-negra
arvoreRN insereRN(arvoreRN w, Artigo *artigo){
    arvoreRN novo = criaNoRN (artigo, noNullRN, noNullRN, noNullRN);
    arvoreRN x = w;
    arvoreRN paix = noNullRN;

    //busca o pai do no novo
    while (x != noNullRN){
        paix = x;
        // verifica se ja existe o ID na arvore
        if(artigo->id == x->artigo->id){
            printf("ID ja existente!");
            return w;
        }
        else if(artigo->id < x->artigo->id)
            x = x->esq;
        else
            x = x->dir;
    }
    novo->pai = paix;

    //arvore vazia
    if (paix == noNullRN)
        w = novo;

    //depois buscar o pai do no novo , insere o id informado a esquerda
    else if (artigo->id < paix->artigo->id)
        paix->esq = novo;

    //depois buscar o pai do no novo , insere o id informado a direita
    else
        paix->dir = novo;

    novo->cor = RED;
    w =  consertaInsereRN(w, novo);
    printf("ID inserido com sucesso!");
    return w;
}

//retorna a altura arvore
int altura(arvoreRN w){
    //caso w seja nulo
    if (w == noNullRN)
        return 0;
    else{
        //pega a profundidade de cada sub-arvore
        int e = altura(w->esq);
        int d = altura(w->dir);

        //usa o maior entre as sub-árvores
        if (e > d)
            return (e + 1);
        else
            return (d + 1);
    }
}

//imprime no's por nivel
void auximprimeNivelRN(arvoreRN w, int nivel){
    //caso w seja nulo
    if (w == noNullRN)
        return;
    //caso o nível seja 1 verifica a cor e imprime
    if (nivel == 1){
        if(w->cor == BLACK)
            printf("[%d | Cor: BLACK] ", w->artigo->id);
        else
            printf("[%d | Cor: RED] ", w->artigo->id);
    }
    //caso contrário chama recursivamente a esquerda e direita de w
    else if (nivel > 1){
        auximprimeNivelRN(w->esq, nivel-1);
        auximprimeNivelRN(w->dir, nivel-1);
    }
}

//imprime a arvore por nivel
void imprimeNivelRN(arvoreRN w){
    printf("\n");
    int h = altura(w);
    for (int i=1; i<=h; i++){
        auximprimeNivelRN(w, i);
        printf("\n");
    }
}

//imprime a arvore em ordem
void imprimeEmOrdemRN(arvoreRN w){
    //caso o nó passado seja nulo
    if (w == noNullRN)
        return;
    //imprime a esquerda
    imprimeEmOrdemRN (w->esq);
    //caso a cor do nó passado seja negro
    if (w->cor == BLACK)
        printf ("Chave: %d | Cor: BLACK\n", w->artigo->id);
    else
        printf ("Chave: %d | Cor: RED\n", w->artigo->id);
    //imprime a direita
    imprimeEmOrdemRN (w->dir);
}

//retorna arvore mais a esquerda do filho a direita
arvoreRN sucessorRN(arvoreRN w){
    //no auxiliar para percorrer a arvore
    arvoreRN aux;
    //verifica se o no passado e nulo
    if (w->dir == noNullRN)
        return noNullRN;
    //faz o auxiliar receber o filho a direita do no w
    aux = w->dir;
    //percorre o caminho a esquerda do no auxiliar ate o menor
    while (aux->esq != noNullRN){
        aux = aux->esq;
    }
    return aux;
}

//conserta as cores apos remocao de um no na arvore rubro-negra
void consertaRemoveRN(arvoreRN T, arvoreRN w){
    arvoreRN x;
    while(w != T && w->cor == BLACK) {
        if(w == w->pai->esq){
            x = w->pai->dir;
            //caso 3.1 sendo w vermelho
            if(x->cor == RED){
                x->cor = BLACK;
                w->pai->cor = RED;
                rotacaoEsquerda(T, w->pai);
                x = w->pai->dir;
            }
            //caso 3.2 sendo w preto
            if(x->esq->cor == BLACK && x->dir->cor == BLACK){
                x->cor = RED;
                x = x->pai;
            }
            //caso 3.3 e 3.4
            else if(x->dir->cor == BLACK){
                x->esq->cor = BLACK;
                x->cor = RED;
                rotacaoDireita(T, x);
                x = w->pai->dir;
            }
            x->cor = w->pai->cor;
            w->pai->cor = BLACK;
            x->dir->cor = BLACK;
            rotacaoEsquerda(T, w->pai);
            w = T;
        }
        else{
            x = w->pai->esq;
            //caso 3.1 sendo w vermelho
            if(x->cor == RED){
                x->cor = BLACK;
                w->pai->cor = RED;
                rotacaoDireita(T, w->pai);
                x = w->pai->esq;
            }
            //caso 3.2 sendo w preto
            if(x->dir->cor == BLACK && x->esq->cor == BLACK){
                x->cor = RED;
                w = w->pai;
            }
            //caso 3.3 e 3.4
            else if(x->esq->cor == BLACK){
                x->dir->cor = BLACK;
                x->cor = RED;
                rotacaoEsquerda(T, x);
                x = w->pai->esq;
            }
            x->cor = w->pai->cor;
            w->pai->cor = BLACK;
            x->esq->cor = BLACK;
            rotacaoDireita (T, w->pai);
            w = T;
        }
    }
    w->cor = BLACK;
}

//remove um no da arvore rubro-negra
void removeRN(arvoreRN T, arvoreRN w){
    arvoreRN noRemove, filho;
    //caso o no buscado seja NULL
    if (w == noNullRN)
        return;
    //caso w possua nenhum ou 1 filho - determina substituo de w
    if (w->esq == noNullRN || w->dir == noNullRN)
        noRemove = w;
    else
        noRemove = sucessorRN(w); //aqui noRemove não tem flho a esquerda
    //determina filho do substituto
    if (noRemove->esq != noNullRN)
        filho = noRemove->esq;
    else
        filho = noRemove->dir;

    //acerta pai do filho de noRemove
    filho->pai = noRemove->pai;

    //caso w seja raiz
    if (noRemove->pai == noNullRN)
        T = filho;
    else if (noRemove == noRemove->pai->esq)
        noRemove->pai->esq = filho; //w é filho esquerdo
    else
        noRemove->pai->dir = filho; //w é filho direito

    //copia dados do noRemove para w
    if (w != noRemove)
        w->artigo->id = noRemove->artigo->id;

    //verifica se o a ser removido é raiz
    //se ele possuir algum filho, remove-o e a raiz recebe o filho trocando a cor pra negro
    //caso não possua filho, então recebe o nó nulo
    if (noRemove == raiz){
        if(noRemove->esq || noRemove->dir){
            free(noRemove->artigo);
            free(noRemove);
            raiz = T;
            raiz->cor = BLACK;
            return;
        }
        raiz = noNullRN;
        return;
    }
    //libera memória do nó a ser removido
    free(noRemove->artigo);
    free(noRemove);
    //realiza o ajuste da cor caso o nó removido seja negro
    if (noRemove->cor == BLACK)
        consertaRemoveRN(T, filho);
}

//busca por no com id
arvoreRN buscaRN (arvoreRN w, int id){
    //caso o no w passado seja null
    if (w == noNullRN)
        return noNullRN;
    //caso os id's sejam iguais
    if (w->artigo->id == id)
        return w;
    //caso o id passado seja menor do que do nó
    else if (id < w->artigo->id)
        return buscaRN(w->esq, id);
    //caso o id passado seja maior do que do nó
    else
        return buscaRN(w->dir, id);
}
