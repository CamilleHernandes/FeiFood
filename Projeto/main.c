#include <stdio.h>
#include <string.h>

#include "funcoes.h"

int main(){
    int opcao;
    int logado = 0;

    do {
        if(!logado){
            printf("\n***** Menu FEIFood *****\n");
            printf("1. Cadastrar Usuário\n");
            printf("2. Login\n");
            printf("0. Sair\nEscolha: ");
            scanf("%d", &opcao);
        
         switch(opcao) {
                case 1:
                    cadastrarUsuario();
                    break;
                case 2:
                    if (loginUsuario()) {
                        printf("Login bem-sucedido!\n\n");
                        logado = 1;
                    } else {
                        printf("Falha no login.\n");
                    }
                    break;
                case 0:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opção inválida.\n");
        }
    }
    else{
            printf("******Bem-vindo(a)! O que deseja fazer agora?******\n");
            printf("1. Buscar alimento\n");
            printf("2. Listar informações de alimentos\n");
            printf("3. Cadastrar pedido\n");
            printf("4. Avaliar pedido\n");
            printf("5. Logout\n");
            printf("0. Sair\nEscolha: ");
            scanf("%d", &opcao);

            switch(opcao) {
                case 1: 
                    buscarAlimento(); 
                    break;
                case 2: 
                    //listarInformacoesAlimento();
                    break;
                case 3: 
                    menuPedidos();
                    break;
                case 4: 
                    avaliarPedido();
                    break;
                case 5:
                    logoutUsuario();
                    break;
                case 0:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opção inválida.\n");
            }
    }
} while(opcao != 0 & opcao != 5);

    return 0;
}

