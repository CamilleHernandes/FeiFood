#include <stdio.h>
#include <string.h>

void cadastrarUsuario() {
    FILE *f = fopen("usuarios.txt", "a");
    char nome[50], senha[20], email[100];

    printf("Nome: ");
    scanf("%s", nome);
    printf("Email: ");
    scanf("%s", email);
    printf("Senha: ");
    scanf("%s", senha);


    fprintf(f, "%s %s %s\n", nome, email,senha);
    fclose(f);

    printf("Usuário cadastrado com sucesso!\n");
}


int loginUsuario() {
    FILE *f = fopen("usuarios.txt", "r");
    char nome[50], senha[20], nomeLido[50], emailLido[100], senhaLida[20];
    int logado = 0;

    printf("Nome: ");
    scanf("%s", nome);
    printf("Senha: ");
    scanf("%s", senha);

    while (fscanf(f, "%s %s %s", nomeLido, emailLido, senhaLida) != EOF) {
        if (strcmp(nome, nomeLido) == 0 && strcmp(senha, senhaLida) == 0) {
            logado = 1;
            break;
        }
    }
    fclose(f);

    if (logado) {
        FILE *sessao = fopen("sessao.txt", "w");
        fprintf(sessao, "%s", nome);
        fclose(sessao);
        printf("Login realizado com sucesso!\n");
        return 1;
    } else {
        printf("Usuário ou senha incorretos.\n");
        return 0;
    }
}



// Desloga o usuário removendo o arquivo de sessão
void logoutUsuario() {
    if (remove("sessao.txt") == 0) {
        printf("Logout realizado com sucesso!\n");
    } else {
        printf("Nenhum usuário estava logado.\n");
    }
}

// Mostra o nome do usuário logado
void mostrarUsuarioLogado() {
    char nome[50];
    FILE *sessao = fopen("sessao.txt", "r");
    if (sessao != NULL) {
        fscanf(sessao, "%s", nome);
        fclose(sessao);
        printf("Usuário logado: %s\n", nome);
    } else {
        printf("Nenhum usuário está logado.\n");
    }
}

