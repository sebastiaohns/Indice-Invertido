#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Indice{
	int key, rpt;
	struct Indice *next;
}indice;

typedef struct Palavra{
	char str[30];
	indice *first;
}palavra;

typedef struct Tnode
{
    palavra *data;
    struct Tnode* l;
    struct Tnode* r;
}tnode;

int checaPalavra(tnode *t, palavra *plv, char* str, int key);
void mostrar(palavra *plv);

tnode* criar();

void inserir(tnode**, char*, int);
palavra *inserirStr(char *str, int key);

palavra *buscarStr(tnode *t, char *str);
int buscarIndice(palavra *plv, int key);

void incrementarRpt(palavra *plv, int key);
void incrementarIndice(palavra *plv, int key);

void abPreOrdem(tnode*);
void abPosOrdem(tnode*);
void abSimetrica(tnode*);
