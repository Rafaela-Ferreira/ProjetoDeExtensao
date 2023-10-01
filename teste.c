#include <stdio.h>

// Função para verificar se um ano é bissexto
int eBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

// Função para imprimir o calendário de um mês e ano específicos
void imprimirCalendario(int ano, int mes) {
    int diasNoMes[] = {0, 31, 28 + eBissexto(ano), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *nomesDosMeses[] = {"", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho","Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    
    if (mes < 1 || mes > 12 || ano < 2023) {
        printf("Ano ou mês inválidos.\n");
        return;
    }

    printf("\nCalendario para %s de %d\n", nomesDosMeses[mes], ano);

    // Encontre o dia da semana para o primeiro dia do mês
    int primeiroDia = 1;
    int diaDaSemana = 0; // 0 corresponde a domingo

    while (diaDaSemana < primeiroDia) {
        printf("\t"); // Espaços para os dias da semana antes do primeiro dia
        diaDaSemana++;
    }

    // Imprimir cabeçalho do calendário
    printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSab\n");

    // Imprimir dias do mês
    for (int dia = 1; dia <= diasNoMes[mes]; dia++) {
        printf("\t%d", dia);
        diaDaSemana++;

        // Se atingir o final da semana (Sábado), vá para a próxima linha
        if (diaDaSemana % 7 == 0) {
            printf("\n");
        }
    }

    printf("\n");
}

int main() {
    int ano, mes;

    while (1) {
        printf("Digite o ano (2023 em diante): ");
        scanf("%d", &ano);

        if (ano >= 2023) {
            break;
        } else {
            printf("Ano inválido.\n");
        }
    }

    while (1) {
        printf("Digite o mês (1-12): ");
        scanf("%d", &mes);

        if (mes >= 1 && mes <= 12) {
            break;
        } else {
            printf("Mês inválido.\n");
        }
    }

    imprimirCalendario(ano, mes);

    return 0;
}
