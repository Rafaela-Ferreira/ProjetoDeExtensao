#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h> // Inclui a biblioteca necess�ria para usar mkdir

// *** INICIO DAS FUN��ES DA KEZIA ***
// Fun��o para fazer o cadastro de clientes
typedef struct
{
    char nome_cliente[100];
    char telefone_cliente[30];
    char cpf_cliente[20];
    char email_cliente[50];
    char endereco_cliente[100];
} CadastroCliente;

typedef struct
{
    char endereco_chacara[100];
    char telefone_chacara[20];
    float valor_locacao;
    char data_contrato[20];
    int numero_contrato;
    char assinatura[100];
} Contrato;

int contadorContrato = 1;

void criarCadastro(CadastroCliente *cliente, Contrato *contrato)
{
    setbuf(stdin, NULL);

    printf("Nome do cliente: ");
    fgets(cliente->nome_cliente, sizeof(cliente->nome_cliente), stdin);
    strtok(cliente->nome_cliente, "\n");

    printf("Telefone: ");
    fgets(cliente->telefone_cliente, sizeof(cliente->telefone_cliente), stdin);
    strtok(cliente->telefone_cliente, "\n");

    printf("CPF do cliente: ");
    fgets(cliente->cpf_cliente, sizeof(cliente->cpf_cliente), stdin);
    strtok(cliente->cpf_cliente, "\n");

    printf("Endere�o do cliente: ");
    fgets(cliente->endereco_cliente, sizeof(cliente->endereco_cliente), stdin);
    strtok(cliente->endereco_cliente, "\n");

    printf("Email do cliente: ");
    fgets(cliente->email_cliente, sizeof(cliente->email_cliente), stdin);
    strtok(cliente->email_cliente, "\n");

    printf("Endere�o da ch�cara: ");
    fgets(contrato->endereco_chacara, sizeof(contrato->endereco_chacara), stdin);
    strtok(contrato->endereco_chacara, "\n");

    contrato->numero_contrato = contadorContrato;
    contadorContrato++;

    printf("Data do contrato: ");
    fgets(contrato->data_contrato, sizeof(contrato->data_contrato), stdin);
    strtok(contrato->data_contrato, "\n");

    printf("Valor da loca��o: ");
    scanf("%f", &contrato->valor_locacao);

    setbuf(stdin, NULL); // Limpa o buffer de entrada

    printf("\n\t\tAssinatura: ");
    fgets(contrato->assinatura, sizeof(contrato->assinatura), stdin);
    strtok(contrato->assinatura, "\n");
}

void salvarCadastro(CadastroCliente *cliente, Contrato *contrato)
{
    char pastaNome[100] = "Contratos";

    // Nome da pasta onde voc� deseja salvar os arquivos
#ifdef _WIN32
    mkdir(pastaNome);
#else
    mkdir(pastaNome, 0755); // Cria a pasta (diret�rio) se ela n�o existir
#endif

    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s/contrato_%s.txt", pastaNome, cliente->cpf_cliente);

    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "\n\t\t\t\t\tRECANTO DOS SONHOS\n");
    fprintf(arquivo, "------------------------------------------------------------------------------\n");
    fprintf(arquivo, "\n");
    fprintf(arquivo, "Contrato de Loca��o de Ch�cara\n");
    fprintf(arquivo, "Cliente: %s\n", cliente->nome_cliente);
    fprintf(arquivo, "Telefone: %s\n", cliente->telefone_cliente);
    fprintf(arquivo, "CPF: %s\n", cliente->cpf_cliente);
    fprintf(arquivo, "Endere�o do cliente: %s\n", cliente->endereco_cliente);
    fprintf(arquivo, "Email do cliente: %s\n", cliente->email_cliente);
    fprintf(arquivo, "Endere�o da Ch�cara: %s\n", contrato->endereco_chacara);
    fprintf(arquivo, "N�mero do Contrato: %d\n", contrato->numero_contrato);
    fprintf(arquivo, "Data do Contrato: %s\n", contrato->data_contrato);
    fprintf(arquivo, "Valor da Loca��o: R$%.2f\n", contrato->valor_locacao);
    fprintf(arquivo, "\n\t\tAssinatura: %s\n", contrato->assinatura);
    fprintf(arquivo, "------------------------------------------------------------------------------\n");

    fclose(arquivo);
    printf("\n\nContrato gerado com sucesso e salvo em '%s'.\n", nomeArquivo);
}


// *** FIM DAS FUN��ES DA KEZIA ***

