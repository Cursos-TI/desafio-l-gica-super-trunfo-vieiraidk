/* supertrunfo_duplo_atributo.c
 *
 * Versão final: escolha de DOIS atributos (menus dinâmicos), comparação por atributo,
 * soma dos atributos e decisão final. Mantido estilo e funções do código anterior.
 *
 * - Usa switch para menus
 * - Usa if / if-else aninhados para decisões
 * - Usa operador ternário para compactar algumas saídas
 *
 * Observação: como no código anterior, PIB retorna em BILHÕES (na função obterValorFloat)
 * e PIB per capita retorna em reais; a soma final usa diretamente os floats retornados.
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

/* Funções utilitárias de I/O do código anterior */
void read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
}

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

const char* nomeAtributo(int opcao) {
    switch (opcao) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        case 6: return "PIB per Capita";
        default: return "Atributo Desconhecido";
    }
}

/* Mostra menu com possibilidade de esconder uma opção (op_excluir),
   retorna a escolha válida do usuário (1..6), ou 0 se inválido. */
int mostrarMenuEscolha(int op_excluir) {
    char temp[32];
    int escolha = 0;

    printf("\nEscolha o atributo para comparar:\n");
    for (int i = 1; i <= 6; ++i) {
        if (i == op_excluir) continue; /* não mostrar a opção já escolhida */
        switch (i) {
            case 1: printf(" 1 - População\n"); break;
            case 2: printf(" 2 - Área\n"); break;
            case 3: printf(" 3 - PIB (em bilhões)\n"); break;
            case 4: printf(" 4 - Número de pontos turísticos\n"); break;
            case 5: printf(" 5 - Densidade demográfica (menor vence)\n"); break;
            case 6: printf(" 6 - PIB per Capita (reais)\n"); break;
        }
    }
    read_line("Opção: ", temp, sizeof(temp));
    if (sscanf(temp, "%d", &escolha) != 1) return 0;

    /* Se escolha == op_excluir, inválido */
    if (escolha < 1 || escolha > 6 || escolha == op_excluir) return 0;
    return escolha;
}

