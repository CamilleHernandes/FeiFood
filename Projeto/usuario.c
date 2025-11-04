#include <stdio.h>
#include <string.h>

void cadastrarUsuario() {
    FILE *usuarios = fopen("usuarios.txt", "a");
    char nome[50], senha[20], email[100];

    printf("Nome: ");
    scanf("%s", nome);
    printf("Email: ");
    scanf("%s", email);
    printf("Senha: ");
    scanf("%s", senha);


    fprintf(usuarios, "%s %s %s\n", nome, email,senha);
    fclose(usuarios);

    printf("Usuário cadastrado com sucesso!\n");
}


int loginUsuario() {
    FILE *usuarios = fopen("usuarios.txt", "r");
    char nome[50], senha[20], nomeLido[50], emailLido[100], senhaLida[20];
    int logado = 0;

    printf("Nome: ");
    scanf("%s", nome);
    printf("Senha: ");
    scanf("%s", senha);

    while (fscanf(usuarios, "%s %s %s", nomeLido, emailLido, senhaLida) != EOF) { // o while lê cada linha do arquivo usuarios.txt
        if (strcmp(nome, nomeLido) == 0 && strcmp(senha, senhaLida) == 0) {
            logado = 1;
            break;
        }
    }
    fclose(usuarios);

    if (logado) {
        FILE *arquivoUserLogado = fopen("sessao.txt", "w");
        fprintf(arquivoUserLogado, "%s", nome);
        fclose(arquivoUserLogado);
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

        // Limpa o conteúdo do arquivo buscados.txt para um novo usuario
        FILE *limpaUser = fopen("buscados.txt", "w");
        fclose(limpaUser);
    } else {
        printf("Nenhum usuário estava logado.\n");
    }
}

// Mostra o nome do usuário logado
void mostrarUsuarioLogado() {
    char nome[50];
    FILE *arquivoUserLogado = fopen("sessao.txt", "r");
    if (arquivoUserLogado != NULL) {
        fscanf(arquivoUserLogado, "%s", nome);
        fclose(arquivoUserLogado);
        printf("Usuário logado: %s\n", nome);
    } else {
        printf("Nenhum usuário está logado.\n");
    }
}

