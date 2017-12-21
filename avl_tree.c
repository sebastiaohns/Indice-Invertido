#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include "indice_invertido.c"

typedef struct Node{
    palavra *data;
    int key;
    struct Node *left;
    struct Node *right;
    int height;
}node;

int height(node*);
int max(int, int);
int getBalance(node*);

node* newNode(int, char*);

node *rightRotate(node*);
node *leftRotate(node*);

node* insert(node*, int, char*);
node* search(node* root, char *x);

void avlPreOrdem(node *t, listaArquivo *arq);
void avlPosOrdem(node *t, listaArquivo *arq);
void avlSimetrica(node *t, listaArquivo *arq);

int main()
{
	setlocale(LC_ALL, "Portuguese");

    clock_t t0, tf;
    double tempo_gasto;

	int x, y, i=0;
	char str[255], arquivo[255], op[2]="s";

	node *avlTree = NULL, *aux;
	palavra *plv = NULL;
	listaArquivo *listaArq = criarListaArquivo();

	FILE *arq;

    printf("-- Leitura do arquivo --\n\n");

	while(strcmp(op, "s") == 0)
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
	        aux = search(avlTree, str);
            if(aux != NULL)
            {
                y = buscarIndice(aux->data, i);
                if(y == 1)
                {
                    incrementarRpt(aux->data, i);
                }
                else
                {
                    incrementarIndice(aux->data, i);
                }
            }
            else
            {
                avlTree = insert(avlTree, i, str);
            }
	        x = fscanf(arq, "%s", str);

	    }

        tf = clock();

		printf("Deseja abrir outro arquivo? (s/n) ");
		scanf("%s", op);
		i++;
	}

    printf("\n-- Palavras inseridas na arvore -- \n\n");
	avlSimetrica(avlTree, listaArq);

    tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;
    printf("> Tempo gasto na inserção: %lf s\n", tempo_gasto);

    printf("\nDeseja fazer uma pesquisa? (s/n) ");
    scanf("%s", op);

    while(strcmp(op, "s") == 0)
	{
	    printf("Palavra: ");
        scanf("%s", str);

        t0 = clock();

        aux = search(avlTree, str);

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

  return 0;
}

int height(node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int getBalance(node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

node* newNode(int key, char *str)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = inserirStr(str, key);
    tmp->key = key;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->height = 1;
    return(tmp);
}

node *rightRotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

node *leftRotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

node* insert(node* node, int key, char *str)
{
    if (node == NULL)
        return(newNode(key, str));

    if (strcmp(str, node->data->str) < 0)
        node->left  = insert(node->left, key, str);
    else if (strcmp(str, node->data->str) > 0)
        node->right = insert(node->right, key, str);
    else
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && strcmp(str, node->left->data->str) < 0)
        return rightRotate(node);

    if (balance < -1 && strcmp(str, node->right->data->str) > 0)
        return leftRotate(node);

    if (balance > 1 && strcmp(str, node->left->data->str) > 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(str, node->right->data->str) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

node* search(node* root, char *x)
{
    if(root==NULL || strcmp(root->data->str, x) == 0)
        return root;

    if(strcmp(root->data->str, x) > 0)
       return  search(root->left,x);
    else
        return search(root->right,x);
}

void avlPreOrdem(node *t, listaArquivo *arq)
{
    if(t != NULL)
    {
        mostrar(t->data, arq);
        avlPreOrdem(t->left, arq);
        avlPreOrdem(t->right, arq);
    }
}

void avlPosOrdem(node *t, listaArquivo *arq)
{
    if(t != NULL)
    {
        avlPosOrdem(t->left, arq);
        avlPosOrdem(t->right, arq);
        mostrar(t->data, arq);
    }
}

void avlSimetrica(node *t, listaArquivo *arq)
{
    if(t != NULL)
    {
        avlSimetrica(t->left, arq);
        mostrar(t->data, arq);
        avlSimetrica(t->right, arq);
    }
}
