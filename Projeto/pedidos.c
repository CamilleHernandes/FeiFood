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
    FILE *arquivoPedidos = fopen("pedidos.txt", "a");
    FILE *arquivoUserLogado = fopen("sessao.txt", "r");

    char nomePedido[50], alimento[50], observacao[100], usuarioLogado[50];
    int quantidadeAlimentos, quantidadeItem;

    fscanf(arquivoUserLogado, "%s", usuarioLogado);
    fclose(arquivoUserLogado);

    printf("\nDigite um nome para o pedido: ");
    scanf("%s", nomePedido);

    printf("Quantos alimentos deseja adicionar ao pedido?: ");
    scanf("%d", &quantidadeAlimentos);

    fprintf(arquivoPedidos, "%s %s ", nomePedido, usuarioLogado); // nome do pedido e usuário

    for (int i = 0; i < quantidadeAlimentos; i++) {
        printf("\nDigite o alimento %d: ", i + 1);
        scanf("%s", alimento);

        printf("Digite a quantidade do alimento %d: ", i + 1);
        scanf("%d", &quantidadeItem);

        fprintf(arquivoPedidos, "Item: %s Qtd: %d", alimento, quantidadeItem);

        if (i < quantidadeAlimentos - 1) {
            fprintf(arquivoPedidos, ";");
        }
    }

    printf("Deseja adicionar alguma observação? (ex: sem cebola, bem passado): ");
    scanf(" %[^\n]", observacao); // lê até o fim da linha

    fprintf(arquivoPedidos, " ;Obs: %s\n", observacao);
    fclose(arquivoPedidos);

    printf("Pedido criado com sucesso!\n");
}