// *** INICIO DAS FUN��ES DA RAFAELA ***
// ---------------- 3. FUN��O PARA CALCULAR DIA DA SEMANA PARA DATA ESPEC�FICA -
int calcularDiaSemana(int ano, int mes, int dia)
{
    if (mes < 3)
    {
        mes += 12;
        ano--;
    }
    int K = ano % 100;
    int J = ano / 100;
    int diaDaSemana = (dia + 13 * (mes + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    // Ajuste para domingo ser o dia 0 e s�bado o dia 6
    diaDaSemana = (diaDaSemana + 6) % 7;
    return diaDaSemana;
}
//---------------- 4. FUN��O PARA DESTACAR DIAS SELECIONADOS - COR [SAB, DOM, DIAS AGENDADOS] ------------------
void destacarDiasSelecionados(int mes, int ano, int diasAgendados[], int numDias)
{
    char *nomesDosMeses[] = {"", "Janeiro", "Fevereiro", "Mar�o", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("\nCalend�rio para %s de %d\n", nomesDosMeses[mes], ano);
    printf("\033[1;31mDom\tSeg\tTer\tQua\tQui\tSex\tSáb\n\033[0m");

    int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);

    for (int i = 0; i < primeiroDiaDoMes; i++)
    {
        printf("\t");
    }

    for (int dia = 1; dia <= diasNoMes[mes]; dia++)
    {
        int agendado = 0;
        int diaDaSemana = calcularDiaSemana(ano, mes, dia);

        for (int i = 0; i < numDias; i++)
        {
            if (dia == diasAgendados[i])
            {
                agendado = 1;
                break;
            }
        }

        if (diaDaSemana == 0)
        {
            if (agendado)
            {
                printf("\033[1;94m%2d\033[0m\t", dia); // Domingo com destaque azul
            }
            else
            {
                printf("\033[1;31m%2d\033[0m\t", dia); // Domingo com destaque vermelho
            }
        }
        else if (diaDaSemana == 6)
        {
            if (agendado)
            {
                printf("\033[1;34m%2d\033[0m\t", dia); // S�bado com destaque azul
            }
            else
            {
                printf("\033[0;90m%2d\033[0m\t", dia); // S�bado com destaque cinza
            }
        }
        else if (agendado)
        {
            printf("\033[1;34m%2d\033[0m\t", dia); // Dia agendado com destaque azul
        }
        else
        {
            printf("%2d\t", dia);
        }

        if ((primeiroDiaDoMes + dia) % 7 == 0 || dia == diasNoMes[mes])
        {
            printf("\n");
        }
    }
    printf("\n");
}
// ---------------- FUN��O PARA VERIFICAR SE O ANO INSERIDO � V�LIDO ------------------
int verificarAno(int ano)
{
    if (ano < 2023 || ano > 2100)
    {
        printf("Ano inv�lido. Por favor, insira um ano entre 2023 e 2100.\n");
        return 0;
    }
    return 1;
}
// ---------------- FUN��O PARA SOLICITAR AO USU�RIO OS DIAS A SEREM AGENDADOS E DESTACALOS NO CALEND�RIO ------------------
// Defina o tamanho inicial do vetor para armazenar as datas agendadas
#define TAMANHO_INICIAL 10
#define ARQUIVO_DATAS "datas_agendadas.txt"



int verificarMes(int mes) {
    return (mes >= 1 && mes <= 12);
}

int verificarDia(int dia, int mes, int ano, int ano_atual, int mes_atual, int dia_atual) {
    if (dia < 1 || dia > 31) {
        return 0;  // Dia inválido
    }

    if ((ano == ano_atual && mes == mes_atual && dia <= dia_atual) || (ano == ano_atual && mes < mes_atual)) {
      printf("\n\033[1;31mNão é possível agendar para uma data que já passou ou é o dia de hoje.\033[0m\n");
        return 0;  // Data inválida
    }

    return 1;  // Data válida
}



void salvarDatas(int *diasAgendados, int numDiasAgendados) {
    FILE *arquivo = fopen(ARQUIVO_DATAS, "w");
    if (arquivo == NULL) {
        printf("\n\033[1;31mErro ao abrir o arquivo para salvar datas.\033[0m\n");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivo, "%d\n", numDiasAgendados);

    for (int i = 0; i < numDiasAgendados; i++) {
        fprintf(arquivo, "%d\n", diasAgendados[i]);
    }

    fclose(arquivo);
}

void carregarDatas(int **diasAgendados, int *numDiasAgendados, int *capacidadeAtual) {
    FILE *arquivo = fopen(ARQUIVO_DATAS, "r");
    if (arquivo == NULL) {
        printf("\n\n\033[1;31mArquivo de datas não encontrado. Criando um novo.\033[0m\n");
        return;
    }

    fscanf(arquivo, "%d", numDiasAgendados);

    if (*numDiasAgendados > *capacidadeAtual) {
        *capacidadeAtual = *numDiasAgendados;
        *diasAgendados = realloc(*diasAgendados, *capacidadeAtual * sizeof(int));
        if (*diasAgendados == NULL) {
            printf("\033[1;31mErro ao alocar memória.\033[0m\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < *numDiasAgendados; i++) {
        fscanf(arquivo, "%d", &((*diasAgendados)[i]));
    }

    fclose(arquivo);
}

void adicionarDias(int **diasAgendados, int *numDiasAgendados, int *capacidadeAtual, int dias) {
    // Redimensiona o vetor se necessário
    if (*numDiasAgendados + dias > *capacidadeAtual) {
        *capacidadeAtual = *numDiasAgendados + dias;
        *diasAgendados = realloc(*diasAgendados, *capacidadeAtual * sizeof(int));
        if (*diasAgendados == NULL) {
            printf("\033[1;31mErro ao alocar memória.\033[0m\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < dias; i++) {
        while (1) {
            printf("Digite o dia a ser agendado (entre 1 e 31): ");
            scanf("%d", &(*diasAgendados)[*numDiasAgendados]);

            if (verificarDia((*diasAgendados)[*numDiasAgendados], 0, 0, 0, 0, 0)) {
                (*numDiasAgendados)++;
                break;
            } else {
              printf("\033[1;31m\nDia inválido ou data já passou ou é o dia de hoje.\033[0m\n");
            }
        }
    }

    // Salva as datas após adicionar os novos dias
    salvarDatas(*diasAgendados, *numDiasAgendados);
}

void agendarNoCalendario() {
    time_t now;
    struct tm *local;
    time(&now);
    local = localtime(&now);
    int ano_atual = local->tm_year + 1900;
    int mes_atual = local->tm_mon + 1;
    int dia_atual = local->tm_mday;
    int mes, ano;

    int dataValida = 0;

    while (!dataValida) {
        while (1) {
            printf("Digite o ano (entre 2023 e 2100): ");
            scanf("%d", &ano);

            if (verificarAno(ano)) {
                break;
            }
        }

        while (1) {
            printf("Digite o mês (entre 1 e 12): ");
            scanf("%d", &mes);

            if (verificarMes(mes)) {
                break;
            } else {
                printf("Mês inválido.\n");
            }
        }

        dataValida = 1;
    }

    int *diasAgendados = malloc(TAMANHO_INICIAL * sizeof(int));
    if (!diasAgendados) {
        printf("\033[1;31mErro ao alocar memória.\033[0m\n");
        exit(EXIT_FAILURE);
    }

    int capacidadeAtual = TAMANHO_INICIAL;
    int numDiasAgendados = 0;

    carregarDatas(&diasAgendados, &numDiasAgendados, &capacidadeAtual);

    printf("\033[1m\nCalendário com dias agendados:\n");
    printf("=============================================\n\033[0m");
    destacarDiasSelecionados(mes, ano, diasAgendados, numDiasAgendados);

    // Adicionar mais dias
    printf("\nDeseja adicionar mais dias ao calendário? (1 - Sim / 0 - Não): ");
    int opcao;
    scanf("%d", &opcao);

    while (opcao == 1) {
        printf("Quantos dias você deseja adicionar? ");
        int numDias;
        scanf("%d", &numDias);

        adicionarDias(&diasAgendados, &numDiasAgendados, &capacidadeAtual, numDias);

        printf("\033[1m\nCalendário com dias agendados:\n");
        printf("=============================================\n\033[0m");
        destacarDiasSelecionados(mes, ano, diasAgendados, numDiasAgendados);

        printf("\nDeseja adicionar mais dias ao calendário? (1 - Sim / 0 - Não): ");
        scanf("%d", &opcao);
    }

    // Libera a memória alocada para o vetor
    free(diasAgendados);
}

//----------------  FUN��O PARA EXIBIR O CALEND�RIO ------------------
void calendario()
{
    int ano, mes;
    while (1)
    {
        printf("Digite o ano (entre 2000 e 2100): ");
        scanf("%d", &ano);

        if (ano >= 2000 && ano <= 2100)
        {
            break; // Sai do loop se o ano for v�lido.
        }
        else
        {
            printf("Ano inv�lido.\n");
        }
    }

    while (1)
    {
        printf("Digite o m�s (entre 1 e 12): ");
        scanf("%d", &mes);

        if (mes >= 1 && mes <= 12)
        {
            break; // Sai do loop se o M�s for v�lido.
        }
        else
        {
            printf("M�s inv�lido.\n");
        }
    }

    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))
    {
        diasNoMes[2] = 29; // Fevereiro tem 29 dias em um ano bissexto
    }

    char *nomesDosMeses[] = {"",        "Janeiro",  "Fevereiro", "Mar�o",
                             "Abril",   "Maio",     "Junho",     "Julho",
                             "Agosto",  "Setembro", "Outubro",   "Novembro",
                             "Dezembro"
                            };

    printf("\nCalend�rio para %s de %d\n", nomesDosMeses[mes], ano);
    printf("\033[1;31mDom\tSeg\tTer\tQua\tQui\tSex\tSáb\n\033[0m");

    int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);

    for (int i = 0; i < primeiroDiaDoMes; i++)
    {
        printf("\t");
    }

    // Gerar 5 dias aleat�rios
    int diasRealcados[5];
    for (int i = 0; i < 5; i++)
    {
        diasRealcados[i] = rand() % diasNoMes[mes] + 1;
    }

    for (int dia = 1; dia <= diasNoMes[mes]; dia++)
    {
        int realcado = 0;
        for (int i = 0; i < 5; i++)
        {
            if (dia == diasRealcados[i])
            {
                realcado = 1;
                break;
            }
        }
        int diaDaSemana = calcularDiaSemana(ano, mes, dia);

        if (realcado)
        {
            printf("\033[1;34m%2d\033[0m\t", dia); // Imprime o dia real�ado em azul
        }
        else if (diaDaSemana == 0)
        {
            printf("\033[1;31m%2d\033[0m\t", dia); // Imprime domingo em vermelho
        }
        else if (diaDaSemana == 6)
        {
            printf("\033[1;90m%2d\033[0m\t", dia); // Imprime s�bado em cinza
        }
        else
        {
            printf("%2d\t", dia);
        }

        if ((primeiroDiaDoMes + dia) % 7 == 0 || dia == diasNoMes[mes])
        {
            printf("\n");
        }
    }
    printf("\n");
}

// -------- FUN��O CADASTRO DE CH�CARAS - VARI�VEIS GLOBAIS ---------
#define MAX_NOME 50
#define MAX_CARACTERISTICAS 9
#define MAX_CHACARAS 10

// Defini��o da estrutura Chacara
typedef struct Chacara
{
    char caracteristicas[MAX_CARACTERISTICAS][MAX_NOME];
    char nome[MAX_NOME];
} Chacara;

// Fun��o para preencher os dados da ch�cara
void preencherChacara(Chacara *chacara, char nome[MAX_NOME], char caracteristicas[MAX_CARACTERISTICAS][MAX_NOME])
{
    for (int i = 0; i < MAX_CARACTERISTICAS; i++)
    {
        strcpy(chacara->caracteristicas[i], caracteristicas[i]);
    }
    strcpy(chacara->nome, nome);
}

// Fun��o para exibir todos os atributos da ch�cara
void exibirChacara(Chacara ch)
{
    printf("\033[1;34m%s\033[0m\n", ch.nome); // Nome em azul e negrito
    printf("Caracter�sticas:\n");
    for (int i = 0; i < MAX_CARACTERISTICAS; i++)
    {
        printf("%d. %s\n", i + 1, ch.caracteristicas[i]);
    }
}

// Fun��o para exibir apenas o nome das ch�caras dispon�veis
void exibirNomesChacarasDisponiveis(Chacara ch[], int n)
{
    printf("Ch�caras Dispon�veis:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. \033[1;34m%s\033[0m\n", i + 1, ch[i].nome);
    }
}

// Fun��o para cadastrar novas ch�caras
void cadastrarChacaras(Chacara ch[], int n)
{
    for (int i = 0; i < n; i++)
    {
        Chacara novaChacara;
        char nome[MAX_NOME];
        char caracteristicas[MAX_CARACTERISTICAS][MAX_NOME];

        printf("Digite o nome da ch�cara: ");
        fgets(nome, MAX_NOME, stdin);
        nome[strcspn(nome, "\n")] = 0; // Remover a quebra de linha

        printf("Digite as caracter�sticas da ch�cara (at� 9 itens separados por v�rgula): ");
        char caracteristicasString[500];
        fgets(caracteristicasString, 500, stdin);
        char *token = strtok(caracteristicasString, ",");
        int j = 0;
        while (token != NULL && j < MAX_CARACTERISTICAS)
        {
            token[strcspn(token, "\n")] = 0; // Remover a quebra de linha
            strcpy(caracteristicas[j], token);
            token = strtok(NULL, ",");
            j++;
        }

        preencherChacara(&novaChacara, nome, caracteristicas);
        ch[i] = novaChacara;
    }
}
// Fun��o para visualizar ch�caras dispon�veis e permitir que o usu�rio escolha uma
Chacara visualizarChacarasDisponiveis()
{
    Chacara chacarasDisponiveis[3];

    const char *caracteristicas1[9] =
    {
        "250m�",
        "Estacionamento para at� 10 carros",
        "Cont�m Churrasqueira",
        "Freezer",
        "2 fog�es",
        "Wi-fi",
        "3 Quartos",
        "Geladeira",
        "Limpeza inclusa"
    };

    const char *caracteristicas2[9] =
    {
        "150m�",
        "Estacionamento para at� 5 carros",
        "Sem Churrasqueira",
        "1 fog�o",
        "Sem Freezer",
        "Sem Wi-fi",
        "1 Quarto",
        "Geladeira",
        "Limpeza n�o inclusa"
    };

    const char *caracteristicas3[9] =
    {
        "200m�",
        "Estacionamento para at� 8 carros",
        "Cont�m Churrasqueira",
        "Freezer",
        "2 fog�es",
        "Wi-fi",
        "2 Quartos",
        "Geladeira",
        "Limpeza inclusa"
    };

    preencherChacara(&chacarasDisponiveis[0], "RECANTO DOS SONHOS", caracteristicas1);
    preencherChacara(&chacarasDisponiveis[1], "CH�CARA GABI", caracteristicas2);
    preencherChacara(&chacarasDisponiveis[2], "OS CARAC�IS", caracteristicas3);

    exibirNomesChacarasDisponiveis(chacarasDisponiveis, 3);

    int escolha;
    do
    {
        printf("Escolha uma ch�cara (1, 2 ou 3): ");
        scanf("%d", &escolha);
    }
    while (escolha < 1 || escolha > 3);

    return chacarasDisponiveis[escolha - 1];
}

// vizualizar const de chacaras
void visualizarConstantes(const char *nomeChacara, const char *caracteristicas[], int num)
{
    printf("\033[1;34m%s:\n\033[0m", nomeChacara);
    for (int i = 0; i < num; i++)
    {
        printf("%s\n", caracteristicas[i]);
    }
    printf("\n");
}

// ------------- DEFININDO A ESTRUTURA PARA ARMAZENAR INFORMA��ES DO USU�RIO -------------
struct Usuario
{
    char nome[50];
    char senha[20];
};
// --------------- FUN��O PARA VERIFICAR O LOGIN ----------------
int verificarLogin(struct Usuario usuarios[], int numUsuarios, char nome[],
                   char senha[])
{
    for (int i = 0; i < numUsuarios; i++)
    {
        if (strcmp(usuarios[i].nome, nome) == 0 &&
                strcmp(usuarios[i].senha, senha) == 0)
        {
            return i; // Retorna o indice do usuario se o login for bem-sucedido
        }
    }
    return -1; // Retorna -1 se o login falhar
}
// *** FIM DAS FUN��ES DA RAFAELA ***

// ***INICIO DAS FUN��ES DO GUSTAVO ***
// ---------------- FUN��O PARA CALCULAR DIA DA SEMANA PARA DATA ESPEC�FICA (GUSTAVO) ------------------
int calcular_dia_semana(int ano_visita, int mes_visita, int dia_visita)
{
    if (mes_visita < 3)
    {
        mes_visita += 12;
        ano_visita--;
    }
    int K = ano_visita % 100;
    int J = ano_visita / 100;
    int dia_semana = (dia_visita + 13 * (mes_visita + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    // Ajuste para domingo ser o dia 0 e s�bado o dia 6
    dia_semana = (dia_semana + 6) % 7;
    return dia_semana;
}
// ---------------- FUN��O PARA VERIFICAR A VALIDA��O DO ANO INSERIDO (GUSTAVO) ------------------
int verifica_ano_visita(int ano_visita)
{
    if (ano_visita < 2023 || ano_visita > 2100)
    {
        printf("\nO ano digitado � inv�lido! \nO ano tem que estar no intervalo entre 2023 e 2100");
        return 0;
    }
    return 1;
}

int verifica_mes_visita(int mes_visita)
{
    if(mes_visita < 1 || mes_visita > 12)
    {
        printf("\nO m�s digitado � inv�lido! \nO m�s tem que estar no intervalo entre 1 e 12");
        return 0;

    }
    return 1;
}
//---------------- FUN��O PARA DESTACAR DIAS SELECIONADOS - COR [SAB, DOM] (GUSTAVO) ------------------
void destaca_dias_selecionados(int mes_visita, int ano_visita, int diaAgendado,
                               int numero_dias)
{
    char *nome_mes[] = {"",        "Janeiro",  "Fevereiro", "Mar�o",
                        "Abril",   "Maio",     "Junho",     "Julho",
                        "Agosto",  "Setembro", "Outubro",   "Novembro",
                        "Dezembro"
                       };

    int mes_dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("\nCalend�rio para %s de %d\n", nome_mes[mes_visita], ano_visita);
    printf("Dom\tSeg\tTer\tQua\tQui\tSex\tS�b\n");

    int mes_primeiro_dia = calcular_dia_semana(ano_visita, mes_visita, 1);

    for (int i = 0; i < mes_primeiro_dia; i++)
    {
        printf("\t");
    }

    for (int dia_visita = 1; dia_visita <= mes_dias[mes_visita]; dia_visita++)
    {
        int agendado = 0;
        for (int i = 0; i < numero_dias; i++)
        {
            if (dia_visita == diaAgendado)
            {
                agendado = 1;
                break;
            }
        }
        int dia_semana = calcular_dia_semana(ano_visita, mes_visita, dia_visita);

        if (dia_semana == 0)
        {
            printf("\033[1;91m%2d\033[0m\t", dia_visita); // Imprime domingo em vermelho
        }
        else if (dia_semana == 6)
        {
            printf("\033[0;90m%2d\033[0m\t", dia_visita); // Imprime s�bado em cinza
        }
        else if (agendado)
        {
            printf("\033[1;34m%2d\033[0m\t", dia_visita); // Imprime o dia agendado em azul
        }
        else
        {
            printf("%2d\t", dia_visita);
        }

        if ((mes_primeiro_dia + dia_visita) % 7 == 0 || dia_visita == mes_dias[mes_visita])
        {
            printf("\n");
        }

    }
    printf("\n");

}
// ---------------- FUN��O PARA SOLICITAR AO USU�RIO O DIA A SER AGENDADO PARA VISITA E DESTAC�-LO NO CALEND�RIO (GUSTAVO) ------------------
void agendar_visita_calendario()
{
    time_t now;
    struct tm *local;
    time(&now);
    local = localtime(&now);
    int ano_visita_atual = local->tm_year + 1900;
    int mes_atual = local->tm_mon + 1;
    int dia_atual = local->tm_mday;
    int mes_visita, dia_visita, ano_visita;
    int diaAgendado;

    while (1)
    {
        printf("\n-------Digite a data que deseja agendar a visita (DD/MM/AAAA)-------\n");
        printf("\nDigite o ano (entre 2023 e 2100): ");
        scanf("%d", &ano_visita);

        if (verifica_ano_visita(ano_visita))
        {
            break;
        }
    }

    while (1)
    {
        printf("\nDigite o m�s (entre 1 e 12): ");
        scanf("%d", &mes_visita);

        if (verifica_mes_visita(mes_visita))
        {
            break;
        }
    }
    printf("\nDigite o dia a ser agendado para visita (entre 1 e 31): ");
    scanf("%d", &diaAgendado);
    // Verifica��o para garantir que o usu�rio n�o agende em datas passadas
    if (ano_visita == ano_visita_atual && mes_visita < mes_atual)
    {
        printf("\nN�o � poss�vel agendar para uma data que j� passou.\n");
        return;
    }

    // Mostra o calend�rio com os dias agendados em azul
    printf("\nCalend�rio com o dia de visita agendado:\n");
    printf("======================================================\n");
    destaca_dias_selecionados(mes_visita, ano_visita, diaAgendado, dia_visita);

    //Mostra a data que foi digitada
    printf("\n-----%d/%d/%d-----", diaAgendado, mes_visita, ano_visita);

    //Mostra o dia da semana dependendo do resultado da f�rmula
    switch(calcular_dia_semana(ano_visita, mes_visita, diaAgendado))
    {

    case 0:
        printf("\nEssa data � um Domingo\n");
        break;
    case 1:
        printf("\nEssa data � uma Segunda - feira\n");
        break;
    case 2:
        printf("\nEssa data � uma Ter�a - feira\n");
        break;
    case 3:
        printf("\nEssa data � uma Quarta - feira\n");
        break;
    case 4:
        printf("\nEssa data � uma Quinta - feira\n");
        break;
    case 5:
        printf("\nEssa data � uma Sexta - feira\n");
        break;
    case 6:
        printf("\nEssa data � um S�bado\n");
        break;
    }
}

//** FIM DAS FUN��ES DO GUSTAVO

//FUN��O PARA SALVAR O CONTRATO EM TXT
void salvarItem(const char *item, const char *nomeCliente)
{
    FILE *arquivo;
    char nomeArquivo[50];  // Ajuste o tamanho conforme necess�rio

    sprintf(nomeArquivo, "contrato_locacao_%s.txt", nomeCliente);

    // Abre o arquivo em modo de escrita, "w" significa criar um novo arquivo para escrita
    arquivo = fopen(nomeArquivo, "w");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Escreve o item no arquivo
    fprintf(arquivo, "%s", item);

    // Fecha o arquivo
    fclose(arquivo);

    printf("Contrato salvo com sucesso no arquivo: %s\n", nomeArquivo);
}



// -------------------- IN�CIO DA MAIN -----------------------
int main()
{
    setlocale(LC_ALL, "Portuguese");

    // Defina os dados do usuario.
    struct Usuario usuarios[2];
    strcpy(usuarios[0].nome, "usuario1");
    strcpy(usuarios[0].senha, "senha1");
    strcpy(usuarios[1].nome, "usuario2");
    strcpy(usuarios[1].senha, "senha2");

    int numUsuarios = 2;

    char nome[50];
    char senha[20];

    int opcao;
    int usuarioLogado = -1;

    while (1)   // Loop principal
    {
        if (usuarioLogado == -1)
        {

            printf("\n\t\t\033[1mBem-vindo!\n\033[0m\n");
            printf("\nRealize o login abaixo para acessar o sistema...\n");
            printf("Nome de usu�rio: ");
            scanf("%s", nome);
            printf("Senha: ");
            scanf("%s", senha);

            usuarioLogado = verificarLogin(usuarios, numUsuarios, nome, senha);

            if (usuarioLogado == -1)
            {
                system("cls");

                printf("Login falhou. Tente novamente.\n");
            }
        }
        else
        {
            system("cls");

            printf("\033[1m\n*** MENU PRINCIPAL ***\n\033[0m\n");
            printf("1. Cadastro de Clientes\n");
            printf("2. Cadastro de Ch�caras\n");
            printf("3. Visualizar Ch�caras Dispon�veis\n");
            printf("4. Agendar Visitas\n");
            printf("5. Agendar Di�rias\n");
            printf("6. Contrato\n");
            printf("7. Calend�rio\n");
            printf("8. Sair\n");
            printf("\nEscolha uma op��o: ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
                system("cls");

                printf("\n\033[1mVOC� SELECIONOU CADASTRO DE CLIENTES.\033[0m\n");
                // Coloque a l�gica do cadastro de clientes aqui
                printf("\n--------------------------------");
                printf("RECANTO DOS SONHOS");
                printf("--------------------------------\n\n");

                CadastroCliente cliente1;
                Contrato contrato1;
                criarCadastro(&cliente1, &contrato1);
                salvarCadastro(&cliente1, &contrato1);

                system("\npause");
                system("cls");

                break;

            case 2:
                system("cls");

                printf("\n\033[1mVOC� SELECIONOU CADASTRO DE CH�CARAS.\033[0m\n\n");
                // Coloque a l�gica do Cadastro de Ch�caras
                // Cadastrar novas ch�caras
                Chacara chacarasDisponiveis[MAX_CHACARAS];
                int numChacarasNovas;

                printf("Quantas ch�caras voc� deseja cadastrar? ");
                scanf("%d", &numChacarasNovas);
                getchar(); // Limpar o buffer do teclado

                cadastrarChacaras(chacarasDisponiveis, numChacarasNovas);

                printf("\nCh�caras cadastradas:\n");
                exibirNomesChacarasDisponiveis(chacarasDisponiveis, numChacarasNovas);

                system("\npause");
                system("cls");

                break;

            case 3:
                system("cls");

                printf("\n\033[1mVOC� SELECIONOU VISUALIZAR CH�CARAS DISPON�VEIS.\n\n\033[0m");
                // Coloque a l�gica de Visualiza��o de Ch�caras Dispon�veis
                const char *caracteristicas1[9] =
                {
                    "250m�",
                    "Estacionamento para at� 10 carros",
                    "Cont�m Churrasqueira",
                    "Freezer",
                    "2 fog�es",
                    "Wi-fi",
                    "3 Quartos",
                    "Geladeira",
                    "Limpeza inclusa"
                };

                const char *caracteristicas2[9] =
                {
                    "150m�",
                    "Estacionamento para at� 5 carros",
                    "Sem Churrasqueira",
                    "1 fog�o",
                    "Sem Freezer",
                    "Sem Wi-fi",
                    "1 Quarto",
                    "Geladeira",
                    "Limpeza n�o inclusa"
                };

                const char *caracteristicas3[9] =
                {
                    "200m�",
                    "Estacionamento para at� 8 carros",
                    "Cont�m Churrasqueira",
                    "Freezer",
                    "2 fog�es",
                    "Wi-fi",
                    "2 Quartos",
                    "Geladeira",
                    "Limpeza inclusa"
                };

                visualizarConstantes("RECANTO DOS SONHOS", caracteristicas1, 9);
                visualizarConstantes("CH�CARA GABI", caracteristicas2, 9);
                visualizarConstantes("OS CARAC�IS", caracteristicas3, 9);

                system("\npause");
                system("cls");

                break;

            case 4:
                system("cls");

                printf("Voc� selecionou Agenda de Visitas.\n");
                // Coloque a logica da agenda de visitas aqui
                printf("Escolha o m�s e o ano, para visualizar as datas dispon�ves\n\n");
                //Fun��o calendario, para visualizar os dias disponiveis
                calendario();
                //Fun��o agendar_visita_calendario, para solicitar ao usu�rio o dia a ser agendado para visita e destac�-lo no calend�rio
                agendar_visita_calendario();
                //Vari�veis para validar a as informa��es das datas
                int hora, min;
                char opcao;

                //Solicita o hor�rio da vissita
                printf("\n-------Digite o hor�rio que deseja agendar a visita (H:Min)-------\n");
                //Solicita a hora da visita
                printf("\nDigite a hora: ");
                scanf("\n%d", &hora);
                //Solicita o minuto da visita
                printf("\nDigite o minuto: ");
                scanf("\n%d", &min);
                //Mostra o hor�rio da visita que foi digitado
                printf("\n------%.2d:%.2d-----\n", hora, min);

                //N�o valida o hor�rio se estiver fora do intervalo
                while(hora < 9 || hora > 17)
                {
                    printf("\nHor�rio inv�lido!\n");
                    printf("\nDigite a hora novamente: ");
                    scanf("\n%d", &hora);
                    printf("\nDigite o minuto novamente: ");
                    scanf("\n%d", &min);
                }

                //Solicita a confirma��o da data e hor�rio digitados
                printf("\nConfirma essa data e hor�rio? (S/N)");
                scanf("%s", &opcao);
                if (opcao == 'S' || opcao == 's')
                {

                    printf("\nAgendamento finalizado!\n");

                    system("pause");
                }

                system("cls");

                break;

            case 5:
                // Coloque a l�gica da agenda de di�rias aqui
                system("cls");

                printf("\n\033[1m\nVOC� SELECIONOU AGENDAR DI�RIAS.\n\n\033[0m");
                visualizarChacarasDisponiveis();
                printf("\nEscolha a data do evento!\n\n");
                agendarNoCalendario();
                printf("\n\n");

                system("pause");
                system("cls");

                break;
            case 6:
                system("cls");

                printf("\n\033[1mVOC� SELECIONOU CONTRATO.\033[0m\n");
                // Coloque a l�gica do contrato aqui

                char nomeCliente[100];
                float valorLocacao = 0.0;
                int telefoneCliente;
                int dddTelefone;
                int diaEvento;
                int mesEvento;
                int anoEvento;
                int anoBissexto;
                int quantidadeDias;
                int maxDiasFevereiro = 28;
                int diaSemana[31];
                int i;

                // SOLICITAR INFORMA��ES PARA O CONTRATO
                printf("\nPREENCHA AS INFORMA��ES NECESS�RIAS PARA IMPRESS�O!\n");
                printf("\nInforme o nome do cliente: ");
                setbuf(stdin, NULL);
                scanf("%99[^\n]", nomeCliente);


                // 1. DDD TELEFONE DO CLIENTE:
                printf("\nInforme o ddd do telefone do cliente: ");
                scanf("%d", &dddTelefone);

                // 1.1 Verifica��o ddd telefone do cliente
                while (dddTelefone < 11 || dddTelefone > 99)
                {
                    printf("\nERRO! o ddd digitado � inv�lido!");
                    printf("\nDigite um ddd v�lido: ");
                    scanf("%d", &dddTelefone);
                }

                // 2. TELEFONE DO CLIENTE:
                printf("\nInforme o telefone do cliente: ");
                scanf("%d", &telefoneCliente);

                // 2.1 Verifica��o Telefone do cliente
                while (telefoneCliente < 0)
                {
                    printf("\nERRO! o valor digitado � inv�lido!");
                    printf("\nDigite um telefone v�lido: ");
                    scanf("%d", &telefoneCliente);
                }

                // 3. ANO DA LOCA��O:
                printf("\nInforme o ano do evento/loca��o: ");
                scanf("%d", &anoEvento);

                // 3.1 Verifica��o ano da loca��o
                while (anoEvento < 0 || anoEvento < 2023)
                {
                    printf("\nERRO! Ano do evento digitado inv�lido!");
                    printf("\nDigite novamente o ano do evento: ");
                    scanf("%d", &anoEvento);
                }

                // 3. M�S DA LOCA��OO:
                printf("\nInforme o m�s do evento/loca��o: ");
                scanf("%d", &mesEvento);

                // 3.1 Verifica��o m�s da loca��o
                while (mesEvento <= 0 || mesEvento > 12)
                {
                    printf("\nERRO! M�s do evento digitado inv�lido!");
                    printf("\nDigite novamente o m�s do evento: ");
                    scanf("%d", &mesEvento);
                }

                // 4. DIA DA LOCA??O:
                printf("\nInforme o dia do evento/locacao: ");
                scanf("%d", &diaEvento);

                // 4.1 Verifica��o dia da loca��o (Meses com 31 dias)
                if (mesEvento == 1 || mesEvento == 3 || mesEvento == 5 ||
                        mesEvento == 7 || mesEvento == 8 || mesEvento == 10 ||
                        mesEvento == 12)
                {
                    while (diaEvento < 0 || diaEvento > 31)
                    {
                        printf("\nERRO! Dia do evento digitado inv�lido!");
                        printf("\nDigite novamente dia do evento (1 - 31): ");
                        scanf("%d", &diaEvento);
                    }
                }

                // 4.2 Verifica��o dia da loca��o (M�s com 28 ou 29 dias)
                // 4.3 verificar se o ano � bissexto ou n�o
                for (int anoBissexto = 2024; anoBissexto <= anoEvento; anoBissexto += 4)
                {
                    maxDiasFevereiro = (anoBissexto % 4 == 0 && (anoBissexto % 100 != 0 || anoBissexto % 400 == 0)) ? 29 : 28;
                }

                if (mesEvento == 2)
                {
                    while (diaEvento < 1 || diaEvento > maxDiasFevereiro)
                    {
                        printf("\nERRO! Dia do evento digitado inv�lido para fevereiro em um ano %s bissexto!\n", (maxDiasFevereiro == 29) ? "�" : "n�o �");
                        printf("Digite novamente o dia do evento (1 - %d): ", maxDiasFevereiro);
                        scanf("%d", &diaEvento);
                    }
                }

                // 4.4 Verificando dia da loca��o (M�s com 30 dias)
                else if (mesEvento == 4 || mesEvento == 6 || mesEvento == 9 || mesEvento == 11)
                {
                    while (diaEvento < 0 || diaEvento > 30)
                    {
                        printf("\nERRO! Dia do evento digitado inv�lido!");
                        printf("\nDigite novamente dia do evento (1 - 30): ");
                        scanf("%d", &diaEvento);
                    }
                }

                // 5. QUANTIDADE DE DIAS LOCA��O
                printf("\nInforme a quantidade de dias de locacao: ");
                scanf("%d", &quantidadeDias);

                // 5.1 Verifica��o da quantidade de dias
                while (quantidadeDias < 1 || quantidadeDias > 31)
                {
                    printf("\nERRO! O valor digitado � inv�lido ou excede o limite m�ximo de 31 dias!");
                    printf("\nDigite a quantidade de dias novamente: ");
                    scanf("%d", &quantidadeDias);
                }

                // 6. DIAS DA LOCA��O
                for (i = 1; i <= quantidadeDias; i++)
                {
                    printf("\nInforme o %d dia da semana da loca��o \n1 - Segunda \n2 - Ter�a \n3 - Quarta \n4 - Quinta \n5 - Sexta \n6 - S�bado \n7 - Domingo: ", i);
                    scanf("%d", &diaSemana[i - 1]);
                }

                // 7. VALOR DA LOCA��O (QUANTIDADE DE DIAS E DIAS DE SEMANA)
                for (i = 0; i < quantidadeDias; i++)
                {
                    switch (diaSemana[i])
                    {
                    case 1: // Segunda
                    case 2: // Ter�a
                    case 3: // Quarta
                    case 4: // Quinta
                    case 5: // Sexta
                        valorLocacao += 500.0;

                        break;
                    case 6: // S�bado
                    case 7: // Domingo
                        valorLocacao += 550.0;

                        break;

                    default:
                        printf("\nERRO! Dia da semana inv�lido! O dia %d n�o ser� considerado.\n", diaSemana[i]);
                        break;
                    }
                }
                // IMPRIMIR DADOS NA TELA DO SISTEMA (obs: impress�o final ser� feita em txt)

                char contrato[10000];

                int *nome;

                // Contrato construido em forma de string
                sprintf(contrato, "\n\n-------------CONTRATO DE LOCA��O-------------\n\n");
                sprintf(contrato + strlen(contrato), "Pelo presente instrumento particular de contrato de loca��o, de um lado denominado LOCADOR, Ch�cara Recanto dos Sonhos, com sede na Rua Dois, n�mero 1071, Jardim Itagua�u 2, Campinas, Estado de S�o Paulo, CEP 13053-788, Brasil, doravante denominado simplesmente LOCADOR, e de outro lado, denominado LOCAT�RIO, %s , telefone (%i)%i, doravante denominado simplesmente LOCAT�RIO.\n\n", nomeCliente, dddTelefone, telefoneCliente);
                sprintf(contrato + strlen(contrato), "CL�USULA PRIMEIRA ? DO OBJETO DO CONTRATO\n\n");
                sprintf(contrato + strlen(contrato), "O presente contrato tem por objeto a loca��o da propriedade denominada Ch�cara Recanto dos Sonhos, localizada no endere�o supracitado, para uso pelo LOCAT�RIO.\n\n");
                sprintf(contrato + strlen(contrato), "CL�USULA SEGUNDA ? DO PRAZO E CONDI��ES DA LOCA��O\n\n");
                sprintf(contrato + strlen(contrato), "2.1 O prazo de loca��o ter� in�cio no(s) dia(s) %i do m�s de %i do ano de %i.\n\n", diaEvento, mesEvento, anoEvento);
                sprintf(contrato + strlen(contrato), "2.2 O LOCAT�RIO dever� desocupar as instala��es f�sicas ao t�rmino do prazo estipulado na Cl�usula 2.1 deste contrato.\n\n");
                sprintf(contrato + strlen(contrato), "2.3 Todos os mobili�rios e utens�lios disponibilizados ao LOCAT�RIO no ato da assinatura deste contrato devem ser restitu�dos nas mesmas condi��es de conserva��o e uso em que foram entregues.\n\n");
                sprintf(contrato + strlen(contrato),"2.4 Os hor�rios e datas estabelecidos para a realiza��o do evento ou uso da propriedade devem ser rigorosamente observados pelo LOCAT�RIO.\n\n");
                sprintf(contrato + strlen(contrato),"CL�USULA TERCEIRA ? DO PAGAMENTO\n\n");
                sprintf(contrato + strlen(contrato),"3.1 Pelo uso da Ch�cara dos Recanto dos Sonhos, o LOCAT�RIO pagar� ao LOCADOR a quantia de R$ %f .\n\n", valorLocacao);
                sprintf(contrato + strlen(contrato),"3.2 O pagamento referido na Cl�usula 3.1 dever� ser realizado nas condi��es acordadas, sendo metade do valor para reservar, e a outra metade no dia da entrega da chave.\n\n");
                sprintf(contrato + strlen(contrato),"CL�USULA QUARTA ? DAS OBRIGA��ES DO LOCAT�RIO\n\n");
                sprintf(contrato + strlen(contrato),"4.1 O LOCAT�RIO se compromete a utilizar a propriedade de forma respons�vel, respeitando as normas e regulamentos locais.\n\n");
                sprintf(contrato + strlen(contrato),"4.2 O LOCAT�RIO ser� respons�vel por quaisquer danos causados �s instala��es f�sicas ou aos m�veis e utens�lios fornecidos.\n\n");
                sprintf(contrato + strlen(contrato),"4.3 � de responsabilidade do LOCAT�RIO a limpeza e organiza��o do local durante o per�odo de loca��o.\n\n");
                sprintf(contrato + strlen(contrato),"E, por estarem assim justos e contratados, as partes firmam o presente contrato de loca��o, em duas vias de igual teor.\n\n\n");
                sprintf(contrato + strlen(contrato),"(Campinas, SP - Brasil),(___/___/______).\n\n\n");
                sprintf(contrato + strlen(contrato),"_____________________________________\n(Assinatura do LOCADOR)\n\n\n");
                sprintf(contrato + strlen(contrato), "_____________________________________\n(Assinatura do LOCAT�RIO)\n\n");

                // Imprime na tela
                printf("%s", contrato);

                // Salva no arquivo
                salvarItem(contrato, nomeCliente);
                printf("\nContrato gerado e salvo com sucesso!\n\n");

                system("pause");
                system("cls");

                break;

            case 7:
                system("cls");

                printf("\n\033[1m\nVOC� SELECIONOU CALEND�RIO.\n\n\033[0m");
                // Coloque a l�gica do calendario aqui
                calendario();

                system("pause");
                system("cls");

                break;


            case 8:
                printf("\n");
                printf("\033[1;31mSAINDO...\n");

                return 0; // Saia do programa

            default:
                printf("\n");
                printf("\n\033[1;31mOP��O INV�LIDA. TENTE NOVAMENTE.\033[0m\n");
            }
        }
    }

    return 0;
}
