#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salao.h"

// Ponteiros globais que representam o início e o fim da lista de pedidos no salão
Pedido* inicio = NULL;
Pedido* fim = NULL;

// Função para adicionar um novo pedido ao salão
void adicionarPedido(int id) {
    // Aloca memória para um novo pedido
    Pedido* novo = (Pedido*)malloc(sizeof(Pedido));
    novo->id = id;
    novo->pratos = NULL; // Lista de pratos começa vazia
    novo->prox = NULL;   // Ainda não há próximo pedido

    int opcao;
    // Cardápio disponível
    char* menu[] = {
        "Sopa de Cebola", "Salada Caesar", "Bruschetta", "Carpaccio de Carne", "Camarao ao Alho",
        "Lasanha a Bolonhesa", "File Mignon com Fritas", "Frango Grelhado com Legumes", "Bacalhau a Gomes de Sa", "Risoto de Cogumelos",
        "Tiramisu", "Cheesecake de Frutas Vermelhas", "Mousse de Chocolate", "Pudim de Leite", "Sorvete de Baunilha com Calda de Morango"
    };

    // Exibe as opções de pratos para o cliente escolher
    printf("Digite o(s) número(s) do(s) prato(s) [0 para sair]:\n[1 a 5: Entradas; 6 a 10: Pratos Principais; 11 a 15: Sobremesas]\n");
    for (int i = 0; i < 15; i++)
        printf("%d - %s\n", i + 1, menu[i]);

    // Loop para permitir que o cliente adicione vários pratos
    while (1) {
        printf("\nPrato: ");
        scanf("%d", &opcao);
        if (opcao == 0) break; // Sai se o cliente digitar 0
        if (opcao < 1 || opcao > 15) {
            printf("Opção inválida.\n");
            continue;
        }

        // Cria e adiciona um novo prato à lista de pratos do pedido
        Prato* p = (Prato*)malloc(sizeof(Prato));
        strcpy(p->nome, menu[opcao - 1]); // Copia o nome do prato do cardápio
        p->prox = novo->pratos; // Insere no início da lista de pratos (ordem inversa da entrada)
        novo->pratos = p;
    }

    // Insere o novo pedido na fila do salão
    if (!inicio)
        inicio = fim = novo; // Se a lista está vazia, o novo é o primeiro e o último
    else {
        fim->prox = novo; // Liga o novo pedido ao fim da lista
        fim = novo;       // Atualiza o ponteiro do fim
    }

    printf("Pedido %d adicionado ao salão.\n", id);
}

// Remove um prato específico de um pedido, com base no nome
void removerPrato(int id, const char* nomePrato) {
    Pedido* p = inicio;
    while (p) {
        if (p->id == id) { // Encontra o pedido com o ID informado
            Prato *anterior = NULL, *atual = p->pratos;
            while (atual) {
                if (strcmp(atual->nome, nomePrato) == 0) { // Prato encontrado
                    if (anterior) anterior->prox = atual->prox; // Remove do meio/final
                    else p->pratos = atual->prox;               // Remove do início
                    free(atual); // Libera a memória do prato removido
                    printf("Prato removido do pedido %d.\n", id);
                    return;
                }
                anterior = atual;
                atual = atual->prox;
            }
            printf("Prato não encontrado no pedido %d.\n", id);
            return;
        }
        p = p->prox;
    }
    printf("Pedido %d não encontrado.\n", id);
}

// Transfere o primeiro pedido do salão (início da fila) para a cozinha
Pedido* transferirPedido() {
    if (!inicio) return NULL; // Nenhum pedido para transferir

    Pedido* p = inicio;       // Primeiro pedido da fila
    inicio = inicio->prox;    // Avança o ponteiro de início para o próximo pedido
    if (!inicio) fim = NULL;  // Se a fila ficou vazia, ajusta o ponteiro de fim
    p->prox = NULL;           // Desconecta o pedido da lista
    return p;                 // Retorna o pedido para ser usado na cozinha
}

// Lista todos os pedidos atualmente no salão e seus respectivos pratos
void listarPedidosSalao() {
    Pedido* p = inicio;
    while (p) {
        printf("Pedido %d:\n", p->id);
        Prato* prato = p->pratos;
        while (prato) {
            printf(" - %s\n", prato->nome);
            prato = prato->prox;
        }
        p = p->prox;
    }
}
