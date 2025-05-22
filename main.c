#include <stdio.h>
#include <string.h>  // Biblioteca necessária para tratar a quebra de linha no fim da string 
#include "salao.h"   // Inclui funções relacionadas ao gerenciamento de pedidos no salão
#include "cozinha.h" // Inclui funções relacionadas à fila de preparo na cozinha

int main() {
    int opcao, idPedido = 1; // Variável para controlar a escolha do menu e gerar IDs únicos para os pedidos

    while (1) {
        // Menu de opções
        printf("\n1. Adicionar Pedido\n2. Remover Prato\n3. Processar Pedido\n4. Listar Pendentes\n5. Listar Cozinha\n0. Sair\nOpçao: ");
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário
        
        if (opcao == 0) break; 

        switch (opcao) {
            case 1:
                // Adiciona um novo pedido
                adicionarPedido(idPedido++);
                break;

            case 2: {
                // Remove um prato de um pedido específico
                int id;
                char nome[100];

                printf("ID do pedido: ");
                scanf("%d", &id);

                printf("Nome do prato a remover: ");
                getchar();
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;

                removerPrato(id, nome);
                break;
            }

            case 3: {
                // Transfere o próximo pedido do salão para a cozinha
                Pedido* p = transferirPedido();
                if (p)
                    enfileirarPedido(p); // Envia o pedido para a fila de preparo
                else
                    printf("Nenhum pedido a processar.\n");
                break;
            }

            case 4:
                listarPedidosSalao();
                break;

            case 5:
                listarCozinha();
                break;

            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}
