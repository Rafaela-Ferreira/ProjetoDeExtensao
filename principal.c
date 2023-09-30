#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura para armazenar informações do usuário
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
      return i; // Retorna o índice do usuário se o login for bem-sucedido
    }
  }
  return -1; // Retorna -1 se o login falhar
}

int main() {
  // Defina os dados do usuário. Isso deve ser feito de forma mais segura em um
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
      printf("Nome de usuário: ");
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
      printf("3. Agenda de Diárias\n");
      printf("4. Contrato\n");
      printf("5. Calendario\n");
      printf("6. Sair\n");
      printf("Escolha uma opção: ");
      scanf("%d", &opcao);

      switch (opcao) {
      case 1:
        printf("Você selecionou Cadastro de Clientes.\n");
        // Coloque a lógica do cadastro de clientes aqui
        break;
      case 2:
        printf("Você selecionou Agenda de Visitas.\n");
        // Coloque a lógica da agenda de visitas aqui
        break;
      case 3:
        printf("Você selecionou Agenda de Diárias.\n");
        // Coloque a lógica da agenda de diárias aqui
        break;
      case 4:
        printf("Você selecionou Contrato.\n");
        // Coloque a lógica do contrato aqui
        break;
      case 5:
        printf("Você selecionou Calendario.\n");
        // Coloque a lógica do contrato aqui
        break;
      case 6:
        printf("Saindo...\n");
        exit(0); // Saia do programa
      default:
        printf("Opção inválida. Tente novamente.\n");
      }
    }
  }

  return 0;
}
