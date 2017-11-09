#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Palavra{
	char str[30];
	int rpt, key;
}palavra;

void main()
{
	// <-- alocação do vetor de palavras
	palavra *vet;
	vet = (palavra*)malloc(15*sizeof(palavra));
	// -->

	char arquivo[30], str[30], op[2];
	int x, i=0, j=0, k, cont=0;

	FILE *arq;

	while(strcmp(op, "n") != 0)
	{
		printf("Arquivo: ");
		gets(arquivo);

		arq = fopen(arquivo, "r");

		x = fscanf(arq, "%s", str);
	    while(x != EOF)
	    {
	    	strcpy(vet[j].str, str);
	    	for(k=j-1; k>=0; k--)
	    	{
	    		if(strcmp(vet[j].str, vet[k].str) == 0)
	    			cont++;
	    	}	  
	    	vet[j].rpt = cont;  	
	    	vet[j].key = i;
	        x = fscanf(arq, "%s", str);
	        j++;
	        cont=0;
	    }

	    printf("Deseja abrir mais um arquivo? [s/n]");
	    gets(op);
	    i++;
	}
	strcpy(vet[j].str, "fim");

	i=0;

	while(strcmp(vet[i].str, "fim") != 0)
	{
		printf("%s %d %d\n", vet[i].str, vet[i].rpt, vet[i].key);
		i++;
	}
}