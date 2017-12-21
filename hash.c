#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include "indice_invertido.c"

typedef struct Node{
    palavra *data;
    struct Node *next;
}node;

int stringParaInt(char *string);
node *criar();
int hash(int v, int n);
node* insere(node *a, int v, char* str, int key);
void imprimir(node *aux);

int stringParaInt(char *string)
{
    int tamanho, primeira, segunda;

    tamanho =  strlen(string);
    primeira = string[0];
    segunda = string[1];
    int resultado = (tamanho * primeira) + segunda;

    return resultado;
}

node *criar()
{
	return NULL;
}

int hash(int v, int n)
{
  return (v%n);
}

node* insere(node *a, int v, char* str, int key)
{
	node *ant = NULL;   /*  aponta para node anterior  */
	node *p = a;

	while (p != NULL)   /*   faz uma busca na tabela     */
	{
		if (stringParaInt(p->data->str) == v)
		{
			printf("\n registro %d já existe",v);
			break;
		}
		ant = p;
		p = p->next;
	}

	if (p == NULL)   /* chave não encontrada ---> CRIANDO o NÓ -----------------*/
	{

		p = (node *)malloc(sizeof(node));
		p->data = inserirStr(str, key);
		p->next = NULL;

		if (ant == NULL)      /* inserção quando a node esta vazia */
		{
			a = p;
			return a;
		}
		else /* quando a node tem registros, verifica opção de inserção */
		{    /* se a op = i, insere no início, senão, insere no final    */
			ant->next = p;
			return ant;
		}
	}
}

void imprimir(node *aux)
{
    while(aux != NULL)
    {
        mostrar(aux->data);
        aux = aux->next;
    }
}

int main()
{
	setlocale(LC_ALL, "Portuguese");

	clock_t t0, tf;
    double tempo_gasto;

	int x, y, i=0, tam, k;
	char str[30], arquivo[50], op[2]="s";

	palavra *plv = NULL;

	FILE *arq;

	printf("Entre com o tamanho da tabela hash: ");
	scanf("%d", &tam);

    node *htable[tam];

    for(k=0; k<tam; k++)
    {
    	htable[k] = criar();
    }

	while(strcmp(op, "s") == 0)
	{
		printf("Nome do arquivo: ");
		scanf("%s", arquivo);

		t0 = clock();

		arq = fopen(arquivo, "r");

	    x = fscanf(arq, "%s", str);
	    while(x != EOF)
	    {
	        normalizar(str);

    		htable[hash(stringParaInt(str),tam)] = insere(htable[hash(stringParaInt(str),tam)], tam, str, i);
	        x = fscanf(arq, "%s", str);
	    }

	    tf = clock();

		printf("Deseja abrir outro arquivo? (s/n)");
		scanf("%s", op);
		i++;
	}

	for(k=0; k<tam; k++)
    {
    	imprimir(htable[k]);
    }

    tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;
    printf("Tempo gasto na inserção: %lf s\n", tempo_gasto);

	return 0;
}
