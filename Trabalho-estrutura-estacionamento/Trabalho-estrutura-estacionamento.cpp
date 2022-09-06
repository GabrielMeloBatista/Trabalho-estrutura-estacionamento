#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 20
// Para o meu compilador Não reclamar
#pragma warning(disable : 4996)

// O estacionamento dos carros é modelo gaveta, assim os modelos são controlados e separados por uma pilha de carros.
typedef struct modeloGaveta {
	char placaCarro[TAM];
	struct modeloGaveta* prox;
} gaveta;

// Existe uma fila de espera de clientes para cada modelo.
typedef struct filaCliente {
	char cliente[TAM];
	struct filaCliente* prox;
} fila;

typedef struct pont {
    fila* p;
    fila* u;
}ponteiros;

// Construa um algoritmo que administre as reservas de carros em uma locadora de veículos, sendo que existe uma lista de modelos de carro
typedef struct modeloCarro
{
    ponteiros* filaInfo;
    fila* filaEspera;
    gaveta* carrosEstacionado;
	char modeloCarro[TAM];
	struct modeloCarro* prox;
} modelo;

int vazioFila(ponteiros* f) {
    if (f->p == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

ponteiros* enfileirar(ponteiros* i, char *name) {
    fila* nova;

    nova = (fila*)malloc(sizeof(fila));
    strcpy(nova->cliente, name);
    nova->prox = NULL;

    if (vazioFila(i)) {
        i->p = nova;
        i->u = nova;
    }
    else {
        i->u->prox = nova;
        i->u = nova;
    }

    return i;

}

void desenfileira(ponteiros* i) {
    //char x[TAM];
    fila* a = i->p;

    // x = i->p->cliente;
    //strcpy(x ,i->p->cliente);

    if (i->p->prox == NULL) {
        i->p = NULL;
        i->u = NULL;
    }
    else {
        i->p = i->p->prox;
    }

    free(a);
    //return x;
}

void empilha(char *y, gaveta* tp) {
    gaveta* nova;
    nova = (gaveta*)malloc(sizeof(gaveta));
    strcpy(nova->placaCarro, y);
    //nova->carro = y;
    nova->prox = tp->prox;
    tp->prox = nova;
}

void desempilha(gaveta* tp) {
    //char x[TAM];
    gaveta* p;
    p = tp->prox;
    //strcpy(x, p->carro);
    // x = p->carro;
    tp->prox = p->prox;
    free(p);
    //return x;
}

void insereLista(char *x, modelo* p)
{
    modelo* nova;
    gaveta* pilhaVazia;
    fila* filaVazia;
    ponteiros* filaPosicao;

    nova = (modelo*)malloc(sizeof(modelo));
    pilhaVazia = (gaveta*)malloc(sizeof(gaveta));
    filaVazia = (fila*)malloc(sizeof(fila));
    filaPosicao = (ponteiros*)malloc(sizeof(ponteiros));

    strcpy(nova->modeloCarro, x);
    //nova->modeloCarro = x;
    nova->filaEspera = filaVazia;
    nova->carrosEstacionado = pilhaVazia;
    nova->prox = p->prox;
    nova->filaInfo = filaPosicao;

    p->prox = nova;
}

void removeLista(modelo* p)
{
    modelo* lixo;
    lixo = p->prox;
    p->prox = lixo->prox;
    free(lixo);
}

modelo* buscaLista(char *x, modelo* le)
{
    modelo* p;
    p = le;
    //while (p != NULL && p->modeloCarro != x)
    while (p != NULL && strcmp(p->modeloCarro, x))
    {
        p = p->prox;
    }
    return p;
}

void empilharCarro(modelo* aux)
{
    char* placaCarro;
    printf("\nDigite a placa do carro: ");
    scanf("%s", placaCarro);
    empilha(placaCarro, aux->carrosEstacionado);
}

// O cliente escolhe o modelo desejado antes ser inserido na fila
void mostrarModelo(modelo* le) {
    modelo* aux;
    
    if (le->prox != NULL)
    {
        aux = le->prox;
        while (aux != NULL)
        {
            if (aux->prox != NULL)
            {
                printf("%s, ", aux->modeloCarro);
            }
            else
            {
                printf("%s.", aux->modeloCarro);
            }
            aux = aux->prox;
        }
    }
    else {
        printf("Lista Vazia");
    }
}

void mostrarGaveta(gaveta* p) {
    gaveta* aux;
    aux = p;
    if (p->prox != NULL)
    {
        while (aux != NULL)
        {
            if (aux->prox != NULL)
            {
                printf("%s, ", aux->placaCarro);
            }
            else
            {
                printf("%s.", aux->placaCarro);
            }
            aux = aux->prox;
        }
    }
    else {
        printf("Pilha Vazia");
    }
}

void mostrarFila(fila* p) {
    fila* aux;
    aux = p;
    if (p->prox != NULL)
    {
        while (aux != NULL)
        {
            if (aux->prox != NULL)
            {
                printf("%s, ", aux->cliente);
            }
            else
            {
                printf("%s.", aux->cliente);
            }
            aux = aux->prox;
        }
    }
    else {
        printf("Fila Vazia");
    }
}

// Assim, se existe carro disponível o cliente é acionado, se concluída a locação, o cliente sai da fila e o carro da pilha.
int carroDisponivel(gaveta *p) {
    if (p!= NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int verificaDisponibilidadeCarro(gaveta* p) {
    if (carroDisponivel(p))
    {
        // Concluida locação
        desempilha(p);
        // cliente sai da fila e o carro da pilha.
        return true;
    }
    else {
        return false;
    }
}

// Quando o cliente faz a devolução do carro ele volta para a pilha(estacionamento)
void devolucaoCarro(modelo* p) {
    // Empilha o carro.
    modelo* aux;
    char nomeModelo[TAM];

    printf("\nDigite o Modelo do carro sendo devolvido: ");
    scanf("%s", nomeModelo);
    getchar();

    mostrarModelo(p);

    aux = buscaLista(nomeModelo, p);

    // Verificar se há clientes esperando pelo carro
    if (p->filaEspera != NULL)
    { 
        printf("\nCarro Disponivel"); 
        desenfileira(p->filaInfo);
        desempilha(p->carrosEstacionado);
    }
    empilharCarro(aux);
}

void escolheModelo(modelo *p) {
    modelo* aux;
    char nomeModelo[TAM];
    char cliente[TAM];
    char verify;
    int boolean = true;

    printf("\nDigite o nome do cliente: ");
    scanf("%s", cliente);
    getchar();
    
    // Lista todos os carros para o cliente poder escolher.
    printf("Modelos diponiveis: ");
    mostrarModelo(p);

    printf("\nDigite o Modelo do carro desejado: ");
    scanf("%s", nomeModelo);
    getchar();

    aux = buscaLista(nomeModelo, p);

    if (verificaDisponibilidadeCarro(aux->carrosEstacionado)) {
        desenfileira(aux->filaInfo);
        printf("\nCarro Disponivel para %s", cliente);
    }
    else
    {
        printf("\nNão a carros disponiveis, deseja colocar %s na fila de espera? S ou N: ", cliente);
        do
        {
            scanf("%s", &verify);
            getchar();
            if (strcmp(strdup(&verify), "Y") || strcmp(strdup(&verify), "S"))
            {
                enfileirar(aux->filaInfo, cliente);
                boolean = false;
            }
            else if (strcmp(strdup(&verify), "N"))
            {
                boolean = false;
            }
            else
            {
                printf("\nValores Validos são S ou N: ");
            }
        } while (boolean);
    }
}

void inserirModeloFila(modelo *q) {
    // Sim função deveras inutil
    escolheModelo(q);
}

// O algoritmo deve permitir inclusões nas filas em qualquer ocasião e remoções das mesmas apenas nos respectivos modelos

// Deverá ser possível consultar a lista de modelos, consultar as pilhas de carros por modelo, e as filas de clientes por cada modelo

// As estruturas que serão criadas deverão possuir dados o suficiente para cada manipulação.

void adicionarLista(modelo* p) {
    char nomeModelo[TAM];
    printf("Inserir nome do modelo: ");
    scanf("%s", nomeModelo);
    getchar();
    insereLista(nomeModelo, p);
}

void menuMostrar(modelo *p) {
    modelo* aux;
    char nomeModelo[TAM];
    int selector;

    printf("\n| 1 - Mostrar Modelos |");
    printf("| 2 - Mostrar Pilha de carro |");
    printf("| 3 - Mostrar fila de cliente |");
    printf("| Outro - Sair |\n");

    scanf("%d", &selector);
    switch (selector)
    {
    case 1:
        // Mostrar Modelos
        printf("\nModelos: ");
        mostrarModelo(p);

        menuMostrar(p);
        break;
    case 2:
        // Mostrar Pilha de carro
        if (p->prox != NULL)
        {

            printf("\nModelos: ");
            mostrarModelo(p);

            printf("\nDigite o modelo a procurar: ");
            scanf("%s", nomeModelo);
            getchar();
            aux = buscaLista(nomeModelo, p);
            mostrarGaveta(aux->carrosEstacionado);
            menuMostrar(p);
        }
        else
        {
            printf("\tVazio!");
        }
        break;
    case 3:
        // Mostrar fila de cliente
        if (p->prox != NULL) {
            printf("\nModelos: ");
            mostrarModelo(p);
            printf("\nDigite o modelo a procurar: ");
            scanf("%s", nomeModelo);
            getchar();
            aux = buscaLista(nomeModelo, p);
            mostrarFila(aux->filaEspera);
            menuMostrar(p);
        }
        else
        {
            printf("\tVazio!!!");
        }
        break;
    default:
        break;
    }
}

void menuPedido(modelo* p) {
    int selector;

    printf("\n| 1 - Pedir Carro |");
    printf("| 2 - Devolver Carro |");
    printf("| Outro - Sair |\n");
    
    scanf("%d", &selector);
    switch (selector)
    {
    case 1:
        // Pedir Carro
        inserirModeloFila(p);
        menuPedido(p);
        break;
    case 2:
        // Devolver Carro
        devolucaoCarro(p);
        menuPedido(p);
    default:
        break;
    }
}

void adicinarModeloCarro(modelo* p) {
    modelo* aux;
    char nomeModelo[TAM];

    printf("\nModelos Disponiveis: ");
    mostrarModelo(p);

    printf("\nDigite o Modelo do carro: ");
    scanf("%s", nomeModelo);
    getchar();


    aux = buscaLista(nomeModelo, p);

    empilharCarro(aux);
}

void menu(modelo *p) {
    int selector;

    printf("\n| 1 - Mostrar Info |");
    printf("| 2 - Adicionar modelo de carro |");
    printf("| 3 - Adicionar carro em um modelo |");
    printf("| 4 - Gerenciar pedido de cliente |");
    printf("| Outro - Sair |\n");

    scanf("%d", &selector);
    switch (selector)
    {
    case 1:
        // Mostrar os modelos
        menuMostrar(p); 
        menu(p);
        break;
    case 2:
        // Adicionar Modelo de carro
        adicionarLista(p);
        menu(p);
        break;
    case 3:
        // Adicionar Carro em um modelo
        adicinarModeloCarro(p);
        menu(p);
        break;
    case 4:
        // Gerenciar pedido de cliente
        menuPedido(p);
        menu(p);
        break;
    default:
        break;
    }
}

int main()
{
    modelo* carro;
    carro = (modelo*)malloc(sizeof(modelo));

    menu(carro);
}
