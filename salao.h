#ifndef SALAO_H
#define SALAO_H

typedef struct Prato {
    char nome[100];
    struct Prato* prox;
} Prato;

typedef struct Pedido {
    int id;
    Prato* pratos;
    struct Pedido* prox;
} Pedido;

void adicionarPedido(int id);
void removerPrato(int id, const char* nomePrato);
void listarPedidosSalao();
Pedido* transferirPedido();

#endif
