#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comum.h"
#include "ativo.h"
#include "tecnicos.h"
#include "departamentos.h"
#include "manutencao.h"
#include "relatorios.h"

void totalAtivos(GestaoAtivos *ga) {
    int i, total;
    total = 0;

    for (i = 0; i < ga->contador; i++) {
        if (ga->lista[i].estado != ATIVO_INATIVO) {
            total++;
        }
    }

    printf("\n   TOTAL DE ATIVOS NO SISTEMA \n");

    if (total == 0) {
        printf("Nao existem ativos operacionais registados.\n");
    } else {
        printf("Total de ativos no inventario: %d\n", total);
    }
}

void totalAtivosPorEstado(GestaoAtivos *ga) {
    int i;
    int conOperacional, conEmManutencao, conAbatido;
    int conViaturas, conEqInformatico, conMobiliario, conFerramenta;

    conOperacional = 0;
    conEmManutencao = 0;
    conAbatido = 0;
    conViaturas = 0;
    conEqInformatico = 0;
    conMobiliario = 0;
    conFerramenta = 0;

    if (ga->contador == 0) {
        printf("\nNao existem ativos para analisar.\n");
        return;
    }

    for (i = 0; i < ga->contador; i++) {
        if (ga->lista[i].estado == ATIVO_INATIVO) {
            continue;
        }

        if (ga->lista[i].estado == OPERACIONAL) {
            conOperacional++;
        } else if (ga->lista[i].estado == EM_MANUTENCAO) {
            conEmManutencao++;
        } else if (ga->lista[i].estado == ABATIDO) {
            conAbatido++;
        }

        if (ga->lista[i].categoria == VIATURA) {
            conViaturas++;
        } else if (ga->lista[i].categoria == EQ_INFORMATICO) {
            conEqInformatico++;
        } else if (ga->lista[i].categoria == MOBILIARIO_URBANO) {
            conMobiliario++;
        } else if (ga->lista[i].categoria == FERRAMENTA) {
            conFerramenta++;
        }
    }

    printf("\n  DISTRIBUICAO DE ATIVOS \n");
    printf("Operacionais: %d\n", conOperacional);
    printf("Em Manutencao: %d\n", conEmManutencao);
    printf("Abatidos: %d\n", conAbatido);

    printf("\n  CATEGORIAS \n");
    printf("Viaturas: %d\n", conViaturas);
    printf("Informatica: %d\n", conEqInformatico);
    printf("Mobiliario: %d\n", conMobiliario);
    printf("Ferramentas: %d\n", conFerramenta);
}

void ativosMaiorOcurrencia(GestaoAtivos *ga, GestaoManutencao *gm) {
    int i, j, contMaximo, numAtivo;
    contMaximo = 0;

    if (ga->contador == 0) {
        printf("\nNao existem ativos registados.\n");
        return;
    }

    for (i = 0; i < ga->contador; i++) {
        if (ga->lista[i].estado == ATIVO_INATIVO) {
            continue;
        }
        numAtivo = 0;
        for (j = 0; j < gm->contador; j++) {
            if (gm->lista[j].idAtivo == ga->lista[i].idAtivo && gm->lista[j].tipo == CORRETIVA) {
                numAtivo++;
            }
        }
        if (numAtivo > contMaximo) {
            contMaximo = numAtivo;
        }
    }

    printf("\n  ATIVOS COM MAIS FALHAS (CORRETIVAS)\n");

    if (contMaximo == 0) {
        printf("Nao existem manutencoes corretivas registadas.\n");
    } else {
        printf("Maior numero de falhas encontrado: %d\n", contMaximo);
        for (i = 0; i < ga->contador; i++) {
            if (ga->lista[i].estado == ATIVO_INATIVO) {
                continue;
            }
            numAtivo = 0;
            for (j = 0; j < gm->contador; j++) {
                if (gm->lista[j].idAtivo == ga->lista[i].idAtivo && gm->lista[j].tipo == CORRETIVA) {
                    numAtivo++;
                }
            }
            if (numAtivo == contMaximo) {
                printf("ID: %d | Nome: %s\n", ga->lista[i].idAtivo, ga->lista[i].Nome);
            }
        }
    }
}

