/* supertrunfo_compare.c
 *
 * Programa: Comparando Cartas do Super Trunfo
 * - Lê duas cartas (estado, código, nome, população, área, PIB em bilhões, pontos turísticos)
 * - Calcula densidade populacional (hab/km²) e PIB per capita (reais)
 * - Compara um único atributo (escolhido por macro ALVO_COMPARACAO)
 * - Usa estruturas de decisão (if / if-else) para determinar o vencedor
 *
 * Observações:
 * - Assume que o PIB digitado está em BILHÕES de reais (ex.: 699.28 significa 699.28 bilhões).
 * - Para PIB per capita o programa converte PIB -> reais (PIB * 1e9) antes de dividir pela população.
 * - População é do tipo int conforme o requisito atual.
 *
 * Para alterar o atributo comparado, modifique a macro ALVO_COMPARACAO abaixo.
 */

#include <stdio.h>
#include <string.h>

/* Valores possíveis para ALVO_COMPARACAO */
#define ATR_POPULACAO     1
#define ATR_AREA          2
#define ATR_PIB           3
#define ATR_DENSIDADE     4
#define ATR_PIB_PER_CAP   5

/* Troque esse define para escolher o atributo comparado (modifique no código) */
#define ALVO_COMPARACAO ATR_POPULACAO

/* Estrutura que representa uma carta/cidade */
typedef struct {
    char estado[8];             /* ex: "SP" ou "S" */
    char codigo[8];             /* ex: "A01" */
    char nomeCidade[80];        /* aceita espaços */
    int populacao;              /* inteiro (requisito atual) */
    float areaKm2;              /* área em km² */
    float pib;                  /* PIB em BILHÕES (ex.: 699.28) */
    int pontosTuristicos;
    /* Campos calculados */
    float densidade;            /* hab / km² */
    float pibPerCapita;         /* reais */
} Carta;

/* Função que lê uma carta do usuário (stdin) */
void lerCarta(Carta *c, int numero) {
    printf("\n--- Cadastro da Carta %d ---\n", numero);

    printf("Estado (ex: SP): ");
    /* lê uma string sem espaços */
    scanf(" %7s", c->estado);

    printf("Código da carta (até 7 chars): ");
    scanf(" %7s", c->codigo);

    /* Para ler nome com espaços até newline */
    printf("Nome da cidade: ");
    scanf(" %79[^\n]", c->nomeCidade);

    printf("População (inteiro): ");
    scanf(" %d", &c->populacao);

    printf("Área em km² (ex: 1521.11): ");
    scanf(" %f", &c->areaKm2);

    printf("PIB (em BILHÕES de reais, ex: 699.28): ");
    scanf(" %f", &c->pib);

    printf("Número de pontos turísticos (inteiro): ");
    scanf(" %d", &c->pontosTuristicos);
}

/* Calcula densidade e PIB per capita (com verificações de divisão por zero) */
void calcularIndicadores(Carta *c) {
    if (c->areaKm2 <= 0.0f) {
        c->densidade = 0.0f;
        printf("Aviso: área inválida para a cidade %s. Densidade definida como 0.0.\n", c->nomeCidade);
    } else {
        c->densidade = (float)c->populacao / c->areaKm2;
    }

    if (c->populacao <= 0) {
        c->pibPerCapita = 0.0f;
        printf("Aviso: população inválida para a cidade %s. PIB per capita definido como 0.0.\n", c->nomeCidade);
    } else {
        /* converte PIB (bilhões) -> reais antes de dividir */
        c->pibPerCapita = (c->pib * 1000000000.0f) / (float)c->populacao;
    }
}

/* Função que retorna o valor do atributo escolhido, em float (para comparação).
 * Para população (int) convertimos para float ao retornar.
 * Para densidade, retornamos a densidade; observe que para densidade menor vence.
 */
float obterValorAtributo(const Carta *c, int atributo) {
    if (atributo == ATR_POPULACAO) {
        return (float)c->populacao;
    } else if (atributo == ATR_AREA) {
        return c->areaKm2;
    } else if (atributo == ATR_PIB) {
        /* Retornamos PIB em BILHÕES (mesma unidade que a entrada) */
        return c->pib;
    } else if (atributo == ATR_DENSIDADE) {
        return c->densidade;
    } else if (atributo == ATR_PIB_PER_CAP) {
        return c->pibPerCapita;
    } else {
        return 0.0f; /* não usado */
    }
}

/* Função que imprime um valor do atributo com formatação adequada */
void imprimirAtributoFormato(const Carta *c, int atributo) {
    if (atributo == ATR_POPULACAO) {
        printf("%d", c->populacao);
    } else if (atributo == ATR_AREA) {
        printf("%.2f km²", c->areaKm2);
    } else if (atributo == ATR_PIB) {
        printf("%.2f bilhões de reais", c->pib);
    } else if (atributo == ATR_DENSIDADE) {
        printf("%.2f hab/km²", c->densidade);
    } else if (atributo == ATR_PIB_PER_CAP) {
        printf("%.2f reais", c->pibPerCapita);
    } else {
        printf("N/A");
    }
}

