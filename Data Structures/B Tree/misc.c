#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdarg.h>

// define para dizer que este é o arquivo principal
#define __MISC_C__
#include "misc.h"

// 03.07.2015

// getchar que não deixa enter no buffer
char _getchar() {
	char str[5];
	fgets(str, 5, stdin);
	return *str;
}

// apenas imitando o pause de system()
void system_pause() {
	puts("Pressione ENTER para continuar. . .");
	_getchar();
}

// scanf que retorna uma string
void _scanf_s(char *str, int size) {
	int i = 0;
	fgets(str, size, stdin);
	while(!iscntrl(str[i])) {
		i++;
	}
	str[i] = '\0';
}

// fgets que corta o \n no final
char *_fgets(char *str, int size, FILE *stream) {
	int i = 0;
	char *result = fgets(str, size, stream);
	while(!iscntrl(str[i])) {
		i++;
	}
	str[i] = '\0';
	return result;
}

// scanf que retorna um int
int _scanf_int() {
	char str[11];
	fgets(str, 11, stdin);
	return atoi(str);
}

// scanf que retorna um double
double _scanf_double() {
	char str[11];
	fgets(str, 11, stdin);
	return atof(str);
}

// funcao malloc que fecha o programa assim que não há mais memória livre
void *_malloc(size_t size) {
	void *result = malloc(size);
	if(result == NULL) {
		fprintf(stderr, "_malloc: no memory available.\n");
		exit(1);
	}
	#ifdef CHECK_LEAK
		printf("MALLOC: %p => ", result);
	#endif // CHECK_LEAK
	return result;
}

// funcao calloc que fecha o programa assim que não há mais memória livre
void *_calloc(size_t count, size_t size) {
	void *result = calloc(count, size);
	if(result == NULL) {
		fprintf(stderr, "_calloc: no memory available.\n");
		exit(1);
	}
	#ifdef CHECK_LEAK
		printf("CALLOC: %p => ", result);
	#endif // CHECK_LEAK
	return result;
}

// funcao realloc que fecha o programa assim que não há mais memória livre
void *_realloc(void *ptr, size_t new_size) {
	void *result = realloc(ptr, new_size);
	if(result == NULL) {
		fprintf(stderr, "_realloc: no memory available.\n");
		exit(1);
	}
	#ifdef CHECK_LEAK
		if(ptr == NULL) {
			printf("REALLOC: %p =>", result);	
		} else if(ptr != result) {
			printf("REALLOCATION: %p => %p =>", ptr, result);
		}
	#endif // CHECK_LEAK
	return result;
}

void _free(void *ptr) {
	free(ptr);
	#ifdef CHECK_LEAK
		if(ptr != NULL) {
			printf("FREE: %p => ", ptr);
		}
	#endif // CHECK_LEAK
}

// funcao fopen que fecha o programa se fopen retornar NULL
FILE *_fopen(char *filename, char *mode) {
	FILE *result = fopen(filename, mode);
	if(result == NULL) {
		fprintf(stderr, "_fopen: error opening file '%s'\n", filename);
		exit(1);
	}
	return result;
}

// funcao fclose que testa se o ponteiro é nulo
int _fclose(FILE *stream) {
	if(stream == NULL) {
		return ;
	}
	return fclose(stream);
}

// funcao que retorna o tamanho de um arquivo
long int _file_size(FILE *file) {
	if(file == NULL) {
		return 0;
	}
	fseek(file, 0, SEEK_END);
	long int result = ftell(file);
	rewind(file);
	return result;
}

// funcao que retorna true ou false se o arquivo existe, retorna um dos três defines
char file_exists(char const *path_file) {
	struct stat status;
	if(stat(path_file, &status) != 0) {
		return FILE_NOT_FOUND;
	}
	if(S_ISDIR(status.st_mode)) {
		return IS_DIR;
	}
	return IS_FILE;
}

// remove um diretorio não vazio por completo
int remove_directory(const char *path) {
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;
   if(d) {
      struct dirent *p;
      r = 0;
      while(!r && (p=readdir(d))) {
          int r2 = -1;
          char *buf;
          size_t len;
          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if(!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
             continue;
          }
          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);
          if(buf) {
             struct stat statbuf;
             snprintf(buf, len, "%s/%s", path, p->d_name);
             if (!stat(buf, &statbuf)) {
                if (S_ISDIR(statbuf.st_mode)) {
                   r2 = remove_directory(buf);
                } else {
                   r2 = unlink(buf);
                }
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }
   if(!r) {
      r = rmdir(path);
   }
   return r;
}

#ifndef __WIN32
#include <termios.h>
// obtem comandos do teclado sem armazenar buffer
void setBufferedInput(bool enable) {
	static bool enabled = true;
	static struct termios old;
	struct termios new;

	if (enable && !enabled) {
		// restore the former settings
		tcsetattr(STDIN_FILENO,TCSANOW,&old);
		// set the new state
		enabled = true;
	} else if (!enable && enabled) {
		// get the terminal settings for standard input
		tcgetattr(STDIN_FILENO,&new);
		// we want to keep the old setting to restore them at the end
		old = new;
		// disable canonical mode (buffered i/o) and local echo
		new.c_lflag &=(~ICANON & ~ECHO);
		// set the new settings immediately
		tcsetattr(STDIN_FILENO,TCSANOW,&new);
		// set the new state
		enabled = false;
	}
}
#endif

// apaga o conteudo da tela
void clearScreen() {
	#ifdef __WIN32
		system("cls");
	#else
		printf("\033[2J");
		printf("\033[H");
	#endif
}

// esconde o cursor
void hide_cursor() {
	printf("\033[?25l");
}

// mostra o cursor dps de escondido
void show_cursor() {
	printf("\033[?25h");
}

// devolve em segundos o tempo passado de starthere = true e starthere = false
float timediff(bool starthere) {
	static clock_t t;
	if(starthere == 1) {
		t = clock();
		return 0;
	}
	t = clock() - t;
	return ((float)t) / CLOCKS_PER_SEC;
}

// funcao boa para debug, imprime strings verticalmente
int printfVerticaly(char *str) {
	printf("===================\n");
	printf("Imprimindo verticalmente: '%s'\n", str);
	int i = 0;
	while(str[i]) {
		printf("char %2d: '%c', %d\n", i, str[i], str[i]);
		i++;
	}
	printf("==================\n");
	return strlen(str);
}

// cria uma seção para facilitar o debug da saida
void section(char *str, ...) {
	printf("/* =============================\n");
	va_list args;
	va_start(args, str);
	printf("   ");
	vprintf(str, args);
	printf("\n");
  va_end(args);
	printf("   ============================= */\n");
}
