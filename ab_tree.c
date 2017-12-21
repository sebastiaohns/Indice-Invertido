#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include "indice_invertido.c"

typedef struct Tnode
{
    palavra *data;
    struct Tnode* l;
    struct Tnode* r;
}tnode;

tnode* criar();

void inserir(tnode**, char*, int);

void abPreOrdem(tnode*, listaArquivo *arq);
void abPosOrdem(tnode*, listaArquivo *arq);
void abSimetrica(tnode *t, listaArquivo *arq);

palavra *buscarStr(tnode *t, char *str);
tnode *buscar(tnode *t, char *str);

void main()
{
    setlocale(LC_ALL, "Portuguese");

    clock_t t0, tf;
    double tempo_gasto;

	int x, y, i=0;
	char str[255], arquivo[255], op[2]="s";

	palavra *plv;
	tnode *t, *aux;
	listaArquivo *listaArq = criarListaArquivo();
	t = criar();

	FILE *arq;

    printf("-- Leitura do arquivo --\n\n");

	while(strcmp(op, "n") != 0)
	{
		printf("Nome do arquivo: ");
		scanf("%s", arquivo);
		inserirArquivo(listaArq, arquivo, i);

        t0 = clock();

		arq = fopen(arquivo, "r");
	    x = fscanf(arq, "%s", str);
	    while(x != EOF)
	    {
	        normalizar(str);
	        plv = buscarStr(t, str);
	        if(plv != NULL)
            {
                y = buscarIndice(plv, i);
                if(y == 1)
                {
                    incrementarRpt(plv, i);
                }
                else
                {
                    incrementarIndice(plv, i);
                }
            }
            else
            {
                inserir(&t, str, i);
            }
	        x = fscanf(arq, "%s", str);

	    }
        tf = clock();

		printf("Deseja abrir outro arquivo? (s/n) ");
		scanf("%s", op);
		i++;
	}

    printf("\n-- Palavras inseridas na arvore -- \n\n");
	abSimetrica(t, listaArq);

    tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;
    printf("> Tempo gasto na insercao: %lf s\n", tempo_gasto);

    printf("\nDeseja fazer uma pesquisa? (s/n) ");
    scanf("%s", op);

    while(strcmp(op, "s") == 0)
    {
        printf("Palavra: ");
        scanf("%s", str);

        t0 = clock();

        aux = buscar(t, str);

        tf = clock();

        if(aux != NULL)
        {
            tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;
            printf("\n");
            mostrar(aux->data, listaArq);
            printf("> Palavra encontrada em: %lf s\n\n", tempo_gasto);
        }
        else
        {
            printf("\n> Palavra nao encontrada!\n\n");
        }

        printf("Deseja fazer outra pesquisa? (s/n)");
        scanf("%s", op);
    }
}

tnode* criar()
{
    return NULL;
}

void inserir(tnode** t, char *str, int key)
{
    if(*t == NULL)
    {
        *t = (tnode*)malloc(sizeof(tnode));
        (*t)->r = NULL;
        (*t)->l = NULL;

        palavra *aux;

        aux = (palavra*)malloc(sizeof(palavra));
        strcpy(aux->str, str);

        (*t)->data = inserirStr(str, key);
    }
    else
    {
        if(strcmp((*t)->data->str, str) >= 0)
        {
            inserir(&(*t)->r, str, key);
        }
        if(strcmp((*t)->data->str, str) < 0)
        {
            inserir(&(*t)->l, str, key);
        }
    }
}

void abPreOrdem(tnode *t, listaArquivo *arq)
{
    if(t != NULL)
    {
        mostrar(t->data, arq);
        abPreOrdem(t->l, arq);
        abPreOrdem(t->r, arq);
    }
}

void abPosOrdem(tnode *t, listaArquivo *arq)
{
    if(t != NULL)
    {
        abPosOrdem(t->l, arq);
        abPosOrdem(t->r, arq);
        mostrar(t->data, arq);
    }
}

void abSimetrica(tnode *t, listaArquivo *arq)
{
    if(t != NULL)
    {
        abSimetrica(t->l, arq);
        mostrar(t->data, arq);
        abSimetrica(t->r, arq);
    }
}

palavra *buscarStr(tnode *t, char *str)
{
    if(t == NULL)
        return NULL;
    if(strcmp(t->data->str, str) == 0)
        return t->data;
    if (strcmp(t->data->str, str) < 0)
       return buscarStr(t->l, str);
    else
       return buscarStr(t->r, str);
}

tnode *buscar(tnode *t, char *str)
{
    if(t == NULL)
        return NULL;
    if(strcmp(t->data->str, str) == 0)
        return t;
    if (strcmp(t->data->str, str) < 0)
       return buscar(t->l, str);
    else
       return buscar(t->r, str);
}