void editarPedido() {
    // abre o arquivo original dos pedidos pra leitura
    FILE *arquivoPedidos = fopen("pedidos.txt", "r");

    // cria um arquivo temporário pra salvar os pedidos atualizados
    FILE *arquivoTemporario = fopen("temp_pedidos.txt", "w");

    // variáveis pra pegar o nome do pedido, novo nome (se for o caso), item que vai ser editado, e o usuário logado
    char nomePedido[50], novoNomePedido[50], itemAlvo[50], usuarioLogado[50];
    int novaQuantidade;
    char linhaPedido[500];
    int pedidoEncontrado = 0, opcao;

    // abre o arquivo da sessão pra saber quem tá logado
    FILE *arquivoUserLogado = fopen("sessao.txt", "r");
    fscanf(arquivoUserLogado, "%s", usuarioLogado);
    fclose(arquivoUserLogado);

    // menu de edição — o usuário escolhe o que quer alterar
    printf("\n*** O que deseja editar? ***\n");
    printf("1. Alterar nome do pedido\n");
    printf("2. Alterar quantidade de um item\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    // pega o nome do pedido que vai ser editado
    printf("Digite o nome do pedido que deseja editar: ");
    scanf("%s", nomePedido);

    // se for pra mudar o nome
    if (opcao == 1) {
        printf("Digite o novo nome para o pedido: ");
        scanf("%s", novoNomePedido);
    }
    // se for pra mudar a quantidade de um item
    else if (opcao == 2) {
        printf("Digite o nome do item que deseja alterar a quantidade: ");
        scanf("%s", itemAlvo);
        printf("Digite a nova quantidade: ");
        scanf("%d", &novaQuantidade);
    }
    // se escolher algo inválido
    else {
        printf("Opção inválida.\n");
        fclose(arquivoPedidos);
        fclose(arquivoTemporario);
        return;
    }

    // começa a ler cada linha do arquivo de pedidos
    while (fgets(linhaPedido, sizeof(linhaPedido), arquivoPedidos)) {
        char nomeLinha[50], usuarioLinha[50], observacao[100];
        char itensBrutos[300], itensCopia[300], novaLista[300];
        novaLista[0] = '\0'; // garante que a lista começa vazia

        // separa nome do pedido e usuário
        sscanf(linhaPedido, "%s %s", nomeLinha, usuarioLinha);

        // verifica se é o pedido certo e se é do usuário logado
        if (strcmp(nomeLinha, nomePedido) == 0 && strcmp(usuarioLinha, usuarioLogado) == 0) {
            pedidoEncontrado = 1;

            // pega onde começam os itens e a observação
            char *inicioItens = strstr(linhaPedido, "Item:");
            char *inicioObs = strstr(linhaPedido, "Obs:");

            // se não tiver os dois, ignora essa linha
            if (inicioItens == NULL || inicioObs == NULL) {
                printf("Formato do pedido inválido.\n");
                continue;
            }

            // copia só os itens (sem a observação)
            strncpy(itensBrutos, inicioItens, inicioObs - inicioItens);
            itensBrutos[inicioObs - inicioItens] = '\0';

            // faz uma cópia dos itens pra usar com strtok
            strcpy(itensCopia, itensBrutos);

            // copia a observação certinha
            sscanf(inicioObs, "Obs: %[^\n]", observacao);

            // se for pra editar a quantidade de um item
            if (opcao == 2) {
                char *itemAtual = strtok(itensCopia, ";");
                int primeiroItem = 1;

                // percorre cada item do pedido
                while (itemAtual != NULL) {
                    char nomeItem[50];
                    int quantidadeAtual;

                    // extrai o nome e a quantidade do item
                    sscanf(itemAtual, "Item: %s Qtd: %d", nomeItem, &quantidadeAtual);

                    // se for o item que queremos editar, atualiza a quantidade
                    if (strcmp(nomeItem, itemAlvo) == 0) {
                        quantidadeAtual = novaQuantidade;
                    }

                    // monta a nova lista com controle do ponto e vírgula
                    if (!primeiroItem) strcat(novaLista, ";");
                    sprintf(novaLista + strlen(novaLista), "Item: %s Qtd: %d", nomeItem, quantidadeAtual);
                    primeiroItem = 0;

                    // vai pro próximo item
                    itemAtual = strtok(NULL, ";");
                }
            }
            // se for pra mudar o nome do pedido, só copia os itens
            else {
                strcpy(novaLista, itensBrutos);
            }

            // salva a linha atualizada no arquivo temporário
            fprintf(arquivoTemporario, "%s %s %s ;Obs: %s\n",
                    (opcao == 1 ? novoNomePedido : nomeLinha),
                    usuarioLinha,
                    novaLista,
                    observacao);

            printf("Pedido editado com sucesso!\n");
        } else {
            // se não for o pedido que queremos, só copia pro arquivo temporário
            fputs(linhaPedido, arquivoTemporario);
        }
    }

    // fecha os arquivos
    fclose(arquivoPedidos);
    fclose(arquivoTemporario);

    // substitui o arquivo original pelo atualizado
    remove("pedidos.txt");
    rename("temp_pedidos.txt", "pedidos.txt");

    // se não achou o pedido, avisa
    if (!pedidoEncontrado) {
        printf("Pedido não encontrado ou não pertence ao usuário logado.\n");
    }
}



void excluirPedido() {
    FILE *arqpedidos = fopen("pedidos.txt", "r");
    FILE *arqaux = fopen("aux.txt", "w");
    char nomePedido[50], usuario[50];
    char linha[300];
    int encontrado = 0;

    // Pega o usuário logado
    FILE *arquivoUserLogado = fopen("sessao.txt", "r");
    fscanf(arquivoUserLogado, "%s", usuario);
    fclose(arquivoUserLogado);

    printf("Digite o nome do pedido que deseja excluir: ");
    scanf("%s", nomePedido);

    while (fgets(linha, sizeof(linha), arqpedidos)) {
        char linhaNome[50], linhaUsuario[50];

        sscanf(linha, "%s %s", linhaNome, linhaUsuario);

        if (strcmp(linhaNome, nomePedido) == 0 && strcmp(linhaUsuario, usuario) == 0) {
            encontrado = 1;
            // Não copia a linha — exclui
        } else {
            fputs(linha, arqaux); // mantém os outros pedidos
        }
    }

    fclose(arqpedidos);
    fclose(arqaux);
    remove("pedidos.txt");
    rename("aux.txt", "pedidos.txt");

    if (encontrado)
        printf("Pedido excluído com sucesso!\n");
    else
        printf("Pedido não encontrado ou não pertence ao usuário logado.\n");
}


void adicionarAlimentoPedido() {
    FILE *arquivoPedidos = fopen("pedidos.txt", "r");

    // cria um arquivo temporário pra salvar os pedidos atualizados
    FILE *arquivoTemporario = fopen("temp_pedidos.txt", "w");

    // variáveis pra pegar o nome do pedido, o novo item, a quantidade e o usuário logado
    char nomePedido[50], novoItem[50], usuarioLogado[50];
    int novaQuantidade;
    char linhaPedido[500];
    int pedidoEncontrado = 0;

    // abre o arquivo da sessão pra saber quem tá logado
    FILE *arquivoUserLogado = fopen("sessao.txt", "r");
    fscanf(arquivoUserLogado, "%s", usuarioLogado);
    fclose(arquivoUserLogado);

    // pega as infos do usuário
    printf("Digite o nome do pedido que deseja alterar: ");
    scanf("%s", nomePedido);
    printf("Digite o nome do item que deseja adicionar: ");
    scanf("%s", novoItem);
    printf("Digite a quantidade: ");
    scanf("%d", &novaQuantidade);

    // começa a ler cada linha do arquivo de pedidos
    while (fgets(linhaPedido, sizeof(linhaPedido), arquivoPedidos)) {
        char nomeLinha[50], usuarioLinha[50];
        char itens[300], observacao[200];
        char novaLista[400] = "";

        // separa nome do pedido e usuário
        sscanf(linhaPedido, "%s %s", nomeLinha, usuarioLinha);

        // verifica se é o pedido certo e se é do usuário logado
        if (strcmp(nomeLinha, nomePedido) == 0 && strcmp(usuarioLinha, usuarioLogado) == 0) {
            pedidoEncontrado = 1;

            // pega onde começam os itens e a observação
            char *inicioItens = strstr(linhaPedido, "Item:");
            char *inicioObs = strstr(linhaPedido, "Obs:");

            if (inicioItens == NULL || inicioObs == NULL) {
                printf("Formato do pedido inválido.\n");
                continue;
            }

            // copia só os itens (sem a parte da observação)
            strncpy(itens, inicioItens, inicioObs - inicioItens);
            itens[inicioObs - inicioItens] = '\0';

            // copia a observação certinha
            strcpy(observacao, inicioObs);

            // verifica se já termina com ponto e vírgula
            int len = strlen(itens);
            if (len > 0 && itens[len - 1] == ';') {
                // já tem ; no final, só adiciona o novo item
                sprintf(novaLista, "%sItem: %s Qtd: %d", itens, novoItem, novaQuantidade);
            } else {
                // precisa adicionar o ;
                sprintf(novaLista, "%s;Item: %s Qtd: %d", itens, novoItem, novaQuantidade);
            }

            // salva a linha atualizada no arquivo temporário
            fprintf(arquivoTemporario, "%s %s %s ;%s\n", nomeLinha, usuarioLinha, novaLista, observacao);
            printf("Item adicionado com sucesso!\n");
        } else {
            // se não for o pedido que queremos, só copia pro arquivo temporário
            fputs(linhaPedido, arquivoTemporario);
        }
    }

    // fecha os arquivos
    fclose(arquivoPedidos);
    fclose(arquivoTemporario);

    // substitui o arquivo original pelo atualizado
    remove("pedidos.txt");
    rename("temp_pedidos.txt", "pedidos.txt");

    // se não achou o pedido, avisa
    if (!pedidoEncontrado) {
        printf("Pedido não encontrado ou não pertence ao usuário logado.\n");
    }
}

void removerAlimentoPedido() {
    FILE *arquivoPedidos = fopen("pedidos.txt", "r");

    // cria um arquivo temporário pra salvar os pedidos atualizados
    FILE *arquivoTemporario = fopen("temp_pedidos.txt", "w");

    // variáveis pra pegar o nome do pedido, o item que vai ser removido e o usuário logado
    char nomePedido[50], itemRemover[50], usuarioLogado[50];
    char linhaPedido[500];
    int pedidoEncontrado = 0;

    // abre o arquivo da sessão pra saber quem tá logado
    FILE *arquivoUserLogado = fopen("sessao.txt", "r");
    fscanf(arquivoUserLogado, "%s", usuarioLogado);
    fclose(arquivoUserLogado);

    // pega as infos do usuário
    printf("\nDigite o nome do pedido que deseja editar: ");
    scanf("%s", nomePedido);
    printf("Digite o nome do item que deseja remover: ");
    scanf("%s", itemRemover);

    // começa a ler cada linha do arquivo de pedidos
    while (fgets(linhaPedido, sizeof(linhaPedido), arquivoPedidos)) {
        char nomeLinha[50], usuarioLinha[50];
        char itensBrutos[300], observacao[200];
        char novaLista[300] = "";
        int totalItens = 0;

        // separa nome do pedido e usuário
        sscanf(linhaPedido, "%s %s", nomeLinha, usuarioLinha);

        // verifica se é o pedido certo e se é do usuário logado
        if (strcmp(nomeLinha, nomePedido) == 0 && strcmp(usuarioLinha, usuarioLogado) == 0) {
            pedidoEncontrado = 1;

            // separa a parte dos itens da parte da observação
            char *inicioItens = strstr(linhaPedido, "Item:");
            char *inicioObs = strstr(linhaPedido, "Obs:");

            // se não tiver os dois, ignora essa linha
            if (inicioItens == NULL || inicioObs == NULL) {
                continue;
            }

            // copia só os itens
            strncpy(itensBrutos, inicioItens, inicioObs - inicioItens);
            itensBrutos[inicioObs - inicioItens] = '\0'; // finaliza a string certinho

            // copia a observação inteira
            sscanf(inicioObs, "Obs: %[^\n]", observacao);

            // separa os itens usando o ponto e vírgula
            char *itemAtual = strtok(itensBrutos, ";");
            int primeiroItem = 1;

            // percorre cada item do pedido
            while (itemAtual != NULL) {
                char nomeItem[50];
                int quantidadeAtual;

                // extrai o nome e a quantidade do item
                sscanf(itemAtual, "Item: %s Qtd: %d", nomeItem, &quantidadeAtual);

                // se for o item que queremos remover, ignora ele
                if (strcmp(nomeItem, itemRemover) != 0) {
                    if (!primeiroItem) strcat(novaLista, ";");
                    sprintf(novaLista + strlen(novaLista), "Item: %s Qtd: %d", nomeItem, quantidadeAtual);
                    primeiroItem = 0;
                    totalItens++;
                }

                // vai pro próximo item
                itemAtual = strtok(NULL, ";");
            }

            // se não sobrou nenhum item, exclui o pedido
            if (totalItens == 0) {
                printf("Item removido e pedido excluído por não ter mais itens.\n");
                continue; // não escreve nada no arquivo temporário
            }

            // salva a linha atualizada no arquivo temporário
            fprintf(arquivoTemporario, "%s %s %s ;Obs: %s\n", nomeLinha, usuarioLinha, novaLista, observacao);
            printf("\nItem removido com sucesso!\n");
        } else {
            // se não for o pedido que queremos, só copia pro arquivo temporário
            fputs(linhaPedido, arquivoTemporario);
        }
    }

    // fecha os arquivos
    fclose(arquivoPedidos);
    fclose(arquivoTemporario);

    // substitui o arquivo original pelo atualizado
    remove("pedidos.txt");
    rename("temp_pedidos.txt", "pedidos.txt");

    // se não achou o pedido, avisa
    if (!pedidoEncontrado) {
        printf("Pedido não encontrado ou não pertence ao usuário logado.\n");
    }
}


void avaliarPedido() {
    FILE *avaliacao = fopen("avaliacoes.txt", "a");
    char nomePedido[50], usuario[50];
    int nota;

    // Pega o usuário logado
    FILE *arquivoUserLogado = fopen("sessao.txt", "r");
    fscanf(arquivoUserLogado, "%s", usuario);
    fclose(arquivoUserLogado);

    printf("Digite o nome do pedido que deseja avaliar: ");
    scanf("%s", nomePedido);
    printf("Quantas estrelas esse pedido merece? (0 a 5): ");
    scanf("%d", &nota);

    if (nota < 0 || nota > 5) {
        printf("Nota inválida. Use um valor entre 0 e 5.\n");
        fclose(avaliacao);
        return;
    }

    fprintf(avaliacao, "Pedido: %s Usuário: %s Nota: %d\n", nomePedido, usuario, nota);
    fclose(avaliacao);

    printf("Avaliação registrada com sucesso!\n\n");
}
