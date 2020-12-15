#include <stdio.h>

int calcularMedia(int x[10]) {
    int soma=0, *menor=&x[0], *maior=&x[0], i;
    for(i=0; i<10; i++) {
        soma += x[i];
        if(x[i] > *maior) maior = &x[i];
        if(x[i] < *menor) menor = &x[i];
    }
    printf("Menor valor: %d\t| Endereco: %d\n", *menor, menor);
    printf("Maior valor: %d\t| Endereco: %d\n", *maior, maior);
    printf("\n");
    printf("Endereco primeiro valor: %d\n", &x[0]);
    printf("Endereco ultimo valor: %d\n", &x[9]);
    return (soma/10);
}

int main() {
    int i;
	int v[10] = {1, 3, 2, 4, 7, 8, 9, 10, 13, 11};
	int media = calcularMedia(v);

	int *maior=&v[0], *menor=&v[0];
	for(i=0; i<10; i++) {
        if(v[i] > media) v[i] -= media;
        if(v[i] > *maior) maior = &v[i];
        if(v[i] < *menor) menor = &v[i];
	}

    printf("\n");
	printf("Endereco - Menor valor: %d\n", menor);
	printf("Endereco - Maior valor: %d\n", maior);

	return 0;
}