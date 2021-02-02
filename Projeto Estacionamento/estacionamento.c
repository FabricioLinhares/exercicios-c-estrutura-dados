#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define LIMITE_VAGAS 6
#define QUANTIDADE_FUNCIONARIOS 4

#define PRECO_HORA 12
#define BUDGET 300

typedef struct manobrista {
    char nome;
    int id;
    int idade;
    struct manobrista *prox;
} manobrista;

typedef struct carro {
    char *placa;
    int hora;
    struct carro *prox;
} carro;

typedef struct carro2 {
    char *placa;
    struct carro2 *ant;
    struct carro2 *prox;
} carro2;

typedef struct registrario { 
    int tipo;
    char *info;
    struct registrario *prox;
} registrario;

typedef struct buscaCarro {
    char *placa;
    struct buscaCarro *pai;
    struct buscaCarro *proxE;
    struct buscaCarro *proxD;
} buscaCarro;

int tempo, dinheiro=0, veiculosEstacionados=0, manobras1=0, manobras2=0;
manobrista *funcionario;
buscaCarro *arvoreCarros;

manobrista* criarFuncionarios(int quantidade) {
    manobrista *inicio, *ultimo, *novo;
    int i=0, letraAtual = 90; // 'Z'

    inicio = malloc(sizeof(manobrista));
    inicio->nome = (char) letraAtual--;
    inicio->idade = rand() % 47 + 18;
    inicio->id = i;

    ultimo = inicio;

    for(i=1; i < quantidade; i++) {
        novo = malloc(sizeof(manobrista));
        novo->nome = (char) letraAtual--;
        novo->idade = rand() % 47 + 18;
        novo->id = i;

        ultimo->prox = novo;
        ultimo = novo;
    }

    ultimo->prox = inicio;

    return inicio;
}

void ordenarFuncNome() {
    manobrista *pivo, *inicio, *ordenado, *inicioOrdenado, *final;
    inicio = funcionario->prox;
    final = funcionario;        

    inicioOrdenado = funcionario;

    funcionario->prox = NULL;
    funcionario = inicio;

    int i=0;

    while (funcionario != final) {
        pivo = funcionario;
        funcionario = funcionario->prox;
        ordenado = inicioOrdenado;

        if(pivo->nome < inicioOrdenado->nome) {
            pivo->prox = inicioOrdenado;
            inicioOrdenado = pivo;
        }
        else {
            while ((ordenado->prox != NULL) && (ordenado->prox->nome < pivo->nome))
                ordenado = ordenado->prox;

            if(ordenado->prox == NULL) {
                ordenado->prox = pivo;
                pivo->prox = NULL;
            }
            else {
                pivo->prox = ordenado->prox;
                ordenado->prox = pivo;
            }
        }
    }

    while (ordenado->prox != NULL)
        ordenado = ordenado->prox;

    ordenado->prox = inicioOrdenado;

    funcionario = inicioOrdenado;
}

void ordenarFuncId() {
    manobrista *pivo, *inicio, *ordenado, *inicioOrdenado, *final;
    inicio = funcionario->prox;
    final = funcionario;
    inicioOrdenado = funcionario;

    funcionario->prox = NULL;
    funcionario = inicio;

    int i=0;

    while (funcionario != final) {
        pivo = funcionario;
        funcionario = funcionario->prox;
        ordenado = inicioOrdenado;

        if(pivo->id < inicioOrdenado->id) {
            pivo->prox = inicioOrdenado;
            inicioOrdenado = pivo;
        }
        else {
            while ((ordenado->prox != NULL) && (ordenado->prox->id < pivo->id))
                ordenado = ordenado->prox;

            if(ordenado->prox == NULL) {
                ordenado->prox = pivo;
                pivo->prox = NULL;
            }
            else {
                pivo->prox = ordenado->prox;
                ordenado->prox = pivo;
            }
        }
    }

    while (ordenado->prox != NULL)
        ordenado = ordenado->prox;

    ordenado->prox = inicioOrdenado;

    funcionario = inicioOrdenado;
}

