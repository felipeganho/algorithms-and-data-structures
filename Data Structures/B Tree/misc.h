#ifndef __MISC_H__
#define __MISC_H__

// #define CHECK_LEAK

char _getchar(); // getchar que não deixa enter no buffer
void system_pause(); // apenas imitando o pause de system()
void _scanf_s(char *str, int size); // scanf que retorna uma string
char *_fgets(char *str, int size, FILE *stream); // fgets que corta o \n no final
int _scanf_int(); // scanf que retorna um int
double _scanf_double(); // scanf que retorna um double
void *_malloc(size_t size); // funcao malloc que fecha o programa assim que não há mais memória livre
void *_calloc(size_t count, size_t size); // funcao calloc que fecha o programa assim que não há mais memória livre
void *_realloc(void *ptr, size_t new_size); // funcao realloc que fecha o programa assim que não há mais memória livre
int _fclose(FILE *stream); // funcao fclose que testa se o ponteiro é nulo
FILE *_fopen(char *filename, char *mode); // funcao fopen que fecha o programa se fopen retornar NULL
long int _file_size(FILE *file); // funcao que retorna o tamanho de um arquivo

#define FILE_NOT_FOUND 0
#define IS_FILE 1
#define IS_DIR 2
char file_exists(char const *str); // funcao que retorna true ou false se o arquivo existe, retorna um dos três defines
int remove_directory(const char *path); // remove um diretorio não vazio por completo

void setBufferedInput(bool enable); // obtem comandos do teclado sem armazenar buffer
void clearScreen(); // apaga o conteudo da tela
void hide_cursor(); // esconde o cursor
void show_cursor(); // mostra o cursor dps de escondido
float timediff(bool starthere); // devolve em segundos o tempo passado de starthere = true e starthere = false
int printfVerticaly(char *str); // funcao boa para debug, imprime strings verticalmente
void section(char *str, ...); // cria uma seção para facilitar o debug da saida

// troca as funções de alocação de memória, menos no arquivo .c
#ifndef __MISC_C__
	#ifdef CHECK_LEAK
		#define malloc(x)     _malloc(x);     printf("ALLOC_LINE: %d, FILE: %s\n", __LINE__, __FILE__);
		#define realloc(x, y) _realloc(x, y); printf("ALLOC_LINE: %d, FILE: %s\n", __LINE__, __FILE__);
		#define calloc(x, y)  _calloc(x, y);  printf("ALLOC_LINE: %d, FILE: %s\n", __LINE__, __FILE__);
		#define free(x)       _free(x);       printf("FREE_LINE: %d, FILE: %s\n", __LINE__, __FILE__);
	#else
		#define malloc _malloc
		#define realloc _realloc
		#define calloc _calloc
		#define free _free
	#endif // CHECK_LEAK
#endif

// definindo a função debug que faz a msma coisa que o printf
#ifdef DEBUG
	#define debug(str, ...) printf(str, ##__VA_ARGS__);
#else
	#define debug(str, ...) ;
#endif // DEBUG

#endif
