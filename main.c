#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função para fazer o cadastro de clientes
typedef struct {
  char cliente_nome[100];
  char tel[20];
  char endereco_chacara[100];
  int numero_contrato;
  char data_contrato[20];
  float valor_locacao;
  int taxa_limpeza;
  float taxa_quebra;
  char assinatura[100];
} Contrato;

//função paa criar contratos
void criarContrato(Contrato *contrato) {
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
  printf("Número do contrato: ");
  scanf("%d", &contrato->numero_contrato);
  getchar(); // Captura o caractere de nova linha
  setbuf(stdin, NULL);
  printf("Data do contrato: ");
  fgets(contrato->data_contrato, sizeof(contrato->data_contrato), stdin);
  strtok(contrato->data_contrato, "\n");
  setbuf(stdin, NULL);
  printf("Valor da locação: ");
  scanf("%f", &contrato->valor_locacao);

  getchar();
  setbuf(stdin, NULL);
  printf("Deseja incluir a taxa de limpeza (R$200,00)? (1-Sim / 0-Não): ");
  scanf("%d", &contrato->taxa_limpeza);
  setbuf(stdin, NULL);
  if (contrato->taxa_limpeza) {
    contrato->valor_locacao += 200.0;
  }
  printf("Valor da taxa de quebra (R$150,00 - R$350,00): ");
  scanf("%f", &contrato->taxa_quebra);
  setbuf(stdin, NULL);
  printf("\n ");
  printf("\t\tAssinatura Eletrônica: ");
  fgets(contrato->assinatura, sizeof(contrato->assinatura), stdin);
  strtok(contrato->assinatura, "\n");
  printf("\t-------------------------------------------------------------------"
         "--");
  setbuf(stdin, NULL);
}

// função para salvar contratos
void salvarContrato(Contrato *contrato) {
  FILE *arquivo = fopen("contrato_chacara.doc", "w");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }
  fprintf(arquivo, "\t\t\t\t\tRECANTO DOS SONHOS\n");
  fprintf(arquivo, "<----------------------------------------------------------"
                   "-------------------->\n");
  fprintf(arquivo, "\n");
  fprintf(arquivo, "Contrato de Locação de Chácara\n");
  fprintf(arquivo, "Cliente: %s\n", contrato->cliente_nome);
  fprintf(arquivo, "Telefone: %s\n", contrato->tel);
  fprintf(arquivo, "Endereço da Chácara: %s\n", contrato->endereco_chacara);
  fprintf(arquivo, "Número do Contrato: %d\n", contrato->numero_contrato);
  fprintf(arquivo, "Data do Contrato: %s\n", contrato->data_contrato);
  fprintf(arquivo, "Valor da Locação: R$%.2f\n", contrato->valor_locacao);
  if (contrato->taxa_limpeza) {
    fprintf(arquivo, "Taxa de Limpeza Incluída: R$200,00\n");
  }
  fprintf(arquivo, "Taxa de Quebra: R$%.2f\n", contrato->taxa_quebra);
  fprintf(arquivo, "\t\tassinatura: %s\n", contrato->assinatura);
  fprintf(arquivo, "------------------------------------------------------\n");
  fclose(arquivo);
  printf(
      "\n\nContrato gerado com sucesso e salvo em 'contrato_chacara.doc'.\n");
}