void totalDepartamentosRegistados(GestaoDepartamentos *gd) {
    int i, total;
    total = 0;

    if (gd->contador == 0) {
        printf("\nNao existem departamentos no sistema.\n");
        return;
    }

    for (i = 0; i < gd->contador; i++) {
        if (gd->lista[i].ativo == 1) {
            total++;
        }
    }

    printf("\n  DEPARTAMENTOS ATIVOS   \n");
    if (total == 0) {
        printf("Existem departamentos mas estao todos inativos.\n");
    } else {
        printf("Total de departamentos ativos no sistema: %d\n", total);
    }
}

void pedidosManutencaoPorDepartamento(GestaoDepartamentos *gd, GestaoManutencao *gm) {
    int i, j, k, totalOrdem;
    float custoTotal;

    if (gd->contador == 0) {
        printf("\nSem dados de departamentos.\n");
        return;
    }

    printf("\n   PEDIDOS E CUSTOS POR DEPARTAMENTO  \n");

    for (i = 0; i < gd->contador; i++) {
        if (gd->lista[i].ativo == 0) {
            continue;
        }

        totalOrdem = 0;
        custoTotal = 0;

        for (j = 0; j < gm->contador; j++) {
            if (gm->lista[j].idDepartamento == gd->lista[i].idDepartamento) {
                totalOrdem++;
                for (k = 0; k < gm->lista[j].numMateriais; k++) {
                    custoTotal = custoTotal + (gm->lista[j].materiais[k].quantidade * gm->lista[j].materiais[k].custoUnitario);
                }
            }
        }
        printf("Departamento: %s | Ordens: %d | Custo: %.2f EUR\n", gd->lista[i].Nome, totalOrdem, custoTotal);
    }
}

void departamentosMaisIntervencoes(GestaoDepartamentos *gd, GestaoManutencao *gm) {
    int i, j, contAtual, recordeIntervencoes;
    recordeIntervencoes = 0;

    if (gd->contador == 0) {
        printf("\nSem departamentos registados.\n");
        return;
    }

    for (i = 0; i < gd->contador; i++) {
        if (gd->lista[i].ativo == 0) {
            continue;
        }
        contAtual = 0;
        for (j = 0; j < gm->contador; j++) {
            if (gm->lista[j].idDepartamento == gd->lista[i].idDepartamento && gm->lista[j].prioridade == URGENTE) {
                contAtual++;
            }
        }
        if (contAtual > recordeIntervencoes) {
            recordeIntervencoes = contAtual;
        }
    }

    printf("\n  DEPARTAMENTOS COM MAIS PEDIDOS URGENTES  \n");

    if (recordeIntervencoes == 0) {
        printf("Nenhum pedido urgente registado ate ao momento.\n");
    } else {
        printf("Recorde de pedidos urgentes: %d\n", recordeIntervencoes);
        for (i = 0; i < gd->contador; i++) {
            if (gd->lista[i].ativo == 0) {
                continue;
            }
            contAtual = 0;
            for (j = 0; j < gm->contador; j++) {
                if (gm->lista[j].idDepartamento == gd->lista[i].idDepartamento && gm->lista[j].prioridade == URGENTE) {
                    contAtual++;
                }
            }
            if (contAtual == recordeIntervencoes) {
                printf("ID: %d | Nome: %s | Responsavel: %s\n", gd->lista[i].idDepartamento, gd->lista[i].Nome, gd->lista[i].Responsavel);
            }
        }
    }
}

