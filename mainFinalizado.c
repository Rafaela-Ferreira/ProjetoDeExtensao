#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h> // Inclui a biblioteca necessária para usar mkdir

// VARIAVEL GLOBAL
#define MAX_NOME 50
#define MAX_CARACTERISTICAS 9
#define MAX_CHACARAS 10

// INÍCIO FUNÇÕES (1)

// ----- ESTRUTURA: CADASTRO DE CLIENTE -----
typedef struct
{
    char nome_cliente[100];
    char telefone_cliente[30];
    char cpf_cliente[12];
    char email_cliente[50];
    char endereco_cliente[100];
} CadastroCliente;

// ----- ESTRUTURA: SALVAR CADASTRO DE CLIENTE -----
typedef struct
{
    char endereco_chacara[100];
    char telefone_chacara;
    float valor_locacao;
    char assinatura[100];

} Contrato;

// ----- FUNÇÃO 1: CRIAR CADASTRO DE CLIENTES -----
void criarCadastro(CadastroCliente *cliente, Contrato *contrato)
{
    setbuf(stdin, NULL);

    printf("Nome do cliente: ");
    fgets(cliente->nome_cliente, sizeof(cliente->nome_cliente), stdin);
    strtok(cliente->nome_cliente, "\n");

    for (int i = 0; cliente->nome_cliente[i]; i++)
    {
        if (!isalpha(cliente->nome_cliente[i]) && cliente->nome_cliente[i] != ' ')
        {
            printf("Nome inv�lido. Por favor, digite novamente:  \n");
            fgets(cliente->nome_cliente, sizeof(cliente->nome_cliente), stdin);
            strtok(cliente->nome_cliente, "\n");
            i = -1; // Reinicia o loop
        }
    }

    setbuf(stdin, NULL);

    printf("Telefone: ");
    fgets(cliente->telefone_cliente, sizeof(cliente->telefone_cliente), stdin);
    strtok(cliente->telefone_cliente, "\n");

    for (int i = 0; cliente->telefone_cliente[i]; i++)
    {
        if (cliente->telefone_cliente[i] < '0')
        {
            printf("Telefone inv�lido. Por favor, digite novamente:  \n");
            fgets(cliente->telefone_cliente, sizeof(cliente->telefone_cliente), stdin);
            strtok(cliente->telefone_cliente, "\n");
            i = -1; // Reinicia o loop
        }
    }

    setbuf(stdin, NULL);

    printf("CPF do cliente: ");
    fgets(cliente->cpf_cliente, sizeof(cliente->cpf_cliente), stdin);
    strtok(cliente->cpf_cliente, "\n");

    for (int i = 0; cliente->cpf_cliente[i]; i++)
    {
        if (cliente->cpf_cliente[i] < '0' || cliente->cpf_cliente[i] > '9')
        {
            printf("CPF INV�LIDO!! Digite novamente: ");
            fgets(cliente->cpf_cliente, sizeof(cliente->cpf_cliente), stdin);
            strtok(cliente->cpf_cliente, "\n");
            i = -1;
            continue;
        }
    }

    setbuf(stdin, NULL);
    printf("Endere�o do cliente: ");
    fgets(cliente->endereco_cliente, sizeof(cliente->endereco_cliente), stdin);
    strtok(cliente->endereco_cliente, "\n");

    printf("Email do cliente: ");
    fgets(cliente->email_cliente, sizeof(cliente->email_cliente), stdin);
    strtok(cliente->email_cliente, "\n");

    // Verifica se o email cont�m a substring "@gmail."
    for (int i = 0; cliente->email_cliente[i]; i++)
    {
        setbuf(stdin, NULL);
        if (strstr(cliente->email_cliente, "@gmail.") == NULL)
        {
            printf("Email INV�LIDO!! Digite novamente: ");
            fgets(cliente->email_cliente, sizeof(cliente->email_cliente), stdin);
            strtok(cliente->email_cliente, "\n");
            i = -1;
            continue;
        }
    }

    setbuf(stdin, NULL);
    printf("Endere�o da ch�cara: ");
    fgets(contrato->endereco_chacara, sizeof(contrato->endereco_chacara), stdin);
    strtok(contrato->endereco_chacara, "\n");

    printf("Valor da loca��o: ");
    scanf("%f", &contrato->valor_locacao);
    if (contrato->valor_locacao < 0)
    {
        printf("Valores negativos n�o � permitido!! Digite novamente: ");
        scanf("%f", &contrato->valor_locacao);
    }

    setbuf(stdin, NULL);

    printf("\n\t\tAssinatura: ");
    fgets(contrato->assinatura, sizeof(contrato->assinatura), stdin);
    strtok(contrato->assinatura, "\n");

    for (int i = 0; contrato->assinatura[i]; i++)
    {
        if (!isalpha(contrato->assinatura[i]) && !isspace(contrato->assinatura[i]))
        {
            printf("Assinatura INV�LIDA!! Digite novamente: ");
            fgets(contrato->assinatura, sizeof(contrato->assinatura), stdin);
            strtok(contrato->assinatura, "\n");
            i = -1;
            continue;
        }
    }
}

