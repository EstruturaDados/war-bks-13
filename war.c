#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Estrutura que representa os territorios
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

//Funçao de ataque/defensor de cada Territorio, utilizando rand para aleatoridade dos dados

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

//Tratamento para favorecer o atacante caso empate
    if (dadoAtacante >= dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;
// Se o defensor fica sem tropas, ele é conquistado
        if (defensor->tropas <= 0) {
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s.\n",
                   defensor->nome, atacante->cor);
// Caso o terriotiro venha a ser conquistado, ele passa a ter a cor do vencedor
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2;
        }
    } else {
// Se o defensor vencer, o atacante perdera 1 tropa
        printf("DEFESA RESISTIU! O atacante perdeu 1 tropa.\n");
// Territorio atacante nao pode ficar com menos de 1 tropa
        atacante->tropas--;
        if (atacante->tropas < 1)
            atacante->tropas = 1;
    }
}

int main() {
//Utilizado para nao repetir sempre os mesmo valores do dado
    srand(time(NULL));

    int total = 5;  
    struct Territorio* territorios;

//Alocação da memoria para armazenar os territorios
    territorios = (struct Territorio*) calloc(total, sizeof(struct Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("===================================\n");
    printf(" WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("===================================\n\n");

// Laço onde sera feito o cadastro dos territorios 
    for (int i = 0; i < total; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf("%s", territorios[i].cor);

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

//Exibe o mapa apos cadastro de territorios
    printf("\n==============================\n");
    printf(" MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("==============================\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n",
               i + 1,
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas);
    }

//Laço de ataque, ate o usuario digitar 0 para sair
    int atk, def;
    for (;;) {
        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", total);
        scanf("%d", &atk);
//Se digitar 0 o jogo acaba
        if (atk == 0) {
            printf("Jogo encerrado e memoria liberada. Ate a proxima!\n");
            break;
        }
//Validação se o numero é valido
        if (atk < 1 || atk > total) {
            printf("Opcao invalida!\n");
            continue;
        }

        printf("Escolha o territorio defensor (1 a %d): ", total);
        scanf("%d", &def);

        if (def < 1 || def > total) {
            printf("Opcao invalida!\n");
            continue;
        }
//Ajuste de indice do vetor, devido usuario digitar 1 e 5
        atk--;
        def--;
//Validação para nao ocorrer ataque entre mesma cor de exercito
        if (strcmp(territorios[atk].cor, territorios[def].cor) == 0) {
            printf("Nao eh possivel atacar um territorio da mesma cor!\n");
            continue;
        }

        atacar(&territorios[atk], &territorios[def]);

//Exibe o mapa atualizado apos o ataque
        printf("\n==============================\n");
        printf(" MAPA DO MUNDO - ESTADO ATUAL\n");
        printf("==============================\n");
        for (int i = 0; i < total; i++) {
            printf("%d. %s (Exercito %s, Tropas: %d)\n",
                   i + 1,
                   territorios[i].nome,
                   territorios[i].cor,
                   territorios[i].tropas);
        }
    }
//Libera a memoria que foi alocada
    free(territorios);
    return 0;
}
