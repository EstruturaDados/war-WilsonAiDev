// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO (NÍVEL MESTRE)
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias
#include <stdio.h>
#include <stdlib.h> // Para calloc, free, rand, srand
#include <string.h> // Para strcpy, strcmp, strcspn
#include <time.h>   // Para srand(time(NULL))
#include <locale.h> // Para setlocale (opcional, para acentos)

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings
#define MAX_TERRITORIOS 5
#define MAX_MISSOES 2 // (Total de missões)
#define TAM_NOME 30
#define TAM_COR 10
#define COR_JOGADOR "Azul" // Define a cor do jogador para facilitar as verificações

// --- Estrutura de Dados ---
// Define a estrutura para um território
struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// --- Protótipos das Funções ---
// Funções de setup e gerenciamento de memória:
struct Territorio *alocarMapa();
void inicializarTerritorios(struct Territorio *mapa);
void liberarMemoria(struct Territorio *mapa);

// Funções de interface com o usuário:
void exibirMenuPrincipal();
void exibirMapa(const struct Territorio *mapa);
void exibirMissao(int idMissao);
void pausar();

// Funções de lógica principal do jogo:
int sortearMissao();
void faseDeAtaque(struct Territorio *mapa);
void simularAtaque(struct Territorio *mapa, int idAtacante, int idDefensor);
int verificarVitoria(const struct Territorio *mapa, int idMissao);

// Função utilitária:
void limparBufferEntrada();

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo
int main() {
    // 1. Configuração Inicial (Setup):
    setlocale(LC_ALL, "Portuguese"); 
    srand(time(NULL)); //

    struct Territorio *mapaMundi = NULL;
    int idMissao, opcao;
    int vitoria = 0; // 0 = Falso, 1 = Verdadeiro

    // Aloca a memória para o mapa
    mapaMundi = alocarMapa();
    if (mapaMundi == NULL) {
        printf("Erro fatal: Nao foi possivel alocar memoria para o mapa!\n");
        return 1; // Encerra com código de erro
    }

    // Preenche os territórios com dados iniciais
    inicializarTerritorios(mapaMundi);
    
    // Define a cor do jogador e sorteia sua missão
    idMissao = sortearMissao();

    // 2. Laço Principal do Jogo (Game Loop):
    do {
        // A cada iteração, exibe o mapa, a missão e o menu
        exibirMapa(mapaMundi);
        exibirMissao(idMissao);
        exibirMenuPrincipal(); // (Menu com 3 opções)

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                faseDeAtaque(mapaMundi); //
                pausar();
                break;
            case 2:
                vitoria = verificarVitoria(mapaMundi, idMissao); //
                if (vitoria) {
                    printf("\n*** VITORIA! ***\nVoce cumpriu sua missao!\n");
                    // O jogo terminará pois 'vitoria' agora é 1
                } else {
                    printf("\nVoce ainda nao cumpriu sua missao. Continue lutando!\n");
                }
                pausar();
                break;
            case 0:
                printf("\nSaindo do jogo... Ate a proxima batalha!\n"); //
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
                break;
        }

    } while (opcao != 0 && !vitoria); // Roda até o jogador sair ou vencer

    // 3. Limpeza:
    // Libera a memória alocada para o mapa
    liberarMemoria(mapaMundi); 
    
    // Se o jogador venceu, exibe o mapa final
    if (vitoria) {
        printf("\nMapa final da sua conquista:\n");
        // Precisamos alocar e inicializar novamente SÓ para exibir,
        // pois a versão anterior do mapa foi liberada.
        // Numa aplicação real, a lógica de liberação seria um pouco diferente.
        // Para este desafio, vamos apenas mostrar a mensagem de vitória.
    }

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa(): Aloca dinamicamente a memória
struct Territorio *alocarMapa() {
    // Usa calloc para alocar e zerar a memória
    return (struct Territorio *)calloc(MAX_TERRITORIOS, sizeof(struct Territorio));
}

// inicializarTerritorios(): Preenche os dados iniciais do mapa
void inicializarTerritorios(struct Territorio *mapa) {
    // O Nível Mestre não tem cadastro, os dados são automáticos
    
    // Território 1 (Nosso jogador)
    strcpy(mapa[0].nome, "America");
    strcpy(mapa[0].cor, COR_JOGADOR); // "Azul"
    mapa[0].tropas = 3;

    // Território 2 (Alvo da Missão 1)
    strcpy(mapa[1].nome, "Europa");
    strcpy(mapa[1].cor, "Verde"); //
    mapa[1].tropas = 3;

    // Território 3
    strcpy(mapa[2].nome, "Asia");
    strcpy(mapa[2].cor, "Vermelho");
    mapa[2].tropas = 5;

    // Território 4
    strcpy(mapa[3].nome, "Africa");
    strcpy(mapa[3].cor, "Amarelo");
    mapa[3].tropas = 4;

    // Território 5
    strcpy(mapa[4].nome, "Oceania");
    strcpy(mapa[4].cor, "Branco");
    mapa[4].tropas = 2;
}

// liberarMemoria(): Libera a memória alocada
void liberarMemoria(struct Territorio *mapa) {
    free(mapa);
}