void listarOrdensManutencao(GestaoManutencao *gm, EstadoOrdem estProc, Prioridade prioProc, TipoManutencao tipoProc) {
    int i, encontrou;
    char *txtPrio;
    char *txtTipo;
    char *txtEst;

    encontrou = 0;

    if (gm->contador == 0) {
        printf("\nNao existem ordens para listar.\n");
        return;
    }

    printf("\n RESULTADO DA FILTRAGEM DE ORDENS   \n");

    for (i = 0; i < gm->contador; i++) {
        if (gm->lista[i].estado == estProc && gm->lista[i].prioridade == prioProc && gm->lista[i].tipo == tipoProc) {
            encontrou = 1;

            if (gm->lista[i].prioridade == BAIXA) { txtPrio = "Baixa"; }
            else if (gm->lista[i].prioridade == NORMAL) { txtPrio = "Normal"; }
            else { txtPrio = "Urgente"; }

            if (gm->lista[i].tipo == PREVENTIVA) { txtTipo = "Preventiva"; }
            else { txtTipo = "Corretiva"; }

            if (gm->lista[i].estado == PENDENTE) { txtEst = "Pendente"; }
            else if (gm->lista[i].estado == EM_EXECUCAO) { txtEst = "Em Execucao"; }
            else if (gm->lista[i].estado == CONCLUIDA) { txtEst = "Concluida"; }
            else { txtEst = "Cancelada"; }

            printf("ID: %d | Ativo: %d | Prioridade: %s | Tipo: %s | Estado: %s\n",
                   gm->lista[i].idOrdem, gm->lista[i].idAtivo, txtPrio, txtTipo, txtEst);
        }
    }

    if (encontrou == 0) {
        printf("Nenhuma ordem encontrada com estes filtros.\n");
    }
}

void tempoMedio(GestaoManutencao *gm) {
    int i, contConcluidas;
    float total, media;
    long pedido, conclusao;

    contConcluidas = 0;
    total = 0;

    if (gm->contador == 0) {
        printf("\nSem ordens registadas.\n");
        return;
    }

    for (i = 0; i < gm->contador; i++) {
        if (gm->lista[i].estado == CONCLUIDA) {
            pedido = dataParaDias(gm->lista[i].dataPedido);
            conclusao = dataParaDias(gm->lista[i].dataConclusao);
            total = total + (conclusao - pedido);
            contConcluidas++;
        }
    }

    printf("\n TEMPO MEDIO DE RESOLUCAO  \n");
    if (contConcluidas > 0) {
        media = total / contConcluidas;
        printf("Media de resolucao: %.2f dias (Base: %d ordens)\n", media, contConcluidas);
    } else {
        printf("Nao existem ordens concluidas para calcular a media.\n");
    }
}

void custosTotais(GestaoManutencao *gm, GestaoAtivos *ga, GestaoDepartamentos *gd) {
    int i, j, k, categoriaEncontrada, departamentoEncontrado;
    float totalViatura, totalEqInformatico, totalMobiliario, totalFerramenta, custoTotal;
    float *custoDepartamento;

    totalViatura = 0;
    totalEqInformatico = 0;
    totalMobiliario = 0;
    totalFerramenta = 0;

    if (gm->contador == 0 || gd->contador == 0) {
        printf("\nSem dados para calcular custos.\n");
        return;
    }

    custoDepartamento = (float *)calloc(gd->contador, sizeof(float));
    if (custoDepartamento == NULL) {
        return;
    }

    for (i = 0; i < gm->contador; i++) {
        categoriaEncontrada = -1;
        departamentoEncontrado = -1;

        for (j = 0; j < ga->contador; j++) {
            if (ga->lista[j].idAtivo == gm->lista[i].idAtivo) {
                categoriaEncontrada = ga->lista[j].categoria;
                break;
            }
        }

        for (j = 0; j < gd->contador; j++) {
            if (gd->lista[j].idDepartamento == gm->lista[i].idDepartamento) {
                departamentoEncontrado = j;
                break;
            }
        }

        for (k = 0; k < gm->lista[i].numMateriais; k++) {
            custoTotal = gm->lista[i].materiais[k].quantidade * gm->lista[i].materiais[k].custoUnitario;

            if (categoriaEncontrada != -1) {
                if (categoriaEncontrada == VIATURA) totalViatura += custoTotal;
                else if (categoriaEncontrada == EQ_INFORMATICO) totalEqInformatico += custoTotal;
                else if (categoriaEncontrada == MOBILIARIO_URBANO) totalMobiliario += custoTotal;
                else if (categoriaEncontrada == FERRAMENTA) totalFerramenta += custoTotal;
            }
            if (departamentoEncontrado != -1) {
                custoDepartamento[departamentoEncontrado] += custoTotal;
            }
        }
    }

    printf("\n  CUSTOS POR CATEGORIA  \n");
    printf("Viaturas: %.2f EUR\n", totalViatura);
    printf("Eq. Informatico: %.2f EUR\n", totalEqInformatico);
    printf("Mobiliario: %.2f EUR\n", totalMobiliario);
    printf("Ferramentas: %.2f EUR\n", totalFerramenta);
    printf("TOTAL GERAL: %.2f EUR\n", (totalViatura + totalEqInformatico + totalMobiliario + totalFerramenta));

    printf("\n  CUSTOS POR DEPARTAMENTO  \n");
    for (i = 0; i < gd->contador; i++) {
        if (gd->lista[i].ativo == 1) {
            printf("Depto: %-15s | Gasto: %.2f EUR\n", gd->lista[i].Nome, custoDepartamento[i]);
        }
    }

    free(custoDepartamento);
}

