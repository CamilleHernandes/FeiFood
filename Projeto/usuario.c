#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>


void cadastrarUsuario() {
    FILE *f = fopen("usuarios.txt", "a");
    char nome[50], senha[20];
    printf("Nome: ");
    scanf("%s", nome);
    printf("Senha: ");
    scanf("%s", senha);
    fprintf(f, "%s %s\n", nome, senha);
    fclose(f);
}

int loginUsuario() {
    FILE *f = fopen("usuarios.txt", "r");
    char nome[50], senha[20], nomeLido[50], senhaLida[20];
    printf("Nome: ");
    scanf("%s", nome);
    printf("Senha: ");
    scanf("%s", senha);
    while (!feof(f)) {
        fscanf(f, "%s %s", nomeLido, senhaLida);
        if (strcmp(nome, nomeLido) == 0 && strcmp(senha, senhaLida) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}


