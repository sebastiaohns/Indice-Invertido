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

typedef struct Node{
	palavra *plv;
	struct Node *next;
}node;

typedef struct Lista{
	node *first;
}lista;

lista *criar();
void inserir(lista *l, char *str, int key);
palavra *inserirStr(char *str, int key);
int checaPalavra(palavra *plv, char* str, int key);
void inserirIndice(palavra *tmp, int key);
void mostrar(lista *l); 

lista *criar()
{
	lista *l;

	l = (lista*)malloc(sizeof(lista));

	if(l != NULL)
	{
		l->first = NULL;
		return l;
	}
	return NULL;
}

void inserir(lista *l, char *str, int key)
{
	if(l != NULL)
	{
		int flag=1;
		node *aux, *tmp;
		tmp = (node*)malloc(sizeof(node));

		if(l->first != NULL)
        {
            aux = l->first;
            while(aux->next != NULL && flag != 0)
            {
            	flag = checaPalavra(aux->plv, str, key);            	
                aux = aux->next;
            }

            if(flag == 1)
            {
            	flag = checaPalavra(aux->plv, str, key);  
            }

            if(flag == 1)
            {
            	tmp->plv = inserirStr(str, key);
            	tmp->next = NULL;
            	aux->next = tmp;
            }
        }
        else
        {
            tmp->plv = inserirStr(str, key);
            tmp->next = NULL;
            l->first = tmp;
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

int checaPalavra(palavra *plv, char* str, int key)
{
	int flag=1;
	indice *aux, *tmp;

	tmp = (indice*)malloc(sizeof(indice));

	if(strcmp(plv->str, str) == 0)
	{
		aux = plv->first;
		while(aux->next != NULL && flag != 0)
		{
			if(aux->key == key)
				flag = 0;
			aux = aux->next;
		}
		if(aux->key == key)
		{
			flag = 0;
		}
		
		if(flag == 0)
		{
			aux->rpt++;
		}
		else
		{
			tmp->key = key;
			tmp->rpt = 1;
			tmp->next = NULL;
			aux->next = tmp;
		}

		return 0;
	}
	return 1;
}

void mostrar(lista *l)
{
	if(l != NULL && l->first != NULL)
	{
		
		node *aux;
		palavra *auxPlv;
		indice *auxI;

		aux = l->first;

		while(aux != NULL)
		{
			auxPlv = aux->plv;

			auxI = auxPlv->first;
			while(auxI != NULL)
			{
				printf("<%d, %d> ", auxI->key, auxI->rpt);
				auxI = auxI->next;
			}

			printf(" %s\n", auxPlv->str);			
			aux = aux->next;
		}
	}
}

void main()
{
	int x, i=0;
	char str[30], arquivo[50], op[2]="s";

	lista *l, *aux;
	l = criar();

	FILE *arq;

	while(strcmp(op, "n") != 0)
	{
		printf("Nome do arquivo: ");
		scanf("%s", arquivo);

		arq = fopen(arquivo, "r");

	    x = fscanf(arq, "%s", str);
	    while(x != EOF)
	    {
	        inserir(l, str, i);
	        x = fscanf(arq, "%s", str);
	    }

		printf("Deseja abrir outro arquivo? (s/n)");
		scanf("%s", op);
		i++;
	}

	mostrar(l);
}