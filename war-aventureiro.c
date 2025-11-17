#include <stdio.h>
#include <stdlib.h> // Para calloc, free, rand, srand
#include <string.h> // Para strcspn, strcpy, strcmp
#include <time.h>   // Para srand(time(NULL))

// --- Constantes Globais ---
#define MAX_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

// --- Estrutura de Dados ---
// (Mesma struct do Nível Novato)
struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// --- Protótipos das Funções ---
void limparBufferEntrada();
void pausar();
void exibirMapa(const struct Territorio *mapa); // (Boas práticas, usa 'const')
void simularAtaque(struct Territorio *mapa);    // (Recebe o ponteiro para modificar)

// --- Função Principal (main) ---
int main() {
    int i, opcao;

    // Inicializa a semente para números aleatórios
    srand(time(NULL)); 

    // --- 1. Alocação Dinâmica ---
    // Substitui o vetor estático por alocação dinâmica com calloc
    struct Territorio *mapaMundi = (struct Territorio *)calloc(MAX_TERRITORIOS, sizeof(struct Territorio));

    // Verifica se a alocação de memória falhou
    if (mapaMundi == NULL) {
        printf("Erro fatal! Nao foi possivel alocar memoria para o mapa.\n");
        return 1; // Encerra o programa com erro
    }

    // --- 2. Cadastro Inicial (Similar ao Novato) ---
    printf("=================================\n");
    printf("  DESAFIO WAR - NIVEL AVENTUREIRO\n");
    printf("=================================\n");
    printf("Cadastre os %d territorios iniciais.\n\n", MAX_TERRITORIOS);

    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do Territorio: ");
        fgets(mapaMundi[i].nome, TAM_NOME, stdin);
        mapaMundi[i].nome[strcspn(mapaMundi[i].nome, "\n")] = '\0';

        printf("Cor do Exercito: ");
        fgets(mapaMundi[i].cor, TAM_COR, stdin);
        mapaMundi[i].cor[strcspn(mapaMundi[i].cor, "\n")] = '\0';

        printf("Numero de Tropas: ");
        scanf("%d", &mapaMundi[i].tropas);
        limparBufferEntrada();
        printf("\n");
    }

    printf("Cadastro inicial concluido!\n\n");
    pausar();

    // --- 3. Laço Interativo de Jogo ---
    // (Laço interativo para o jogador escolher)
    do {
        exibirMapa(mapaMundi); // Mostra o mapa a cada rodada

        printf("\n--- FASE DE COMANDO ---\n");
        printf("1. Atacar\n");
        printf("0. Sair (Encerrar Jogo)\n");
        printf("Escolha sua acao: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                simularAtaque(mapaMundi); //
                pausar();
                break;
            case 0:
                printf("\nEncerrando o jogo... Obrigado por jogar!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
                break;
        }

    } while (opcao != 0);

    // --- 4. Limpeza ---
    // Libera a memória alocada com calloc
    free(mapaMundi);

    return 0;
}


// --- Implementação das Funções ---

// exibirMapa(): Mostra o estado atual dos territórios
// Usa 'const' para garantir que a função apenas LEIA os dados
void exibirMapa(const struct Territorio *mapa) {
    printf("\n=======================================================\n");
    printf("                MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("-------------------------------------------------------\n");
    printf("| ID | TERRITORIO | EXERCITO (COR) | TROPAS |\n");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("| %-2d | %-10s | %-14s | %-6d |\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
    printf("=======================================================\n");
}

// simularAtaque(): Lógica de batalha
void simularAtaque(struct Territorio *mapa) {
    int idAtacante, idDefensor;

    // Entrada: Escolha de atacante e defensor
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio de ATAQUE (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &idAtacante);
    printf("Escolha o territorio de DEFESA (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &idDefensor);
    limparBufferEntrada();

    // Converte a entrada do usuário (1-5) para índice de vetor (0-4)
    idAtacante--;
    idDefensor--;

    // --- Validações ---
    // Verifica se os IDs são válidos
    if (idAtacante < 0 || idAtacante >= MAX_TERRITORIOS || idDefensor < 0 || idDefensor >= MAX_TERRITORIOS) {
        printf("Ataque invalido! IDs de territorio nao existem.\n");
        return;
    }
    // Verifica se o atacante tem tropas suficientes (precisa ter > 1 para atacar)
    if (mapa[idAtacante].tropas < 2) {
        printf("Ataque invalido! %s precisa ter pelo menos 2 tropas para atacar.\n", mapa[idAtacante].nome);
        return;
    }
    // Verifica se não está atacando um território próprio
    if (strcmp(mapa[idAtacante].cor, mapa[idDefensor].cor) == 0) {
        printf("Ataque invalido! Nao pode atacar um territorio que ja e seu.\n");
        return;
    }

    // --- Lógica da Batalha (Dados) ---
    printf("\nBatalha: %s (%d tropas) ataca %s (%d tropas)\n",
           mapa[idAtacante].nome, mapa[idAtacante].tropas,
           mapa[idDefensor].nome, mapa[idDefensor].tropas);

    // Simulação de dados de ataque e defesa
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dados: Atacante [ %d ] vs Defensor [ %d ]\n", dadoAtacante, dadoDefensor);

    // Lógica: Empates favorecem o atacante
    if (dadoAtacante >= dadoDefensor) {
        printf("Atacante venceu a batalha! %s (defensor) perde 1 tropa.\n", mapa[idDefensor].nome);
        mapa[idDefensor].tropas--; //

        // Verifica se o território foi conquistado
        if (mapa[idDefensor].tropas == 0) {
            printf(">>> CONQUISTA! <<< %s tomou %s do exercito %s!\n",
                   mapa[idAtacante].nome, mapa[idDefensor].nome, mapa[idDefensor].cor);
            
            // Transfere a propriedade (cor)
            strcpy(mapa[idDefensor].cor, mapa[idAtacante].cor);
            
            // Move 1 tropa do atacante para o novo território
            mapa[idDefensor].tropas = 1;
            mapa[idAtacante].tropas--;
        }
    } else {
        printf("Defensor venceu a batalha! %s (atacante) perde 1 tropa.\n", mapa[idAtacante].nome);
        mapa[idAtacante].tropas--;
    }
}

// limparBufferEntrada(): Limpa o buffer de entrada (stdin)
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// pausar(): Espera o usuário pressionar Enter
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar(); // Pega o '\n' que sobrou do último scanf ou o novo
}