void ordenarFuncIdade() {
    manobrista *pivo, *inicio, *ordenado, *inicioOrdenado, *final;
    inicio = funcionario->prox;
    final = funcionario;
    inicioOrdenado = funcionario;

    funcionario->prox = NULL;
    funcionario = inicio;

    int i=0;

    while (funcionario != final) {
        pivo = funcionario;
        funcionario = funcionario->prox;
        ordenado = inicioOrdenado;

        if(pivo->idade < inicioOrdenado->idade) {
            pivo->prox = inicioOrdenado;
            inicioOrdenado = pivo;
        }
        else {
            while ((ordenado->prox != NULL) && (ordenado->prox->idade < pivo->idade))
                ordenado = ordenado->prox;

            if(ordenado->prox == NULL) {
                ordenado->prox = pivo;
                pivo->prox = NULL;
            }
            else {
                pivo->prox = ordenado->prox;
                ordenado->prox = pivo;
            }
        }
    }

    while (ordenado->prox != NULL)
        ordenado = ordenado->prox;

    ordenado->prox = inicioOrdenado;

    funcionario = inicioOrdenado;
}

void gerarPlaca(char *placa) {
    int i;
    for(i=0; i < 3; i++)
        placa[i] = (char) (rand() % 26 + 65);
    placa[3] = '-';
    for(i=4; i < 8; i++)
        placa[i] = (char) (rand() % 10 + 48);
    placa[8] = '\0';
}

carro* empilhar(carro *topo, char *placa) {
    int i;
    
    carro *novo = malloc(sizeof(carro));
    novo->prox = topo;

    novo->placa = placa;

    return novo;
}

carro* estacionar(carro *topo, char *placa) {
    carro *novo = empilhar(topo, placa);
    novo->hora = tempo;

    veiculosEstacionados++;
    printf("Veiculo %s entrou! Total: %d\n", placa, veiculosEstacionados);

    return novo;
}

carro* desestacionar(carro *topo, char placa[9]) {
    carro *manobrado = NULL;

    printf("Veiculo %s ira sair\n",  placa);

    while (topo != NULL && strcmp(topo->placa, placa) != 0 ) {
        manobrado = empilhar(manobrado, topo->placa);
        printf("Funcionario %c manobrou para fora um carro! Placa: %s\n", funcionario->nome, topo->placa);
        funcionario = funcionario->prox;
        topo = topo->prox;
        manobras1++;
    }

    carro *veiculoCerto = topo;

    printf("Funcionario %c manobrou para fora um carro! Placa: %s\n", funcionario->nome, veiculoCerto->placa);
    funcionario = funcionario->prox;
    dinheiro += ceil((tempo - veiculoCerto->hora) / 60.0) * PRECO_HORA;
    dinheiro = dinheiro > 12 ? dinheiro : 12;
    topo = veiculoCerto->prox;
    manobras1++;

    while (manobrado != NULL) {
        topo = empilhar(topo, manobrado->placa);
        printf("Funcionario %c retornou o carro %s\n", funcionario->nome, topo->placa);
        funcionario = funcionario->prox;
        manobrado = manobrado->prox;
        manobras1++;
    }

    veiculosEstacionados--;

    printf("Veiculo %s saiu! Total: %d\n", placa, veiculosEstacionados);
    
    free(veiculoCerto);

    return topo;
}

carro2* empilhar2(carro2 *topo, char *placa) {    
    int i;
    carro2 *novo = malloc(sizeof(carro2));
    novo->prox = topo;
    novo->ant = NULL;
    if (topo != NULL)
        topo->ant = novo;
    novo->placa = placa;

    return novo;
}

carro2* porFundo(carro2 *fundo, char *placa) {
    int i;
    carro2 *novo = malloc(sizeof(carro2));
    novo->ant = fundo;
    novo->prox = NULL;
    if (fundo != NULL)
        fundo->prox = novo;
    novo->placa = placa;

    return novo;
}

carro2* estacionar2(carro2 *topo, char *placa) {
    carro2 *novo = empilhar2(topo, placa);

    veiculosEstacionados++;
    printf("Veiculo %s entrou! Total: %d\n", placa, veiculosEstacionados);

    return novo;
}