void listarTecnicosEspecialidade(GestaoTecnicos *gt, char *especialidadeProc, EstadoTecnico estadoProc) {
    int i, encontrou;
    char *txtEstado;

    encontrou = 0;

    if (gt->contador == 0) {
        printf("\nNao existem tecnicos.\n");
        return;
    }

    printf("\n  TECNICOS POR ESPECIALIDADE  \n");

    for (i = 0; i < gt->contador; i++) {
        if (strcmp(gt->lista[i].Especialidade, especialidadeProc) == 0 && gt->lista[i].estado == estadoProc) {
            encontrou = 1;

            if (gt->lista[i].estado == DISPONIVEL) { txtEstado = "Disponivel"; }
            else if (gt->lista[i].estado == OCUPADO) { txtEstado = "Ocupado"; }
            else { txtEstado = "Inativo"; }

            printf("ID: %d | Nome: %s | Estado: %s\n", gt->lista[i].idTecnico, gt->lista[i].Nome, txtEstado);
        }
    }

    if (encontrou == 0) {
        printf("Nenhum técnico encontrado com estes critérios.\n");
    }
}

void taxaOcupacao(GestaoTecnicos *gt, GestaoManutencao *gm) {
    int i, j, ordensEmExecucao, trabalhoPendente, totalTrabalhoAtual;
    float taxa;

    if (gt->contador == 0) {
        printf("\nSem tecnicos registados.\n");
        return;
    }

    printf("\n--- TAXA DE OCUPACAO DOS TECNICOS ---\n");

    for (i = 0; i < gt->contador; i++) {
        if (gt->lista[i].estado == TECNICO_INATIVO) {
            continue;
        }

        ordensEmExecucao = 0;
        trabalhoPendente = 0;

        for (j = 0; j < gm->contador; j++) {
            if (gm->lista[j].idTecnico == gt->lista[i].idTecnico) {
                if (gm->lista[j].estado == EM_EXECUCAO) {
                    ordensEmExecucao++;
                } else if (gm->lista[j].estado == PENDENTE) {
                    trabalhoPendente++;
                }
            }
        }

        totalTrabalhoAtual = ordensEmExecucao + trabalhoPendente;
        taxa = 0.0;
        if (totalTrabalhoAtual > 0) {
            taxa = ((float)ordensEmExecucao / totalTrabalhoAtual) * 100;
        }

        printf("Nome: %-20s | Em Execucao: %d | Pendente: %d | Taxa: %.2f%%\n",
               gt->lista[i].Nome, ordensEmExecucao, trabalhoPendente, taxa);
    }
}

