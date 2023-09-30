#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  // Defina os dados do usu�rio. Isso deve ser feito de forma mais segura em um
  // ambiente real.
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
        break;
      case 3:
        printf("Voc� selecionou Agenda de Di�rias.\n");
        // Coloque a l�gica da agenda de di�rias aqui
        break;
      case 4:
        printf("Voc� selecionou Contrato.\n");
        // Coloque a l�gica do contrato aqui
        break;
      case 5:
        printf("Voc� selecionou Calendario.\n");
        // Coloque a l�gica do calendario aqui
        char *diasSemana[] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};
        int mes, ano;

        while (1) {
          printf("Digite o ano (entre 2023 e 2100): ");
          scanf("%d", &ano);

          if (ano >= 2023 && ano <= 2100) {
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
        // até aqui está validado!!

        int diasNoMes[] = {
            0,  31, 28 + ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0),
            31, 30, 31,
            30, 31, 31,
            30, 31, 30,
            31};
        char calendario[6][7]; // Matriz 6x7 para armazenar os números dos dias
                               // do mês.

        // Preencher o calendário com espaços em branco.
        for (int i = 0; i < 6; i++) {
          for (int j = 0; j < 7; j++) {
            calendario[i][j] = ' ';
          }
        }

        // Preencher o calendário com os números dos dias do mês.
        int dia = 1;
        int diaDaSemana = 0; // Começa no domingo.

        for (int i = 0; i < 6; i++) {
          for (int j = diaDaSemana; j < 7; j++) {
            if (dia <= diasNoMes[mes]) {
              calendario[i][j] = dia + '0';
              dia++;
            }
          }
          diaDaSemana = 0; // Reinicia no domingo após a primeira linha.
        }

        // Imprimir o cabeçalho do calendário.
        printf("\nCalendario para %d/%d\n", mes, ano);
        for (int i = 0; i < 7; i++) {
          printf("%s ", diasSemana[i]);
        }
        printf("\n");

        // Imprimir o calendário.
        for (int i = 0; i < 6; i++) {
          for (int j = 0; j < 7; j++) {
            printf("%c ", calendario[i][j]);
          }
          printf("\n");
        }

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
