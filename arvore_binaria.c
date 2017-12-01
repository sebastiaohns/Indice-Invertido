#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arvore_binaria.h"


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

palavra *inserirStr(char *str, int key)
{
	palavra *plv;
	plv = (palavra*)malloc(sizeof(palavra));

	if(plv != NULL)
	{
		strcpy(plv->str, str);

		indice *tmp;
		tmp = (indice*)malloc(sizeof(indice));

		tmp->key = key;
		tmp->rpt = 1;
		tmp->next = NULL;
		plv->first = tmp;

        return plv;
	}
	return NULL;
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

int buscarIndice(palavra *plv, int key)
{
    indice *aux;
    aux = plv->first;
    while(aux != NULL)
    {
        if(aux->key == key)
        {
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

void incrementarRpt(palavra *plv, int key)
{
    if(plv != NULL)
    {
        indice *aux;
        aux = plv->first;
        while(aux != NULL)
        {
            if(aux->key == key)
            {
                aux->rpt++;
            }
            aux = aux->next;
        }
    }
}

void incrementarIndice(palavra *plv, int key)
{
    if(plv != NULL)
    {
        indice *aux, *tmp;

        tmp = (indice*)malloc(sizeof(indice));
        tmp->key = key;
        tmp->rpt = 1;
        tmp->next = NULL;

        aux = plv->first;
        while(aux->next != NULL)
        {
            aux = aux->next;
        }

        aux->next = tmp;
    }
}


/*
 * FUNÇÕES DE MOSTRAR A ARVORE
 */


void abPreOrdem(tnode *t)
{
    if(t != NULL)
    {
        mostrar(t->data);
        abPreOrdem(t->l);
        abPreOrdem(t->r);
    }
}

void abPosOrdem(tnode *t)
{
    if(t != NULL)
    {
        abPosOrdem(t->l);
        abPosOrdem(t->r);
        printf("%s ", t->data->str);
    }
}

void abSimetrica(tnode *t)
{
    if(t != NULL)
    {
        abSimetrica(t->l);
        mostrar(t->data);
        abSimetrica(t->r);
    }
}

void mostrar(palavra *plv)
{
	if(plv != NULL && plv->first != NULL)
	{
	    indice *aux;
        aux = plv->first;
        while(aux != NULL)
        {
            printf("<%d, %d> ", aux->key, aux->rpt);
            aux = aux->next;
        }

        printf(" %s\n", plv->str);
	}
}


/*
 * FUNÇÃO PARA NORMALIZAR UMA STRING
 */


void normalizar(char *p)
{
    char *src = p, *dst = p;

    while (*src)
    {
       if (ispunct((unsigned char)*src))
       {
          /* Skip this character */
          src++;
       }
       else if (isupper((unsigned char)*src))
       {
          /* Make it lowercase */
          *dst++ = tolower((unsigned char)*src);
          src++;
       }
       else if (src == dst)
       {
          /* Increment both pointers without copying */
          src++;
          dst++;
       }
       else
       {
          /* Copy character */
          *dst++ = *src++;
       }
    }

    *dst = 0;
}
