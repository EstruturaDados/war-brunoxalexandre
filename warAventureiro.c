#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// Procedimento para imprimir todos os territórios cadastrados
void imprimirTerritorios(Territorio *territorios, int maxTerritorios) {
    printf("\n====================================\n");        
    printf("    MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("====================================\n\n");

    for (int i = 0; i < maxTerritorios; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", 
            i+1, 
            territorios[i].nome, 
            territorios[i].cor, 
            territorios[i].tropas);
    }
}

// Procedimento para executar um ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante, dadoDefensor;
    printf("\n--- RESULTADO DA BATALHA ---\n");

    srand(time(NULL));
    dadoAtacante = rand() % 6 + 1;
    printf("O atacante %s rolou um dado e tirou: %d\n",
        atacante->nome,
        dadoAtacante);
    
    dadoDefensor = rand() % 6 + 1;
    printf("O defensor %s rolou um dado e tirou: %d\n",
        defensor->nome,
        dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa\n");
        if (defensor->tropas == 1) {
            strcpy(defensor->cor, atacante->cor);
            atacante->tropas = atacante->tropas / 2;
            defensor->tropas = atacante->tropas;
        } else {
            defensor->tropas = defensor->tropas - 1;
        }
    } else {
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa\n");
        atacante->tropas = atacante->tropas - 1;        
    }
}

void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    Territorio *territorios;

    printf("====================================\n");        
    printf(" WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("====================================\n\n");

    int maxTerritorios = 0;
    printf("Informe o número total de territorios: ");
    scanf("%d", &maxTerritorios);
    limparBufferEntrada();

    territorios = (Territorio *) calloc(maxTerritorios, sizeof(Territorio));
    if (territorios == NULL) {
        perror("Erro ao alocar memória para territórios"); // Prints an error message
        exit(EXIT_FAILURE); // Terminate the program cleanly
    }
    
    // Laço para cadastro dos territórios
    int numeroTerritorio = 0;
    do {
        printf("\n--- Cadastrando Territorio %d ---\n", numeroTerritorio+1);
        printf("Nome do Territorio: ");
        fgets(territorios[numeroTerritorio].nome, sizeof(territorios[numeroTerritorio].nome), stdin);

        printf("Cor do Exercito: ");
        fgets(territorios[numeroTerritorio].cor, sizeof(territorios[numeroTerritorio].cor), stdin);

        printf("Numero de Tropas: ");
        scanf("%d", &territorios[numeroTerritorio].tropas);

        territorios[numeroTerritorio].nome[strcspn(territorios[numeroTerritorio].nome, "\n")] = '\0'; // Remove newline
        territorios[numeroTerritorio].cor[strcspn(territorios[numeroTerritorio].cor, "\n")] = '\0'; // Remove newline

        limparBufferEntrada();

        numeroTerritorio++;
    } while (numeroTerritorio < maxTerritorios);

    int continuaTurno = 1;
    do {
        imprimirTerritorios(territorios, maxTerritorios);

        int territorioAtacante = -1;
        int territorioDefensor = -1;

        do {
            printf("\n--- FASE DE ATAQUE ---\n");
            printf("Escolha o território atacante (1 a 5, ou 0 para sair): ");
            scanf("%d", &territorioAtacante);
            limparBufferEntrada();

            if (territorioAtacante < 0 || territorioAtacante > 5) {
                printf("Território inválido!\n");
            }
        } while (territorioAtacante < 0 || territorioAtacante > 5);

        if (territorioAtacante == 0) {
            continuaTurno = 0;
            break;
        }

        do {
            printf("Escolha o território defensor (1 a 5): ");
            scanf("%d", &territorioDefensor);
            limparBufferEntrada();
            
            if (territorioDefensor < 1 || territorioDefensor > 5 || territorioAtacante == territorioDefensor) {
                printf("Território inválido!\n");
            }   

            if (strcmp(territorios[territorioAtacante-1].cor, territorios[territorioDefensor-1].cor) == 0) {
                printf("Territorios possuem o mesmo exercito!\n");
                territorioDefensor = -1;
            }
        } while (territorioDefensor < 1 || territorioDefensor > 5 || territorioAtacante == territorioDefensor);          

        if (territorios[territorioAtacante-1].tropas > 1) {
            atacar(&territorios[territorioAtacante-1], &territorios[territorioDefensor-1]);
        } else {
            printf("\nAtacante nao tem tropas suficientes para atacar!\n");
        }
        printf("\nPressione Enter para continuar para o proximo turno...\n\n");
        getchar();
    } while (continuaTurno > 0);

    liberarMemoria(territorios);
    return 0;    
}