#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comum.h"
#include <time.h>

int validarData(Data d) {
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (d.ano <= 0) {
        return 0;
    }

    if (d.mes < 1 || d.mes > 12) {
        return 0;
    }

    if (d.dia < 1 || d.dia > diasPorMes[d.mes - 1]) {
        return 0;
    }

    return 1;
}

long dataParaDias(Data d) {
    long totalDias;
    int i;
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    totalDias = 0;
    totalDias = (long)(d.ano - 1) * 365;

    for (i = 0; i < d.mes - 1; i++) {
        totalDias = totalDias + diasPorMes[i];
    }

    totalDias = totalDias + d.dia;

    return totalDias;
}

void escreverLog(char *mensagem) {
    FILE *f;

    f = fopen("log.txt", "a");

    if (f == NULL) {
        return;
    }

    fprintf(f, "%s\n", mensagem);

    fclose(f);
}

void escreverLogAuditoria(char *entidade, int id, char *antes, char *depois) {
    FILE *f;
    time_t t;
    struct tm infoTempo;

    f = fopen("auditoria.txt", "a");

    if (f == NULL) {
        return;
    }

    t = time(NULL);
    infoTempo = *localtime(&t);

    fprintf(f, "[%02d-%02d-%d %02d:%02d:%02d] %s ID: %d | %s -> %s\n", infoTempo.tm_mday, infoTempo.tm_mon + 1, infoTempo.tm_year + 1900, infoTempo.tm_hour, infoTempo.tm_min, infoTempo.tm_sec, entidade, id, antes, depois);

    fclose(f);
}