// Função para validar a data
int validarData(int dia, int mes, int ano) {
    // Verifique se o ano é válido (a partir de 2023)
    if (ano < 2023) {
        return 0; // Ano inválido
    }

    // Verifique se o mês está dentro do intervalo de 1 a 12
    if (mes < 1 || mes > 12) {
        return 0; // Mês inválido
    }
        // Verifique se o dia está dentro do intervalo válido para o mês
        //int diasNoMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (dia < 1 || dia > 31) { //dia > diasNoMes[mes]
        return 0; // Dia inválido
    }

    return 1; // Data válida
}

