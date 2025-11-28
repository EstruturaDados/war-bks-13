#include <stdio.h>
#include <string.h>


//Estrutura que representa os territorios

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    struct Territorio territorios[5];

    printf("===================================\n");
    printf(" WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("===================================\n\n");

    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n\n");

    // Laço onde sera feito o cadastro dos territorios 
    for (int i = 0; i < 5; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf("%s", territorios[i].cor);

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    printf("Cadastro Inicial concluido com sucesso!\n\n");

    // Mostra as respostas preenchida pelo usuario referente aos territorios
    printf("==============================\n");
    printf(" MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("==============================\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);
        printf("    - Nome: %s\n", territorios[i].nome);
        printf("    - Dominado por: Exercito %s\n", territorios[i].cor); 
        printf("    - Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}
