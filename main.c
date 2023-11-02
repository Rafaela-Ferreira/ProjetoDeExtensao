#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Função para fazer o cadastro de clientes
typedef struct
{
    char cliente_nome[100];
    char tel[20];
    char endereco_chacara[100];
    int numero_contrato;
    char data_contrato[20];
    float valor_locacao;
    int taxa_limpeza;
    float taxa_quebra;
    char assinatura[100];
}Contrato;

// ---------------- 1. FUNÇÃO PARA CADASTRAR CLIENTES ------------------
void criarContrato(Contrato *contrato)
{
    setbuf(stdin, NULL);
    printf("Nome do cliente: ");
    fgets(contrato->cliente_nome, sizeof(contrato->cliente_nome), stdin);
    strtok(contrato->cliente_nome, "\n");

    printf("Telefone: ");
    scanf("%19s[^\n]", &contrato->tel);
    getchar(); // Captura o caractere de nova linha
    setbuf(stdin, NULL);

    printf("Endereço da chácara: ");
    fgets(contrato->endereco_chacara, sizeof(contrato->endereco_chacara), stdin);
    strtok(contrato->endereco_chacara, "\n");
    setbuf(stdin, NULL);

    printf("\n ");
    printf("\t\tAssinatura Eletrônica: ");
    fgets(contrato->assinatura, sizeof(contrato->assinatura), stdin);
    strtok(contrato->assinatura, "\n");
    printf("\t-------------------------------------------------------------------"
           "--");
    setbuf(stdin, NULL);
}

 // ------------ 2. FUNÇÃO PARA SALVAR O CADASTRO DE CLIENTES -----------------