/* Executa a comparação (usa if / if-else conforme requisito) e imprime o resultado */
void compararECriarRelatorio(const Carta *c1, const Carta *c2, int atributo) {
    float v1 = obtener_valor_dummy:0; /* placeholder para evitar warnings - será substituído abaixo */
}

/* Note: função acima era placeholder; definimos a real abaixo. */

void compararECriarRelatorio_real(const Carta *c1, const Carta *c2, int atributo) {
    float valor1 = obterValorAtributo(c1, atributo);
    float valor2 = obterValorAtributo(c2, atributo);

    /* Mostrar cabeçalho */
    const char *nomeAtributo;
    if (atributo == ATR_POPULACAO) nomeAtributo = "População";
    else if (atributo == ATR_AREA) nomeAtributo = "Área";
    else if (atributo == ATR_PIB) nomeAtributo = "PIB";
    else if (atributo == ATR_DENSIDADE) nomeAtributo = "Densidade Populacional";
    else if (atributo == ATR_PIB_PER_CAP) nomeAtributo = "PIB per Capita";
    else nomeAtributo = "Atributo Desconhecido";

    printf("\n=== Comparação de cartas (Atributo: %s) ===\n\n", nomeAtributo);

    /* Imprime os valores formatados */
    printf("Carta 1 - %s (%s): ", c1->nomeCidade, c1->estado);
    imprimirAtributoFormato(c1, atributo);
    printf("\n");

    printf("Carta 2 - %s (%s): ", c2->nomeCidade, c2->estado);
    imprimirAtributoFormato(c2, atributo);
    printf("\n\n");

    /* Decisão: para Densidade, menor vence; para os demais, maior vence. Usamos if / if-else. */
    if (atributo == ATR_DENSIDADE) {
        /* menor vence */
        if (valor1 < valor2) {
            printf("Resultado: Carta 1 (%s) venceu!\n", c1->nomeCidade);
        } else if (valor1 > valor2) {
            printf("Resultado: Carta 2 (%s) venceu!\n", c2->nomeCidade);
        } else { /* empate */
            printf("Resultado: Empate (valores iguais para %s).\n", nomeAtributo);
        }
    } else {
        /* maior vence */
        if (valor1 > valor2) {
            printf("Resultado: Carta 1 (%s) venceu!\n", c1->nomeCidade);
        } else if (valor1 < valor2) {
            printf("Resultado: Carta 2 (%s) venceu!\n", c2->nomeCidade);
        } else { /* empate */
            printf("Resultado: Empate (valores iguais para %s).\n", nomeAtributo);
        }
    }
}

int main(void) {
    Carta carta1, carta2;

    printf("Comparando Cartas do Super Trunfo\n");
    printf("Registrando duas cartas e calculando indicadores...\n");

    /* Leitura das cartas */
    lerCarta(&carta1, 1);
    lerCarta(&carta2, 2);

    /* Cálculo de densidade e PIB per capita */
    calcularIndicadores(&carta1);
    calcularIndicadores(&carta2);

    /* Exibição sumária das cartas (inclui os indicadores calculados) */
    printf("\n----- Resumo das Cartas -----\n");
    printf("Carta 1: %s (%s)\n", carta1.nomeCidade, carta1.estado);
    printf("  População: %d\n", carta1.populacao);
    printf("  Área: %.2f km²\n", carta1.areaKm2);
    printf("  PIB: %.2f bilhões de reais\n", carta1.pib);
    printf("  Pontos turísticos: %d\n", carta1.pontosTuristicos);
    printf("  Densidade: %.2f hab/km²\n", carta1.densidade);
    printf("  PIB per Capita: %.2f reais\n", carta1.pibPerCapita);

    printf("\nCarta 2: %s (%s)\n", carta2.nomeCidade, carta2.estado);
    printf("  População: %d\n", carta2.populacao);
    printf("  Área: %.2f km²\n", carta2.areaKm2);
    printf("  PIB: %.2f bilhões de reais\n", carta2.pib);
    printf("  Pontos turísticos: %d\n", carta2.pontosTuristicos);
    printf("  Densidade: %.2f hab/km²\n", carta2.densidade);
    printf("  PIB per Capita: %.2f reais\n", carta2.pibPerCapita);

    /* Chamar rotina de comparação usando a macro ALVO_COMPARACAO */
#if (ALVO_COMPARACAO == ATR_POPULACAO)  || \
    (ALVO_COMPARACAO == ATR_AREA)       || \
    (ALVO_COMPARACAO == ATR_PIB)        || \
    (ALVO_COMPARACAO == ATR_DENSIDADE)  || \
    (ALVO_COMPARACAO == ATR_PIB_PER_CAP)
    compararECriarRelatorio_real(&carta1, &carta2, ALVO_COMPARACAO);
#else
    printf("\nAtributo de comparação inválido. Verifique a macro ALVO_COMPARACAO no código.\n");
#endif

    return 0;
}
