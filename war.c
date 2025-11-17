#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para a função strcspn

// --- Constantes Globais ---
#define MAX_TERRITORIOS 5 // (Vetor estático de 5 elementos)
#define TAM_NOME 30
#define TAM_COR 10

// --- Estrutura de Dados ---
// (Criar uma struct chamada Territorio)
struct Territorio {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

// --- Função para limpar o buffer de entrada ---
// Função utilitária para misturar scanf e fgets
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal (main) ---
int main() {
    // Declara o VETOR ESTÁTICO de 5 elementos
    struct Territorio mapaMundi[MAX_TERRITORIOS];
    int i; // Variável para os laços 'for'

    printf("===============================\n");
    printf("  DESAFIO WAR - NIVEL NOVATO\n");
    printf("===============================\n");
    printf("Vamos cadastrar os %d territorios iniciais.\n\n", MAX_TERRITORIOS);

    // --- 1. Laço de Cadastro (Entrada) ---
    // O usuário digita os dados para cada um dos 5 territórios
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        // Pede e lê o NOME do território
        printf("Nome do Territorio: ");
        fgets(mapaMundi[i].nome, TAM_NOME, stdin);
        mapaMundi[i].nome[strcspn(mapaMundi[i].nome, "\n")] = '\0';

        // Pede e lê a COR do exército
        printf("Cor do Exercito (ex: Azul, Verde): ");
        fgets(mapaMundi[i].cor, TAM_COR, stdin);
        mapaMundi[i].cor[strcspn(mapaMundi[i].cor, "\n")] = '\0';

        // Pede e lê o número de TROPAS
        printf("Numero de Tropas: ");
        scanf("%d", &mapaMundi[i].tropas);
        limparBufferEntrada(); // Limpa o "Enter" que ficou no buffer

        printf("\n"); // Apenas para organizar a saída
    }

    // --- 2. Exibição dos Dados (Saída) ---
    // Exibe o estado atual do mapa
    
    printf("Cadastro inicial concluido com sucesso!\n\n");
    
    printf("=======================================================\n");
    printf("                MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("-------------------------------------------------------\n");
    printf("| ID | TERRITORIO | EXERCITO (COR) | TROPAS |\n");
    printf("-------------------------------------------------------\n");
    
    // Laço 'for' para imprimir todos os territórios cadastrados
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("| %-2d | %-10s | %-14s | %-6d |\n",
               i + 1,
               mapaMundi[i].nome,
               mapaMundi[i].cor,
               mapaMundi[i].tropas);
    }
    printf("=======================================================\n");

    return 0; // Fim do programa
}