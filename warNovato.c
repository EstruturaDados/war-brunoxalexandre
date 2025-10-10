#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de Struct como tipo de dado para armazenar informações dos territórios
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Procedimento para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Territorio territorios[5]; // Inicialização de vetor de Struct
    int totalTerritorios = 0; // Contador de territórios cadastrados

    printf("====================================\n");        
    printf(" WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("====================================\n\n");
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");

    // Laço para cadastro dos territórios
    do {
        printf("\n--- Cadastrando Territorio %d ---\n", totalTerritorios+1);
        printf("Nome do Territorio: ");
        fgets(territorios[totalTerritorios].nome, sizeof(territorios[totalTerritorios].nome), stdin);

        printf("Cor do Exercito (ex: Azul, Verde): ");
        fgets(territorios[totalTerritorios].cor, sizeof(territorios[totalTerritorios].cor), stdin);

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[totalTerritorios].tropas);

        territorios[totalTerritorios].nome[strcspn(territorios[totalTerritorios].nome, "\n")] = '\0'; // Remove newline
        territorios[totalTerritorios].cor[strcspn(territorios[totalTerritorios].cor, "\n")] = '\0'; // Remove newline

        limparBufferEntrada();

        totalTerritorios++;
    } while (totalTerritorios < 5);

    printf("\n\nCadastro inicial concluido com sucesso!\n\n");

    printf("====================================\n");        
    printf("    MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("====================================\n\n");

    // Laço para exibir o estado atual dos territórios
    for (int i = 0; i < totalTerritorios; i++) {
        printf("TERRITORIO: %d\n", i+1);
        printf("- Nome: %s\n", territorios[i].nome);
        printf("- Dominado por: Exercito %s\n", territorios[i].cor);
        printf("- Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;    
}