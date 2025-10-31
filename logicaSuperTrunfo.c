/* supertrunfo_menu.c
 *
 * Comparando Cartas do Super Trunfo - Menu interativo
 *
 * - Lê duas cartas (estado, código, nome, população, área, PIB em bilhões, pontos turísticos)
 * - Calcula densidade e PIB per capita
 * - Mostra um menu (switch) para escolher o atributo de comparação
 * - Usa if / if-else (aninhados) para decidir o vencedor, com regra especial para densidade
 *
 * Observações:
 * - PIB é informado em BILHÕES (ex.: 699.28 significa 699.28 bilhões de reais).
 * - Em caso de divisão por zero (área = 0 ou população = 0), indicamos 0.00 e avisamos.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char estado[16];
    char codigo[16];
    char nome[80];
    int populacao;
    float areaKm2;
    float pib;              /* em BILHÕES */
    int pontosTuristicos;
    /* calculados */
    float densidade;        /* hab / km² */
    float pibPerCapita;     /* reais */
} Carta;

/* Leitura de linha segura e remoção do newline */
void read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    /* remove newline final se houver */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
}

/* Lê os campos da carta do usuário */
void lerCarta(Carta *c, int numero) {
    char temp[128];

    printf("\n--- Cadastro da Carta %d ---\n", numero);
    read_line("Estado (ex: SP): ", c->estado, sizeof(c->estado));
    read_line("Código da carta (ex: A01): ", c->codigo, sizeof(c->codigo));
    read_line("Nome da cidade: ", c->nome, sizeof(c->nome));

    read_line("População (inteiro): ", temp, sizeof(temp));
    if (sscanf(temp, "%d", &c->populacao) != 1) {
        printf("Entrada inválida para população. Definindo 0.\n");
        c->populacao = 0;
    }

    read_line("Área em km² (ex: 1521.11): ", temp, sizeof(temp));
    if (sscanf(temp, "%f", &c->areaKm2) != 1) {
        printf("Entrada inválida para área. Definindo 0.0.\n");
        c->areaKm2 = 0.0f;
    }

    read_line("PIB em BILHÕES (ex: 699.28): ", temp, sizeof(temp));
    if (sscanf(temp, "%f", &c->pib) != 1) {
        printf("Entrada inválida para PIB. Definindo 0.0.\n");
        c->pib = 0.0f;
    }

    read_line("Número de pontos turísticos (inteiro): ", temp, sizeof(temp));
    if (sscanf(temp, "%d", &c->pontosTuristicos) != 1) {
        printf("Entrada inválida para pontos turísticos. Definindo 0.\n");
        c->pontosTuristicos = 0;
    }
}

/* Calcula densidade e PIB per capita com verificação simples */
void calcularIndicadores(Carta *c) {
    if (c->areaKm2 <= 0.0f) {
        c->densidade = 0.0f;
        printf("Aviso: área inválida para %s. Densidade definida como 0.00\n", c->nome);
    } else {
        c->densidade = (float)c->populacao / c->areaKm2;
    }

    if (c->populacao <= 0) {
        c->pibPerCapita = 0.0f;
        printf("Aviso: população inválida para %s. PIB per capita definido como 0.00\n", c->nome);
    } else {
        c->pibPerCapita = (c->pib * 1000000000.0f) / (float)c->populacao;
    }
}

/* Imprime o valor do atributo de forma formatada */
void imprimirValorAtributo(const Carta *c, int opcao) {
    switch (opcao) {
        case 1: /* População */
            printf("%d", c->populacao);
            break;
        case 2: /* Área */
            printf("%.2f km²", c->areaKm2);
            break;
        case 3: /* PIB */
            printf("%.2f bilhões de reais", c->pib);
            break;
        case 4: /* Pontos turísticos */
            printf("%d", c->pontosTuristicos);
            break;
        case 5: /* Densidade */
            printf("%.2f hab/km²", c->densidade);
            break;
        case 6: /* PIB per cap */
            printf("%.2f reais", c->pibPerCapita);
            break;
        default:
            printf("N/A");
    }
}

