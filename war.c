#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa os territórios
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função criadar para exibir o mapa do mundo
void exibirMapa(struct Territorio* mapa, int tamanho) {
    printf("\n=============== MAPA DO MUNDO ==================\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %-12s (Exercito: %-7s, Tropas: %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("================================================\n");
}

// Função que sorteia e atribui a missao para o jogador
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    *destino = (char*) malloc(strlen(missoes[indice]) + 1);
    strcpy(*destino, missoes[indice]);
}

// Função de exibição da missao no inicio
void exibirMissao(char* missao, char* exercito) {
    printf("\n--- SUA MISSÃO (Exercito %s) ---\n%s\n\n", exercito, missao);
}

// Função de ataque dos territorios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Ataque (%s): %d | Defesa (%s): %d\n",
           atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;
        // // Se o defensor fica sem tropas, ele é conquistado
        if (defensor->tropas <= 0) {
            printf("CONQUISTA! O territorio%s foi dominado pelo Exercito%s\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2; 
        }
    } else {
        // Se o defensor vencer, o atacante perdera 1 tropa
        printf("DEFESA RESISTIU! O atacante perdeu 1 tropa.\n");
        // Territorio atacante nao pode ficar com menos de 1 tropa
        atacante->tropas--;
        if (atacante->tropas < 1) atacante->tropas = 1; 
    }

    printf("Pressione Enter para continuar...");
    scanf("%*c");
}

// Validação da missao se ela foi cumprida
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Destruir o exercito Verde") == 0) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0)
                return 0; 
        return 1; 
    }
    if (strcmp(missao, "Destruir o exercito Vermelho") == 0) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0)
                return 0;
        return 1;
    }
    if (strcmp(missao, "Destruir o exercito Amarelo") == 0) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "Amarelo") == 0 && mapa[i].tropas > 0)
                return 0;
        return 1;
    }

    // Missoes para conquistar o territorio
    if (strcmp(missao, "Conquistar America e Europa") == 0) {
        int conquistou = 0;
        for (int i = 0; i < tamanho; i++)
            if ((strcmp(mapa[i].nome, "America") == 0 || strcmp(mapa[i].nome, "Europa") == 0) &&
                strcmp(mapa[i].cor, "Azul") == 0)
                conquistou++;
        return (conquistou == 2);
    }

    if (strcmp(missao, "Conquistar Asia e Africa") == 0) {
        int conquistou = 0;
        for (int i = 0; i < tamanho; i++)
            if ((strcmp(mapa[i].nome, "Asia") == 0 || strcmp(mapa[i].nome, "Africa") == 0) &&
                strcmp(mapa[i].cor, "Azul") == 0)
                conquistou++;
        return (conquistou == 2);
    }

    return 0; 
}

// Função para liberar memória alocada durante o jogo
void liberarMemoria(struct Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {
    //Utilizado para nao repetir sempre os mesmo valores do dado
    srand(time(NULL));

    int total = 5;
    struct Territorio* territorios = (struct Territorio*) calloc(total, sizeof(struct Territorio));
    if (!territorios) { printf("Erro ao alocar memoria.\n"); return 1; }

    // Inicializa o mapa fixo
    strcpy(territorios[0].nome, "America"); strcpy(territorios[0].cor, "Verde"); territorios[0].tropas = 4;
    strcpy(territorios[1].nome, "Europa"); strcpy(territorios[1].cor, "Azul"); territorios[1].tropas = 2;
    strcpy(territorios[2].nome, "Asia"); strcpy(territorios[2].cor, "Vermelho"); territorios[2].tropas = 2;
    strcpy(territorios[3].nome, "Africa"); strcpy(territorios[3].cor, "Amarelo"); territorios[3].tropas = 4;
    strcpy(territorios[4].nome, "Oceania"); strcpy(territorios[4].cor, "Branco"); territorios[4].tropas = 1;

    // Vetores das missoes
    char* missoes[5] = {
        "Destruir o exercito Verde",
        "Destruir o exercito Vermelho",
        "Destruir o exercito Amarelo",
        "Conquistar America e Europa",
        "Conquistar Asia e Africa"
    };

    char* missaoJogador;
    atribuirMissao(&missaoJogador, missoes, 5);

    // Exibir mapa e missão apenas uma vez no início
    exibirMapa(territorios, total);
    exibirMissao(missaoJogador, "Azul");

    int opcao;
    while (1) {
        // Menu
        printf("--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d", &opcao);
        scanf("%*c"); 

        if (opcao == 0) {
            printf("Encerrando o jogo...\n");
            liberarMemoria(territorios, missaoJogador);
            printf("Memoria liberada com sucesso.\n");
            break;
        }

        if (opcao == 1) {
            int atk, def;
            printf("--- FASE DE ATAQUE ---\n");
            printf("Escolha o territorio atacante (1 a %d): ", total);
            scanf("%d", &atk);
            printf("Escolha o territorio defensor (1 a %d): ", total);
            scanf("%d", &def);
            scanf("%*c");

            atk--; def--;
            if (strcmp(territorios[atk].cor, territorios[def].cor) == 0) {
                printf("Nao eh possivel atacar um territorio da mesma cor!\n");
                printf("Pressione Enter para continuar...");
                scanf("%*c");
                continue;
            }

            atacar(&territorios[atk], &territorios[def]);
            exibirMapa(territorios, total);

            // Verificação silenciosa da missão
            if (verificarMissao(missaoJogador, territorios, total)) {
                printf("\nPARABENS! Voce cumpriu sua missao e venceu o jogo!\n");
                liberarMemoria(territorios, missaoJogador);
                break;
            }
        }
        else if (opcao == 2) {
            // Informa se a missao foi cumprida
            if (verificarMissao(missaoJogador, territorios, total))
                printf("Parabens! Voce cumpriu sua missao!\n");
            else
                printf("Voce ainda nao cumpriu sua missao. Continue a lutar.\n\n");
            printf("Pressione Enter para continuar...");
            scanf("%*c");
        }
        else {
            printf("Opcao invalida!\n");
            printf("Pressione Enter para continuar...");
            scanf("%*c");
        }
    }

    return 0;
}
