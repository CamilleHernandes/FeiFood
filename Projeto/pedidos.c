#include <stdio.h>
#include<string.h>

#include"funcoes.h"

void menuPedidos() {
    int opcao;

    do {
        printf("\n--- Menu de Pedidos ---\n");
        printf("1. Criar pedido\n");
        printf("2. Editar pedido\n");
        printf("3. Excluir pedido\n");
        printf("4. Adicionar alimento ao pedido\n");
        printf("5. Remover alimento do pedido\n");
        printf("0. Voltar ao menu principal\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                criarPedido();
                break;
            case 2:
                editarPedido();
                break;
            case 3:
                excluirPedido();
                break;
            case 4:
                // adicionarAlimentoPedido();
                break;
            case 5:
                removerAlimentoPedido();
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(opcao != 0);
}

void criarPedido() {
    FILE *f = fopen("pedidos.txt", "a");
    char nomePedido[50], usuario[50], alimento[50];
    int qtd;

    printf("Digite um nome para o pedido: ");
    scanf("%s", nomePedido);

    printf("Digite seu nome de usuário: ");
    scanf("%s", usuario);

    printf("Quantos alimentos deseja adicionar ao pedido? ");
    scanf("%d", &qtd);

    fprintf(f, "%s %s ", nomePedido, usuario); // nome do pedido e usuário

    for (int i = 0; i < qtd; i++) {
        printf("Digite o alimento %d: ", i + 1);
        scanf("%s", alimento);
        fprintf(f, "%s; ", alimento);
    }

    fprintf(f, "\n");
    fclose(f);

    printf("Pedido criado com sucesso!\n");
}


void editarPedido() { // tem que arrumar 
    FILE *f = fopen("pedidos.txt", "r");
    FILE *arqaux = fopen("aux.txt", "w");
    char nomePedido[50], usuario[50], novoAlimentos[200];
    char linhaNome[50], linhaUsuario[50], linhaAlimentos[200];
    int encontrado = 0;

    printf("Digite o nome do pedido que deseja editar: ");
    scanf("%s", nomePedido);
    printf("Digite seu nome de usuário: ");
    scanf("%s", usuario);
    printf("Digite a nova lista de alimentos separados por ';': ");
    scanf("%s", novoAlimentos);

    while (fscanf(f, "%s %s %s", linhaNome, linhaUsuario, linhaAlimentos) != EOF) {
        if (strcmp(linhaNome, nomePedido) == 0 && strcmp(linhaUsuario, usuario) == 0) {
            fprintf(arqaux, "%s %s %s\n", nomePedido, usuario, novoAlimentos);
            encontrado = 1;
        } else {
            fprintf(arqaux, "%s %s %s\n", linhaNome, linhaUsuario, linhaAlimentos);
        }
    }

    fclose(f);
    fclose(arqaux);
    remove("pedidos.txt");
    rename("aux.txt", "pedidos.txt");

    if (encontrado)
        printf("Pedido editado com sucesso!\n");
    else
        printf("Pedido não encontrado.\n");
}

void excluirPedido() {
    FILE *f = fopen("pedidos.txt", "r");
    FILE *arqaux = fopen("aux.txt", "w");
    char nomePedido[50], usuario[50];
    char linhaNome[50], linhaUsuario[50], linhaAlimentos[200];
    int encontrado = 0;

    printf("Digite o nome do pedido que deseja excluir: ");
    scanf("%s", nomePedido);
    printf("Digite seu nome de usuário: ");
    scanf("%s", usuario);

    while (fscanf(f, "%s %s %s", linhaNome, linhaUsuario, linhaAlimentos) != EOF) {
        if (strcmp(linhaNome, nomePedido) == 0 && strcmp(linhaUsuario, usuario) == 0) {
            encontrado = 1;
            continue;
        }
        fprintf(arqaux, "%s %s %s\n", linhaNome, linhaUsuario, linhaAlimentos);
    }

    fclose(f);
    fclose(arqaux);
    remove("pedidos.txt");
    rename("aux.txt", "pedidos.txt");

    if (encontrado)
        printf("Pedido excluído com sucesso!\n");
    else
        printf("Pedido não encontrado.\n");
}

// void adicionarAlimentoPedido() {
//     FILE *f = fopen("pedidos.txt", "a");
//     char usuario[50], alimento[50];

//     printf("Digite seu nome de usuário: ");
//     scanf("%s", usuario);
//     printf("Digite o alimento que deseja adicionar: ");
//     scanf("%s", alimento);

//     fprintf(f, "%s %s\n", usuario, alimento);
//     fclose(f);

//     printf("Alimento adicionado ao pedido!\n");
// }

void removerAlimentoPedido() {
    FILE *f = fopen("pedidos.txt", "r");
    FILE *arqaux = fopen("aux.txt", "w");
    char nomePedido[50], usuario[50], alimentoRemover[50];
    char linha[300];
    int encontrado = 0;

    printf("Digite o nome do pedido: ");
    scanf("%s", nomePedido);
    printf("Digite seu nome de usuário: ");
    scanf("%s", usuario);
    printf("Digite o alimento que deseja remover: ");
    scanf("%s", alimentoRemover);

    while (fgets(linha, sizeof(linha), f)) {
        char linhaNome[50], linhaUsuario[50], alimentos[200];
        sscanf(linha, "%s %s %[^\n]", linhaNome, linhaUsuario, alimentos);

        if (strcmp(linhaNome, nomePedido) == 0 && strcmp(linhaUsuario, usuario) == 0) {
            encontrado = 1;

            char novaLista[200] = "";
            char *alimentoAtual = strtok(alimentos, ";"); // Divide a string de alimentos em partes usando o ;

            while (alimentoAtual != NULL) {
                if (strcmp(alimentoAtual, alimentoRemover) != 0) {
                    strcat(novaLista, alimentoAtual);
                    strcat(novaLista, ";");
                }
                alimentoAtual = strtok(NULL, ";");
            }

            fprintf(arqaux, "%s %s %s\n", linhaNome, linhaUsuario, novaLista);
        } 
        else {
            fputs(linha, arqaux); //copia a linha original para o aux.txt
        }
    }

    fclose(f);
    fclose(arqaux);
    remove("pedidos.txt");
    rename("aux.txt", "pedidos.txt");

    if (encontrado)
        printf("Alimento removido com sucesso!\n");
    else
        printf("Pedido não encontrado.\n");
}


void avaliarPedido() { // tem que arrumar
    FILE *f = fopen("avaliacoes.txt", "a");
    char nomePedido[50], usuario[50];
    int nota;

    printf("Digite o nome do pedido que deseja avaliar: ");
    scanf("%s", nomePedido);
    printf("Digite seu nome de usuário: ");
    scanf("%s", usuario);
    printf("Digite a nota (0 a 5): ");
    scanf("%d", &nota);

    if (nota < 0 || nota > 5) {
        printf("Nota inválida. Use um valor entre 0 e 5.\n");
        fclose(f);
        return;
    }

    fprintf(f, "%s %s %d\n", nomePedido, usuario, nota);
    fclose(f);

    printf("Avaliação registrada com sucesso!\n");
}
