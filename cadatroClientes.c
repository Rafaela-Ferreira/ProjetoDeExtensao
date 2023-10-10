#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


int main()
{    setlocale(LC_ALL, "Portuguese");
    typedef struct {
    char nome;
    int cpf;
    char endereco;
} cliente;

void inserirDados(cliente*cadastro, int quant) {
    int i;
    printf("Digite os dados do cliente:\n");
    for (i = 0; i < quant; i++) {
         printf("cliente %d:\n", i + 1);
        printf("Digite o nome:");
        scanf("%49s", cadastro[i].nome);

        printf("Digite o cpf:");
        scanf("%i", &cadastro[i].cpf);

        printf("Digite o endere�o:");
        scanf("%49s", cadastro[i].endereco);
    }
}

void salvarDados(cliente *cadastro, int quant) {
    FILE *arquivo;
    arquivo = fopen("cadastro.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i;
    for (i = 0; i < quant; i++) {
        fprintf(arquivo, "Cliente %d\n", i + 1);
        fprintf(arquivo, "Nome: %s\n", cadastro[i].nome);
        fprintf(arquivo, "CPF: %d\n", cadastro[i].cpf);
        fprintf(arquivo, "endere�o: %s\n", cadastro[i].endereco);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    printf("Dados salvos no arquivo com sucesso.\n");
}
    return 0;
}
