#include <stdio.h>
#include<string.h>

#include"funcoes.h"

void buscarAlimento() {
    FILE *f = fopen("alimentos.txt", "r");
    char busca[50], nome[50], preco[10];

    printf("Digite o nome ou parte do nome do alimento: ");
    scanf("%s", busca);

    if (f == NULL) {
        printf("Arquivo de alimentos não encontrado.\n");
        return;
    }

    printf("\n--- Alimentos encontrados ---\n");
    while (fscanf(f, "%s %s", nome, preco) != EOF) {
        if (strstr(nome, busca)) {
            listarInformacoesAlimento(nome, preco);
        }
    }

    fclose(f);
}

void listarInformacoesAlimento(char nome[], char preco[]) {
    printf("Nome: %s\n", nome);
    printf("Preço: R$%s\n", preco);
    printf("-------------------------\n");
}