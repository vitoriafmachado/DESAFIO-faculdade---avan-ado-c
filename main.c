#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Função para mostrar todos os componentes
void mostrarComponentes(Componente comps[], int n) {
    printf("\nLista de Componentes:\n");
    printf("Nome\t\tTipo\t\tPrioridade\n");
    printf("-------------------------------------------\n");
    for(int i = 0; i < n; i++) {
        printf("%-15s %-15s %d\n", comps[i].nome, comps[i].tipo, comps[i].prioridade);
    }
    printf("\n");
}

// Bubble Sort por nome
int bubbleSortNome(Componente comps[], int n) {
    int comparacoes = 0;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            comparacoes++;
            if(strcmp(comps[j].nome, comps[j+1].nome) > 0) {
                Componente temp = comps[j];
                comps[j] = comps[j+1];
                comps[j+1] = temp;
            }
        }
    }
    return comparacoes;
}

// Insertion Sort por tipo
int insertionSortTipo(Componente comps[], int n) {
    int comparacoes = 0;
    for(int i = 1; i < n; i++) {
        Componente key = comps[i];
        int j = i - 1;
        while(j >=0 && (++comparacoes && strcmp(comps[j].tipo, key.tipo) > 0)) {
            comps[j+1] = comps[j];
            j--;
        }
        comps[j+1] = key;
    }
    return comparacoes;
}

// Selection Sort por prioridade
int selectionSortPrioridade(Componente comps[], int n) {
    int comparacoes = 0;
    for(int i = 0; i < n-1; i++) {
        int min_idx = i;
        for(int j = i+1; j < n; j++) {
            comparacoes++;
            if(comps[j].prioridade < comps[min_idx].prioridade) {
                min_idx = j;
            }
        }
        Componente temp = comps[i];
        comps[i] = comps[min_idx];
        comps[min_idx] = temp;
    }
    return comparacoes;
}

// Busca binária por nome
int buscaBinariaPorNome(Componente comps[], int n, char chave[]) {
    int left = 0, right = n-1;
    int comparacoes = 0;
    while(left <= right) {
        int mid = left + (right-left)/2;
        comparacoes++;
        int cmp = strcmp(comps[mid].nome, chave);
        if(cmp == 0) {
            printf("Componente encontrado: [%s, %s, %d] (Comparações: %d)\n",
                   comps[mid].nome, comps[mid].tipo, comps[mid].prioridade, comparacoes);
            return mid;
        } else if(cmp < 0) {
            left = mid + 1;
        } else {
            right = mid -1;
        }
    }
    printf("Componente não encontrado (Comparações: %d)\n", comparacoes);
    return -1;
}

int main() {
    Componente componentes[MAX_COMPONENTES];
    int n = 0;

    printf("=== Cadastro de Componentes da Torre ===\n");
    printf("Insira até %d componentes.\n", MAX_COMPONENTES);

    char buffer[50];
    while(n < MAX_COMPONENTES) {
        printf("\nComponente %d\n", n+1);

        printf("Nome: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(componentes[n].nome, buffer);

        printf("Tipo: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(componentes[n].tipo, buffer);

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[n].prioridade);
        while(getchar() != '\n'); // limpar buffer

        n++;
        char resp;
        if(n < MAX_COMPONENTES) {
            printf("Deseja adicionar outro componente? (s/n): ");
            scanf("%c", &resp);
            while(getchar() != '\n'); // limpar buffer
            if(resp != 's' && resp != 'S') break;
        }
    }

    int opcao;
    do {
        printf("\n=== Menu de Ordenação e Busca ===\n");
        printf("1 - Ordenar por nome (Bubble Sort)\n");
        printf("2 - Ordenar por tipo (Insertion Sort)\n");
        printf("3 - Ordenar por prioridade (Selection Sort)\n");
        printf("4 - Buscar componente por nome (busca binária)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        while(getchar() != '\n');

        clock_t start, end;
        int comparacoes;

        switch(opcao) {
            case 1:
                start = clock();
                comparacoes = bubbleSortNome(componentes, n);
                end = clock();
                mostrarComponentes(componentes, n);
                printf("Bubble Sort concluído. Comparações: %d, Tempo: %.5f s\n",
                       comparacoes, (double)(end-start)/CLOCKS_PER_SEC);
                break;
            case 2:
                start = clock();
                comparacoes = insertionSortTipo(componentes, n);
                end = clock();
                mostrarComponentes(componentes, n);
                printf("Insertion Sort concluído. Comparações: %d, Tempo: %.5f s\n",
                       comparacoes, (double)(end-start)/CLOCKS_PER_SEC);
                break;
            case 3:
                start = clock();
                comparacoes = selectionSortPrioridade(componentes, n);
                end = clock();
                mostrarComponentes(componentes, n);
                printf("Selection Sort concluído. Comparações: %d, Tempo: %.5f s\n",
                       comparacoes, (double)(end-start)/CLOCKS_PER_SEC);
                break;
            case 4:
                printf("Digite o nome do componente para buscar: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                buscaBinariaPorNome(componentes, n, buffer);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}
