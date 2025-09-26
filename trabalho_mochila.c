#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10
#define TAM_STRING 30

// --- Definição da struct ---
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// --- Protótipos das funções ---
void limparBufferEntrada();
void inserirItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void removerItem(Item mochila[], int *total);
void buscarItem(Item mochila[], int total);

// --- Função para limpar buffer ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função para listar itens ---
void listarItens(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    // Primeira listagem em tabela
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", total, MAX_ITENS);
    printf("---------------------------------------------------\n");
    printf("NOME                | TIPO          | QUANTIDADE\n");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%-20s | %-12s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("---------------------------------------------------\n");

    // Segunda listagem em formato de relatório
    printf("\n================ LISTA DETALHADA DE ITENS =================\n");
    for (int i = 0; i < total; i++) {
        printf("Item %d:\n", i + 1);
        printf(" Nome      : %s\n", mochila[i].nome);
        printf(" Tipo      : %s\n", mochila[i].tipo);
        printf(" Quantidade: %d\n", mochila[i].quantidade);
        printf("---------------------------------------------------\n");
    }
}

// --- Função para inserir um item ---
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");

    printf("Nome do item: ");
    fgets(mochila[*total].nome, TAM_STRING, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = '\0';

    printf("Tipo do item (arma, municao, cura, etc.): ");
    fgets(mochila[*total].tipo, TAM_STRING, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    limparBufferEntrada();

    printf("\nItem '%s' adicionado com sucesso!\n", mochila[*total].nome);

    (*total)++;

    // 👉 Mostrar tabelas automaticamente após adicionar item
    listarItens(mochila, *total);
}

// --- Função para remover um item ---
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nA mochila já está vazia.\n");
        return;
    }

    char nome[TAM_STRING];
    printf("\nDigite o nome do item a remover: ");
    fgets(nome, TAM_STRING, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("Item '%s' removido com sucesso!\n", nome);
            return;
        }
    }
    printf("Item '%s' não encontrado.\n", nome);
}

// --- Função para buscar um item ---
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    char nome[TAM_STRING];
    printf("\nDigite o nome do item para buscar: ");
    fgets(nome, TAM_STRING, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado:\n");
            printf(" Nome      : %s\n", mochila[i].nome);
            printf(" Tipo      : %s\n", mochila[i].tipo);
            printf(" Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }
    printf("Item '%s' não encontrado.\n", nome);
}

// --- Função principal ---
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n==========================================\n");
        printf(" MOCHILA DE SOBREVIVÊNCIA - Código da ilha \n");
        printf("==========================================\n");
        printf(" Itens na Mochila: %d/%d\n", total, MAX_ITENS); // <-- atualizado
        printf("1 - Adicionar item (Loot)\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens da mochila\n");
        printf("0 - Sair\n");
        printf("------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1: inserirItem(mochila, &total); break;
            case 2: removerItem(mochila, &total); break;
            case 3: listarItens(mochila, total); break;
            case 4: buscarItem(mochila, total); break;
            case 0: printf("\nSaindo do sistema...\n"); break;
            default: printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}