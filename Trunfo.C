#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma cidade no Super Trunfo
typedef struct {
    char codigo[4];
    char nome[50];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
} Cidade;

// Função para cadastrar uma nova cidade
void cadastrarCidades(Cidade **cidades, int *totalCidades) {
    Cidade nova;

    printf("\n📋 Cadastro de Nova Cidade\n");
    printf("Código (Ex: CD01): ");
    scanf(" %4s", nova.codigo);

    printf("Nome da cidade: ");
    getchar(); // Limpa o buffer
    fgets(nova.nome, sizeof(nova.nome), stdin);
    nova.nome[strcspn(nova.nome, "\n")] = '\0';

    printf("População: ");
    scanf("%d", &nova.populacao);

    printf("Área (km²): ");
    scanf("%f", &nova.area);

    printf("PIB (em bilhões de R$): ");
    scanf("%f", &nova.pib);

    printf("Número de pontos turísticos: ");
    scanf("%d", &nova.pontos_turisticos);

    nova.densidade_populacional = nova.populacao / nova.area;
    nova.pib_per_capita = (nova.pib * 1000000000) / nova.populacao;

    // Realoca o vetor para adicionar a nova cidade
    *cidades = realloc(*cidades, (*totalCidades + 1) * sizeof(Cidade));
    if (*cidades == NULL) {
        printf("❌ Erro de memória!\n");
        exit(1);
    }

    (*cidades)[*totalCidades] = nova;
    (*totalCidades)++;

    printf("✅ Cidade cadastrada com sucesso!\n");
}

// Função para listar cidades
void listarCidades(Cidade *cidades, int totalCidades) {
    if (totalCidades == 0) {
        printf("\n📭 Nenhuma cidade cadastrada ainda.\n");
        return;
    }

    printf("\n📑 Lista de Cidades:\n");
    for (int i = 0; i < totalCidades; i++) {
        printf("\n===============================");
        printf("\n🔹 Carta #%d", i);
        printf("\nCódigo: %s", cidades[i].codigo);
        printf("\nNome: %s", cidades[i].nome);
        printf("\nPopulação: %d", cidades[i].populacao);
        printf("\nÁrea: %.2f km²", cidades[i].area);
        printf("\nPIB: R$ %.2f bilhões", cidades[i].pib);
        printf("\nPontos turísticos: %d", cidades[i].pontos_turisticos);
        printf("\nDensidade Populacional: %.2f hab/km²", cidades[i].densidade_populacional);
        printf("\nPIB per capita: R$ %.2f", cidades[i].pib_per_capita);
    }
    printf("\n===============================\n");
}

// Função para comparar duas cidades
void compararCartas(Cidade c1, Cidade c2, int atributo) {
    float valor1 = 0, valor2 = 0;
    char *atributoNome = "";

    switch (atributo) {
        case 1: valor1 = c1.populacao; atributoNome = "População"; valor2 = c2.populacao; break;
        case 2: valor1 = c1.area; atributoNome = "Área"; valor2 = c2.area; break;
        case 3: valor1 = c1.pib; atributoNome = "PIB"; valor2 = c2.pib; break;
        case 4: valor1 = c1.pontos_turisticos; atributoNome = "Pontos Turísticos"; valor2 = c2.pontos_turisticos; break;
        case 5: valor1 = c1.densidade_populacional; atributoNome = "Densidade Populacional"; valor2 = c2.densidade_populacional; break;
        case 6: valor1 = c1.pib_per_capita; atributoNome = "PIB per capita"; valor2 = c2.pib_per_capita; break;
        default:
            printf("\n⚠️ Atributo inválido!\n");
            return;
    }

    printf("\n⚔️ Comparando %s:\n", atributoNome);
    printf("%s: %.2f\n", c1.nome, valor1);
    printf("%s: %.2f\n", c2.nome, valor2);

    if (valor1 == valor2) {
        printf("🔸 Resultado: Empate!\n");
    } else if (atributo == 5) {
        printf("🏆 Vencedor: %s\n", (valor1 < valor2) ? c1.nome : c2.nome);
    } else {
        printf("🏆 Vencedor: %s\n", (valor1 > valor2) ? c1.nome : c2.nome);
    }
}

// Função principal (menu)
int main() {
    Cidade *cidades = NULL;
    int totalCidades = 0;
    int opcao;

    do {
        printf("\n=========== 🌍 SUPER TRUNFO: PAÍSES 🌍 ===========\n");
        printf("1. ➕ Cadastro de Cidade ➕\n");
        printf("2. 📋 Lista de Cidades 📋\n");
        printf("3. ⚖️ Comparar Cartas ⚖️\n");
        printf("4. 🚪 Sair 🚪\n");
        printf("===============================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCidades(&cidades, &totalCidades);
                break;
            case 2:
                listarCidades(cidades, totalCidades);
                break;
            case 3:
                if (totalCidades < 2) {
                    printf("\n É necessário cadastrar pelo menos duas cidades.\n");
                } else {
                    int i1, i2, atributo;
                    printf("Índice da primeira cidade (0 a %d): ", totalCidades - 1);
                    scanf("%d", &i1);
                    printf("Índice da segunda cidade (0 a %d): ", totalCidades - 1);
                    scanf("%d", &i2);

                    printf("Escolha o atributo para comparar:\n");
                    printf("1 - População\n");
                    printf("2 - Área\n");
                    printf("3 - PIB\n");
                    printf("4 - Pontos Turísticos\n");
                    printf("5 - Densidade Populacional (menor = melhor)\n");
                    printf("6 - PIB per capita\n");
                    printf("Opção: ");
                    scanf("%d", &atributo);

                    compararCartas(cidades[i1], cidades[i2], atributo);
                }
                break;
            case 4:
                printf("\n Encerrando o programa. Até a próxima!\n");
                break;
            default:
                printf("\n Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    free(cidades); 
    return 0;
}
