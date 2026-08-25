// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
char* listaMissoes[] = {
    "Conquistar 2 territórios",
    "Eliminar todas as tropas da cor vermelha",
    "Conquistar qualquer território inimigo",
    "Ter pelo menos 10 tropas em um território",
    "Conquistar o território 1"
};
int totalMissoes = 5;
// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};
// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
struct Territorio* alocarMapa(int n);
void inicializarTerritorios(struct Territorio* mapa, int n);
void exibirMapa(const struct Territorio* mapa, int n);
void simularAtaque(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);
void limparBufferEntrada();
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
void exibirMissao(const char* missao);
int verificarMissao(const char* missao, struct Territorio* mapa, int n);

// Funções de setup e gerenciamento de memória:
struct Territorio* alocarMapa(int n)
{
    struct Territorio* mapa = calloc(n, sizeof(struct Territorio));
    if (!mapa)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    return mapa;
}
// Funções de interface com o usuário:
void inicializarTerritorios(struct Territorio* mapa, int n)
{

    printf("=====================================================\n");
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n\n");

    for (int i = 0; i < n; i++)
    {
        printf(" --- Cadastrando o Territorio %d --- \n", i + 1);

        printf("Nome do Território: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do Exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de Tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

    // Exibe o mapa
    void exibirMapa(const struct Territorio* mapa, int n){
        printf("\n===== MAPA ATUAL =====\n");
        for (int i = 0; i < n; i++)
        {
            printf("Território %d:\n", i + 1);
            printf("Nome: %s\n", mapa[i].nome);
            printf("Cor: %s\n", mapa[i].cor);
            printf("Tropas: %d\n", mapa[i].tropas);
            printf("-------------------------\n");
        }
    }

    // Funções de lógica principal do jogo:
    void simularAtaque(struct Territorio*  atacante, struct Territorio*  defensor)
    {
        printf("\n=== ATAQUE ===\n");
        printf("%s (%s) está atacando %s (%s)\n",
               atacante->nome, atacante->cor,
               defensor->nome, defensor->cor);

        if (strcmp(atacante->cor, defensor->cor) == 0)
        {
            printf("Erro: não é possível atacar um território da mesma cor!\n");
            return;
        }
        if (atacante->tropas < 2)
        {
            printf("O atacante precisa de pelo menos 2 tropas.\n");
            return;
        }
        int dadoAtacante = (rand() % 6) + 1;
        int dadoDefensor = (rand() % 6) + 1;

        printf("Dado do atacante: %d\n", dadoAtacante);
        printf("Dado do defensor: %d\n", dadoDefensor);

        if (dadoAtacante > dadoDefensor)
        {
            printf("O atacante venceu!\n");

            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = atacante->tropas / 2;

            printf("%s foi conquistado!\n", defensor->nome);
        }
        else
        {
            printf("O defensor resistiu!\n");
            atacante->tropas -= 1;
        }
    }

    // Libera memória
    void liberarMemoria(struct Territorio*  mapa)
    {
        free(mapa);
    }

    // Função utilitária:
    void limparBufferEntrada()
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    void atribuirMissao(char* destino, char* missoes[], int totalMissoes){
        int sorteio = rand() % totalMissoes;
        strcpy(destino, missoes[sorteio]);
    }

    void exibirMissao(const char* missao){
        printf("\n===== SUA MISSÃO =====\n");
        printf("%s\n", missao);
        printf("=========================\n\n");
    }

    int verificarMissao(const char* missao, struct Territorio* mapa, int n){
        //Missao 1: Conquistar 2 territórios
        if (strcmp(missao, "Conquistar 2 territórios") == 0) {
            int count = 0;
            for (int i = 0; i < n; i++) {
                if (strcmp(mapa[i].cor, "azul") == 0) {
                    count++;
                }
            }
            return count >= 2;
        }

        //Missão 2: Eliminar tropas vermelhas
        if(strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
            for (int i = 0; i < n; i++) {
                if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
                return 0;
            }
            return 1;
        }

        //Missão 3: Conquistar qualquer território inimigo
        if (strcmp(missao, "Conquistar qualquer território inimigo") == 0) {
            for (int i = 0; i < n; i++) {
                if (strcmp(mapa[i].cor, "azul") == 0) {
                    return 1;
                }
            }
            return 0;
        }

        //Missão 4: Ter pelo menos 10 tropas em um território
        if (strcmp(missao, "Ter pelo menos 10 tropas em um território") == 0) {
            for (int i = 0; i < n; i++) {
                if (mapa[i].tropas >= 10)
                return 1;
            }
        }
        return 0;

        // Missão 5: Conquistar o território 1
        if (strcmp(missao, "Conquistar o território 1") == 0) {
            return strcmp(mapa[0].cor, "azul") == 0;
        }
        return 0;
    }



    // --- Função Principal (main) ---
    // Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
    int main()
{
    srand(time(NULL));

    int n = 5;
    struct Territorio *territorios = alocarMapa(n);

    printf("=====================================================\n");
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n");

    inicializarTerritorios(territorios, n);
    exibirMapa(territorios, n);

    // Missão do jogador
    char* missaoJogador = malloc(100);
    atribuirMissao(missaoJogador, listaMissoes, totalMissoes);
    exibirMissao(missaoJogador);

    int opcao;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Atacar\n");
        printf("2 - Exibir mapa\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int atacante, defensor;

            printf("\nEscolha o território atacante (1 a %d): ", n);
            scanf("%d", &atacante);

            printf("Escolha o território defensor (1 a %d): ", n);
            scanf("%d", &defensor);

            simularAtaque(&territorios[atacante - 1], &territorios[defensor - 1]);

            // Verifica missão após o ataque
            if (verificarMissao(missaoJogador, territorios, n)) {
                printf("\n==================================\n");
                printf("PARABENS! VOCÊ CUMPRIU SUA MISSAO!\n");
                printf("MISSAO: %s\n", missaoJogador);
                printf("==================================\n");
                break; // encerra o jogo
            }
        }
        else if (opcao == 2) {
            exibirMapa(territorios, n);
        }
        else if (opcao == 0) {
            printf("\nSaindo do jogo...\n");
        }
        else {
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(territorios);
    free(missaoJogador);
        // 1. Configuração Inicial (Setup):
        // - Define o locale para português.
        // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
        // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
        // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
        // - Define a cor do jogador e sorteia sua missão secreta.

        // 2. Laço Principal do Jogo (Game Loop):
        // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
        // - A cada iteração, exibe o mapa, a missão e o menu de ações.
        // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
        //   - Opção 1: Inicia a fase de ataque.
        //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
        //   - Opção 0: Encerra o jogo.
        // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

        // 3. Limpeza:
        // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

        return 0;
    }

    // --- Implementação das Funções ---

    // alocarMapa():
    // Aloca dinamicamente a memória para o vetor de territórios usando calloc.
    // Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

    // inicializarTerritorios():
    // Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
    // Esta função modifica o mapa passado por referência (ponteiro).

    // liberarMemoria():
    // Libera a memória previamente alocada para o mapa usando free.

    // exibirMenuPrincipal():
    // Imprime na tela o menu de ações disponíveis para o jogador.

    // exibirMapa():
    // Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
    // Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

    // exibirMissao():
    // Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

    // faseDeAtaque():
    // Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
    // Chama a função simularAtaque() para executar a lógica da batalha.

    // simularAtaque():
    // Executa a lógica de uma batalha entre dois territórios.
    // Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
    // Se um território for conquistado, atualiza seu dono e move uma tropa.

    // sortearMissao():
    // Sorteia e retorna um ID de missão aleatório para o jogador.
    
    // verificarVitoria():
    // Verifica se o jogador cumpriu os requisitos de sua missão atual.
    // Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
    // Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

    // limparBufferEntrada():
    // Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
