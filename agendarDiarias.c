#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void marcarDatasNoCalendario(int ano, int mes, int *diasMarcados, int totalDias) {
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
        diasNoMes[2] = 29; // Fevereiro tem 29 dias em um ano bissexto
    }

    int primeiroDiaDoMes = calcularDiaSemana(ano, mes, 1);

    for (int i = 0; i < primeiroDiaDoMes; i++) {
        printf("\t");
    }

    for (int dia = 1; dia <= diasNoMes[mes]; dia++) {
        int diaDaSemana = calcularDiaSemana(ano, mes, dia);

        if (diasMarcados[dia]) {
            printf("\033[1;34m%2d\033[0m\t", dia); // Imprime o dia marcado em azul
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

int main() {
    int ano, mes, qtdDias;
    printf("Digite o ano, o mês (no formato AAAA MM) e a quantidade de dias para agendar: ");
    scanf("%d %d %d", &ano, &mes, &qtdDias);

    char *nomesDosMeses[] = {"", "Janeiro", "Fevereiro", "Março",
                             "Abril", "Maio", "Junho", "Julho",
                             "Agosto", "Setembro", "Outubro", "Novembro",
                             "Dezembro"};

    printf("\nCalendário para %s de %d\n", nomesDosMeses[mes], ano);
    //printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");

    // Abrir o arquivo para leitura e gravação
    FILE *arquivo = fopen("datas.txt", "a+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Solicitar as datas para agendamento
    for (int i = 0; i < qtdDias; i++) {
        int diaAgendado;
        printf("Digite o dia para agendar: ");
        scanf("%d", &diaAgendado);

        // Verificar se a data já passou ou é hoje
        time_t t = time(NULL);
        struct tm *dataAtual = localtime(&t);

        if ((ano < dataAtual->tm_year + 1900) ||
            (ano == dataAtual->tm_year + 1900 && mes < dataAtual->tm_mon + 1) ||
            (ano == dataAtual->tm_year + 1900 && mes == dataAtual->tm_mon  && diaAgendado <= dataAtual->tm_mday)) {
            printf("\033[1;31mNÃO É POSSÍVEL AGENDAR UMA DATA QUE JÁ PASSOU OU É HOJE.\033[0m\n\n");
            i--; // Descontar a iteração, pois o usuário deve inserir uma nova data
            continue;
        }

        fprintf(arquivo, "%d/%d/%d\n", diaAgendado, mes, ano);
    }

    // Ler as datas do arquivo e marcá-las no calendário
    printf("Dom\tSeg\tTer\tQua\tQui\tSex\tSáb\n");
    rewind(arquivo);

    int *diasMarcados = (int *)calloc(32, sizeof(int)); // Usamos índices 1-31 para diasMarcados

    int diaLido;
    int mesLido;
    int anoLido;
    int totalDias = 0;

    while (fscanf(arquivo, "%d/%d/%d", &diaLido, &mesLido, &anoLido) == 3) {
        if (mesLido == mes && anoLido == ano) {
            diasMarcados[diaLido] = 1;
            totalDias++;
        }
    }

    fclose(arquivo);

    marcarDatasNoCalendario(ano, mes, diasMarcados, totalDias);

    free(diasMarcados);

    return 0;
}
