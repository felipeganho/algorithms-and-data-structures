/*
    Estudantes:
        Felipe Silva Ganho
        Leonardo Loureiro de Almeida
*/

//inclusao de bibliotecas
#include "huffman.h"

//inicia estrutura, realiza contagem de caracteres e simbolos
int preProcessamento(char *arquivo){
    //zerando variaveis globais para caso queira comprimir mais vezes
    nsimb=NSIMB=NBYTES=0;
    //variavel de contador
    int j;
    //inicia estrutura
    for(j=0; j<256; j++){
        no[j].dir=no[j].esq=no[j].pai=NULL;
        no[j].contagem=0;
        no[j].caracter=j;
        no[j].codigo=NULL;
    }

    //realiza contagem de cada caractere no arquivo pelo numero da tabela ASCII e
    //acrescenta mais 1 no numero de bytes
    //verifica se houve sucesso ao abrir o arquivo
    if((f=fopen(arquivo,"rb")) != NULL){
        //percorre ate o fim do arquivo
        while((j=fgetc(f)) != EOF){
            no[j].contagem++;
            NBYTES++;
        }
        //fecha arquivo
        fclose(f);
    }
    //caso nao tenha conseguido abrir o arquivo
    else return 1;

    //realiza a contagem de simbolos 
    for(j=0; j<256; j++){
        if(no[j].contagem != 0)
            NSIMB++;
    }

    //atribui o numero de simbolos a nsimb auxiliar
    nsimb=NSIMB;
    return 0;
}

//faz aux apontar pra no
void atribuiAux(){
    //percorre toda as estruturas fazendo cada aux apontar pra cada no
    for(int j=0; j<256; j++){
        aux[j] = &(no[j]);
    }
    return;
}

//constroi a arvore de huffman
void arvHuffman(){
    int menor = -1;     //guarda indice do menor
    int segundo = -1;   //guarda indice do segundo menor
    int auxConta;       //guarda conta
    int j;              //variavel auxiliar
    struct no *P;       //estrutura auxiliar

    //caso base
    if (nsimb == 1) return;

    //busca menor valor de ocorrencias 
    for(j=0; j<256; j++){
        //verifica se e nulo ou nao possui contagem
        if(aux[j] == NULL || aux[j]->contagem == 0) continue;
        //caso seja o primeiro a percorrer
        if (menor == -1){
            menor = j;
            auxConta = aux[j]->contagem;
        }         
        //verifica se a contagem atual e menor auxConta
        //e faz auxConta receber a contagem atual
        else{
            if (aux[j]->contagem < auxConta){
                menor = j;
                auxConta = aux[j]->contagem;
            }
        }
    }

    //busca segundo menor valor de ocorrencias
    for(j=0; j<256; j++){
        //verifica se e nulo, nao possui contagem ou e igual ao indice do menor
        if(aux[j] == NULL || aux[j]->contagem == 0 || j == menor) continue;
        //caso seja o primeiro a percorrer
        if (segundo == -1){
            segundo = j;
            auxConta = aux[j]->contagem;
        } 
        //verifica se a contagem atual e menor auxConta
        //e caso sim, faz auxConta receber a contagem atual
        else{
            if (aux[j]->contagem < auxConta){
                segundo = j;
                auxConta = aux[j]->contagem;
            }
        }
    }

    //realiza o arranjo do novo no
    P=(struct no *)malloc(sizeof(struct no));
    //aponta o pai dos dois menores 
    aux[menor]->pai = P;
    aux[segundo]->pai = P;
    //define a esquerda, direita e o pai do novo no
    P->esq = aux[menor];
    P->dir = aux[segundo];
    P->pai = NULL;
    //atribui 0 ao menor
    aux[menor]->bit = 0;
    //atribui 1 ao segundo menor
    aux[segundo]->bit = 1;
    //faz a contagem do novo no receber a soma do menor e segundo menor
    P->contagem = aux[menor]->contagem + aux[segundo]->contagem;
    //procura por outro menor
    aux[menor] = NULL;
    aux[segundo] = P;
    nsimb--;

    //nova chamada da funcao ate que reste apenas um simbolo
    arvHuffman();
}

//realiza a codificacao por meio de um pilha indo da folha ate a raiz
void codificar(){
    char pilha[100];
    char topo;
    int j;
    char *w;
    struct no *P;

    //percorre toda a estrutura
    for(j=0; j<256; j++){
        //verifica se nao possui contagem
        if (no[j].contagem == 0) continue;

        //faz P receber no
        P=(struct no *)(&(no[j]));
        topo=0;

        //percorre ate a raiz empilhando seu respectivo bit a pilha
        while(P->pai != NULL){
            pilha[topo] = P->bit;
            topo++;
            P = P->pai;
        }
        
        //quantidade de bits
        no[j].nbits = topo;
        //aloca espaco para o codigo 
        no[j].codigo = (char *)malloc((topo+1)*sizeof(char));
        w = no[j].codigo;
        topo--;

        //desempilha atribuindo o bit a variavel codigo da estrutura
        while(topo >= 0){
            *w=pilha[topo];
            topo--;
            w++;
        }
        *w=2;
    }
    return;
}

