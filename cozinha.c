#include <stdio.h>
#include <stdlib.h>
#include "cozinha.h"

// Estrutura auxiliar para representar cada elemento da fila de pedidos da cozinha
typedef struct NoFila {
    Pedido* pedido;        // pedido que será preparado
    struct NoFila* prox;   // próximo nó na fila
} NoFila;

NoFila* next = NULL;
NoFila* prev = NULL;

// Função para enfileirar um pedido que veio do salão para a cozinha
void enfileirarPedido(Pedido* pedido) {
    // Aloca memória para o novo nó da fila
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    novo->pedido = pedido;
    novo->prox = NULL;

    if (!next)
        next = prev = novo;
    else {
        prev->prox = novo;
        prev = novo;
    }

    printf("Pedido %d enviado para a cozinha.\n", pedido->id);
}

// Função que lista todos os pedidos atualmente em preparo na cozinha
void listarCozinha() {
    NoFila* temp = next;
    while (temp) {
        // Mostra o número do pedido
        printf("Pedido %d em preparo:\n", temp->pedido->id);
        
        // Percorre e imprime os pratos que fazem parte desse pedido
        Prato* p = temp->pedido->pratos;
        while (p) {
            printf(" - %s\n", p->nome);
            p = p->prox;
        }

        temp = temp->prox; // Avança para o próximo pedido na fila
    }
}
