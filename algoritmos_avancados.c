#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa uma sala da mansão
typedef struct Sala {
    char nome[50];            // Nome do cômodo
    struct Sala *esquerda;    // Caminho para a próxima sala à esquerda
    struct Sala *direita;     // Caminho para a próxima sala à direita
} Sala;

/*
 * Função: criarSala
 * Cria dinamicamente uma sala com o nome informado
 * e inicializa seus ponteiros filhos como NULL.
 */
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro na alocação de memória!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

/*
 * Função: explorarSalas
 * Permite ao jogador navegar pela mansão a partir da sala atual.
 * O jogador escolhe ir para a esquerda ('e'), direita ('d') ou sair ('s').
 * A exploração termina quando o jogador chega a uma sala sem caminhos.
 */
void explorarSalas(Sala* atual) {
    if (atual == NULL) return;

    printf("\nVocê entrou na sala: %s\n", atual->nome);

    // Verifica se é uma sala folha (sem caminhos)
    if (atual->esquerda == NULL && atual->direita == NULL) {
        printf("Esta sala não possui mais caminhos. Exploração encerrada aqui!\n");
        return;
    }

    // Menu de navegação
    char escolha;
    do {
        printf("Escolha seu caminho: (e) esquerda, (d) direita, (s) sair: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            explorarSalas(atual->esquerda);
            break;
        } else if (escolha == 'd' && atual->direita != NULL) {
            explorarSalas(atual->direita);
            break;
        } else if (escolha == 's') {
            printf("Saindo da exploração...\n");
            break;
        } else {
            printf("Escolha inválida ou caminho não disponível. Tente novamente.\n");
        }
    } while (1);
}

/*
 * Função principal
 * Monta o mapa da mansão e inicia a exploração a partir do Hall de Entrada.
 */
int main() {
    // Criando o mapa da mansão
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEsq = criarSala("Sala de Estar");
    Sala* salaDir = criarSala("Sala de Jantar");
    Sala* salaEsqEsq = criarSala("Biblioteca");
    Sala* salaEsqDir = criarSala("Cozinha");
    Sala* salaDirEsq = criarSala("Jardim");
    Sala* salaDirDir = criarSala("Despensa");

    // Conectando as salas (montando a árvore)
    hall->esquerda = salaEsq;
    hall->direita = salaDir;

    salaEsq->esquerda = salaEsqEsq;
    salaEsq->direita = salaEsqDir;

    salaDir->esquerda = salaDirEsq;
    salaDir->direita = salaDirDir;

    // Início da exploração
    printf("Bem-vindo ao Detective Quest! Explore a mansão.\n");
    explorarSalas(hall);

    // Liberando memória
    free(salaDirDir);
    free(salaDirEsq);
    free(salaDir);
    free(salaEsqDir);
    free(salaEsqEsq);
    free(salaEsq);
    free(hall);

    printf("Fim da exploração da mansão.\n");
    return 0;
}