// Função para calcular o dia da semana para uma data específica
int calcularDiaSemana(int ano, int mes, int dia) {
  if (mes < 3) {
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
//função para destacar dias selecionados - cor [sab, dom], e quantidades de dias no mês.
void destacarDiasSelecionados(int mes, int ano, int diasAgendados[],
                              int numDias) {
  char *nomesDosMeses[] = {"",        "Janeiro",  "Fevereiro", "Março",
                           "Abril",   "Maio",     "Junho",     "Julho",
                           "Agosto",  "Setembro", "Outubro",   "Novembro",
                           "Dezembro"};

  int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  printf("\nCalendário para %s de %d\n", nomesDosMeses[mes], ano);
  printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");

  int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);

  for (int i = 0; i < primeiroDiaDoMes; i++) {
    printf("\t");
  }

  for (int dia = 1; dia <= diasNoMes[mes]; dia++) {
    int agendado = 0;
    for (int i = 0; i < numDias; i++) {
      if (dia == diasAgendados[i]) {
        agendado = 1;
        break;
      }
    }
    int diaDaSemana = calcularDiaSemana(ano, mes, dia);

    if (diaDaSemana == 0) {
      printf("\033[1;91m%2d\033[0m\t", dia); // Imprime domingo em vermelho
    } else if (diaDaSemana == 6) {
      printf("\033[0;90m%2d\033[0m\t", dia); // Imprime sábado em cinza
    } else if (agendado) {
      printf("\033[1;34m%2d\033[0m\t", dia); // Imprime o dia agendado em azul
    } else {
      printf("%2d\t", dia);
    }

    if ((primeiroDiaDoMes + dia) % 7 == 0 || dia == diasNoMes[mes]) {
      printf("\n");
    }
  }
  printf("\n");
}
// Função para verificar se o ano inserido é válido
int verificarAno(int ano) {
  if (ano < 2023 || ano > 2100) {
    printf("Ano inválido. Por favor, insira um ano entre 2023 e 2100.\n");
    return 0;
  }
  return 1;
}
// Função para solicitar ao usuário os dias a serem agendados e destacá-los no calendário
void agendarNoCalendario() {
  time_t now;
  struct tm *local;
  time(&now);
  local = localtime(&now);
  int ano_atual = local->tm_year + 1900;
  int mes_atual = local->tm_mon + 1;
  int dia_atual = local->tm_mday;
  int mes, dia, ano;

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

    if (mes < 1 || mes > 12) {
      printf("Mês inválido.\n");
    } else {
      break;
    }
  }

  // Solicita ao usuário os dias a serem agendados
  printf("Quantos dias você deseja agendar? ");
  int numDias;
  scanf("%d", &numDias);

  int diasAgendados[numDias];
  for (int i = 0; i < numDias; i++) {
    printf("Digite o dia a ser agendado (entre 1 e 31): ");
    scanf("%d", &diasAgendados[i]);
  }

  // Verificação para garantir que o usuário não agende em datas passadas
  if (ano == ano_atual && mes < mes_atual) {
    printf("Não é possível agendar para uma data que já passou.\n");
    return;
  }

  // Mostra o calendário com os dias agendados em azul
  printf("\nCalendário com dias agendados:\n");
  printf("=============================================\n");
  destacarDiasSelecionados(mes, ano, diasAgendados, numDias);
}
//função exibir o calendario
void calendario() {
  int ano, mes;
  while (1) {
    printf("Digite o ano (entre 2000 e 2100): ");
    scanf("%d", &ano);

    if (ano >= 2000 && ano <= 2100) {
      break; // Sai do loop se o ano for válido.
    } else {
      printf("Ano inválido.\n");
    }
  }

  while (1) {
    printf("Digite o mês (entre 1 e 12): ");
    scanf("%d", &mes);

    if (mes >= 1 && mes <= 12) {
      break; // Sai do loop se o Mês for válido.
    } else {
      printf("Mês inválido.\n");
    }
  }

  int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
    diasNoMes[2] = 29; // Fevereiro tem 29 dias em um ano bissexto
  }

  char *nomesDosMeses[] = {"",        "Janeiro",  "Fevereiro", "Março",
                           "Abril",   "Maio",     "Junho",     "Julho",
                           "Agosto",  "Setembro", "Outubro",   "Novembro",
                           "Dezembro"};

  printf("\nCalendário para %s de %d\n", nomesDosMeses[mes], ano);
  printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");

  int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);

  for (int i = 0; i < primeiroDiaDoMes; i++) {
    printf("\t");
  }

  // Gerar 5 dias aleatórios
  int diasRealcados[5];
  for (int i = 0; i < 5; i++) {
    diasRealcados[i] = rand() % diasNoMes[mes] + 1;
  }

  for (int dia = 1; dia <= diasNoMes[mes]; dia++) {
    int realcado = 0;
    for (int i = 0; i < 5; i++) {
      if (dia == diasRealcados[i]) {
        realcado = 1;
        break;
      }
    }
    int diaDaSemana = calcularDiaSemana(ano, mes, dia);

    if (realcado) {
      printf("\033[1;34m%2d\033[0m\t", dia); // Imprime o dia realçado em azul
    } else if (diaDaSemana == 0) {
      printf("\033[1;31m%2d\033[0m\t", dia); // Imprime domingo em vermelho
    } else if (diaDaSemana == 6) {
      printf("\033[1;90m%2d\033[0m\t", dia); // Imprime sábado em cinza
    } else {
      printf("%2d\t", dia);
    }

    if ((primeiroDiaDoMes + dia) % 7 == 0 || dia == diasNoMes[mes]) {
      printf("\n");
    }
  }
  printf("\n");
}