//imprime as informacoes de cada caracter - numero de aparicoes e a cadeia de codificacao
void imprimeInfos(){
    int j;
    char *w;
    int tamanhoComprimido = 0;
    printf("\n");
    printf("ELEMENTO n. ocorrencias : codigo binario\n");
    for(j=0; j<256; j++){
        if(no[j].contagem == 0) continue;
        //realiza a contagem do tamanho comprimido -> contagem * qtd. bits
        tamanhoComprimido += (no[j].contagem * no[j].nbits);
        //imprime o caracter e a frequencia
        printf("%3c %6d : ", j, no[j].contagem);
        w = no[j].codigo;
        //imprime todos os bits do codigo do caracter
        while(*w != 2){
            printf("%c", 48+(*w));
            w++;
        }
        printf("\n");
    }
    //numero de simbolos pela variavel global
    printf("Numero de Simbolos: %d\n", NSIMB);
    //numero de bytes pela variavel global
    printf("Numero de Bytes: %d\n", NBYTES);
    //tamanho comprimido
    printf("Tamanho comprimido: %d\n", tamanhoComprimido/8+1);
    printf("\n");
    return;
}

/* 
    escreve cabecalho do arquivo de saidas contendo:
        1)numero de bytes do arquivo de origem
        2)numero de caracteres distintos
        3)pares de simbolo e frequencia
*/
int escreveCabecalho(char *destino){
    int j, k;
    FILE *g;

    //1)escreve numero de bytes
    char *p=(char *)(&NBYTES);
    if ((g=fopen(destino,"wb")) == NULL) return 1;
    for(j=0; j<4; j++){
        fputc(*p,g);
        p++;
    }

    //2)escreve numero de simbolos
    p=(char *)(&NSIMB);
    fputc(*p,g);

    //3)escreve o simbolo e sua frequencia
    for(j=0; j<256; j++){
        if (no[j].contagem == 0) continue;
        fputc(j, g);
        p=(char *)(&(no[j].contagem));
        for(k=0; k<4; k++){
            fputc(*p,g);
            p++;
        }
    }
    fclose(g);
    return 0;
}

/* 
    comprime arquivo
        - varre caracter a caracter e usa a codificacao para escrever no arquivo comprimido
*/
int comprimir(char *origem, char *destino){
    unsigned char d=0;
    int x;
    char nbit=0;
    char *p;

    //abertura dos arquivos original e do comprimido
    if ((f=fopen(origem,"rb"))==NULL) return 1;
    if ((g=fopen(destino,"ab"))==NULL) return 2; //o cabecalho ja esta nesse arquivo

    //percorre ate o fim do arquivo
    while((x=fgetc(f)) != EOF){
        //variavel aux p recebe o codigo do caracter
        p=no[x].codigo;
        while(*p!=2){
            //caso o numero tenha completado 8 bits coloca no arquivo
            if(nbit==8){
                nbit=0;
                fputc(d,g);
                d=0;
            }
            //caso contrario altera e continua
            else{
                //utilizacao de mascara de bits para alteracao
                if(*p==1) d|=(1<<nbit);
                nbit++;
                p++;
            }
        }
    }
    //coloca no arquivo e fecha arquivos
    fputc(d,g);
    fclose(f);
    fclose(g);
    return 0;
}

/* 
    descomprime arquivo
        - realiza a leitura do cabecalho:
            NBYTES|NSIMB|(caracter, frequencia)
*/
int descomprimir(char *origem, char *destino){
    char *p;
    int j, k, n, m;
    unsigned char x, nbit;
    struct no *P,*Q;

    //abertura dos arquivos comprimido e que sera descomprimido
    if ((g=fopen(origem,"rb"))==NULL) return 1;
    if ((f=fopen(destino,"wb"))==NULL) return 2;

    //realiza leitura dos bytes - NBYTES
    p=(char *)(&n);
    for(j=0;j<4;++j){
        *p=(unsigned char)fgetc(g);
        p++;
    }
    NBYTES=n;

    //realiza a leitura do numero de simbolos
    NSIMB=nsimb=fgetc(g);

    //prepara a estrutura no
    for(j=0; j<256; j++){
        no[j].contagem=0;
        no[j].esq=no[j].dir=no[j].pai=NULL;
        no[j].caracter=j;
    }

    //para cada simbolo insere a sua frequencia
    for(j=0; j<NSIMB; j++){
        n=fgetc(g);
        p=(char *)(&m);
        for(k=0; k<4; k++){
            *p=(unsigned char)fgetc(g);
            p++;
        }
        no[n].contagem=m;
    }

    //constroi a arvore
    atribuiAux();
    arvHuffman();

    //realiza o apontamento da raiz da arvore
    j=0;
    while(no[j].contagem==0) j++;
    P=(struct no *)(&(no[j]));
    while(P->pai!=NULL) P=P->pai;

    //realiza a descompressao do arquivo
    j=0;
    x=fgetc(g);
    nbit=0;
    Q=P;
    while(j < NBYTES){
        //verifica se ha a esquerda
        if(Q->esq == NULL){
            fputc(Q->caracter, f);
            Q = P;
            j++;
        } 
        else{
            //caso o numero de bits seja 8
            if(nbit == 8){
                x = fgetc(g);
                nbit = 0;
            } 
            else{
                //testa valor de bit com deslocamento 
                //e faz Q receber a direita
                if(x&(1<<nbit)){
                    Q = Q->dir;
                }
                //caso contrario a esquerda
                else{
                    Q = Q->esq;
                }
                nbit++;
            }
        }
    }
    //fecha arquivos
    fclose(f);
    fclose(g);
    return 0;
}