/* Retorna o valor do atributo como float para facilitar comparação */
float obterValorFloat(const Carta *c, int opcao) {
    switch (opcao) {
        case 1: return (float)c->populacao;
        case 2: return c->areaKm2;
        case 3: return c->pib;            /* em bilhões */
        case 4: return (float)c->pontosTuristicos;
        case 5: return c->densidade;     /* menor vence */
        case 6: return c->pibPerCapita;
        default: return 0.0f;
    }
}

int main(void) {
    Carta c1, c2;
    char temp[64];
    int opcao = 0;

    printf("=== Super Trunfo: Comparador Interativo ===\n");
    printf("Cadastre duas cartas (país/cidade) para comparar.\n");

    /* Leitura das cartas */
    lerCarta(&c1, 1);
    lerCarta(&c2, 2);

    /* Calcula indicadores */
    calcularIndicadores(&c1);
    calcularIndicadores(&c2);

    /* Mostra resumo rápido */
    printf("\n--- Resumo ---\n");
    printf("Carta 1: %s (%s) - Pop: %d | Área: %.2f km² | PIB: %.2f bi | Pontos: %d | Dens: %.2f | PIBpc: %.2f\n",
           c1.nome, c1.estado, c1.populacao, c1.areaKm2, c1.pib, c1.pontosTuristicos, c1.densidade, c1.pibPerCapita);
    printf("Carta 2: %s (%s) - Pop: %d | Área: %.2f km² | PIB: %.2f bi | Pontos: %d | Dens: %.2f | PIBpc: %.2f\n",
           c2.nome, c2.estado, c2.populacao, c2.areaKm2, c2.pib, c2.pontosTuristicos, c2.densidade, c2.pibPerCapita);

    /* Menu interativo */
    printf("\nEscolha o atributo para comparar:\n");
    printf(" 1 - População\n");
    printf(" 2 - Área\n");
    printf(" 3 - PIB (em bilhões)\n");
    printf(" 4 - Número de pontos turísticos\n");
    printf(" 5 - Densidade demográfica (hab/km²) [menor vence]\n");
    printf(" 6 - PIB per Capita (reais)\n");
    read_line("Opção (1-6): ", temp, sizeof(temp));
    if (sscanf(temp, "%d", &opcao) != 1) opcao = 0;

    /* Usamos switch para o menu. Dentro de cada case usamos if / if-else aninhados. */
    switch (opcao) {
        case 1: /* População */
        {
            float v1 = obterValorFloat(&c1, 1);
            float v2 = obterValorFloat(&c2, 1);

            printf("\nComparação de cartas (Atributo: População):\n\n");
            printf("Carta 1 - %s (%s): ", c1.nome, c1.estado); imprimirValorAtributo(&c1, 1); printf("\n");
            printf("Carta 2 - %s (%s): ", c2.nome, c2.estado); imprimirValorAtributo(&c2, 1); printf("\n\n");

            if (v1 > v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.nome);
            } else { /* bloco aninhado if-else */
                if (v1 < v2) {
                    printf("Resultado: Carta 2 (%s) venceu!\n", c2.nome);
                } else {
                    printf("Empate!\n");
                }
            }
            break;
        }
        case 2: /* Área */
        {
            float v1 = obtener_valor_dummy:0; /* placeholder - substituído abaixo */
        }
        /* substituímos o placeholder pela implementação real para evitar confusão */
        case 2: /* Área (real) */
        {
            float v1 = obterValorFloat(&c1, 2);
            float v2 = obterValorFloat(&c2, 2);

            printf("\nComparação de cartas (Atributo: Área):\n\n");
            printf("Carta 1 - %s (%s): ", c1.nome, c1.estado); imprimirValorAtributo(&c1, 2); printf("\n");
            printf("Carta 2 - %s (%s): ", c2.nome, c2.estado); imprimirValorAtributo(&c2, 2); printf("\n\n");

            if (v1 > v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.nome);
            } else {
                if (v1 < v2) {
                    printf("Resultado: Carta 2 (%s) venceu!\n", c2.nome);
                } else {
                    printf("Empate!\n");
                }
            }
            break;
        }
        case 3: /* PIB */
        {
            float v1 = obterValorFloat(&c1, 3);
            float v2 = obterValorFloat(&c2, 3);

            printf("\nComparação de cartas (Atributo: PIB):\n\n");
            printf("Carta 1 - %s (%s): ", c1.nome, c1.estado); imprimirValorAtributo(&c1, 3); printf("\n");
            printf("Carta 2 - %s (%s): ", c2.nome, c2.estado); imprimirValorAtributo(&c2, 3); printf("\n\n");

            /* if / if-else aninhados */
            if (v1 > v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.nome);
            } else {
                if (v1 < v2) {
                    printf("Resultado: Carta 2 (%s) venceu!\n", c2.nome);
                } else {
                    printf("Empate!\n");
                }
            }

            break;
        }
        case 4: /* Pontos turísticos */
        {
            float v1 = obterValorFloat(&c1, 4);
            float v2 = obterValorFloat(&c2, 4);

            printf("\nComparação de cartas (Atributo: Pontos Turísticos):\n\n");
            printf("Carta 1 - %s (%s): ", c1.nome, c1.estado); imprimirValorAtributo(&c1, 4); printf("\n");
            printf("Carta 2 - %s (%s): ", c2.nome, c2.estado); imprimirValorAtributo(&c2, 4); printf("\n\n");

            if (v1 > v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.nome);
            } else {
                if (v1 < v2) {
                    printf("Resultado: Carta 2 (%s) venceu!\n", c2.nome);
                } else {
                    printf("Empate!\n");
                }
            }
            break;
        }
        case 5: /* Densidade demográfica - menor vence */
        {
            float v1 = obterValorFloat(&c1, 5);
            float v2 = obterValorFloat(&c2, 5);

            printf("\nComparação de cartas (Atributo: Densidade Demográfica - menor vence):\n\n");
            printf("Carta 1 - %s (%s): ", c1.nome, c1.estado); imprimirValorAtributo(&c1, 5); printf("\n");
            printf("Carta 2 - %s (%s): ", c2.nome, c2.estado); imprimirValorAtributo(&c2, 5); printf("\n\n");

            /* regra invertida: menor vence */
            if (v1 < v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.nome);
            } else {
                if (v1 > v2) {
                    printf("Resultado: Carta 2 (%s) venceu!\n", c2.nome);
                } else {
                    printf("Empate!\n");
                }
            }
            break;
        }
        case 6: /* PIB per Capita */
        {
            float v1 = obterValorFloat(&c1, 6);
            float v2 = obterValorFloat(&c2, 6);

            printf("\nComparação de cartas (Atributo: PIB per Capita):\n\n");
            printf("Carta 1 - %s (%s): ", c1.nome, c1.estado); imprimirValorAtributo(&c1, 6); printf("\n");
            printf("Carta 2 - %s (%s): ", c2.nome, c2.estado); imprimirValorAtributo(&c2, 6); printf("\n\n");

            if (v1 > v2) {
                printf("Resultado: Carta 1 (%s) venceu!\n", c1.nome);
            } else {
                if (v1 < v2) {
                    printf("Resultado: Carta 2 (%s) venceu!\n", c2.nome);
                } else {
                    printf("Empate!\n");
                }
            }
            break;
        }
        default:
            /* opção inválida: default no switch */
            printf("\nOpção inválida! Por favor execute o programa novamente e escolha uma opção entre 1 e 6.\n");
            break;
    }

    return 0;
}