carro2* desestacionar2(carro2 *topo, carro2 *fundo, char *placa) {
    carro *manobrado = NULL;
    carro2 *aux=topo, *veiculoCerto;
    int contador=0;

    printf("Veiculo %s ira sair!\n",  placa);

    while (strcmp(aux->placa, placa) != 0) {
        aux = aux->prox;
        contador++;
    }

    if (contador < veiculosEstacionados/2.0) {
        while (strcmp(topo->placa, placa) != 0) {
            manobrado = empilhar(manobrado, topo->placa);
            printf("Funcionario %c manobrou para fora um carro! Placa: %s\n", funcionario->nome, topo->placa);
            funcionario = funcionario->prox;
            topo = topo->prox;
            manobras2++;
        }

        veiculoCerto = topo;

        printf("Funcionario %c manobrou para fora um carro! Placa: %s\n", funcionario->nome, veiculoCerto->placa);
        funcionario = funcionario->prox;

        topo = veiculoCerto->prox;

        if (topo != NULL) {
            topo->ant = veiculoCerto->ant;
            if (topo->ant != NULL)
                veiculoCerto->ant->prox = topo;
        }
        manobras2++;
        

        while (manobrado != NULL) {
            topo = empilhar2(topo, manobrado->placa);
            printf("Funcionario %c retornou o carro %s\n", funcionario->nome, topo->placa);
            funcionario = funcionario->prox;
            manobrado = manobrado->prox;
            manobras2++;
        }
    }
    else {
        while (strcmp(fundo->placa, placa) != 0) {
            manobrado = empilhar(manobrado, fundo->placa);
            printf("Funcionario %c manobrou para fora um carro! Placa: %s\n", funcionario->nome, fundo->placa);
            funcionario = funcionario->prox;
            fundo = fundo->ant;
            manobras2++;
        }

        veiculoCerto = fundo;

        printf("Funcionario %c manobrou para fora um carro! Placa: %s\n", funcionario->nome, veiculoCerto->placa);
        funcionario = funcionario->prox;

        fundo = veiculoCerto->ant;

        if (fundo != NULL) {
            fundo->prox = veiculoCerto->prox;
            if (veiculoCerto->prox != NULL)
                veiculoCerto->prox->ant = fundo;
        }
        manobras2++;

        
        while (manobrado != NULL) {
            fundo = porFundo(fundo, manobrado->placa);
            printf("Funcionario %c retornou o carro %s\n", funcionario->nome, fundo->placa);
            funcionario = funcionario->prox;
            manobrado = manobrado->prox;
            manobras2++;
        }
    }

    veiculosEstacionados--;

    printf("Veiculo %s saiu! Total: %d\n", placa, veiculosEstacionados);
    
    free(veiculoCerto->placa);
    free(veiculoCerto);

    return topo;
}

registrario* registrar(registrario *registro, int tipo, char *info) {
    registrario *novo = malloc(sizeof(registrario));
    novo->tipo = tipo;
    novo->info = info;
    novo->prox = NULL;
    
    if (registro == NULL)
        return novo;

    registrario *inicio = registro;

    while (registro->prox != NULL)
        registro = registro->prox;

    registro->prox = novo;

    return inicio;
}

void porFolha(buscaCarro *raiz, buscaCarro *novaFolha) {    
    int folhaEhMaior = strcmp(novaFolha->placa, raiz->placa) > 0;
    
    if (folhaEhMaior) {
        if (raiz->proxD == NULL) {
            raiz->proxD = novaFolha;
            novaFolha->pai = raiz;
        }
        else {
            porFolha(raiz->proxD, novaFolha);
        }
    }
    else {
        if (raiz->proxE == NULL){
            raiz->proxE = novaFolha;
            novaFolha->pai = raiz;
        }
        else {
            porFolha(raiz->proxE, novaFolha);
        }
    }
}

void adicionarBuscaCarro(char *placa) {
    buscaCarro *novaFolha = malloc(sizeof(buscaCarro));
    novaFolha->placa = placa;
    novaFolha->pai = NULL;
    novaFolha->proxE = NULL;
    novaFolha->proxD = NULL;

    if (arvoreCarros == NULL)
        arvoreCarros = novaFolha;
    else
        porFolha(arvoreCarros, novaFolha);
}

buscaCarro* maiorBuscaCarro(buscaCarro *raiz) {
    if (raiz->proxD == NULL)
        return raiz;
    else
        return maiorBuscaCarro(raiz->proxD);
}

void removerNo(buscaCarro *raiz, char *placa) {
    int achou = strcmp(raiz->placa, placa) == 0;

    if (achou) {
        if (raiz->pai != NULL) {
            buscaCarro *filhoSubstituto;

            if (raiz->proxE == NULL && raiz->proxD == NULL) {
                filhoSubstituto = NULL;
            }
            else {
                if (raiz->proxE != NULL && raiz->proxD != NULL) {
                    filhoSubstituto = maiorBuscaCarro(raiz->proxE);
                    filhoSubstituto->pai->proxD = NULL;
                    filhoSubstituto->proxD = raiz->proxD;
                    if (filhoSubstituto != raiz->proxE)
                        porFolha(filhoSubstituto, raiz->proxE);
                }
                else {
                    filhoSubstituto = raiz->proxE != NULL ? raiz->proxE : raiz->proxD;
                    filhoSubstituto->pai = raiz->pai;
                }
            }

            //free(raiz);
            if (raiz->pai->proxE == raiz)
                raiz->pai->proxE = filhoSubstituto;
            else
                raiz->pai->proxD = filhoSubstituto;
        }
        else {
            arvoreCarros = NULL;
        }
    }
    else {
        int ehMaior = strcmp(placa, raiz->placa) > 0;

        if (ehMaior)
            removerNo(raiz->proxD, placa);
        else
            removerNo(raiz->proxE, placa);
    }
}

