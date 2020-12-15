#include <stdio.h>

void imprimirVogais(int n, char x[n]) {
    int i;
    printf("Vogais da string: ");
    for(i=0; i < n; i++) {
        if(x[i] == 'a' || x[i] == 'e' || x[i] == 'i' || x[i] == 'o' || x[i] == 'u')
        {
            printf("%c ", x[i]);
        }
        if(x[i] == 'A' || x[i] == 'E' || x[i] == 'I' || x[i] == 'O' || x[i] == 'U')
        {
            printf("%c ", x[i]);
        }
    }
    printf("\n");
}

int main() {
	char string[] = "String Teste";
	imprimirVogais(sizeof(string), string);

	return 0;
}
