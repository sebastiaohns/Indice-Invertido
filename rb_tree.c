#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include "indice_invertido.c"

enum type {RED,BLACK};

typedef struct Node{
    palavra *data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    enum type color;
}node;

void LeftRotate(node** T, node** x);
void RightRotate(node** T, node** x);

void insert_fixup(node** T, node** z);
node* insert(node* T, int key, char *str);
node* search(node* root, char *x);

void rbPreOrdem(node *t, listaArquivo *arq);
void rbPosOrdem(node *t, listaArquivo *arq);
void rbSimetrica(node *t, listaArquivo *arq);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    clock_t t0, tf;
    double tempo_gasto;

    int x, y, i=0;
    char str[255], arquivo[255], op[2]="s";

    node *rbTree = NULL, *aux;
    palavra *plv = NULL;
    listaArquivo *listaArq = criarListaArquivo();

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

            aux = search(rbTree, str);
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
                rbTree = insert(rbTree, i, str);
            }
            x = fscanf(arq, "%s", str);

        }

        tf = clock();

        printf("Deseja abrir outro arquivo? (s/n) ");
        scanf("%s", op);
        i++;
    }

    printf("\n-- Palavras inseridas na arvore -- \n\n");
    rbSimetrica(rbTree, listaArq);

    tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;
    printf("> Tempo gasto na insercao: %lf s\n", tempo_gasto);

    printf("\nDeseja fazer uma pesquisa? (s/n) ");
    scanf("%s", op);

    while(strcmp(op, "s") == 0)
    {
        printf("Palavra: ");
        scanf("%s", str);

        t0 = clock();

        aux = search(rbTree, str);

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

void LeftRotate(node** T, node** x)
{
    node* y = (*x)->right;
    (*x)->right = y->left;

    if(y->left!=NULL)
        y->left->parent = *x;

    y->parent = (*x)->parent;

    if((*x)->parent == NULL)
        *T = y;

    else if(*x == (*x)->parent->left)
        (*x)->parent->left = y;

    else
        (*x)->parent->right = y;

    y->left = *x;

    (*x)->parent = y;
}

void RightRotate(node** T, node** x)
{
    node* y = (*x)->left;
    (*x)->left = y->right;

    if(y->right!=NULL)
        y->right->parent = *x;

    y->parent = (*x)->parent;

    if((*x)->parent==NULL)
        *T = y;

    else if((*x)== (*x)->parent->left)
        (*x)->parent->left = y;

    else
        (*x)->parent->right = y;

    y->right = *x;
    (*x)->parent = y;
}

void insert_fixup(node** T, node** z)
{
    node* grandparent = NULL;
    node* parentpt = NULL;

    while(((*z)!=*T)&& ((*z)->color!= BLACK) && ((*z)->parent->color == RED))
    {
        parentpt = (*z)->parent;
        grandparent = (*z)->parent->parent;

        if(parentpt == grandparent->left)
        {
            node* uncle = grandparent->right;

            if(uncle!=NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                *z = grandparent;
            }

            else
            {
                if((*z) == parentpt->right)
                {
                    LeftRotate(T,&parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }

                RightRotate(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }

        else
        {
            node* uncle = grandparent->left;

            if(uncle!=NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                (*z) = grandparent;
            }

            else
            {
                if((*z) == parentpt->left)
                {
                    RightRotate(T,&parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }

                LeftRotate(T,&grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }
    }
    (*T)->color = BLACK;
}

node* insert(node* T, int key, char *str)
{
    node* z = (node*)malloc(sizeof(node));
    z->data = inserirStr(str, key);
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->color = RED;

    node* y = NULL;
    node* x = T;//root

    while(x!=NULL)
    {
        y = x;
        if(strcmp(z->data->str, x->data->str) < 0)
            x = x->left;

        else
            x = x->right;
    }
    z->parent = y;

    if(y==NULL)
        T = z;

    else if(strcmp(z->data->str, y->data->str) < 0)
        y->left = z;

    else
        y->right = z;

    insert_fixup(&T,&z);

    return T;
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

void rbPreOrdem(node *t, listaArquivo *arq)
{
    if(t != NULL)
    {
        mostrar(t->data, arq);
        rbPreOrdem(t->left, arq);
        rbPreOrdem(t->right, arq);
    }
}

void rbPosOrdem(node *t, listaArquivo *arq)
{
    if(t != NULL)
    {
        rbPosOrdem(t->left, arq);
        rbPosOrdem(t->right, arq);
        mostrar(t->data, arq);
    }
}

void rbSimetrica(node *t, listaArquivo *arq)
{
    if(t != NULL)
    {
        rbSimetrica(t->left, arq);
        mostrar(t->data, arq);
        rbSimetrica(t->right, arq);
    }
}
