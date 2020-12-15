#include <stdio.h>
#include <stdlib.h>

#define FLAG "sairtexto\0"

int isFlag(char str[]) {
    int i=0;

    while(str[i] == FLAG[i]) {
        if (FLAG[i++] == '\0') return 1;
    }

    return 0;
}

char* getPhrase() {
    char keyPress, *aux;
    char *phrase = malloc(sizeof(char)*1);
    int i=0;

    while((keyPress = getchar()) != '\n') {
        phrase = realloc(phrase, sizeof(char)*(++i + 1));
        if(phrase == NULL) return NULL;
        phrase[i-1] = keyPress;
    }
    phrase[i] = '\0';
    return phrase;
}

void showPhrases(char **text, int p) {
    int i;

    printf("\n\n================\n");
    printf("Frases digitadas\n");
    printf("================\n\n");
    for(i=0; i < p; i++) {
        printf("[%d] %s\n", i, text[i]);
    }
}

void editText(char **text, int p) {
    int i, changeId=0;

    do
    {
        showPhrases(text, p);

        printf("\nDigite o id da frase que deseja editar (-1 para sair): ");
        scanf("%d", &changeId);
        fflush(stdin);
        if(changeId >= 0 && changeId < p) {
            printf("Frase escolhida: %s\n", text[changeId]);
            printf("Nova frase: ");
            
            char *phrase = getPhrase();
            if(phrase == NULL) {
                printf("Memória indisponivel para adicionar frase, saindo...");
                break;
            }
            else {
                free(text[changeId]);
                text[changeId] = phrase;
            }
        }
    } while (changeId >= 0);
}

int main()
{
    int index=0;
    char **text, **aux;
    text = calloc(sizeof(char), 1);
    printf("==================\n");
    printf(" Editor de Poemas\n");
    printf("==================\n");

    char *phrase;
    while(!isFlag(phrase = getPhrase()) || phrase == NULL) {
        aux = realloc(text, sizeof(char)*(index+1));

        if(aux == NULL) {
            printf("Memória indisponivel para adicionar frase, saindo...");
            break;
        }
        else {
            text = aux;
            text[index] = phrase;
        }

        index++;
    }

    editText(text, index);
}