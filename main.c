#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para calcular o dia da semana para uma data específica
int calcularDiaSemana(int ano, int mes, int dia) {
  if (mes < 3) {
    mes += 12;
    ano--;
  }
  int K = ano % 100;
  int J = ano / 100;
  int diaDaSemana = (dia + 13 * (mes + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
  return diaDaSemana;
}

void calendario() {
  int ano, mes, dia_escolhido;
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
      break; // Sai do loop se o Mês for válido.
    } else {
      printf("Mês invalido.\n");
    }
  }
  int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  char *nomesDosMeses[] = {"","Janeiro","Fevereiro","Março","Abril","Maio","Junho","Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};

  printf("\nCalendario para %s de %d\n", nomesDosMeses[mes], ano);
  printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");

  int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);
  primeiroDiaDoMes = (primeiroDiaDoMes + 6) % 7; // Ajuste para o início da semana em 0 ao invés de 1

  for (int i = 0; i < primeiroDiaDoMes; i++) {
    printf("\t");
  }

  for (int dia = 1; dia <= diasNoMes[mes]; dia++) {
    if (dia == dia_escolhido) {
      printf("\033[1;31m%2d\033[0m\t",dia); // Imprime o dia escolhido em vermelho
    } else {
      printf("%2d\t", dia);
    }
    primeiroDiaDoMes++;

    if (primeiroDiaDoMes % 7 == 0) {
      printf("\n");
    }
  }
  printf("\n");
}

// função cadastro de chácaras
// Estrutura para armazenar os detalhes das chácaras
typedef struct {
    char nome[50];
    char detalhes[11][50];
} Chacara;

// Função para imprimir os detalhes de cada chácara
void imprimirDetalhesChacara(Chacara chacara) {
    printf("Nome da Chácara: %s\n", chacara.nome);
    printf("Detalhes:\n");
    for (int i = 0; i < 11; i++) {
        printf("- %s\n", chacara.detalhes[i]);
    }
    printf("\n");
}

// Função de cadastro e exibição de chácaras
void cadastroChacaras() {
    Chacara chacarasDisponiveis[3] = {
        {"RECANTO DOS SONHOS", {"250m²", "Estacionamento para até 10 carros", "Contém Churrasqueira", "Freezer", "2 fogões", "Wi-fi", "3 Quartos", "Geladeira", "Limpeza inclusa", "", ""}},
        {"CHÁCARA GABI", {"150m²", "Estacionamento para até 5 carros", "Sem Churrasqueira", "1 fogão", "Sem Freezer", "Sem Wi-fi", "1 Quarto", "Geladeira", "Limpeza não inclusa", "", ""}},
        {"OS CARACÓIS", {"200m²", "Estacionamento para até 8 carros", "Contém Churrasqueira", "Freezer", "2 fogões", "Wi-fi", "2 Quartos", "Geladeira", "Limpeza inclusa", "", ""}}
    };

    printf("********* Bem-vindo ao Cadastro de Chácaras *********\n\n");

    int numChacaras = 3;

    while (1) {
        printf("Deseja cadastrar uma nova chácara pressione [S]\nDeseja somente visualizar pressione [N]: ");
        char resposta;
        scanf(" %c", &resposta);

        if (resposta == 'S' || resposta == 's') {
            if (numChacaras < 10) {
                Chacara novaChacara;
                printf("Digite o nome da chácara: ");
                scanf("%s", novaChacara.nome);

                printf("Digite os detalhes da chácara:\n");
                for (int i = 0; i < 11; i++) {
                    printf("Detalhe %d: ", i + 1);
                    scanf("%s", novaChacara.detalhes[i]);
                }

                chacarasDisponiveis[numChacaras] = novaChacara;
                numChacaras++;
            } else {
                printf("Limite máximo de chácaras atingido.\n");
            }
        } else {
            break;
        }
    }

    printf("********* Chácaras Cadastradas *********\n\n");

    for (int i = 0; i < numChacaras; i++) {
        imprimirDetalhesChacara(chacarasDisponiveis[i]);
    }
}

// Definindo a estrutura para armazenar informa��es do usu�rio
struct Usuario {
  char nome[50];
  char senha[20];
};
// Fun��o para verificar o login
int verificarLogin(struct Usuario usuarios[], int numUsuarios, char nome[],char senha[]) {
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
      printf("2. Cadastro de Chácaras\n");
      printf("3. Agenda de Visitas\n");
      printf("4. Agenda de Di�rias\n");
      printf("5. Contrato\n");
      printf("6. Calendario\n");
      printf("7. Sair\n");
      printf("Escolha uma op��o: ");
      scanf("%d", &opcao);

      switch (opcao) {
      case 1:
        printf("Voc� selecionou Cadastro de Clientes.\n");
        // Coloque a l�gica do cadastro de clientes aqui
        break;
      case 2:
        printf("Voc� selecionou Cadastro de Chácaras.\n");
        // Coloque a l�gica do Cadastro de Chácaras
        cadastroChacaras();
        break;
      case 3:
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
      case 4:
        printf("Voc� selecionou Agenda de Di�rias.\n");
        // Coloque a l�gica da agenda de di�rias aqui
        // visualizar os dias disponiveis
        // calendario();

        printf("\n\n");
        break;
      case 5:
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
        else if (mesEvento == 4 || mesEvento == 6 || mesEvento == 9 || mesEvento == 11) {
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
          printf("\nInforme o %d� dia da semana da loca��o \n1 - Segunda \n2 - " "Ter�a \n3 - Quarta \n4 - Quinta \n5 - Sexta \n6 - S�bado \n7 ""- Domingo: ",i);
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
            printf("\nERRO! Dia da semana inv�lido! O dia %d n�o ser� " "considerado.\n", diaSemana[i]);
            break;
          }
        }

        // IMPRIMIR DADOS NA TELA DO SISTEMA (obs: impress�o final ser� feita em
        // txt)
        printf("\n\n\nCONTRATO DE LOCA��O RECANTO DOS SONHOS\n\n");
        printf("Valor da diaria: Segunda � Sexta: R$500,00 - Sabado � Domingo: " "R$550,00\n");
        printf("Telefone: (19) 99580-8156\n");
        printf("Endereco: Rua dois, N� 1071 - jardim Itagua�u 2, Campinas - " "SP, CEP 13053-788, Brasil\n\n");
        printf("Locatario: %s\n", nomeCliente);
        printf("Quantidade de Dias de Locacao: %d\n", quantidadeDias);
        printf("Valor total da Loca��o: R$%.2f\n", valorLocacao);
        printf("Telefone do Locatario: (%d)%d\n", dddTelefone, telefoneCliente);
        printf("Data do Evento/Locacao: %d/%d/%d\n\n", diaEvento, mesEvento,anoEvento);
        printf("Assinatura do Locatario: ____________\n");
        printf("Data de hoje: __ /__ /_____\n");
        printf("Campinas, SP\n\n");
        printf("Assinatura do Locador: ____________\n");

        break;
      case 6:
        printf("Voc� selecionou Calendario.\n");
        // Coloque a l�gica do calendario aqui
        calendario();
        break;

      case 7:
        printf("Saindo...\n");
        exit(0); // Saia do programa
      default:
        printf("Op��o inv�lida. Tente novamente.\n");
      }
    }
  }

  return 0;
}