// ----- FUNÇÃO 2: SALVAR CADASTRO DE CLIENTES EM ARQUIVO -----
void salvarCadastro(CadastroCliente *cliente, Contrato *contrato)
{
    char pastaNome[100] = "Contratos";

#ifdef _WIN32
    mkdir(pastaNome);
#else
    mkdir(pastaNome, 0755);
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
    fprintf(arquivo, "Valor da Loca��o: R$%.2f\n", contrato->valor_locacao);
    fprintf(arquivo, "\n\t\tAssinatura: %s\n", contrato->assinatura);
    fprintf(arquivo, "------------------------------------------------------------------------------\n");

    fclose(arquivo);
    printf("\n\nContrato gerado com sucesso e salvo em '%s'.\n", nomeArquivo);
}

// *** FIM DAS FUNÇÕES (1) ***

// *** INICIO DAS FUNÇÕES (2) ***

// ----- FUNÇÃO 3: CALCULAR DIA DA SEMANA -----
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
    // Ajuste para domingo ser o dia 0 e sábado o dia 6
    diaDaSemana = (diaDaSemana + 6) % 7;
    return diaDaSemana;
}

// ----- FUNÇÃO 4: MARCAR DATAS NO CALENDÁRIO -----
void marcarDatasNoCalendario(int ano, int mes, int *diasMarcados, int totalDias)
{
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))
    {
        diasNoMes[2] = 29; // Fevereiro tem 29 dias em um ano bissexto
    }

    int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);

    for (int i = 0; i < primeiroDiaDoMes; i++)
    {
        printf("\t");
    }

    for (int dia = 1; dia <= diasNoMes[mes]; dia++)
    {
        int diaDaSemana = calcularDiaSemana(ano, mes, dia);

        if (diasMarcados[dia])
        {
            printf("\033[1;34m%2d\033[0m\t", dia); // Imprime o dia marcado em azul
        }
        else if (diaDaSemana == 0)
        {
            printf("\033[1;31m%2d\033[0m\t", dia); // Imprime domingo em vermelho
        }
        else if (diaDaSemana == 6)
        {
            printf("\033[1;90m%2d\033[0m\t", dia); // Imprime sábado em cinza
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

// ----- FUNÇÃO 5: AGENDAR DIÁRIAS -----
void agendarDiarias()
{
    int ano, mes, qtdDias;

    while (1)
    {
        printf("Digite o \033[1mANO\033[0m o \033[1mMÊS\033[0m (no formato \033[1mAAAA MM\033[0m) e a \033[1mQUANTIDADE\033[0m de dias para agendar\n");
        printf("Ou use o formato \033[1mAAAA MM ZERO\033[0m para exibir o calendário:\n");

        scanf("%d", &ano);
        if (ano == 0)
        {
            break;
        }

        while (1)
        {
            scanf("%d", &mes);
            if (mes >= 1 && mes <= 12)
            {
                break;
            }
            else
            {
                printf("\033[1;31mMÊS INVÁLIDO. POR FAVOR, DIGITE UM VALOR ENTRE 1 E 12.\033[0m\n");
            }
        }

        scanf("%d", &qtdDias);

        char *nomesDosMeses[] = {"", "Janeiro", "Fevereiro", "Março",
                                 "Abril", "Maio", "Junho", "Julho",
                                 "Agosto", "Setembro", "Outubro", "Novembro",
                                 "Dezembro"};

        printf("\nCalendário para %s de %d\n", nomesDosMeses[mes], ano);

        FILE *arquivo = fopen("datas.txt", "a+");
        if (arquivo == NULL)
        {
            printf("\033[1;31mERRO AO ABRIR O ARQUIVO.\033[0m\n");
            exit(EXIT_FAILURE);
        }

        int *diasMarcados = (int *)calloc(32, sizeof(int));

        // Ler as datas do arquivo e marcá-las no calendário
        rewind(arquivo);

        int diaLido, mesLido, anoLido, totalDias = 0;

        while (fscanf(arquivo, "%d/%d/%d", &diaLido, &mesLido, &anoLido) == 3)
        {
            if (mesLido == mes && anoLido == ano)
            {
                diasMarcados[diaLido] = 1;
                totalDias++;
            }
        }

        fclose(arquivo);

        marcarDatasNoCalendario(ano, mes, diasMarcados, totalDias);

        // Solicitar as datas para agendamento
        if (qtdDias > 0)
        {
            int dataAgendadaNoFuturo = 0;

            for (int i = 0; i < qtdDias; i++)
            {
                int diaAgendado;

                do
                {
                    printf("Digite o %d° dia para agendar (0 para sair): ", i + 1);
                    scanf("%d", &diaAgendado);

                    if (diaAgendado == 0)
                    {
                        break;
                    }

                    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))
                    {
                        diasNoMes[2] = 29; // Fevereiro tem 29 dias em um ano bissexto
                    }

                    int diasNoMesAtual = diasNoMes[mes];
                    if (diaAgendado < 1 || diaAgendado > diasNoMesAtual || diasMarcados[diaAgendado] == 1)
                    {
                        printf("\033[1;31mDIA INVÁLIDO OU JÁ ESCOLHIDO. DIGITE UM VALOR ENTRE 1 E %d QUE NÃO TENHA SIDO ESCOLHIDO.\033[0m\n\n", diasNoMesAtual);
                    }
                    else
                    {
                        break;
                    }
                } while (1);

                if (diaAgendado == 0)
                {
                    break;
                }

                time_t t = time(NULL);
                struct tm *dataAtual = localtime(&t);

                if ((ano < dataAtual->tm_year + 1900) ||
                    (ano == dataAtual->tm_year + 1900 && mes < dataAtual->tm_mon + 1) ||
                    (ano == dataAtual->tm_year + 1900 && mes == dataAtual->tm_mon + 1 && diaAgendado <= dataAtual->tm_mday))
                {
                    printf("\033[1;31mNÃO É POSSÍVEL AGENDAR UMA DATA QUE JÁ PASSOU OU É HOJE.\033[0m\n\n");
                    i--;
                    continue;
                }

                dataAgendadaNoFuturo = 1;

                diasMarcados[diaAgendado] = 1;

                arquivo = fopen("datas.txt", "a+");
                fprintf(arquivo, "%d/%d/%d\n", diaAgendado, mes, ano);
                fclose(arquivo);
            }

            free(diasMarcados);

            if (dataAgendadaNoFuturo)
            {
                printf("\033[1;32mData(s) agendada(s) com sucesso!\033[0m\n");
            }
            else
            {
                printf("\033[1;31mNenhuma data agendada ou todas estão no passado.\033[0m\n");
            }
        }

        printf("\nDeseja agendar uma nova data? (1 - Sim, 0 - Não): ");
        int opcao;

        while (1)
        {
            if (scanf("%d", &opcao) != 1 || (opcao != 0 && opcao != 1))
            {
                while (getchar() != '\n')
                    ;
                printf("\n\033[1;31mOpção inválida.\033[0m Digite 0 para Não ou 1 para Sim: ");
            }
            else
            {
                break;
            }
        }

        if (opcao == 0)
        {
            break;
        }
    }
}

