#include <stdio.h>
#include <stdlib.h>
#include "SkipList.c"

/*
    INTRODUÇÃO
    A questão a ser resolvida é tornar mais eficiente a busca, inserção e remoção de uma lista ligada
por meio da estrutura de dados Skip List, que é uma estrutura de níveis hierárquicos e cada nível possui
uma lista simplesmente encadeada ordenada, sendo a primeira camada debaixo para cima a lista com todos os elementos
e as camadas superiores contendo a metade de elementos do nível abaixo.

    IMPLEMENTAÇÃO
    A estrutura de dados utilizada é uma SkipList com cabeça (estrutura SkipList) e possui diversos níveis (estrutura Node)
que forma as hierarquias sendo cada uma lista ligada. Há também a estrutura Apontador onde armazenará os elementos
anteriores para utilização das funções de remover, inserir e buscar. As principais funções são a de busca, inserção e
remoção. Começando pela função de BUSCA, ela verifica se já existe o elemento a ser buscado e retorna 1 caso encontre,
senão retorna 0. A função percorre todos os níves verificando se o próximo elemento da hierarquia é nulo ou menor que
o valor passado como parâmetro, caso seja verdade as duas condições, na próxima iteração o elemento a ser comparado
será o próximo elemento do nível. Como a primeira camada (0) contém a lista simplesmente encadeada completa, então
concluimos que caso o elemento buscado esteja na estrutura, com certeza ele estará nesse nível. Por fim,
verificamos se o parâmetro imprimir passado na função é 1 ou 0, caso seja 1 ele imprime todos os elementos anteriores ao
elemento buscado, senão retorna o valor da própria função. Seguindo, a função de INSERÇÃO usa a função de busca para
verificar se existe o elemento na estrutura. Caso esteja, então não há a possibilidade de inserir e retorna 0. Senão,
é criado um novo nó pela função createNodo. Como é passado a hierarquia como parâmetro, concluimos a função inserindo
o novo nó em todos os níveis abaixo do que indicado, assim como o próprio reapontando o nó anterior salvo pela função de
busca para o novo e do novo para o próximo do anterior (inserindo no meio, como uma função insere de uma lista ligada
simples) e retorna 1. Na função de REMOÇÃO, usa-se também a função busca para verificar se existe o elemento pretendido
a ser removido ou não. Caso não encontre, retorna 0, senão a lógica é feita de forma semelhante a função de remover da
lista ligada, guardando o elemento anterior e fazendo ele apontar para o próximo do elemento a ser removido para todos os
níveis da estrutura. Conclui a função liberando memória do elemento removido e retorna 1. Foram acrescentados funções
como createAll para criação tanto da cabeça e dos níveis de forma imediata e um createHead para criação de apenas a cabeça
da estrutura SkipList. A função createApont cria todos os nós para os níveis, sendo que ela retorna uma estrutura apontador
que armazenará todos os elementos anteriores ao elemento buscado. Já as funções de printList e printListH servem para
impressão no visor, sendo uma para visualização de todos os elementos da estrutura e a outra para um nível específico
passado como parâmetro da função respectivamente. Além disso, foram criadas funções auxiliares como gravaSaidaStr,
gravaSaidaInt e gravaSaidaPrint para gravar no arquivo de saída. Portanto, com essas funções auxiliares, será impresso
tanto no dispositivo padrão de saída (stdout) como no arquivo "saida.txt".

    CONCLUSÃO
    Em uma Skip List com n elementos teremos uma complexidade O(log n) para busca, inserção e remoção.
    A maior dificuldade do trabalho prático foi entender a estrutura para conseguir desenvolver o presente trabalho.

    BIBLIOGRAFIA
    https://www.inf.pucrs.br/~pinho/LaproI/Arquivos/Arquivos.htm
    http://linguagemc.com.br/arquivos-em-c-categoria-usando-arquivos/

*/

int main(){
    SkipList *skp;
    /* criação da cabeça */
    skp=createHead();
    /* criação dos níves */
    createList(skp);
    /* criação da lista de ponteiros auxiliar para guardar o anteriror */
    Apontador *apont=createApont();

    FILE *arq;
    int valor,hierarquia;
    char Linha[100],*result,strHierarquia[10],strValor[100];

    /* abre arquivo para leitura */
    arq = fopen("entrada.txt", "rt");
    if (arq == NULL)
    {
        printf("Nao e possivel abrir o arquivo");
        return 0;
    }

    /* após a abertura, é verificado as instruções contidas no arquvio
    podendo estar vazio ou não. Caso possua instruções, irá verificar de acordo com as necessidades pedidadas,
    como 'I' para inserir, 'A' para imprimir todos, e consequentemente as demais*/
    while(!feof(arq)){
        int i=0;
        result=fgets(Linha,100,arq);
        if(result){
            if(Linha[0]=='I'){
                for(i;Linha[2+i]!=' ';i++){
                    strValor[i]=Linha[2+i];
                }
                strValor[i]='\0';
                strHierarquia[0]=Linha[2+i+1];
                hierarquia=atoi(strHierarquia);
                valor=atoi(strValor);
                if(Insere(valor,hierarquia,skp)){
                    gravaSaidaStr("true\n");
                    printf("true\n");
                }
                else{
                    gravaSaidaStr("false\n");
                    printf("false\n");
                }
            }
            if(Linha[0]=='A'){
                printList(skp);
            }
            if(Linha[0]=='R'){
                for(i;Linha[2+i]!='\0';i++){
                    strValor[i]=Linha[2+i];
                }
                valor=atoi(strValor);
                removeList(valor,skp);
            }
            if(Linha[0]=='B'){
                for(i;Linha[2+i]!='\0';i++){
                    strValor[i]=Linha[2+i];
                }
                valor=atoi(strValor);
                searchList(valor,skp,apont,1);
            }
            if(Linha[0]=='P'){
                strHierarquia[0]=Linha[2];
                hierarquia=atoi(strHierarquia);
                printListH(skp,hierarquia);
            }
        }
    }
    fclose(arq);

    return 21;
}
