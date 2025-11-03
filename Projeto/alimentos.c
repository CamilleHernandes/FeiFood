#include <stdio.h>
#include<string.h>

#include"funcoes.h"

void buscarAlimento() {
    // abre o arquivo de alimentos pra leitura
    FILE *alim = fopen("alimentos.txt", "r");
    // abre o arquivo de alimentos buscados pra adicionar
    FILE *buscados = fopen("buscados.txt", "a");

    char nomeBusca[50], nome[50];
    float preco;
    int encontrado = 0;

    printf("\nQual alimento que deseja buscar?: ");
    scanf("%s", nomeBusca);

    // percorre o arquivo de alimentos procurando o nome
    while (fscanf(alim, "%s %f", nome, &preco) != EOF) {
        // se encontrar, mostra na tela e salva no arquivo de buscados
        if (strcmp(nomeBusca, nome) == 0) {
            printf("\nAlimento encontrado: %s - R$ %.2f\n", nome, preco);
            fprintf(buscados, "%s %.2f\n\n", nome, preco);
            encontrado = 1;
            break; 
        }
    }

    // fecha os arquivos
    fclose(alim);
    fclose(buscados);

    if (!encontrado) {
        printf("Alimento não encontrado.\n");
    }
}


void listarAlimentosBuscados() {
    // abre o arquivo de alimentos buscados pra leitura
    FILE *busca = fopen("buscados.txt", "r");
    // variáveis pra guardar o nome e o preço de cada alimento buscado
    char nome[50];
    float preco;

    printf("\n****Alimentos buscados****\n");

    // percorre o arquivo e mostra cada alimento buscado
    while (fscanf(busca, "%s %f", nome, &preco) != EOF) {
        printf("%s - R$ %.2f\n\n", nome, preco);
    }

    // fecha o arquivo
    fclose(busca);
}