//----- FUNÇÃO 6: CALENDÁRIO -----
void calendario()
{
    int ano, mes;
    while (1)
    {
        printf("Digite o ano (entre 2000 e 2100): ");
        scanf("%d", &ano);

        if (ano >= 2000 && ano <= 2100)
        {
            break; // Sai do loop se o ano for válido.
        }
        else
        {
            printf("Ano inválido.\n");
        }
    }

    while (1)
    {
        printf("Digite o mês (entre 1 e 12): ");
        scanf("%d", &mes);

        if (mes >= 1 && mes <= 12)
        {
            break; // Sai do loop se o Mês for válido.
        }
        else
        {
            printf("Mês inválido.\n");
        }
    }

    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))
    {
        diasNoMes[2] = 29; // Fevereiro tem 29 dias em um ano bissexto
    }

    char *nomesDosMeses[] = {"", "Janeiro", "Fevereiro", "Março",
                             "Abril", "Maio", "Junho", "Julho",
                             "Agosto", "Setembro", "Outubro", "Novembro",
                             "Dezembro"};

    printf("\nCalendário para %s de %d\n", nomesDosMeses[mes], ano);
    printf("\033[1;31mDOM\tSEG\tTER\tQUA\tQUI\tSEX\tSÁB\n\033[0m");

    int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);

    for (int i = 0; i < primeiroDiaDoMes; i++)
    {
        printf("\t");
    }

    // Gerar 5 dias aleatórios
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
            printf("\033[1;34m%2d\033[0m\t", dia); // Imprime o dia realçado em azul
        }
        else if (diaDaSemana == 0)
        {
            printf("\033[1;31m%2d\033[0m\t", dia); // Imprime domingo em vermelho
        }
        else if (diaDaSemana == 6)
        {
            printf("\033[1;90m%2d\033[0m\t", dia); // Imprime sábado em cinza
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

// -------- CADASTRO DE CHÁCARAS ---------

// ----- ESTRUTURA: CHÁCARA -----
typedef struct Chacara
{
    char caracteristicas[MAX_CARACTERISTICAS][MAX_NOME];
    char nome[MAX_NOME];
} Chacara;

// ----- FUNÇÃO 7: PREENCHER OS DADOS DA CHÁCARA -----
void preencherChacara(Chacara *chacara, char nome[MAX_NOME], char caracteristicas[MAX_CARACTERISTICAS][MAX_NOME])
{
    for (int i = 0; i < MAX_CARACTERISTICAS; i++)
    {
        strcpy(chacara->caracteristicas[i], caracteristicas[i]);
    }
    strcpy(chacara->nome, nome);
}

// ----- FUNÇÃO 8: EXIBIR TODOS ATRIBUTOS DA CHÁCARA -----
void exibirChacara(Chacara ch)
{
    printf("\033[1;34m%s\033[0m\n", ch.nome); // Nome em azul e negrito
    printf("Caracteristicas:\n");
    for (int i = 0; i < MAX_CARACTERISTICAS; i++)
    {
        printf("%d. %s\n", i + 1, ch.caracteristicas[i]);
    }
}

// ----- FUNÇÃO 9: EXIBIR APENAS O NOME DAS CHÁCARAS DISPONÍVEIS -----
void exibirNomesChacarasDisponiveis(Chacara ch[], int n)
{
    printf("Chácaras Disponíveis:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. \033[1;34m%s\033[0m\n", i + 1, ch[i].nome);
    }
}

