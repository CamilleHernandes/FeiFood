#include <stdio.h>
#include<string.h>

#include"funcoes.h"

void menuPedidos() {
    int opcao;

    do {
        printf("\n*********** Menu de Pedidos ***********\n");
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
                adicionarAlimentoPedido();
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
    char nomePedido[50], alimento[50], observacao[100], usuario[50];
    int quantidade, qtdAlimento;

    // Pega o usuário logado
    FILE *sessao = fopen("sessao.txt", "r");
    fscanf(sessao, "%s", usuario);
    fclose(sessao);

    printf("Digite um nome para o pedido: ");
    scanf("%s", nomePedido);

    printf("Quantos alimentos deseja adicionar ao pedido? ");
    scanf("%d", &quantidade);

    fprintf(f, "%s %s ", nomePedido, usuario); // nome do pedido e usuário

    for (int i = 0; i < quantidade; i++) {
        printf("Digite o alimento %d: ", i + 1);
        scanf("%s", alimento);

        printf("Digite a qtd do alimento %d: ", i + 1);
        scanf("%d", qtdAlimento);

        fprintf(f, "alimento: %s qtd: %d", alimento, qtdAlimento);

        if (i < quantidade - 1) {
            fprintf(f, ";");
        }
    }


    printf("Deseja adicionar alguma observação? (ex: sem cebola, bem passado): ");
    scanf(" %[^\n]", observacao); // lê até o fim da linha

    fprintf(f, " ;Qtd Itens: %d Obs: %s\n", quantidade, observacao);
    fclose(f);

    printf("Pedido criado com sucesso!\n");
}


void editarPedido() {
    FILE *f = fopen("pedidos.txt", "r");
    FILE *arqaux = fopen("aux.txt", "w");
    char nomePedido[50], usuario[50];
    char linha[300];
    int encontrado = 0;

    // Pega o usuário logado
    FILE *sessao = fopen("sessao.txt", "r");
    fscanf(sessao, "%s", usuario);
    fclose(sessao);

    printf("Digite o nome do pedido que deseja editar: ");
    scanf("%s", nomePedido);

    while (fgets(linha, sizeof(linha), f)) {
        char linhaNome[50], linhaUsuario[50], alimentos[200], observacao[100];
        int quantidade;

        sscanf(linha, "%s %s %s %d %[^\n]", linhaNome, linhaUsuario, alimentos, &quantidade, observacao);

        if (strcmp(linhaNome, nomePedido) == 0 && strcmp(linhaUsuario, usuario) == 0) {
            encontrado = 1;

            printf("Novo(s) alimento(s): ");
            scanf("%s", alimentos);
            printf("Nova quantidade: ");
            scanf("%d", &quantidade);
            printf("Nova observação: ");
            scanf(" %[^\n]", observacao);

            fprintf(arqaux, "%s %s %s Qtd: %d Obs: %s\n", linhaNome, linhaUsuario, alimentos, quantidade, observacao);
        } else {
            fputs(linha, arqaux);
        }
    }

    fclose(f);
    fclose(arqaux);
    remove("pedidos.txt");
    rename("aux.txt", "pedidos.txt");

    if (encontrado)
        printf("Pedido editado com sucesso!\n");
    else
        printf("Pedido não encontrado ou não pertence ao usuário logado.\n");
}



void excluirPedido() {
    FILE *f = fopen("pedidos.txt", "r");
    FILE *arqaux = fopen("aux.txt", "w");
    char nomePedido[50], usuario[50];
    char linha[300];
    int encontrado = 0;

    // Pega o usuário logado
    FILE *sessao = fopen("sessao.txt", "r");
    fscanf(sessao, "%s", usuario);
    fclose(sessao);

    printf("Digite o nome do pedido que deseja excluir: ");
    scanf("%s", nomePedido);

    while (fgets(linha, sizeof(linha), f)) {
        char linhaNome[50], linhaUsuario[50];

        sscanf(linha, "%s %s", linhaNome, linhaUsuario);

        if (strcmp(linhaNome, nomePedido) == 0 && strcmp(linhaUsuario, usuario) == 0) {
            encontrado = 1;
            // Não copia a linha — exclui
        } else {
            fputs(linha, arqaux); // mantém os outros pedidos
        }
    }

    fclose(f);
    fclose(arqaux);
    remove("pedidos.txt");
    rename("aux.txt", "pedidos.txt");

    if (encontrado)
        printf("Pedido excluído com sucesso!\n");
    else
        printf("Pedido não encontrado ou não pertence ao usuário logado.\n");
}


void adicionarAlimentoPedido() {
    FILE *f = fopen("pedidos.txt", "r");
    FILE *arqaux = fopen("aux.txt", "w");
    char nomePedido[50], novoAlimento[50], usuario[50];
    char linha[300];
    int encontrado = 0;

    // Pega o usuário logado
    FILE *sessao = fopen("sessao.txt", "r");
    fscanf(sessao, "%s", usuario);
    fclose(sessao);

    printf("Digite o nome do pedido que deseja alterar: ");
    scanf("%s", nomePedido);
    printf("Digite o alimento que deseja adicionar: ");
    scanf("%s", novoAlimento);

    while (fgets(linha, sizeof(linha), f)) {
        char linhaNome[50], linhaUsuario[50], alimentos[200], observacao[100];
        int quantidade;

        sscanf(linha, "%s %s %s %d %[^\n]", linhaNome, linhaUsuario, alimentos, &quantidade, observacao);

        if (strcmp(linhaNome, nomePedido) == 0 && strcmp(linhaUsuario, usuario) == 0) {
            encontrado = 1;

            strcat(alimentos, ";");
            strcat(alimentos, novoAlimento);

            fprintf(arqaux, "%s %s %s %d %s\n", linhaNome, linhaUsuario, alimentos, quantidade, observacao);
        } else {
            fputs(linha, arqaux);
        }
    }

    fclose(f);
    fclose(arqaux);
    remove("pedidos.txt");
    rename("aux.txt", "pedidos.txt");

    if (encontrado)
        printf("Alimento adicionado com sucesso!\n");
    else
        printf("Pedido não encontrado ou não pertence ao usuário logado.\n");
}

void removerAlimentoPedido() {// tem q arrumar olha no copilot q tem 
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


void avaliarPedido() {
    FILE *f = fopen("avaliacoes.txt", "a");
    char nomePedido[50], usuario[50];
    int nota;

    // Pega o usuário logado
    FILE *sessao = fopen("sessao.txt", "r");
    fscanf(sessao, "%s", usuario);
    fclose(sessao);

    printf("Digite o nome do pedido que deseja avaliar: ");
    scanf("%s", nomePedido);
    printf("Quantas estrelas esse pedido merece? (0 a 5): ");
    scanf("%d", &nota);

    if (nota < 0 || nota > 5) {
        printf("Nota inválida. Use um valor entre 0 e 5.\n");
        fclose(f);
        return;
    }

    fprintf(f, "Pedido: %s Usuário: %s Nota: %d\n", nomePedido, usuario, nota);
    fclose(f);

    printf("Avaliação registrada com sucesso!\n\n");
}
