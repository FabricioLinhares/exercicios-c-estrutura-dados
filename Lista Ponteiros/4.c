#include <stdio.h>
#include <stdlib.h>

void inserirValor(int n, int array[n], int num) {
    int aux=0, aux2=0, indiceParou=0, i;
    for(i=0; i < n; i++)
    { 
        if(num > array[i] || i == n-1) {
            aux = array[i];
            array[i] = num;
            indiceParou = i;
            break;
        }
    }

    for(i=indiceParou+1; i < n; i++)
    {
        aux2 = aux;
        aux = array[i];
        array[i] = aux2;
    }
}

int main() {
	int c=0, querContinuar, novoValor, i;
	int *vetor = calloc(1, sizeof(int));
	do
    {
        int *vAux = realloc(vetor, (c+1) * sizeof(int));

        if(vAux != NULL) {
            vetor = vAux;
            printf("Digite o valor %d: ", ++c);
            scanf("%d", &novoValor);
            inserirValor(c, vetor, novoValor);
        }
        else {
            printf("Memória indisponivel para adicionar valor, saindo...");
            break;
        }

        printf("Quer continuar? Digite 0 para sair: ");
        scanf("%d", &querContinuar);
    } while (querContinuar);

    printf("\nVetor ordenado: ");
    for(i=0; i < c; i++)
    {
        printf("%d ", vetor[i]);
    }

	return 0;
}