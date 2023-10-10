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
        int mes, ano;

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