// função cadastro de chácaras - variaveis globais
#define MAX_CARACTERISTICAS 9
#define MAX_NOME 50

typedef struct {
  char nome[MAX_NOME];
  char caracteristicas[MAX_CARACTERISTICAS][100];
} Chacara;

void preencherChacara(Chacara *chacara, const char *nome,
                      const char *caracteristicas[MAX_CARACTERISTICAS]) {
  snprintf(chacara->nome, MAX_NOME, "%s", nome);
  for (int i = 0; i < MAX_CARACTERISTICAS; i++) {
    snprintf(chacara->caracteristicas[i], 100, "%s", caracteristicas[i]);
  }
}

void exibirChacara(Chacara chacara) {
  printf("\033[34m%s\033[0m\n", chacara.nome);
  printf("\033[1mDESCRIÇÃO:\033[0m\n");
  for (int i = 0; i < MAX_CARACTERISTICAS; i++) {
    printf("%s\n", chacara.caracteristicas[i]);
  }
  printf("\n");
}

// Definindo a estrutura para armazenar informações do usuario
struct Usuario {
  char nome[50];
  char senha[20];
};
// Função para verificar o login
int verificarLogin(struct Usuario usuarios[], int numUsuarios, char nome[],
                   char senha[]) {
  for (int i = 0; i < numUsuarios; i++) {
    if (strcmp(usuarios[i].nome, nome) == 0 &&
        strcmp(usuarios[i].senha, senha) == 0) {
      return i; // Retorna o indice do usuario se o login for bem-sucedido
    }
  }
  return -1; // Retorna -1 se o login falhar
}

