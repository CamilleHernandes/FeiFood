#include <stdio.h>
#include<string.h>

#include"funcoes.h"

void buscarAlimento() {
    FILE *alim = fopen("alimentos.txt", "r");
    FILE *buscados = fopen("buscados.txt", "a");
    char nomeBusca[50], nome[50];
    float preco;
    int encontrado = 0;

    printf("\nQual alimento que deseja buscar?: ");
    scanf("%s", nomeBusca);

    while (fscanf(alim, "%s %f", nome, &preco) != EOF) {
        if (strcmp(nomeBusca, nome) == 0) {
            printf("\nAlimento encontrado: %s - R$ %.2f\n", nome, preco);
            fprintf(buscados, "%s %.2f\n\n", nome, preco);
            encontrado = 1;
            break;
        }
    }

    fclose(alim);
    fclose(buscados);

    if (!encontrado) {
        printf("Alimento não encontrado.\n");
    }
}


void listarAlimentosBuscados() {
    FILE *busca = fopen("buscados.txt", "r");
    char nome[50];
    float preco;

    printf("\n****Alimentos buscados****\n");

    while (fscanf(busca, "%s %f", nome, &preco) != EOF) {
        printf("%s - R$ %.2f\n\n", nome, preco);
    }

    fclose(busca);
}
