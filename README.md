# DESAFIO-faculdade---avançado-c


# Desafio Nível Mestre: Torre de Resgate

## Descrição
No desafio final, você deve organizar componentes para montar uma torre de resgate. O jogador pode escolher critérios de ordenação e buscar o componente-chave para ativar a torre.

## Objetivos
- Implementar **Bubble Sort** (por nome), **Insertion Sort** (por tipo) e **Selection Sort** (por prioridade)  
- Aplicar **busca binária** por nome  
- Medir comparações e tempo de execução  
- Exibir componentes ordenados e confirmar presença do componente-chave  

## Estrutura de Dados
```c
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

