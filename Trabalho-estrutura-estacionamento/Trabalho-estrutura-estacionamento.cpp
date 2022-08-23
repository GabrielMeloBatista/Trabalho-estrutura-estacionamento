#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 20
// Construa um algoritmo que administre as reservas de carros em uma locadora de veículos, sendo que existe uma lista de modelos de carro
typedef struct modeloCarro
{
	char modeloCarro[TAM];
	struct modeloCarro* prox;
} modelo;

// O estacionamento dos carros é modelo gaveta, assim os modelos são controlados e separados por uma pilha de carros.
typedef struct modeloGaveta {
	char carro[TAM];
	struct modeloGaveta* Carro;
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
    // TODO Colocar a forma correta de colocar string
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

char* desenfileira(ponteiros* i) {
    char x[TAM];
    fila* a = i->p;

    // TODO corrigir colocando a forma de modificar string
    // x = i->p->cliente;
    strcpy(x ,i->p->cliente);

    if (i->p->prox == NULL) {
        i->p = NULL;
        i->u = NULL;
    }
    else {
        i->p = i->p->prox;
    }

    free(a);
    return x;
}

// Assim, se existe carro disponível o cliente é acionado, se concluída a locação, o cliente sai da fila e o carro da pilha.

// Quando o cliente faz a devolução do carro ele volta para a pilha(estacionamento)

// O cliente escolhe o modelo desejado antes ser inserido na fila

// O algoritmo deve permitir inclusões nas filas em qualquer ocasião e remoções das mesmas apenas nos respectivos modelos

// Deverá ser possível consultar a lista de modelos, consultar as pilhas de carros por modelo, e as filas de clientes por cada modelo

// As estruturas que serão criadas deverão possuir dados o suficiente para cada manipulação.

int main()
{

}