void salvarContrato(Contrato *contrato)
{
    FILE *arquivo = fopen("contrato_chacara.doc", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fprintf(arquivo, "\t\t\t\t\tRECANTO DOS SONHOS\n");
    fprintf(arquivo, "<----------------------------------------------------------"
            "-------------------->\n");
    fprintf(arquivo, "\n");
    fprintf(arquivo, "Cadastro de Cliente\n");
    fprintf(arquivo, "Cliente: %s\n", contrato->cliente_nome);
    fprintf(arquivo, "Telefone: %s\n", contrato->tel);
    fprintf(arquivo, "Endereço da Chácara: %s\n", contrato->endereco_chacara);
    fprintf(arquivo, "\t\tassinatura: %s\n", contrato->assinatura);
    fprintf(arquivo, "------------------------------------------------------\n");
    fclose(arquivo);
    printf("\n\nCadastro gerado com sucesso e salvo em 'contrato_chacara.doc'.\n");
}

// ---------------- 3. FUNÇÃO PARA CALCULAR DIA DA SEMANA PARA DATA ESPECÍFICA ------------------
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
//---------------- 4. FUNÇÃO PARA DESTACAR DIAS SELECIONADOS - COR [SAB, DOM, DIAS AGENDADOS] ------------------
void destacarDiasSelecionados(int mes, int ano, int diasAgendados[], int numDias) {
    char *nomesDosMeses[] = {"", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("\nCalendário para %s de %d\n", nomesDosMeses[mes], ano);
    printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");

    int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);

    for (int i = 0; i < primeiroDiaDoMes; i++) {
        printf("\t");
    }

    for (int dia = 1; dia <= diasNoMes[mes]; dia++) {
        int agendado = 0;
        int diaDaSemana = calcularDiaSemana(ano, mes, dia);

        for (int i = 0; i < numDias; i++) {
            if (dia == diasAgendados[i]) {
                agendado = 1;
                break;
            }
        }

        if (diaDaSemana == 0) {
            if (agendado) {
                printf("\033[1;34m%2d\033[0m\t", dia); // Domingo com destaque azul
            } else {
                printf("\033[1;91m%2d\033[0m\t", dia); // Domingo com destaque vermelho
            }
        } else if (diaDaSemana == 6) {
            if (agendado) {
                printf("\033[1;34m%2d\033[0m\t", dia); // Sábado com destaque azul
            } else {
                printf("\033[0;90m%2d\033[0m\t", dia); // Sábado com destaque cinza
            }
        } else if (agendado) {
            printf("\033[1;34m%2d\033[0m\t", dia); // Dia agendado com destaque azul
        } else {
            printf("%2d\t", dia);
        }

        if ((primeiroDiaDoMes + dia) % 7 == 0 || dia == diasNoMes[mes]) {
            printf("\n");
        }
    }
    printf("\n");
}
// ---------------- 5. FUNÇÃO PARA VERIFICAR SE O ANO INSERIDO É VÁLIDO ------------------
int verificarAno(int ano)
{
    if (ano < 2023 || ano > 2100)
    {
        printf("Ano inválido. Por favor, insira um ano entre 2023 e 2100.\n");
        return 0;
    }
    return 1;
}
// ---------------- 6. FUNÇÃO PARA SOLICITAR AO USUÁRIO OS DIAS A SEREM AGENDADOS E DESTACALOS NO CALENDÁRIO ------------------
void agendarNoCalendario()
{
    time_t now;
    struct tm *local;
    time(&now);
    local = localtime(&now);
    int ano_atual = local->tm_year + 1900;
    int mes_atual = local->tm_mon + 1;
    int dia_atual = local->tm_mday;
    int mes, dia, ano;

    while (1)
    {
        printf("Digite o ano (entre 2023 e 2100): ");
        scanf("%d", &ano);

        if (verificarAno(ano))
        {
            break;
        }
    }

    while (1)
    {
        printf("Digite o mês (entre 1 e 12): ");
        scanf("%d", &mes);

        if (mes < 1 || mes > 12)
        {
            printf("Mês inválido.\n");
        }
        else
        {
            break;
        }
    }

    // Solicita ao usuário os dias a serem agendados
    printf("Quantos dias você deseja agendar? ");
    int numDias;
    scanf("%d", &numDias);

    int diasAgendados[numDias];
    for (int i = 0; i < numDias; i++)
    {
        printf("Digite o dia a ser agendado (entre 1 e 31): ");
        scanf("%d", &diasAgendados[i]);
    }

    // Verificação para garantir que o usuário não agende em datas passadas
    if (ano == ano_atual && mes < mes_atual)
    {
        printf("Não é possível agendar para uma data que já passou.\n");
        return;
    }

    // Mostra o calendário com os dias agendados em azul
    printf("\nCalendário com dias agendados:\n");
    printf("=============================================\n");
    destacarDiasSelecionados(mes, ano, diasAgendados, numDias);
}
//---------------- 7. FUNÇÃO PARA EXIBIR O CALENDÁRIO ------------------
void calendario() {
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

    char *nomesDosMeses[] = {"",        "Janeiro",  "Fevereiro", "Março",
                             "Abril",   "Maio",     "Junho",     "Julho",
                             "Agosto",  "Setembro", "Outubro",   "Novembro",
                             "Dezembro"
                            };

    printf("\nCalendário para %s de %d\n", nomesDosMeses[mes], ano);
    printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");

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

// -------- 8. FUNÇÃO CADASTRO DE CHÁCARAS - VARIÁVEIS GLOBAIS ---------
#define MAX_NOME 50
#define MAX_CARACTERISTICAS 9
#define MAX_CHACARAS 10

// Definição da estrutura Chacara
typedef struct Chacara {
    char caracteristicas[MAX_CARACTERISTICAS][MAX_NOME];
    char nome[MAX_NOME];
} Chacara;

// Função para preencher os dados da chácara
void preencherChacara(Chacara *chacara, char nome[MAX_NOME], char caracteristicas[MAX_CARACTERISTICAS][MAX_NOME]) {
    for (int i = 0; i < MAX_CARACTERISTICAS; i++) {
        strcpy(chacara->caracteristicas[i], caracteristicas[i]);
    }
    strcpy(chacara->nome, nome);
}

// Função para exibir todos os atributos da chácara
void exibirChacara(Chacara ch) {
    printf("\033[1;34m%s\033[0m\n", ch.nome); // Nome em azul e negrito
    printf("Características:\n");
    for (int i = 0; i < MAX_CARACTERISTICAS; i++) {
        printf("%d. %s\n", i + 1, ch.caracteristicas[i]);
    }
}

// Função para exibir apenas o nome das chácaras disponíveis
void exibirNomesChacarasDisponiveis(Chacara ch[], int n) {
    printf("Chácaras Disponíveis:\n");
    for (int i = 0; i < n; i++) {
      printf("%d. \033[1;34m%s\033[0m\n", i + 1, ch[i].nome);
    }
}

// Função para cadastrar novas chácaras
void cadastrarChacaras(Chacara ch[], int n) {
    for (int i = 0; i < n; i++) {
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
        while (token != NULL && j < MAX_CARACTERISTICAS) {
            token[strcspn(token, "\n")] = 0; // Remover a quebra de linha
            strcpy(caracteristicas[j], token);
            token = strtok(NULL, ",");
            j++;
        }

        preencherChacara(&novaChacara, nome, caracteristicas);
        ch[i] = novaChacara;
    }
}
// Função para visualizar chácaras disponíveis e permitir que o usuário escolha uma
Chacara visualizarChacarasDisponiveis() {
    Chacara chacarasDisponiveis[3];

    const char *caracteristicas1[9] = {
        "250m²",
        "Estacionamento para até 10 carros",
        "Contém Churrasqueira",
        "Freezer",
        "2 fogões",
        "Wi-fi",
        "3 Quartos",
        "Geladeira",
        "Limpeza inclusa"
    };

    const char *caracteristicas2[9] = {
        "150m²",
        "Estacionamento para até 5 carros",
        "Sem Churrasqueira",
        "1 fogão",
        "Sem Freezer",
        "Sem Wi-fi",
        "1 Quarto",
        "Geladeira",
        "Limpeza não inclusa"
    };

    const char *caracteristicas3[9] = {
        "200m²",
        "Estacionamento para até 8 carros",
        "Contém Churrasqueira",
        "Freezer",
        "2 fogões",
        "Wi-fi",
        "2 Quartos",
        "Geladeira",
        "Limpeza inclusa"
    };

    preencherChacara(&chacarasDisponiveis[0], "RECANTO DOS SONHOS", caracteristicas1);
    preencherChacara(&chacarasDisponiveis[1], "CHÁCARA GABI", caracteristicas2);
    preencherChacara(&chacarasDisponiveis[2], "OS CARACÓIS", caracteristicas3);

    exibirNomesChacarasDisponiveis(chacarasDisponiveis, 3);

    int escolha;
    do {
        printf("Escolha uma chácara (1, 2 ou 3): ");
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > 3);

    return chacarasDisponiveis[escolha - 1];
}

// vizualizar const de chacaras
void visualizarConstantes(const char *nomeChacara, const char *caracteristicas[], int num) {
   printf("\033[1;34m%s:\n\033[0m", nomeChacara);
    for (int i = 0; i < num; i++) {
        printf("%s\n", caracteristicas[i]);
    }
    printf("\n");
}

// ------------- 9. DEFININDO A ESTRUTURA PARA ARMAZENAR INFORMAÇÕES DO USUÁRIO -------------
struct Usuario
{
    char nome[50];
    char senha[20];
};
// --------------- 10. FUNÇÃO PARA VERIFICAR O LOGIN ----------------
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
// -------------------- 11. INÍCIO DA MAIN -----------------------
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
          
            printf("\033[1mBem-vindo!\n\033[0m\n");
            printf("Nome de usuário: ");
            scanf("%s", nome);
            printf("Senha: ");
            scanf("%s", senha);

            usuarioLogado = verificarLogin(usuarios, numUsuarios, nome, senha);

            if (usuarioLogado == -1)
            {
                printf("Login falhou. Tente novamente.\n");
            }
        }
        else
        {
            printf("\033[1m\n*** MENU PRINCIPAL ***\n\033[0m\n");
            printf("1. Cadastro de Clientes\n");
            printf("2. Cadastro de Chácaras\n");
            printf("3. Visualizar Chácaras Disponíveis\n");
            printf("4. Agendar Visitas\n");
            printf("5. Agendar Diárias\n");
            printf("6. Contrato\n");
            printf("7. Calendário\n");
            printf("8. Sair\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
                printf("\n\033[1mVOCÊ SELECIONOU CADASTRO DE CLIENTES.\033[0m\n");
                // Coloque a lógica do cadastro de clientes aqui
                printf("\n--------------------------------");
                printf("RECANTOS DOS SONHOS");
                printf("-------------------------------------------\n");
                Contrato contrato;
                criarContrato(&contrato);
                salvarContrato(&contrato);

                break;

            case 2:
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
                break;

            case 3:
              printf("\n\033[1mVOCÊ SELECIONOU VISUALIZAR CHÁCARAS DISPONÍVEIS.\n\n\033[0m");
              // Coloque a lógica de Visualização de Chácaras Disponíveis
              const char *caracteristicas1[9] = {
                  "250m²",
                  "Estacionamento para até 10 carros",
                  "Contém Churrasqueira",
                  "Freezer",
                  "2 fogões",
                  "Wi-fi",
                  "3 Quartos",
                  "Geladeira",
                  "Limpeza inclusa"
              };

              const char *caracteristicas2[9] = {
                  "150m²",
                  "Estacionamento para até 5 carros",
                  "Sem Churrasqueira",
                  "1 fogão",
                  "Sem Freezer",
                  "Sem Wi-fi",
                  "1 Quarto",
                  "Geladeira",
                  "Limpeza não inclusa"
              };

              const char *caracteristicas3[9] = {
                  "200m²",
                  "Estacionamento para até 8 carros",
                  "Contém Churrasqueira",
                  "Freezer",
                  "2 fogões",
                  "Wi-fi",
                  "2 Quartos",
                  "Geladeira",
                  "Limpeza inclusa"
              };

              visualizarConstantes("RECANTO DOS SONHOS", caracteristicas1, 9);
              visualizarConstantes("CHÁCARA GABI", caracteristicas2, 9);
              visualizarConstantes("OS CARACÓIS", caracteristicas3, 9);
              
                break;
            case 4:
                printf("Você selecionou Agenda de Visitas.\n");
                // Coloque a logica da agenda de visitas aqui
                printf("Escolha o mês e o ano, para visualizar as datas disponíves\n\n");
                //função calendario, para visualizar os dias disponiveis
                calendario();
                //Variáveis para validar a as informações das datas
                int dia, mes, ano, formula, dia_semana;
                int hora, min;
                char opcao;

                //Solicita a data da visita
                printf("\n-----Digite a data que deseja agendar a visita (DD/MM/AAAA)------- ");
                //Solicita o ano da visita
                printf("\nDigite o ano: ");
                scanf("%d", &ano);
                //Não valida o ano se estiver fora do intervalo
                while(ano < 2023 || ano > 2100)
                {
                    printf("\nO ano digitado é inválido! \nO ano tem que estar no intervalo entre 2023 e 2100");
                    printf("\nDigite o ano novamente: ");
                    scanf("%d", &ano);
                }

                //Solicita o mês da visita
                printf("\nDigite o mês: ");
                scanf("%d", &mes);
                //Não valida o mês se estiver fora do intervalo
                while(mes < 1 || mes > 12)
                {
                    printf("\nO mês digitado é inválido! \nO mês tem que estar no intervalo entre 1 e 12");
                    printf("\nDigite o mês novamente: ");
                    scanf("%d", &mes);
                }

                //Solicita o dia
                printf("\nDigite o dia: ");
                scanf("%d", &dia);

                //Mostra a data que foi digitada
                printf("\n-----%d/%d/%d-----", dia, mes, ano);

                //Fórmula para calcular o dia da semana que foi digitado pelo usuário
                formula = dia + 2*mes + (3*(mes+1)/5) + ano + ano/4 - ano/100 + ano/400 + 2;
                dia_semana = (formula + 6) % 7;

                //Mostra o dia da semana dependendo do resultado da fórmula
                if(dia_semana == 0)
                {
                    printf("\nEssa data é um Domingo");
                }

                else if(dia_semana == 1)
                {
                    printf("\nEssa data é uma Segunda - feira");
                }

                else if(dia_semana == 2)
                {
                    printf("\nEssa data é uma Terça - feira\n");
                }

                else if(dia_semana == 3)
                {
                    printf("\nEssa data é uma Quarta - feira\n");
                }

                else if(dia_semana == 4)
                {
                    printf("\nEssa data é uma Quinta - feira\n");
                }

                else if(dia_semana == 5)
                {
                    printf("\nEssa data é uma Sexta - feira\n");
                }

                else if(dia_semana == 6)
                {
                    printf("\nEssa data é um Sábado\n");
                }

                //Solicita o horário da vissita
                printf("\n-----Digite o horário que deseja agendar a visita (H:Min)------- ");
                //Solicita a hora da visita
                printf("\nDigite a hora: ");
                scanf("\n%d", &hora);
                //Solicita o minuto da visita
                printf("\nDigite o minuto: ");
                scanf("\n%d", &min);
                //Mostra o horário da visita que foi digitado
                printf("\n------%.2d:%.2d-----", hora, min);

                //Não valida o horário  se estiver fora do intervalo (Sujeito a mudanças)
                while(hora < 10 || hora > 18)
                {
                    printf("\nHorário inválido!\n");
                    printf("\nDigite a hora novamente: ");
                    scanf("\n%d", &hora);
                    printf("\nDigite o minuto novamente: ");
                    scanf("\n%d", &min);
                }

                // Mostra o calendário com o dia da visita agendada (Incompleto)
                printf("\nCalendário com o dia da visita agendada:\n");
                printf("=============================================\n");
                //void destacarDiasSelecionados(mes, ano, dia, dia_semana);

                //Solicita a confirmação da data e horário digitados
                printf("\nConfirma essa data e horário? (S/N)");
                scanf("%s", &opcao);
                if (opcao == 'S' || opcao == 's')
                {
                    printf("\nAgendamento finalizado!\n");
                }
                break;

            case 5:
                // Coloque a lógica da agenda de diárias aqui
                printf("\n\033[1m\nVOCÊ SELECIONOU AGENDAR DIÁRIAS.\n\n\033[0m");
                visualizarChacarasDisponiveis(); 
                printf("\n\nEscolha a data do evento!\n\n");  
                agendarNoCalendario();
                printf("\033[1;32mData agendada com sucesso!\033[0m");
                printf("\n\n");
                break;
            case 6:
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
                printf("\nPREENCHA AS INFORMAÇÕES NECESSÁRIAS PARA IMPRESSÃO!\n");
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

                // 3. MÊS DA LOCAÇÃOO:
                printf("\nInforme o mês do evento/locação: ");
                scanf("%d", &mesEvento);

                // 3.1 Verificação mês da locação
                while (mesEvento <= 0 || mesEvento > 12)
                {
                    printf("\nERRO! Mês do evento digitado inválido!");
                    printf("\nDigite novamente o mês do evento: ");
                    scanf("%d", &mesEvento);
                }

                // 4. DIA DA LOCA��O:
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
                        printf("\nERRO! Dia do evento digitado inválido para fevereiro em um ano %s bissexto!\n", (maxDiasFevereiro == 29) ? "é" : "não é");
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
                   printf("-------------CONTRATO DE LOCAÇÃO-------------\n\n");
                   printf("Pelo presente instrumento particular de contrato de locação, de um lado denominado LOCADOR, Chácara Recanto dos Sonhos, com sede na Rua Dois, número 1071, Jardim Itaguaçu 2, Campinas, Estado de São Paulo, CEP 13053-788, Brasil, doravante denominado simplesmente LOCADOR, e de outro lado, denominado LOCATÁRIO, %s , telefone (%i)%i, doravante denominado simplesmente LOCATÁRIO.\n\n", nomeCliente, dddTelefone, telefoneCliente);
                   printf("CLÁUSULA PRIMEIRA – DO OBJETO DO CONTRATO\n\n");
                   printf("O presente contrato tem por objeto a locação da propriedade denominada Chácara Recanto dos Sonhos, localizada no endereço supracitado, para uso pelo LOCATÁRIO.\n\n");
                   printf("CLÁUSULA SEGUNDA – DO PRAZO E CONDIÇÕES DA LOCAÇÃO\n\n");
                   printf("2.1 O prazo de locação terá início no(s) dia(s) %i do mês de %i do ano de %i.\n\n", diaEvento, mesEvento, anoEvento);
                   printf("2.2 O LOCATÁRIO deverá desocupar as instalações físicas ao término do prazo estipulado na Cláusula 2.1 deste contrato.\n\n");
                   printf("2.3 Todos os mobiliários e utensílios disponibilizados ao LOCATÁRIO no ato da assinatura deste contrato devem ser restituídos nas mesmas condições de conservação e uso em que foram entregues.\n\n");
                   printf("2.4 Os horários e datas estabelecidos para a realização do evento ou uso da propriedade devem ser rigorosamente observados pelo LOCATÁRIO.\n\n");
                   printf("CLÁUSULA TERCEIRA – DO PAGAMENTO\n\n");
                   printf("3.1 Pelo uso da Chácara dos Recanto dos Sonhos, o LOCATÁRIO pagará ao LOCADOR a quantia de R$ %f .\n\n", valorLocacao);
                   printf("3.2 O pagamento referido na Cláusula 3.1 deverá ser realizado nas condições acordadas, sendo metade do valor para reservar, e a outra metade no dia da entrega da chave.\n\n");
                   printf("CLÁUSULA QUARTA – DAS OBRIGAÇÕES DO LOCATÁRIO\n\n");
                   printf("4.1 O LOCATÁRIO se compromete a utilizar a propriedade de forma responsável, respeitando as normas e regulamentos locais.\n\n");
                   printf("4.2 O LOCATÁRIO será responsável por quaisquer danos causados às instalações físicas ou aos móveis e utensílios fornecidos.\n\n");
                   printf("4.3 É de responsabilidade do LOCATÁRIO a limpeza e organização do local durante o período de locação.\n\n");
                   printf("E, por estarem assim justos e contratados, as partes firmam o presente contrato de locação, em duas vias de igual teor.\n\n\n");
                   printf("(Campinas, SP - Brasil),(___/___/______).\n\n\n");
                   printf("_____________________________________\n(Assinatura do LOCADOR)\n\n\n");
                   printf("_____________________________________\n(Assinatura do LOCATÁRIO)\n\n");

                break;

            case 7:
                printf("\n\033[1m\nVOCÊ SELECIONOU CALENDÁRIO.\n\n\033[0m");
                // Coloque a lógica do calendario aqui
                calendario();
                break;

            case 8:
                printf("\033[1;31mSAINDO...\n");
                exit(0); // Saia do programa

            default:
                printf("\n");
                printf("\n\033[1;31mOPÇÃO INVÁLIDA. TENTE NOVAMENTE.\033[0m\n");
            }
        }
    }

    return 0;
}
