#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavra.c"

void main()
{
	int x, y, i=0;
	char str[30], arquivo[50], op[2]="s";

	palavra *plv;

	tnode *t, *aux;
	t = criar();

	FILE *arq;

	while(strcmp(op, "n") != 0)
	{
		printf("Nome do arquivo: ");
		scanf("%s", arquivo);

		arq = fopen(arquivo, "r");

	    x = fscanf(arq, "%s", str);
	    while(x != EOF)
	    {
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

		printf("Deseja abrir outro arquivo? (s/n)");
		scanf("%s", op);
		i++;
	}

	abSimetrica(t);
}
