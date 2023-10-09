// Função para imprimir o calendário de um mês e ano específicos
#include <stdio.h>

// Função para verificar se um ano é bissexto
int eBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int main() {
    int ano, mes;

    printf("Digite o ano (2023 em diante): ");
    scanf("%d", &ano);

    printf("Digite o mês (1-12): ");
    scanf("%d", &mes);

    if (mes < 1 || mes > 12 || ano < 2023) {
        printf("Ano ou mês inválidos.\n");
        return 1;
    }

    // Determine o número de dias no mês (levando em consideração o ano bissexto)
    int diasNoMes[] = {0, 31, 28 + eBissexto(ano), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("\nCalendário para %d/%d:\n", mes, ano);
    printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");

    // Encontre o dia da semana para o primeiro dia do mês (1º de janeiro)
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

    return 0;
}