int main(void) {
    Carta c1, c2;
    char temp[64];
    int atr1 = 0, atr2 = 0;

    printf("=== Super Trunfo: Comparador Avançado (DOIS atributos) ===\n");
    printf("Cadastre duas cartas (país/cidade) para comparar.\n");

    /* Ler cartas (mantive a mesma leitura do código anterior) */
    lerCarta(&c1, 1);
    lerCarta(&c2, 2);

    /* Calcular indicadores */
    calcularIndicadores(&c1);
    calcularIndicadores(&c2);

    /* Resumo */
    printf("\n--- Resumo ---\n");
    printf("Carta 1: %s (%s) - Pop: %d | Área: %.2f km² | PIB: %.2f bi | Pontos: %d | Dens: %.2f | PIBpc: %.2f\n",
           c1.nome, c1.estado, c1.populacao, c1.areaKm2, c1.pib, c1.pontosTuristicos, c1.densidade, c1.pibPerCapita);
    printf("Carta 2: %s (%s) - Pop: %d | Área: %.2f km² | PIB: %.2f bi | Pontos: %d | Dens: %.2f | PIBpc: %.2f\n",
           c2.nome, c2.estado, c2.populacao, c2.areaKm2, c2.pib, c2.pontosTuristicos, c2.densidade, c2.pibPerCapita);

    /* Menu dinâmico: escolher primeiro atributo */
    while (1) {
        printf("\nEscolha o PRIMEIRO atributo (1-6):\n");
        printf(" 1 - População\n 2 - Área\n 3 - PIB\n 4 - Pontos Turísticos\n 5 - Densidade demográfica (menor vence)\n 6 - PIB per Capita\n");
        read_line("Opção: ", temp, sizeof(temp));
        if (sscanf(temp, "%d", &atr1) != 1) atr1 = 0;
        if (atr1 >= 1 && atr1 <= 6) break;
        printf("Opção inválida. Tente novamente.\n");
    }

    /* Menu dinâmico para segundo atributo — não permite escolher o mesmo */
    while (1) {
        printf("\nEscolha o SEGUNDO atributo (diferente do %d - %s):\n", atr1, nomeAtributo(atr1));
        int escolha = mostrarMenuEscolha(atr1);
        if (escolha >= 1 && escolha <=6) {
            atr2 = escolha;
            break;
        }
        printf("Opção inválida (ou você escolheu o mesmo atributo). Tente novamente.\n");
    }

    /* Obter valores float para ambas cartas e ambos atributos */
    float c1_a = obterValorFloat(&c1, atr1);
    float c2_a = obterValorFloat(&c2, atr1);
    float c1_b = obterValorFloat(&c1, atr2);
    float c2_b = obterValorFloat(&c2, atr2);

    /* Mostra os detalhes dos atributos escolhidos */
    printf("\n=== Comparação selecionada: %s e %s ===\n\n",
           nomeAtributo(atr1), nomeAtributo(atr2));

    printf("Carta 1 - %s (%s):\n", c1.nome, c1.estado);
    printf("  %s: ", nomeAtributo(atr1)); imprimirValorAtributo(&c1, atr1); printf("\n");
    printf("  %s: ", nomeAtributo(atr2)); imprimirValorAtributo(&c1, atr2); printf("\n\n");

    printf("Carta 2 - %s (%s):\n", c2.nome, c2.estado);
    printf("  %s: ", nomeAtributo(atr1)); imprimirValorAtributo(&c2, atr1); printf("\n");
    printf("  %s: ", nomeAtributo(atr2)); imprimirValorAtributo(&c2, atr2); printf("\n\n");

    /* Comparações individuais (if / if-else aninhados) */
    int vencedorA = 0; /* 1 -> carta1, 2 -> carta2, 0 -> empate */
    int vencedorB = 0;

    /* Atributo A */
    if (atr1 == 5) { /* densidade: menor vence */
        if (c1_a < c2_a) vencedorA = 1;
        else { if (c1_a > c2_a) vencedorA = 2; else vencedorA = 0; }
    } else { /* maior vence */
        if (c1_a > c2_a) vencedorA = 1;
        else { if (c1_a < c2_a) vencedorA = 2; else vencedorA = 0; }
    }

    /* Atributo B */
    if (atr2 == 5) { /* densidade: menor vence */
        if (c1_b < c2_b) vencedorB = 1;
        else { if (c1_b > c2_b) vencedorB = 2; else vencedorB = 0; }
    } else { /* maior vence */
        if (c1_b > c2_b) vencedorB = 1;
        else { if (c1_b < c2_b) vencedorB = 2; else vencedorB = 0; }
    }

    /* Imprimir resultados individuais usando operador ternário para strings */
    const char *resA = (vencedorA == 1) ? "Carta 1" : (vencedorA == 2) ? "Carta 2" : "Empate";
    const char *resB = (vencedorB == 1) ? "Carta 1" : (vencedorB == 2) ? "Carta 2" : "Empate";

    printf("Resultado (atributo 1 - %s): %s\n", nomeAtributo(atr1), resA);
    printf("Resultado (atributo 2 - %s): %s\n\n", nomeAtributo(atr2), resB);

    /* Soma dos atributos (usando os valores float obtidos) */
    float soma1 = c1_a + c1_b;
    float soma2 = c2_a + c2_b;

    printf("Soma dos atributos:\n");
    printf("  Carta 1 (%s): %.2f\n", c1.nome, soma1);
    printf("  Carta 2 (%s): %.2f\n", c2.nome, soma2);

    /* Decisão final (if-else aninhado) */
    if (soma1 > soma2) {
        printf("\nResultado Final: Carta 1 (%s) venceu!\n", c1.nome);
    } else {
        if (soma1 < soma2) {
            printf("\nResultado Final: Carta 2 (%s) venceu!\n", c2.nome);
        } else {
            printf("\nEmpate!\n");
        }
    }

    return 0;
}