void rankingDesempenho(GestaoTecnicos *gt, GestaoManutencao *gm) {
    int i, j, count;
    long totalDiasGasto, inicio, fim;
    AuxRanking *ranking;
    AuxRanking temp;

    if (gt->contador == 0 || gm->contador == 0) {
        printf("\nDados insuficientes para o ranking.\n");
        return;
    }

    ranking = (AuxRanking *)malloc(gt->contador * sizeof(AuxRanking));
    if (ranking == NULL) {
        return;
    }

    for (i = 0; i < gt->contador; i++) {
        ranking[i].idTecnico = gt->lista[i].idTecnico;
        strcpy(ranking[i].nome, gt->lista[i].Nome);
        ranking[i].concluidas = 0;
        totalDiasGasto = 0;

        for (j = 0; j < gm->contador; j++) {
            if (gm->lista[j].idTecnico == gt->lista[i].idTecnico && gm->lista[j].estado == CONCLUIDA) {
                ranking[i].concluidas++;
                inicio = dataParaDias(gm->lista[j].dataPedido);
                fim = dataParaDias(gm->lista[j].dataConclusao);
                totalDiasGasto = totalDiasGasto + (fim - inicio);
            }
        }

        if (ranking[i].concluidas > 0) {
            ranking[i].tempoMedio = (float)totalDiasGasto / ranking[i].concluidas;
        } else {
            ranking[i].tempoMedio = 999.0;
        }
    }

    for (i = 0; i < gt->contador - 1; i++) {
        for (j = 0; j < gt->contador - i - 1; j++) {
            if (ranking[j].concluidas < ranking[j + 1].concluidas ||
               (ranking[j].concluidas == ranking[j + 1].concluidas && ranking[j].tempoMedio > ranking[j+1].tempoMedio)) {
                temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    printf("\n  RANKING DE DESEMPENHO  \n");
    count = 0;
    for (i = 0; i < gt->contador; i++) {
        if (ranking[i].concluidas > 0) {
            count++;
            printf("%d. %-20s | Concluidas: %d | Media: %.1f dias\n",
                   count, ranking[i].nome, ranking[i].concluidas, ranking[i].tempoMedio);
        }
    }

    if (count == 0) {
        printf("Nenhum tecnico concluiu ordens ainda.\n");
    }

    free(ranking);
}

void auditoriaAtivo() {
    FILE *f;
    int idProcurado, encontrou;
    char linha[256], termoBusca[50];

    f = fopen("auditoria.txt", "r");
    encontrou = 0;

    if (f == NULL) {
        printf("\nFicheiro de auditoria nao encontrado.\n");
        return;
    }

    printf("\n  ANALISE DA AUDITORIA DO ATIVO  \n");
    printf("Insira o ID do Ativo: ");
    if (scanf("%d", &idProcurado) != 1) {
        while (getchar() != '\n');
        fclose(f);
        return;
    }
    while (getchar() != '\n');

    sprintf(termoBusca, "ATIVO ID: %d |", idProcurado);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        if (strstr(linha, termoBusca) != NULL) {
            printf("%s", linha);
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhum historico encontrado para o ID %d.\n", idProcurado);
    }

    fclose(f);
}

void frequenciaFalhasPorCategoria(GestaoAtivos *ga) {
    FILE *f;
    char linha[256];
    int contadores[4];
    int idLido, i, totalFalhas;
    char *categorias[] = {"Viatura", "Informatica", "Mobiliario", "Ferramenta"};
    float percentagem;

    totalFalhas = 0;
    for(i=0; i<4; i++) { contadores[i] = 0; }

    f = fopen("auditoria.txt", "r");
    if (f == NULL) {
        printf("\nLog de auditoria nao encontrado.\n");
        return;
    }

    if (ga->contador == 0) {
        fclose(f);
        return;
    }

    while (fgets(linha, sizeof(linha), f) != NULL) {
        if (strstr(linha, "-> Em Manutencao") != NULL) {
            if (sscanf(strstr(linha, "ID:"), "ID: %d", &idLido) == 1) {
                for (i = 0; i < ga->contador; i++) {
                    if (ga->lista[i].idAtivo == idLido) {
                        contadores[ga->lista[i].categoria]++;
                        totalFalhas++;
                        break;
                    }
                }
            }
        }
    }

    printf("\n  FREQUENCIA DE FALHAS POR CATEGORIA  \n");

    if (totalFalhas == 0) {
        printf("Sem registos de falhas no log.\n");
    } else {
        for (i = 0; i < 4; i++) {
            percentagem = ((float)contadores[i] / totalFalhas) * 100;
            printf("%-15s : %d falhas (%.2f%%)\n", categorias[i], contadores[i], percentagem);
        }
        printf("Total de falhas analisadas: %d\n", totalFalhas);
    }

    fclose(f);
}