void removerBuscaCarro(char *placa) {
    removerNo(arvoreCarros, placa);
}

void main() {
    srand(time(NULL));
    funcionario = criarFuncionarios(QUANTIDADE_FUNCIONARIOS);
    carro *entrada=NULL;
    registrario *registro=NULL;
    
    tempo=0;
    int i;

    printf("Estacionamento abriu!\n");

    while(dinheiro < BUDGET) 
    {
        int escolha = rand() % 3;
        switch (escolha)
        {
            case 0: // Estacionar
            { 
                if(veiculosEstacionados < LIMITE_VAGAS) {
                    char *placa = malloc(sizeof(char) * 9);
                    gerarPlaca(placa);
                    entrada = estacionar(entrada, placa);

                    registro = registrar(registro, 0, placa);
                }
                else {
                    printf("Veiculo chegou, mas o estacionamento esta cheio!\n");
                    registro = registrar(registro, 0, NULL);
                }
                
                break;
            }
            case 1: // Desestacionar
            {
                if(veiculosEstacionados > 0) {
                    char *placa;
                    
                    int veiculo = rand() % veiculosEstacionados;
                    carro *aux = entrada;
                    for(i=rand() % veiculosEstacionados; i > 0; i--)
                        aux = aux->prox;

                    placa = aux->placa;

                    entrada = desestacionar(entrada, placa);

                    registro = registrar(registro, 1, placa);
                }
                else
                    registro = registrar(registro, 1, NULL);
                break;
            }
            case 2: // Ordenar Funcionários
            {
                int tipoOrdem = rand() % 3;
                
                switch (tipoOrdem)
                {
                    case 0:
                    {
                        ordenarFuncNome();
                        printf("Administrador ordenou os funcionarios por Nome\n");
                        registro = registrar(registro, 2, "NOME");
                        break;
                    }
                        
                    case 1: 
                    {
                        ordenarFuncId();
                        printf("Administrador ordenou os funcionarios por ID\n");
                        registro = registrar(registro, 2, "ID");
                        break;
                    }
                        
                    case 2:
                    {
                        ordenarFuncIdade();
                        printf("Administrador ordenou os funcionarios por Idade\n");
                        registro = registrar(registro, 2, "IDADE");
                        break;
                    }
                }
                break;
            }
        }

        tempo += rand() % 30 + 1;
    }

    printf("Estacionamento fechou!\n");

    ordenarFuncId();
    while(entrada != NULL) {
        carro *retirar = entrada;
        entrada = entrada->prox;
        free(retirar);
    }
    veiculosEstacionados = 0;

    carro2 *estacionamento=NULL;

    printf("\n\n");
    printf("Abrindo simulacao!\n");

    while (registro != NULL)
    {
        switch (registro->tipo)
        {
            case 0: // Estacionar
            {
                if(veiculosEstacionados < LIMITE_VAGAS)
                    estacionamento = estacionar2(estacionamento, registro->info);
                else
                    printf("Veiculo chegou, mas o estacionamento esta cheio!\n");
                
                break;
            }
            case 1: // Desestacionar
            {
                if(veiculosEstacionados > 0) {
                    carro2 *aux = estacionamento;
                    while (aux->prox != NULL) {
                        aux = aux->prox;
                    }
                    estacionamento = desestacionar2(estacionamento, aux, registro->info);
                }

                break;
            }
            case 2: // Ordenar Funcionários
            { 
                if (strcmp(registro->info, "NOME") == 0) {
                    ordenarFuncNome();
                    printf("Administrador ordenou os funcionarios por Nome\n");
                }
                else {
                    if (strcmp(registro->info, "ID") == 0) {
                        ordenarFuncId();
                        printf("Administrador ordenou os funcionarios por ID\n");
                    }
                    else {
                        ordenarFuncIdade();
                        printf("Administrador ordenou os funcionarios por Idade\n");
                    }
                }

                break;
            }
        }

        registrario *antigo = registro;

        registro = registro->prox;

        free(antigo);
    }

    printf("Fechando simulacao!\n\n");

    printf("Manobras antes do portao: %d\n", manobras1);
    printf("Manobras depois do portao: %d\n", manobras2);
}