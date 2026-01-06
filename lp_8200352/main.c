#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ativo.h"
#include "tecnicos.h"
#include "departamentos.h"
#include "manutencao.h"
#include "relatorios.h"
#include "comum.h"

void subMenuAtivos(GestaoAtivos *ga, GestaoManutencao *gm);
void relatoriosAtivos(GestaoAtivos *ga, GestaoManutencao *gm);
void subMenuTecnicos(GestaoTecnicos *gt, GestaoManutencao *gm);
void relatoriosTecnicos(GestaoTecnicos *gt, GestaoManutencao *gm);
void subMenuDepartamentos(GestaoDepartamentos *gd, GestaoManutencao *gm);
void relatoriosDepartamentos(GestaoDepartamentos *gd, GestaoManutencao *gm);
void subMenuManutencao(GestaoManutencao *gm, GestaoAtivos *ga, GestaoDepartamentos *gd, GestaoTecnicos *gt);
void relatoriosManutencao(GestaoManutencao *gm, GestaoAtivos *ga, GestaoDepartamentos *gd);

int main() {
    GestaoAtivos ga = {NULL, 0, 0};
    GestaoTecnicos gt = {NULL, 0, 0};
    GestaoDepartamentos gd = {NULL, 0, 0};
    GestaoManutencao gm = {NULL, 0, 0};
    int opcao, i;

    carregarAtivos(&ga);
    carregarTecnicos(&gt);
    carregarDepartamentos(&gd);
    carregarManutencoes(&gm);

    escreverLog("Aplicacao iniciada.");

    do {
        printf("\n--- SISTEMA MUNICIPAL DE MANUTENCAO ---");
        printf("\n1. Gestao de Ativos");
        printf("\n2. Gestao de Tecnicos");
        printf("\n3. Gestao de Departamentos");
        printf("\n4. Gestao de Manutencao (Ordens)");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida! Use apenas numeros.\n");
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                subMenuAtivos(&ga, &gm);
                break;
            case 2:
                subMenuTecnicos(&gt, &gm);
                break;
            case 3:
                subMenuDepartamentos(&gd, &gm);
                break;
            case 4:
                subMenuManutencao(&gm, &ga, &gd, &gt);
                break;
            case 0:
                printf("\nA guardar dados e a libertar memoria...\n");
                guardarAtivos(&ga);
                guardarTecnicos(&gt);
                guardarDepartamentos(&gd);
                guardarManutencoes(&gm);

                /* Libertar materiais de cada ordem antes de libertar a lista */
                for (i = 0; i < gm.contador; i++) {
                    if (gm.lista[i].materiais != NULL) {
                        free(gm.lista[i].materiais);
                    }
                }
                free(gm.lista);
                free(ga.lista);
                free(gt.lista);
                free(gd.lista);

                escreverLog("Aplicacao encerrada pelo utilizador.");
                break;
            default:
                printf("\nOpcao inexistente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

void subMenuAtivos(GestaoAtivos *ga, GestaoManutencao *gm) {
    int op;
    do {
        printf("\n--- MENU GESTAO DE ATIVOS ---");
        printf("\n1. Inserir Ativo");
        printf("\n2. Editar Ativo");
        printf("\n3. Listar Ativos");
        printf("\n4. Inativar Ativo");
        printf("\n5. RELATORIOS");
        printf("\n6. Reativar Ativo");
        printf("\n0. Voltar");
        printf("\nEscolha: ");

        if (scanf("%d", &op) != 1) { while (getchar() != '\n'); op = -1; continue; }
        while (getchar() != '\n');

        switch (op) {
            case 1: criarAtivo(ga); break;
            case 2: atualizarAtivo(ga); break;
            case 3: lerAtivo(ga); break;
            case 4: eliminarAtivo(ga, gm); break;
            case 5: relatoriosAtivos(ga, gm); break;
            case 6: reativarAtivo(ga); break;
        }
    } while (op != 0);
}

void relatoriosAtivos(GestaoAtivos *ga, GestaoManutencao *gm) {
    int op;
    do {
        printf("\n--- RELATORIOS: ATIVOS ---");
        printf("\n1. Total de Ativos em Inventario");
        printf("\n2. Distribuicao por Categoria e Estado");
        printf("\n3. Ativos com maior recorrencia de Manutencoes");
        printf("\n4. Analise de Ciclo de Vida");
        printf("\n5. Frequencia de Falhas por Categoria");
        printf("\n0. Voltar");
        printf("\nEscolha: ");

        if (scanf("%d", &op) != 1) { while (getchar() != '\n'); op = -1; continue; }
        while (getchar() != '\n');

        switch (op) {
            case 1: totalAtivos(ga); break;
            case 2: totalAtivosPorEstado(ga); break;
            case 3: ativosMaiorOcurrencia(ga, gm); break;
            case 4: auditoriaAtivo(); break;
            case 5: frequenciaFalhasPorCategoria(ga); break;
        }
    } while (op != 0);
}

void subMenuTecnicos(GestaoTecnicos *gt, GestaoManutencao *gm) {
    int op;
    do {
        printf("\n--- MENU GESTAO DE TECNICOS ---");
        printf("\n1. Inserir Tecnico");
        printf("\n2. Editar Tecnico");
        printf("\n3. Listar Tecnicos");
        printf("\n4. Inativar Tecnico");
        printf("\n5. Reativar Tecnico");
        printf("\n6. RELATORIOS");
        printf("\n0. Voltar");
        printf("\nEscolha: ");

        if (scanf("%d", &op) != 1) { while (getchar() != '\n'); op = -1; continue; }
        while (getchar() != '\n');

        switch (op) {
            case 1: criarTecnicos(gt); break;
            case 2: atualizarTecnicos(gt); break;
            case 3: lerTecnicos(gt); break;
            case 4: eliminarTecnicos(gt, gm); break;
            case 5: reativarTecnico(gt); break;
            case 6: relatoriosTecnicos(gt, gm); break;
        }
    } while (op != 0);
}

void relatoriosTecnicos(GestaoTecnicos *gt, GestaoManutencao *gm) {
    int op;
    char esp[50];
    do {
        printf("\n--- RELATORIOS: TECNICOS ---");
        printf("\n1. Listar por Especialidade e Disponibilidade");
        printf("\n2. Taxa de Ocupacao");
        printf("\n3. Ranking de Desempenho");
        printf("\n0. Voltar");
        printf("\nEscolha: ");

        if (scanf("%d", &op) != 1) { while (getchar() != '\n'); op = -1; continue; }
        while (getchar() != '\n');

        switch (op) {
            case 1:
                printf("Insira a especialidade: ");
                scanf(" %49[^\n]", esp);
                while (getchar() != '\n');
                listarTecnicosEspecialidade(gt, esp, DISPONIVEL);
                break;
            case 2: taxaOcupacao(gt, gm); break;
            case 3: rankingDesempenho(gt, gm); break;
        }
    } while (op != 0);
}

void subMenuDepartamentos(GestaoDepartamentos *gd, GestaoManutencao *gm) {
    int op;
    do {
        printf("\n--- MENU GESTAO DE DEPARTAMENTOS ---");
        printf("\n1. Inserir Departamento");
        printf("\n2. Editar Departamento");
        printf("\n3. Listar Departamentos");
        printf("\n4. Inativar Departamento");
        printf("\n5. Reativar Departamento");
        printf("\n6. RELATORIOS");
        printf("\n0. Voltar");
        printf("\nEscolha: ");

        if (scanf("%d", &op) != 1) { while (getchar() != '\n'); op = -1; continue; }
        while (getchar() != '\n');

        switch (op) {
            case 1: criarDepartamento(gd); break;
            case 2: atualizarDepartamento(gd); break;
            case 3: lerDepartamento(gd); break;
            case 4: eliminarDepartamento(gd, gm); break;
            case 5: reativarDepartamento(gd); break;
            case 6: relatoriosDepartamentos(gd, gm); break;
        }
    } while (op != 0);
}

void relatoriosDepartamentos(GestaoDepartamentos *gd, GestaoManutencao *gm) {
    int op;
    do {
        printf("\n--- RELATORIOS: DEPARTAMENTOS ---");
        printf("\n1. Total de Departamentos Registados");
        printf("\n2. Historico de Pedidos e Custos");
        printf("\n3. Departamentos com mais Intervencoes Urgentes");
        printf("\n0. Voltar");
        printf("\nEscolha: ");

        if (scanf("%d", &op) != 1) { while (getchar() != '\n'); op = -1; continue; }
        while (getchar() != '\n');

        switch (op) {
            case 1: totalDepartamentosRegistados(gd); break;
            case 2: pedidosManutencaoPorDepartamento(gd, gm); break;
            case 3: departamentosMaisIntervencoes(gd, gm); break;
        }
    } while (op != 0);
}

void subMenuManutencao(GestaoManutencao *gm, GestaoAtivos *ga, GestaoDepartamentos *gd, GestaoTecnicos *gt) {
    int op;
    do {
        printf("\n--- MENU GESTAO DE ORDENS DE MANUTENCAO ---");
        printf("\n1. Inserir Ordem");
        printf("\n2. Editar Ordem");
        printf("\n3. Listar Ordens");
        printf("\n4. Cancelar Ordem");
        printf("\n5. RELATORIOS");
        printf("\n0. Voltar");
        printf("\nEscolha: ");

        if (scanf("%d", &op) != 1) { while (getchar() != '\n'); op = -1; continue; }
        while (getchar() != '\n');

        switch (op) {
            case 1: criarManutencao(gm, ga, gd, gt); break;
            case 2: atualizarManutencao(gm, ga, gd, gt); break;
            case 3: lerManutencao(gm); break;
            case 4: eliminarManutencao(gm); break;
            case 5: relatoriosManutencao(gm, ga, gd); break;
        }
    } while (op != 0);
}

void relatoriosManutencao(GestaoManutencao *gm, GestaoAtivos *ga, GestaoDepartamentos *gd) {
    int op;
    do {
        printf("\n--- RELATORIOS: MANUTENCAO ---");
        printf("\n1. Filtrar Ordens (Estado/Prioridade/Tipo)");
        printf("\n2. Tempo Medio de Resolucao");
        printf("\n3. Analise de Custos Totais");
        printf("\n0. Voltar");
        printf("\nEscolha: ");

        if (scanf("%d", &op) != 1) { while (getchar() != '\n'); op = -1; continue; }
        while (getchar() != '\n');

        switch (op) {
            case 1: listarOrdensManutencao(gm, PENDENTE, URGENTE, CORRETIVA); break;
            case 2: tempoMedio(gm); break;
            case 3: custosTotais(gm, ga, gd); break;
        }
    } while (op != 0);
}