int main() {
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

  while (1) { // Loop principal
    if (usuarioLogado == -1) {
      printf("Bem-vindo!\n");
      printf("Nome de usu�rio: ");
      scanf("%s", nome);
      printf("Senha: ");
      scanf("%s", senha);

      usuarioLogado = verificarLogin(usuarios, numUsuarios, nome, senha);

      if (usuarioLogado == -1) {
        printf("Login falhou. Tente novamente.\n");
      }
    } else {
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

      switch (opcao) {
      case 1:
        printf("\n\033[1mVOCÊ SELECIONOU CADASTRO DE CLIENTES.\033[0m\n");
        // Coloque a l�gica do cadastro de clientes aqui
        printf("\n--------------------------------");
        printf("RECANTOS DOS SONHOS");
        printf("-------------------------------------------\n");
        Contrato contrato;
        criarContrato(&contrato);
        salvarContrato(&contrato);

        break;
      case 2:
        printf("\n\033[1mVOCÊ SELECIONOU CADASTRO DE CHÁCARAS.\033[0m\n\n");
        // Coloque a l�gica do Cadastro de Chácaras
        Chacara chacarasDisponiveis[10];
        int numChacarasNovas;
        printf("Quantas chácaras você deseja cadastrar? ");
        scanf("%d", &numChacarasNovas);
        getchar(); // Limpar o buffer do teclado

        for (int i = 0; i < numChacarasNovas; i++) {
          Chacara novaChacara;
          char nome[MAX_NOME];
          const char *caracteristicas[MAX_CARACTERISTICAS];

          printf("Digite o nome da chácara: ");
          fgets(nome, MAX_NOME, stdin);
          nome[strcspn(nome, "\n")] = 0; // Remover a quebra de linha

          printf("Digite as características da chácara (até 9 itens separadas "
                 "por vírgula): ");
          char caracteristicasString[500];
          fgets(caracteristicasString, 500, stdin);
          char *token = strtok(caracteristicasString, ",");
          int j = 0;
          while (token != NULL && j < MAX_CARACTERISTICAS) {
            token[strcspn(token, "\n")] = 0; // Remover a quebra de linha
            caracteristicas[j] = token;
            token = strtok(NULL, ",");
            j++;
          }

          preencherChacara(&novaChacara, nome, caracteristicas);
          chacarasDisponiveis[i] = novaChacara;
        }

        printf("\nChácaras cadastradas:\n");
        for (int i = 0; i < numChacarasNovas; i++) {
          exibirChacara(chacarasDisponiveis[i]);
        }

        break;
      case 3:
        printf("\n\033[1mVOCÊ SELECIONOU VISUALIZAR CHÁCARAS DISPONÍVEIS.\n\n\033[0m");
        // Coloque a l�gica de Visualização de Chácaras Disponíveis
        // Chacara chacarasDisponiveis[10];
        const char *caracteristicas1[9] = {"250m²",
                                           "Estacionamento para até 10 carros",
                                           "Contém Churrasqueira",
                                           "Freezer",
                                           "2 fogões",
                                           "Wi-fi",
                                           "3 Quartos",
                                           "Geladeira",
                                           "Limpeza inclusa"};
        const char *caracteristicas2[9] = {"150m²",
                                           "Estacionamento para até 5 carros",
                                           "Sem Churrasqueira",
                                           "1 fogão",
                                           "Sem Freezer",
                                           "Sem Wi-fi",
                                           "1 Quarto",
                                           "Geladeira",
                                           "Limpeza não inclusa"};
        const char *caracteristicas3[9] = {"200m²",
                                           "Estacionamento para até 8 carros",
                                           "Contém Churrasqueira",
                                           "Freezer",
                                           "2 fogões",
                                           "Wi-fi",
                                           "2 Quartos",
                                           "Geladeira",
                                           "Limpeza inclusa"};

        preencherChacara(&chacarasDisponiveis[0], "RECANTO DOS SONHOS",
                         caracteristicas1);
        preencherChacara(&chacarasDisponiveis[1], "CHÁCARA GABI",
                         caracteristicas2);
        preencherChacara(&chacarasDisponiveis[2], "OS CARACÓIS",
                         caracteristicas3);

        for (int i = 0; i < 3; i++) {
          exibirChacara(chacarasDisponiveis[i]);
        }
        break;
      case 4:
        printf("Você selecionou Agenda de Visitas.\n");
        // Coloque a logica da agenda de visitas aqui
        printf("Escolha o mês e o ano, para visualizar as datas disponíves\n\n");
        //função calendario, para visualizar os dias disponiveis
        calendario();
        //Variáveis para validar a as informações das datas
        int dia , mes, ano, formula, dia_semana;
        int hora , min;
        char opcao;

        //Solicita a data da visita
        printf("\n-----Digite a data que deseja agendar a visita (DD/MM/AAAA)------- ");
        //Solicita o ano da visita
        printf("\nDigite o ano: ");
        scanf("%d", &ano);
        //Não valida o ano se estiver fora do intervalo
        while(ano < 2023 || ano > 2100){
          printf("\nO ano digitado é inválido! \nO ano tem que estar no intervalo entre 2023 e 2100");
          printf("\nDigite o ano novamente: ");
          scanf("%d", &ano);
        }

        //Solicita o mês da visita
        printf("\nDigite o mês: ");
        scanf("%d", &mes);
        //Não valida o mês se estiver fora do intervalo
        while(mes < 1 || mes > 12){
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
        if(dia_semana == 0){
          printf("\nEssa data é um Domingo");
        }

        else if(dia_semana == 1){
          printf("\nEssa data é uma Segunda - feira");
        }

        else if(dia_semana == 2){
          printf("\nEssa data é uma Terça - feira\n");
        }

        else if(dia_semana == 3){
          printf("\nEssa data é uma Quarta - feira\n");
        }

        else if(dia_semana == 4){
          printf("\nEssa data é uma Quinta - feira\n");
        }

        else if(dia_semana == 5){
          printf("\nEssa data é uma Sexta - feira\n");
        }

        else if(dia_semana == 6){
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
        while(hora < 10 || hora > 18){
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
        if (opcao == 'S' || opcao == 's'){
          printf("\nAgendamento finalizado!\n");
        }
        break;
      case 5:
        // Coloque a l�gica da agenda de di�rias aqui
        printf("\n\033[1m\nVOCÊ SELECIONOU AGENDAR DIÁRIAS.\n\n\033[0m");
        agendarNoCalendario();
        printf("\n\n");
        break;
      case 6:
        printf("\n\033[1mVOCÊ SELECIONOU CONTRATO.\033[0m\n");
        // Coloque a l�gica do contrato aqui
        // Vari�veis para informa��es do contrato
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
        scanf("%99[^\n]", nomeCliente);

        // 1. DDD TELEFONE DO CLIENTE:
        printf("\nInforme o ddd do telefone do cliente: ");
        scanf("%d", &dddTelefone);

        // 1.1 Verifica��o ddd telefone do cliente
        while (dddTelefone < 11 || dddTelefone > 99) {
          printf("\nERRO! o ddd digitado � inv�lido!");
          printf("\nDigite um ddd v�lido: ");
          scanf("%d", &dddTelefone);
        }

        // 2. TELEFONE DO CLIENTE:
        printf("\nInforme o telefone do cliente: ");
        scanf("%d", &telefoneCliente);

        // 2.1 Verifica��o Telefone do cliente
        while (telefoneCliente < 0) {
          printf("\nERRO! o valor digitado � inv�lido!");
          printf("\nDigite um telefone v�lido: ");
          scanf("%d", &telefoneCliente);
        }

        // 3. ANO DA LOCA��O:
        printf("\nInforme o ano do evento/loca��o: ");
        scanf("%d", &anoEvento);

        // 3.1 Verifica��o ano da loca��o
        while (anoEvento < 0 || anoEvento < 2023) {
          printf("\nERRO! Ano do evento digitado inv�lido!");
          printf("\nDigite novamente o ano do evento: ");
          scanf("%d", &anoEvento);
        }

        // 3. M�S DA LOCA��O:
        printf("\nInforme o m�s do evento/loca��o: ");
        scanf("%d", &mesEvento);

        // 3.1 Verifica��o m�s da loca��o
        while (mesEvento <= 0 || mesEvento > 12) {
          printf("\nERRO! M�s do evento digitado inv�lido!");
          printf("\nDigite novamente o m�s do evento: ");
          scanf("%d", &mesEvento);
        }

        // 4. DIA DA LOCA��O:
        printf("\nInforme o dia do evento/locacao: ");
        scanf("%d", &diaEvento);

        // 4.1 Verifica��o dia da loca��o (Meses com 31 dias)
        if (mesEvento == 1 || mesEvento == 3 || mesEvento == 5 ||
            mesEvento == 7 || mesEvento == 8 || mesEvento == 10 ||
            mesEvento == 12) {
          while (diaEvento < 0 || diaEvento > 31) {
            printf("\nERRO! Dia do evento digitado inv�lido!");
            printf("\nDigite novamente dia do evento (1 - 31): ");
            scanf("%d", &diaEvento);
          }
        }

        // 4.2 Verifica��o dia da loca��o (M�s com 28 ou 29 dias)
        // 4.3 verificar se o ano � bissexto ou n�o
        for (int anoBissexto = 2024; anoBissexto <= anoEvento; anoBissexto += 4) {
          maxDiasFevereiro = (anoBissexto % 4 == 0 && (anoBissexto % 100 != 0 || anoBissexto % 400 == 0)) ? 29 : 28;
        }

        if (mesEvento == 2) {
          while (diaEvento < 1 || diaEvento > maxDiasFevereiro) {
            printf("\nERRO! Dia do evento digitado inv�lido para fevereiro em "
                   "um ano %s bissexto!\n",
                   (maxDiasFevereiro == 29) ? "�" : "n�o �");
            printf("Digite novamente o dia do evento (1 - %d): ",
                   maxDiasFevereiro);
            scanf("%d", &diaEvento);
          }
        }

        // 4.4 Verificando dia da loca��o (M�s com 30 dias)
        else if (mesEvento == 4 || mesEvento == 6 || mesEvento == 9 ||
                 mesEvento == 11) {
          while (diaEvento < 0 || diaEvento > 30) {
            printf("\nERRO! Dia do evento digitado inv�lido!");
            printf("\nDigite novamente dia do evento (1 - 30): ");
            scanf("%d", &diaEvento);
          }
        }

        // 5. QUANTIDADE DE DIAS LOCA��O
        printf("\nInforme a quantidade de dias de locacao: ");
        scanf("%d", &quantidadeDias);

        // 5.1 Verifica��o da quantidade de dias
        while (quantidadeDias < 1 || quantidadeDias > 31) {
          printf("\nERRO! O valor digitado � inv�lido ou excede o limite "
                 "m�ximo de 31 dias!");
          printf("\nDigite a quantidade de dias novamente: ");
          scanf("%d", &quantidadeDias);
        }

        // 6. DIAS DA LOCA��O
        for (i = 1; i <= quantidadeDias; i++) {
          printf("\nInforme o %d� dia da semana da loca��o \n1 - Segunda \n2 - "
                 "Ter�a \n3 - Quarta \n4 - Quinta \n5 - Sexta \n6 - S�bado \n7 "
                 "- Domingo: ",
                 i);
          scanf("%d", &diaSemana[i - 1]);
        }

        // 7. VALOR DA LOCA��O (QUANTIDADE DE DIAS E DIAS DE SEMANA)
        for (i = 0; i < quantidadeDias; i++) {
          switch (diaSemana[i]) {
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
            printf("\nERRO! Dia da semana inv�lido! O dia %d n�o ser� "
                   "considerado.\n",
                   diaSemana[i]);
            break;
          }
        }

        // IMPRIMIR DADOS NA TELA DO SISTEMA (obs: impress�o final ser� feita em
        // txt)
        printf("\n\n\nCONTRATO DE LOCA��O RECANTO DOS SONHOS\n\n");
        printf("Valor da diaria: Segunda � Sexta: R$500,00 - Sabado � Domingo: "
               "R$550,00\n");
        printf("Telefone: (19) 99580-8156\n");
        printf("Endereco: Rua dois, N� 1071 - jardim Itagua�u 2, Campinas - "
               "SP, CEP 13053-788, Brasil\n\n");
        printf("Locatario: %s\n", nomeCliente);
        printf("Quantidade de Dias de Locacao: %d\n", quantidadeDias);
        printf("Valor total da Loca��o: R$%.2f\n", valorLocacao);
        printf("Telefone do Locatario: (%d)%d\n", dddTelefone, telefoneCliente);
        printf("Data do Evento/Locacao: %d/%d/%d\n\n", diaEvento, mesEvento,
               anoEvento);
        printf("Assinatura do Locatario: ____________\n");
        printf("Data de hoje: __ /__ /_____\n");
        printf("Campinas, SP\n\n");
        printf("Assinatura do Locador: ____________\n");
        break;
      case 7:
        printf("\n\033[1m\nVOCÊ SELECIONOU CALENDÁRIO.\n\n\033[0m");
        // Coloque a l�gica do calendario aqui
        calendario();
        break;

      case 8:
        printf("\033[0;31mSAINDO...\n");
        exit(0); // Saia do programa
      default:
        printf("\n");
        printf("\n\033[1;31mOPÇÃO INVÁLIDA. TENTE NOVAMENTE.\033[0m\n");
      }
    }
  }

  return 0;
}
