#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura para armazenar informa��es do usu�rio
struct Usuario {
  char nome[50];
  char senha[20];
};
// função calendario
void calendario() {
  int ano, mes;
  while (1) {
    printf("Digite o ano (entre 2000 e 2100): ");
    scanf("%d", &ano);

    if (ano >= 2000 && ano <= 2100) {
      break; // Sai do loop se o ano for válido.
    } else {
      printf("Ano invalido.\n");
    }
  }
  while (1) {
    printf("Digite o mes (entre 1 e 12): ");
    scanf("%d", &mes);

    if (mes >= 1 && mes <= 12) {
      printf("Mes invalido.\n");
      break; // Sai do loop se o Mês for válido.
    } else {
      printf("Mês invalido.\n");
    }
  }
  // Determine o número de dias no mês
  int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  char *nomesDosMeses[] = {"",        "Janeiro",  "Fevereiro", "Março",
                           "Abril",   "Maio",     "Junho",     "Julho",
                           "Agosto",  "Setembro", "Outubro",   "Novembro",
                           "Dezembro"};

  printf("\nCalendario para %s de %d\n", nomesDosMeses[mes], ano);
  printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");

  // Encontre o dia da semana para o primeiro dia do mês
  int primeiroDia = 1;
  int diaDaSemana = primeiroDia % 7;

  // Preencha os espaços para o primeiro dia
  for (int i = 0; i < diaDaSemana; i++) {
    printf("\t");
  }
  // Imprima os dias do mês
  for (int dia = 1; dia <= diasNoMes[mes]; dia++) {
    printf("%2d\t", dia);
    diaDaSemana++;

    // Se for o último dia da semana (sábado), vá para a próxima linha
    if (diaDaSemana % 7 == 0) {
      printf("\n");
    }
  }
  printf("\n");
  // return;
}

// Fun��o para verificar o login
int verificarLogin(struct Usuario usuarios[], int numUsuarios, char nome[],
                   char senha[]) {
  for (int i = 0; i < numUsuarios; i++) {
    if (strcmp(usuarios[i].nome, nome) == 0 &&
        strcmp(usuarios[i].senha, senha) == 0) {
      return i; // Retorna o �ndice do usu�rio se o login for bem-sucedido
    }
  }
  return -1; // Retorna -1 se o login falhar
}

int main() {
  setlocale(LC_ALL, "Portuguese");
  // Defina os dados do usu�rio.
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
      printf("\n*** Menu Principal ***\n");
      printf("1. Cadastro de Clientes\n");
      printf("2. Agenda de Visitas\n");
      printf("3. Agenda de Di�rias\n");
      printf("4. Contrato\n");
      printf("5. Calendario\n");
      printf("6. Sair\n");
      printf("Escolha uma op��o: ");
      scanf("%d", &opcao);

      switch (opcao) {
      case 1:
        printf("Voc� selecionou Cadastro de Clientes.\n");
        // Coloque a l�gica do cadastro de clientes aqui
        break;
      case 2:
        printf("Voc� selecionou Agenda de Visitas.\n");
        // Coloque a l�gica da agenda de visitas aqui
        int dia, mes, ano;
        int hora = 0, min = 0;
        char opcao;

        printf("\nQue dia você deseja agendar uma visita? ");
        scanf("%d %d %d", &dia, &mes, &ano);
        printf("\n%d/%d/%d", dia, mes, ano);
        printf("\nConfirma essa data? (S/N) ");
        scanf("%s", &opcao);
        if (opcao == 'S' || opcao == 's') {
          printf("Opção válida\n");

        } else if ((opcao == 'N' || opcao == 'n')) {
          printf("Opção inválida\n");
          return 0;
        }
        printf("\nQue hora você deseja agendar o horário? ");
        scanf("\n%d", &hora);
        scanf("\n%d", &min);

        printf("%d:%d", hora, min);
        printf("\nConfirma esse horário? (S/N)");
        scanf("%s", &opcao);
        if (opcao == 'S' || opcao == 's') {
          printf("Opção válida\n");

        } else if ((opcao == 'N' || opcao == 'n')) {
          printf("Opção inválida\n");
          return 0;
        }

        break;
      case 3:
        printf("Voc� selecionou Agenda de Di�rias.\n");
        // Coloque a l�gica da agenda de di�rias aqui
        // visualizar os dias disponiveis
        calendario();
        printf("\n\n");

        printf("ESCOLHA UMA CHACARA!!");
        printf("\n\n");

        char *nomeDasChacaras[] = {"RECANTO DOS SONHOS: ", "CHACARA GABI: "};

        char *chacarasDisponiveis[2][11] = {{"250m² |", "Estacionamento para até 10 carros |", "Contem Churrasqueira | ", "", "","", "", "", "", "", ""},
{"150m² | ", "Estacionamento para até 5 carros | ", "Sem Churrasqueira |", "", "","", "", "", "", "", ""}};

        for (int i = 0; i < 2; i++) { // Ajustado para iterar apenas 2 vezes
          printf("\n%s", nomeDasChacaras[i]);
          for (int j = 0; j < 11; j++) {
            printf("%s ", chacarasDisponiveis[i][j]);
          }
          printf("\n");
        }

        printf("\n\n");
        break;
      case 4:
        printf("Voc� selecionou Contrato.\n");
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
        for (int anoBissexto = 2024; anoBissexto <= anoEvento;
             anoBissexto += 4) {
          maxDiasFevereiro = (anoBissexto % 4 == 0 && (anoBissexto % 100 != 0 ||
                                                       anoBissexto % 400 == 0))
                                 ? 29
                                 : 28;
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
      case 5:
        printf("Voc� selecionou Calendario.\n");
        // Coloque a l�gica do calendario aqui
        calendario();
        break;

      case 6:
        printf("Saindo...\n");
        exit(0); // Saia do programa
      default:
        printf("Op��o inv�lida. Tente novamente.\n");
      }
    }
  }

  return 0;
}