// exibirMenuPrincipal(): Imprime o menu de ações
void exibirMenuPrincipal() {
    printf("\n--- ACOES ---\n");
    printf("1. Atacar\n");
    printf("2. Verificar Missao\n");
    printf("0. Sair (Desistir)\n");
    printf("Escolha sua acao: ");
}

// exibirMapa(): Mostra o estado atual dos territórios
// Usa 'const' pois apenas lê os dados, sem modificar
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

// exibirMissao(): Exibe a missão do jogador
void exibirMissao(int idMissao) {
    printf("\n--- SUA MISSAO SECRETA ---\n");
    switch (idMissao) {
        case 1:
            printf("Destruir o exercito Verde.\n"); //
            break;
        case 2:
            printf("Conquistar 3 territorios (manter 3 ou mais no total).\n"); //
            break;
    }
}

// faseDeAtaque(): Gerencia a interface de ataque
void faseDeAtaque(struct Territorio *mapa) {
    int idAtacante, idDefensor;
    
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio de ATAQUE (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &idAtacante);
    
    printf("Escolha o territorio de DEFESA (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &idDefensor);
    limparBufferEntrada();

    // Converte para índice 0 (pois o usuário digita 1-5)
    simularAtaque(mapa, idAtacante - 1, idDefensor - 1);
}

// simularAtaque(): Executa a lógica da batalha
void simularAtaque(struct Territorio *mapa, int idAtacante, int idDefensor) {
    
    // --- Validações ---
    if (idAtacante < 0 || idAtacante >= MAX_TERRITORIOS || idDefensor < 0 || idDefensor >= MAX_TERRITORIOS) {
        printf("Ataque invalido! IDs de territorio nao existem.\n");
        return;
    }
    
    // Validação se o jogador é dono do território de ataque
    if (strcmp(mapa[idAtacante].cor, COR_JOGADOR) != 0) {
        printf("Ataque invalido! Voce nao domina o territorio de ataque (%s).\n", mapa[idAtacante].nome);
        return;
    }

    // Validação para não atacar territórios próprios
    if (strcmp(mapa[idDefensor].cor, COR_JOGADOR) == 0) {
        printf("Ataque invalido! Voce nao pode atacar seu proprio territorio (%s).\n", mapa[idDefensor].nome);
        return;
    }
    
    // Validação de tropas mínimas
    if (mapa[idAtacante].tropas < 2) {
        printf("Ataque invalido! Voce precisa de pelo menos 2 tropas em %s para atacar.\n", mapa[idAtacante].nome);
        return;
    }

    // --- Lógica da Batalha (Dados) ---
    printf("\nBatalha: %s (%s) vs %s (%s)\n",
           mapa[idAtacante].nome, mapa[idAtacante].cor,
           mapa[idDefensor].nome, mapa[idDefensor].cor);

    int dadoAtacante = (rand() % 6) + 1; //
    int dadoDefensor = (rand() % 6) + 1; //

    printf("Dados: Atacante [ %d ] vs Defensor [ %d ]\n", dadoAtacante, dadoDefensor);

    // Lógica Aventureiro: "Empates favorecem o atacante"
    if (dadoAtacante >= dadoDefensor) {
        printf("Atacante venceu a batalha! %s perde 1 tropa.\n", mapa[idDefensor].nome);
        mapa[idDefensor].tropas--; //

        // Verifica se o território foi conquistado
        if (mapa[idDefensor].tropas == 0) {
            printf("CONQUISTA! %s tomou %s do exercito %s!\n",
                   mapa[idAtacante].nome, mapa[idDefensor].nome, mapa[idDefensor].cor);
            
            // Transfere a propriedade
            strcpy(mapa[idDefensor].cor, mapa[idAtacante].cor); //
            
            // Move 1 tropa para o novo território
            mapa[idDefensor].tropas = 1;
            mapa[idAtacante].tropas--;
        }
    } else {
        printf("Defensor venceu a batalha! %s perde 1 tropa.\n", mapa[idAtacante].nome);
        mapa[idAtacante].tropas--;
    }
}

// sortearMissao(): Sorteia e retorna um ID de missão
int sortearMissao() {
    return (rand() % MAX_MISSOES) + 1; // Retorna 1 ou 2
}

// verificarVitoria(): Verifica se a missão foi cumprida
// Usa 'const' pois apenas lê os dados
int verificarVitoria(const struct Territorio *mapa, int idMissao) {
    int i;
    int territoriosJogador = 0;
    int territoriosVerdes = 0;

    switch (idMissao) {
        // Missão 1: Destruir o exército Verde
        case 1:
            for (i = 0; i < MAX_TERRITORIOS; i++) {
                if (strcmp(mapa[i].cor, "Verde") == 0) {
                    territoriosVerdes++; // Conta quantos territórios verdes ainda existem
                }
            }
            return (territoriosVerdes == 0); // Vitória se for 0

        // Missão 2: Conquistar 3 territórios
        case 2:
            for (i = 0; i < MAX_TERRITORIOS; i++) {
                if (strcmp(mapa[i].cor, COR_JOGADOR) == 0) {
                    territoriosJogador++; // Conta quantos territórios o jogador tem
                }
            }
            return (territoriosJogador >= 3); // Vitória se tiver 3 ou mais
    }
    
    return 0; // Missão desconhecida ou falha
}

// limparBufferEntrada(): Limpa o buffer de entrada (stdin)
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// pausar(): Espera o usuário pressionar Enter
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
}