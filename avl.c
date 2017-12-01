// C program to insert a node in AVL tree
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Indice{
	int key, rpt;
	struct Indice *next;
}indice;

typedef struct Palavra{
	char str[30];
	indice *first;
}palavra;

struct Node
{
    palavra *data;
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int max(int a, int b);

int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
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


struct Node* newNode(int key, char *str)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = inserirStr(str, key);
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int key, char *str)
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

void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%d %s %d %d\n", root->key, root->data->str, root->data->first->key, root->data->first->rpt);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
  struct Node *root = NULL;

  /* Constructing tree given in the above figure */
  root = insert(root, 10, "a");
  root = insert(root, 20, "b");
  root = insert(root, 30, "d");
  root = insert(root, 40, "e");
  root = insert(root, 50, "f");
  root = insert(root, 25, "c");

  /* The constructed AVL Tree would be
            30
           /  \
         20   40
        /  \     \
       10  25    50
  */

  printf("Preorder traversal of the constructed AVL"
         " tree is \n");
  preOrder(root);

  return 0;
}
