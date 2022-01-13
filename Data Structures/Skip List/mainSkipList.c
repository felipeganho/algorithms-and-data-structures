#include <stdio.h>
#include <stdlib.h>
#include "SkipList.c"

/*
    INTRODU��O
    A quest�o a ser resolvida � tornar mais eficiente a busca, inser��o e remo��o de uma lista ligada
por meio da estrutura de dados Skip List, que � uma estrutura de n�veis hier�rquicos e cada n�vel possui
uma lista simplesmente encadeada ordenada, sendo a primeira camada debaixo para cima a lista com todos os elementos
e as camadas superiores contendo a metade de elementos do n�vel abaixo.

    IMPLEMENTA��O
    A estrutura de dados utilizada � uma SkipList com cabe�a (estrutura SkipList) e possui diversos n�veis (estrutura Node)
que forma as hierarquias sendo cada uma lista ligada. H� tamb�m a estrutura Apontador onde armazenar� os elementos
anteriores para utiliza��o das fun��es de remover, inserir e buscar. As principais fun��es s�o a de busca, inser��o e
remo��o. Come�ando pela fun��o de BUSCA, ela verifica se j� existe o elemento a ser buscado e retorna 1 caso encontre,
sen�o retorna 0. A fun��o percorre todos os n�ves verificando se o pr�ximo elemento da hierarquia � nulo ou menor que
o valor passado como par�metro, caso seja verdade as duas condi��es, na pr�xima itera��o o elemento a ser comparado
ser� o pr�ximo elemento do n�vel. Como a primeira camada (0) cont�m a lista simplesmente encadeada completa, ent�o
concluimos que caso o elemento buscado esteja na estrutura, com certeza ele estar� nesse n�vel. Por fim,
verificamos se o par�metro imprimir passado na fun��o � 1 ou 0, caso seja 1 ele imprime todos os elementos anteriores ao
elemento buscado, sen�o retorna o valor da pr�pria fun��o. Seguindo, a fun��o de INSER��O usa a fun��o de busca para
verificar se existe o elemento na estrutura. Caso esteja, ent�o n�o h� a possibilidade de inserir e retorna 0. Sen�o,
� criado um novo n� pela fun��o createNodo. Como � passado a hierarquia como par�metro, concluimos a fun��o inserindo
o novo n� em todos os n�veis abaixo do que indicado, assim como o pr�prio reapontando o n� anterior salvo pela fun��o de
busca para o novo e do novo para o pr�ximo do anterior (inserindo no meio, como uma fun��o insere de uma lista ligada
simples) e retorna 1. Na fun��o de REMO��O, usa-se tamb�m a fun��o busca para verificar se existe o elemento pretendido
a ser removido ou n�o. Caso n�o encontre, retorna 0, sen�o a l�gica � feita de forma semelhante a fun��o de remover da
lista ligada, guardando o elemento anterior e fazendo ele apontar para o pr�ximo do elemento a ser removido para todos os
n�veis da estrutura. Conclui a fun��o liberando mem�ria do elemento removido e retorna 1. Foram acrescentados fun��es
como createAll para cria��o tanto da cabe�a e dos n�veis de forma imediata e um createHead para cria��o de apenas a cabe�a
da estrutura SkipList. A fun��o createApont cria todos os n�s para os n�veis, sendo que ela retorna uma estrutura apontador
que armazenar� todos os elementos anteriores ao elemento buscado. J� as fun��es de printList e printListH servem para
impress�o no visor, sendo uma para visualiza��o de todos os elementos da estrutura e a outra para um n�vel espec�fico
passado como par�metro da fun��o respectivamente. Al�m disso, foram criadas fun��es auxiliares como gravaSaidaStr,
gravaSaidaInt e gravaSaidaPrint para gravar no arquivo de sa�da. Portanto, com essas fun��es auxiliares, ser� impresso
tanto no dispositivo padr�o de sa�da (stdout) como no arquivo "saida.txt".

    CONCLUS�O
    Em uma Skip List com n elementos teremos uma complexidade O(log n) para busca, inser��o e remo��o.
    A maior dificuldade do trabalho pr�tico foi entender a estrutura para conseguir desenvolver o presente trabalho.

    BIBLIOGRAFIA
    https://www.inf.pucrs.br/~pinho/LaproI/Arquivos/Arquivos.htm
    http://linguagemc.com.br/arquivos-em-c-categoria-usando-arquivos/

*/

int main(){
    SkipList *skp;
    /* cria��o da cabe�a */
    skp=createHead();
    /* cria��o dos n�ves */
    createList(skp);
    /* cria��o da lista de ponteiros auxiliar para guardar o anteriror */
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

    /* ap�s a abertura, � verificado as instru��es contidas no arquvio
    podendo estar vazio ou n�o. Caso possua instru��es, ir� verificar de acordo com as necessidades pedidadas,
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
