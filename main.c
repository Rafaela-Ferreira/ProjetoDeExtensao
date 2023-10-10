#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definindo a estrutura para armazenar informa��es do usu�rio
struct Usuario {
  char nome[50];
  char senha[20];
};

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
        int dia , mes, ano;
        int hora = 0, min = 0;
        char opcao;

        printf("\nQue dia você deseja agendar uma visita? ");
        scanf("%d %d %d", &dia, &mes, &ano);
        printf("\n%d/%d/%d", dia, mes, ano);
        printf("\nConfirma essa data? (S/N) ");
        scanf("%s", &opcao);
        if (opcao == 'S' || opcao == 's'){
            printf("Opção válida\n");
    
        }else if ((opcao == 'N' || opcao == 'n')){
            printf("Opção inválida\n");
            return 0;
        }
        printf("\nQue hora você deseja agendar o horário? ");
        scanf("\n%d", &hora);
        scanf("\n%d", &min);
    
        printf("%d:%d", hora, min);
        printf("\nConfirma esse horário? (S/N)");
        scanf("%s", &opcao);
        if (opcao == 'S' || opcao == 's'){
            printf("Opção válida\n");
    
        }else if ((opcao == 'N' || opcao == 'n')){
            printf("Opção inválida\n");
            return 0;
        }

        break;
      case 3:
        printf("Voc� selecionou Agenda de Di�rias.\n");
        // Coloque a l�gica da agenda de di�rias aqui
        break;
      case 4:
        printf("Voc� selecionou Contrato.\n");
        // Coloque a l�gica do contrato aqui
        // Vari�veis para informa��es do contrato
        char nomeCliente[100];
        float valorLocacao;
        char telefoneCliente[20];
        char dataEvento[20];
        int quantidadeDias;
        int diaSemana;
        // Exibir a sele��o do contrato
        // Solicitar informa��es para o contrato
        printf("\nPREENCHA AS INFORMA��ES NECESS�RIAS PARA IMPRESS�O!\n");
        printf("\nInforme o nome do cliente: ");
        scanf("%s", nomeCliente);
    
        printf("\nInforme o telefone do cliente (ex:(11)99999-8888): ");
        scanf(" %s", telefoneCliente);
    
        printf("\nInforme a data do evento/locacao (DD/MM/AAAA): ");
        scanf("%s", dataEvento);
    
        printf("\nInforme o dia da semana da loca��o: \nDigite 1: SEG - SEX \nDigite 2: SAB - DOM \n");
        scanf("%d", &diaSemana);
        //Verfica��o do dia de semana
        while(diaSemana != 1 && diaSemana != 2){
          printf("\nERRO! \nDigite 1 = Para dias entre Segunda e Sexta \nDigite 2 = Para S�bado ou Domingo!");
          printf("\nInforme o dia de semana: ");
          scanf("%d", &diaSemana);
        }

        printf("\nInforme a quantidade de dias de locacao: ");
        scanf("%d", &quantidadeDias);
        //Verifica��o da quantidade de dias
        while(quantidadeDias < 1){
          printf("\nERRO! O valor digitado � inv�lido!");
          printf("\nDigite um valor v�lido: ");
          scanf("%d", &quantidadeDias);
        }

        //Calculando valor total de loca��o
        if(diaSemana == 1){
            valorLocacao = 500 * quantidadeDias;
        }
        else if(diaSemana == 2){
            valorLocacao = 550 * quantidadeDias;
        }

        // Imprimir os dados no sistema
        printf("\n\n\nCONTRATO DE LOCA��O RECANTO DOS SONHOS\n\n");
        printf("Valor da diaria: Segunda � Sexta: R$500,00 - Sabado � Domingo: R$550,00\n");
        printf("Telefone: (19) 99580-8156\n");
        printf("Endereco: Rua dois, N� 1071 - jardim Itagua�u 2, Campinas - SP, CEP 13053-788, Brasil\n\n");
        printf("Locatario: %s\n", nomeCliente);
        printf("Quantidade de Dias de Locacao: %d\n", quantidadeDias);
        printf("Valor total da Locacao: R$%.2f\n", valorLocacao);
        printf("Telefone do Locatario: %s\n", telefoneCliente);
        printf("Data do Evento/Locacao: %s\n\n", dataEvento);
        printf("Assinatura do Locatario: _____\n");
        printf("Data de hoje: _ /_ /___\n");
        printf("Campinas, SP\n\n");
        printf("Assinatura do Locador: _____\n");

        return 0;
        break;
      case 5:
        printf("Voc� selecionou Calendario.\n");
        // Coloque a l�gica do calendario aqui
        //int mes, ano;

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
        int diasNoMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        char *nomesDosMeses[] = {"","Janeiro","Fevereiro","Março",
      "Abril","Maio","Junho","Julho","Agosto","Setembro","Outubro",         "Novembro","Dezembro"};
    
        printf("\nCalendario para %s de %d\n", nomesDosMeses[mes],           ano);
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
    
            // Se for o último dia da semana (sábado), vá para a                 próxima linha
            if (diaDaSemana % 7 == 0) {
                printf("\n");
            }
        }
        printf("\n");
        return 0;
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