// ----- FUNÇÃO 10: CADASTRAR NOVAS CHÁCARAS -----
void cadastrarChacaras(Chacara ch[], int n)
{
    for (int i = 0; i < n; i++)
    {
        Chacara novaChacara;
        char nome[MAX_NOME];
        char caracteristicas[MAX_CARACTERISTICAS][MAX_NOME];

        printf("Digite o nome da chácara: ");
        fgets(nome, MAX_NOME, stdin);
        nome[strcspn(nome, "\n")] = 0; // Remover a quebra de linha

        printf("Digite as características da chácara (até 9 itens separados por vírgula): ");
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
// ----- FUNÇÃO 11: VISUALIZAR CHÁCARAS DISPONÍVEIS E PERMITIR QUE O USUÁRIO ESCOLHA -----
Chacara visualizarChacarasDisponiveis()
{
    Chacara chacarasDisponiveis[3];

    const char *caracteristicas1[9] =
        {
            "250m²",
            "Estacionamento para até 10 carros",
            "Contém Churrasqueira",
            "Freezer",
            "2 fogões",
            "Wi-fi",
            "3 Quartos",
            "Geladeira",
            "Limpeza inclusa"};

    const char *caracteristicas2[9] =
        {
            "150m²",
            "Estacionamento para até 5 carros",
            "Sem Churrasqueira",
            "1 fogão",
            "Sem Freezer",
            "Sem Wi-fi",
            "1 Quarto",
            "Geladeira",
            "Limpeza não inclusa"};

    const char *caracteristicas3[9] =
        {
            "200m²",
            "Estacionamento para até 8 carros",
            "Contém Churrasqueira",
            "Freezer",
            "2 fogões",
            "Wi-fi",
            "2 Quartos",
            "Geladeira",
            "Limpeza inclusa"};

    preencherChacara(&chacarasDisponiveis[0], "RECANTO DOS SONHOS", caracteristicas1);
    preencherChacara(&chacarasDisponiveis[1], "CHÁCARA GABI", caracteristicas2);
    preencherChacara(&chacarasDisponiveis[2], "OS CARACÓIS", caracteristicas3);

    exibirNomesChacarasDisponiveis(chacarasDisponiveis, 3);

    int escolha;
    do
    {
        printf("Escolha uma chácara (1, 2 ou 3): ");
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > 3);

    return chacarasDisponiveis[escolha - 1];
}

// ----- FUNÇÃO 12: VISUALIZAR CONSTANTES DE CHÁCARAS -----
void visualizarConstantes(const char *nomeChacara, const char *caracteristicas[], int num)
{
    printf("\033[1;34m%s:\n\033[0m", nomeChacara);
    for (int i = 0; i < num; i++)
    {
        printf("%s\n", caracteristicas[i]);
    }
    printf("\n");
}

// ----- ESTRUTURA: PARA ARMAZENAR INFORMAÇÕES DO USUÁRIO -----
struct Usuario
{
    char nome[50];
    char senha[20];
};

// ------ FUNÇÃO 13: VERIFICA O LOGIN -----
int verificarLogin(struct Usuario usuarios[], int numUsuarios, char nome[], char senha[])
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
// *** FIM DAS FUNÇÕES (2)***

// ***INICIO DAS FUNÇÕES DO (3) ***
// ------ FUNÇÃO 14: CALCULAR DIA DA SEMANA PARA DATA ESPECÍFICA -----
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
    // Ajuste para domingo ser o dia 0 e sábado o dia 6
    dia_semana = (dia_semana + 6) % 7;
    return dia_semana;
}

// ------ FUNÇÃO 15: DESTACAR DIAS SELECIONADOS - COR [SAB, DOM]-----
void destaca_dias_selecionados(int mes_visita, int ano_visita, int diaAgendado)
{
    char *nome_mes[] = {"", "Janeiro", "Fevereiro", "Março",
                        "Abril", "Maio", "Junho", "Julho",
                        "Agosto", "Setembro", "Outubro", "Novembro",
                        "Dezembro"};

    int mes_dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ano_visita % 4 == 0 && (ano_visita % 100 != 0 || ano_visita % 400 == 0))
    {
        mes_dias[2] = 29; // Fevereiro tem 29 dias em um ano bissexto
    }

    printf("\nCalendário para %s de %d\n", nome_mes[mes_visita], ano_visita);
    printf("\033[1;31mDOM\tSEG\tTER\tQUA\tQUI\tSEX\tSÁB\n\033[0m");

    int mes_primeiro_dia = calcular_dia_semana(ano_visita, mes_visita, 1);

    for (int i = 0; i < mes_primeiro_dia; i++)
    {
        printf("\t");
    }

    for (int dia_visita = 1; dia_visita <= mes_dias[mes_visita]; dia_visita++)
    {
        int agendado_dia = 0;
        int numero_dias; // Mudei essa parte
        int dia_semana = calcularDiaSemana(ano_visita, mes_visita, dia_visita);

        for (int i = 0; i < numero_dias; i++)
        {
            if (dia_visita == diaAgendado)
            {
                agendado_dia = 1;
                break;
            }
        }

        if (dia_semana == 0)
        {
            if (agendado_dia)
            {
                printf("\033[1;34m%2d\033[0m\t", dia_visita); // Imprime Domingo em azul
            }
            else
            {
                printf("\033[1;91m%2d\033[0m\t", dia_visita); // Imprime Domingo em vermelho
            }
        }
        else if (dia_semana == 6)
        {
            if (agendado_dia)
            {
                printf("\033[1;34m%2d\033[0m\t", dia_visita); // Imprime Sábado em azul
            }
            else
            {
                printf("\033[0;90m%2d\033[0m\t", dia_visita); // Imprime Sábado em cinza
            }
        }
        else if (agendado_dia)
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

// ------ FUNÇÃO 16: SOLICITAR AO USUÁRIO O DIA A SER AGENDADO PARA VISITA E DESTACÁ-LO NO CALENDÁRIO  -----
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

    while (1)
    {
        printf("\n-------Digite a data que deseja agendar a visita (DD/MM/AAAA)-------\n");
        printf("\nDigite o ano (entre 2023 e 2100): ");
        scanf("%d", &ano_visita);

        if (ano_visita < 2023 || ano_visita > 2100)
        {
            printf("\nO ano digitado é inválido! \nO ano tem que estar no intervalo entre 2023 e 2100");
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        printf("\nDigite o mês (entre 1 e 12): ");
        scanf("%d", &mes_visita);

        if (mes_visita < 1 || mes_visita > 12)
        {
            printf("\nO mês digitado é inválido! \nO mês tem que estar no intervalo entre 1 e 12");
        }
        else

        {
            break;
        }
    }

    if ((mes_visita == 1) || (mes_visita == 3) || (mes_visita == 5) || (mes_visita == 7) ||
        (mes_visita == 8) || (mes_visita == 10) || (mes_visita == 12))
    {
        do
        {
            printf("\nDigite o dia a ser agendado para visita (entre 1 e 31): ");
            scanf("%d", &dia_visita);

            if (dia_visita >= 1 && dia_visita <= 31)
            {
                break;
            }
            else
            {
                printf("\nData inválida! \nA data tem que estar no intervalo de 1 e 31");
            }

        } while (1);
    }

    if ((mes_visita == 4) || (mes_visita == 6) || (mes_visita == 9) || (mes_visita == 11))
    {
        do
        {
            printf("\nDigite o dia a ser agendado para visita (entre 1 e 30): ");
            scanf("%d", &dia_visita);

            if (dia_visita >= 1 && dia_visita <= 30)
            {
                break;
            }
            else
            {
                printf("\nData inválida! \nA data tem que estar no intervalo de 1 e 30");
            }

        } while (1);
    }

    if ((mes_visita == 2))
    {
        do
        {
            printf("\nDigite o dia a ser agendado para visita (entre 1 e 29): ");
            scanf("%d", &dia_visita);

            if (dia_visita >= 1 && dia_visita <= 29)
            {
                break;
            }
            else
            {
                printf("\nData inválida! \nA data tem que estar no intervalo de 1 e 29");
            }
        } while (1);
    }

    // Verificação para garantir que o usuário não agende em datas passadas
    if ((ano_visita < ano_visita_atual) ||
        (ano_visita == ano_visita_atual && mes_visita < mes_atual) ||
        (ano_visita == ano_visita_atual && mes_visita == mes_atual && dia_visita < dia_atual))
    {
        printf("\nNão é possível agendar para uma data que já passou\n");
    }
    else
    {
        // Mostra o calendário com os dia agendado em azul
        printf("\nCalendário com o dia de visita agendado:\n");
        printf("======================================================\n");
        destaca_dias_selecionados(mes_visita, ano_visita, dia_visita);

        // Mostra a data que foi digitada
        printf("\n-----%d/%d/%d-----", dia_visita, mes_visita, ano_visita);

        // Mostra o dia da semana dependendo do resultado da fórmula
        switch (calcularDiaSemana(ano_visita, mes_visita, dia_visita))
        {
        case 0:
            printf("\nEssa data é um Domingo\n");
            break;
        case 1:
            printf("\nEssa data é uma Segunda - feira\n");
            break;
        case 2:
            printf("\nEssa data é uma Terça - feira\n");
            break;
        case 3:
            printf("\nEssa data é uma Quarta - feira\n");
            break;
        case 4:
            printf("\nEssa data é uma Quinta - feira\n");
            break;
        case 5:
            printf("\nEssa data é uma Sexta - feira\n");
            break;
        case 6:
            printf("\nEssa data é um Sábado\n");
            break;
        }
        // Variáveis para validar a as informações das datas
        int hora, min;
        char opcao;

        // Solicita o horário da vissita
        printf("\n-------Digite o horário que deseja agendar a visita (Entre às 09h até às 17h)-------\n");
        // Solicita a hora da visita
        printf("\nDigite a hora: ");
        scanf("\n%d", &hora);
        // Solicita o minuto da visita
        printf("\nDigite o minuto: ");
        scanf("\n%d", &min);
        // Mostra o horário da visita que foi digitado
        printf("\n------%.2d:%.2d-----\n", hora, min);

        // Não valida o horário se estiver fora do intervalo
        while (hora < 9 || hora >= 17)
        {
            printf("\nHorário inválido!\n");
            printf("\nDigite a hora novamente: ");
            scanf("\n%d", &hora);
            printf("\nDigite o minuto novamente: ");
            scanf("\n%d", &min);
        }

        // Solicita a confirmação da data e horário digitados
        printf("\nConfirma essa data e horário? (S/N)");
        scanf("%s", &opcao);
        if (opcao == 'S' || opcao == 's')
        {
            printf("\n\033[1;34mAgendamento finalizado!\033[0m\t\n");
            system("pause");
        }
    }
}

//** FIM DAS FUNÇÃES (3)

// ------ FUNÇÃO 17: SALVAR O CONTRATO EM TXT  -----
void salvarItem(const char *item, const char *nomeCliente)
{
    FILE *arquivo;
    char nomeArquivo[50]; // Ajuste o tamanho conforme necess�rio

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

// -------------------- INÍCIO DA MAIN -----------------------
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

    while (1) // Loop principal
    {
        if (usuarioLogado == -1)
        {

            printf("\n\t\t\033[1mBem-vindo!\n\033[0m\n");
            printf("\nRealize o login abaixo para acessar o sistema...\n");
            printf("Nome de usuário: ");
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
            printf("2. Cadastro de Chácaras\n");
            printf("3. Visualizar Chácaras Disponíveis\n");
            printf("4. Agendar Visitas\n");
            printf("5. Agendar Diárias\n");
            printf("6. Contrato\n");
            printf("7. Calendário\n");
            printf("8. Sair\n");
            printf("\nEscolha uma opção: ");
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
                printf("\n\033[1mVOCÊ SELECIONOU CADASTRO DE CHÁCARAS.\033[0m\n\n");
                // Coloque a lógica do Cadastro de Chácaras
                // Cadastrar novas chácaras
                Chacara chacarasDisponiveis[MAX_CHACARAS];
                int numChacarasNovas;

                printf("Quantas chácaras você deseja cadastrar? ");
                scanf("%d", &numChacarasNovas);
                getchar(); // Limpar o buffer do teclado

                cadastrarChacaras(chacarasDisponiveis, numChacarasNovas);

                printf("\nChácaras cadastradas:\n");
                exibirNomesChacarasDisponiveis(chacarasDisponiveis, numChacarasNovas);

                system("\npause");
                system("cls");
                break;

            case 3:
                system("cls");

                printf("\n\033[1mVOCÊ SELECIONOU VISUALIZAR CHÁCARAS DISPONÍVEIS.\n\n\033[0m");
                // Coloque a lógica de Visualização de Chácaras Disponíveis
                const char *caracteristicas1[9] =
                    {
                        "250m²",
                        "Estacionamento para até 10 carros",
                        "Contém Churrasqueira",
                        "Freezer",
                        "2 fogões",
                        "Wi-fi",
                        "3 Quartos",
                        "Geladeira",
                        "Limpeza inclusa"};

                const char *caracteristicas2[9] =
                    {
                        "150m²",
                        "Estacionamento para até 5 carros",
                        "Sem Churrasqueira",
                        "1 fogão",
                        "Sem Freezer",
                        "Sem Wi-fi",
                        "1 Quarto",
                        "Geladeira",
                        "Limpeza não inclusa"};

                const char *caracteristicas3[9] =
                    {
                        "200m²",
                        "Estacionamento para até 8 carros",
                        "Contém Churrasqueira",
                        "Freezer",
                        "2 fogões",
                        "Wi-fi",
                        "2 Quartos",
                        "Geladeira",
                        "Limpeza inclusa"};

                visualizarConstantes("RECANTO DOS SONHOS", caracteristicas1, 9);
                visualizarConstantes("CHÁCARA GABI", caracteristicas2, 9);
                visualizarConstantes("OS CARACÓIS", caracteristicas3, 9);

                system("\npause");
                system("cls");
                break;

            case 4:
                system("cls");
                printf("Você selecionou Agenda de Visitas.\n");
                // Coloque a logica da agenda de visitas aqui
                printf("Escolha o mês e o ano, para visualizar as datas disponíves\n\n");
                // Função calendario, para visualizar os dias disponiveis
                calendario();
                // Função agendar_visita_calendario, para solicitar ao usuário o dia a ser agendado para visita e destacá-lo no calendário
                agendar_visita_calendario();
                system("cls");
                break;

            case 5:
                // Coloque a lógica da agenda de diárias aqui
                system("cls");
                printf("\n\033[1m\nVOCÊ SELECIONOU AGENDAR DIÁRIAS.\n\n\033[0m");
                agendarDiarias();
                printf("\n\n");
                system("pause");
                system("cls");
                break;

            case 6:
                system("cls");

                printf("\n\033[1mVOCÊ SELECIONOU CONTRATO.\033[0m\n");
                // Coloque a lógica do contrato aqui

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

                // SOLICITAR INFORMAÇÕES PARA O CONTRATO
                printf("\nPREENCHA AS INFORMAÇÕES NECESSÁRIAS PARA IMPRESSO!\n");
                printf("\nInforme o nome do cliente: ");
                setbuf(stdin, NULL);
                scanf("%99[^\n]", nomeCliente);

                // 1. DDD TELEFONE DO CLIENTE:
                printf("\nInforme o ddd do telefone do cliente: ");
                scanf("%d", &dddTelefone);

                // 1.1 Verificação ddd telefone do cliente
                while (dddTelefone < 11 || dddTelefone > 99)
                {
                    printf("\nERRO! o ddd digitado é inválido!");
                    printf("\nDigite um ddd válido: ");
                    scanf("%d", &dddTelefone);
                }

                // 2. TELEFONE DO CLIENTE:
                printf("\nInforme o telefone do cliente: ");
                scanf("%d", &telefoneCliente);

                // 2.1 Verificação Telefone do cliente
                while (telefoneCliente < 0)
                {
                    printf("\nERRO! o valor digitado é inválido!");
                    printf("\nDigite um telefone válido: ");
                    scanf("%d", &telefoneCliente);
                }

                // 3. ANO DA LOCAÇÃO:
                printf("\nInforme o ano do evento/locação: ");
                scanf("%d", &anoEvento);

                // 3.1 Verificação ano da locação
                while (anoEvento < 0 || anoEvento < 2023)
                {
                    printf("\nERRO! Ano do evento digitado inválido!");
                    printf("\nDigite novamente o ano do evento: ");
                    scanf("%d", &anoEvento);
                }

                // 3. MÊS DA LOCAÇÃO:
                printf("\nInforme o mês do evento/locação: ");
                scanf("%d", &mesEvento);

                // 3.1 Verificação mês da locação
                while (mesEvento <= 0 || mesEvento > 12)
                {
                    printf("\nERRO! Mês do evento digitado inválido!");
                    printf("\nDigite novamente o mês do evento: ");
                    scanf("%d", &mesEvento);
                }

                // 4. DIA DA LOCA??O:
                printf("\nInforme o dia do evento/locacao: ");
                scanf("%d", &diaEvento);

                // 4.1 Verificação dia da locação (Meses com 31 dias)
                if (mesEvento == 1 || mesEvento == 3 || mesEvento == 5 ||
                    mesEvento == 7 || mesEvento == 8 || mesEvento == 10 ||
                    mesEvento == 12)
                {
                    while (diaEvento < 0 || diaEvento > 31)
                    {
                        printf("\nERRO! Dia do evento digitado inválido!");
                        printf("\nDigite novamente dia do evento (1 - 31): ");
                        scanf("%d", &diaEvento);
                    }
                }

                // 4.2 Verificação dia da locação (Mês com 28 ou 29 dias)
                // 4.3 verificar se o ano é bissexto ou não
                for (int anoBissexto = 2024; anoBissexto <= anoEvento; anoBissexto += 4)
                {
                    maxDiasFevereiro = (anoBissexto % 4 == 0 && (anoBissexto % 100 != 0 || anoBissexto % 400 == 0)) ? 29 : 28;
                }

                if (mesEvento == 2)
                {
                    while (diaEvento < 1 || diaEvento > maxDiasFevereiro)
                    {
                        printf("\nERRO! Dia do evento digitado inválido para fevereiro em um ano %s bissexto!\n", (maxDiasFevereiro == 29) ? "�" : "n�o �");
                        printf("Digite novamente o dia do evento (1 - %d): ", maxDiasFevereiro);
                        scanf("%d", &diaEvento);
                    }
                }

                // 4.4 Verificando dia da locação (Mês com 30 dias)
                else if (mesEvento == 4 || mesEvento == 6 || mesEvento == 9 || mesEvento == 11)
                {
                    while (diaEvento < 0 || diaEvento > 30)
                    {
                        printf("\nERRO! Dia do evento digitado inválido!");
                        printf("\nDigite novamente dia do evento (1 - 30): ");
                        scanf("%d", &diaEvento);
                    }
                }

                // 5. QUANTIDADE DE DIAS LOCAÇÃO
                printf("\nInforme a quantidade de dias de locacao: ");
                scanf("%d", &quantidadeDias);

                // 5.1 Verificação da quantidade de dias
                while (quantidadeDias < 1 || quantidadeDias > 31)
                {
                    printf("\nERRO! O valor digitado é inválido ou excede o limite máximo de 31 dias!");
                    printf("\nDigite a quantidade de dias novamente: ");
                    scanf("%d", &quantidadeDias);
                }

                // 6. DIAS DA LOCAÇÃO
                for (i = 1; i <= quantidadeDias; i++)
                {
                    printf("\nInforme o %d dia da semana da locação \n1 - Segunda \n2 - Terça \n3 - Quarta \n4 - Quinta \n5 - Sexta \n6 - Sábado \n7 - Domingo: ", i);
                    scanf("%d", &diaSemana[i - 1]);
                }

                // 7. VALOR DA LOCAÇÃO (QUANTIDADE DE DIAS E DIAS DE SEMANA)
                for (i = 0; i < quantidadeDias; i++)
                {
                    switch (diaSemana[i])
                    {
                    case 1: // Segunda
                    case 2: // Terça
                    case 3: // Quarta
                    case 4: // Quinta
                    case 5: // Sexta
                        valorLocacao += 500.0;

                        break;
                    case 6: // Sábado
                    case 7: // Domingo
                        valorLocacao += 550.0;

                        break;

                    default:
                        printf("\nERRO! Dia da semana inválido! O dia %d não será considerado.\n", diaSemana[i]);
                        break;
                    }
                }
                // IMPRIMIR DADOS NA TELA DO SISTEMA (obs: impressão final será feita em txt)

                char contrato[10000];

                int *nome;

                // Contrato construído em forma de string
                sprintf(contrato, "\n\n-------------CONTRATO DE LOCAÇÃO-------------\n\n");
                sprintf(contrato + strlen(contrato), "Pelo presente instrumento particular de contrato de locação, de um lado denominado LOCADOR, Chácara Recanto dos Sonhos, com sede na Rua Dois, número 1071, Jardim Itaguaçu 2, Campinas, Estado de São Paulo, CEP 13053-788, Brasil, doravante denominado simplesmente LOCADOR, e de outro lado, denominado LOCATÁRIO, %s, telefone (%i)%i, doravante denominado simplesmente LOCATÁRIO.\n\n", nomeCliente, dddTelefone, telefoneCliente);
                sprintf(contrato + strlen(contrato), "CLÁUSULA PRIMEIRA – DO OBJETO DO CONTRATO\n\n");
                sprintf(contrato + strlen(contrato), "O presente contrato tem por objeto a locação da propriedade denominada Chácara Recanto dos Sonhos, localizada no endereço supracitado, para uso pelo LOCATÁRIO.\n\n");
                sprintf(contrato + strlen(contrato), "CLÁUSULA SEGUNDA – DO PRAZO E CONDIÇÕES DA LOCAÇÃO\n\n");
                sprintf(contrato + strlen(contrato), "2.1 O prazo de locação terá início no(s) dia(s) %i do mês de %i do ano de %i.\n\n", diaEvento, mesEvento, anoEvento);
                sprintf(contrato + strlen(contrato), "2.2 O LOCATÁRIO deverá desocupar as instalações físicas ao término do prazo estipulado na Cláusula 2.1 deste contrato.\n\n");
                sprintf(contrato + strlen(contrato), "2.3 Todos os mobiliários e utensílios disponibilizados ao LOCATÁRIO no ato da assinatura deste contrato devem ser restituídos nas mesmas condições de conservação e uso em que foram entregues.\n\n");
                sprintf(contrato + strlen(contrato), "2.4 Os horários e datas estabelecidos para a realização do evento ou uso da propriedade devem ser rigorosamente observados pelo LOCATÁRIO.\n\n");
                sprintf(contrato + strlen(contrato), "CLÁUSULA TERCEIRA – DO PAGAMENTO\n\n");
                sprintf(contrato + strlen(contrato), "3.1 Pelo uso da Chácara dos Recanto dos Sonhos, o LOCATÁRIO pagará ao LOCADOR a quantia de R$ %f.\n\n", valorLocacao);
                sprintf(contrato + strlen(contrato), "3.2 O pagamento referido na Cláusula 3.1 deverá ser realizado nas condições acordadas, sendo metade do valor para reservar, e a outra metade no dia da entrega da chave.\n\n");
                sprintf(contrato + strlen(contrato), "CLÁUSULA QUARTA – DAS OBRIGAÇÕES DO LOCATÁRIO\n\n");
                sprintf(contrato + strlen(contrato), "4.1 O LOCATÁRIO se compromete a utilizar a propriedade de forma responsável, respeitando as normas e regulamentos locais.\n\n");
                sprintf(contrato + strlen(contrato), "4.2 O LOCATÁRIO será responsável por quaisquer danos causados às instalações físicas ou aos móveis e utensílios fornecidos.\n\n");
                sprintf(contrato + strlen(contrato), "4.3 É de responsabilidade do LOCATÁRIO a limpeza e organização do local durante o período de locação.\n\n");
                sprintf(contrato + strlen(contrato), "E, por estarem assim justos e contratados, as partes firmam o presente contrato de locação, em duas vias de igual teor.\n\n\n");
                sprintf(contrato + strlen(contrato), "(Campinas, SP - Brasil), (__/__/______).\n\n\n");
                sprintf(contrato + strlen(contrato), "_____________________________________\n(Assinatura do LOCADOR)\n\n\n");
                sprintf(contrato + strlen(contrato), "_____________________________________\n(Assinatura do LOCATÁRIO)\n\n");
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
                printf("\n\033[1m\nVOCÊ SELECIONOU CALENDÁRIO.\n\n\033[0m");
                // Coloque a lógica do calendário aqui
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
                printf("\n\033[1;31mOPÇÃO INVÁLIDA. TENTE NOVAMENTE.\033[0m\n");
            }
        }
    }
    return 0;
}
