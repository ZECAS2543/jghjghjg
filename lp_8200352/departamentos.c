#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "departamentos.h"
#include "manutencao.h"
#include "comum.h"

void criarDepartamento(GestaoDepartamentos *gd) {
    int novaCapacidade;
    Departamento *temp;

    if (gd->contador == gd->capacidade) {
        if (gd->capacidade == 0) {
            novaCapacidade = 1;
        } else {
            novaCapacidade = gd->capacidade * 2;
        }

        temp = (Departamento *) realloc(gd->lista, novaCapacidade * sizeof(Departamento));

        if (temp == NULL) {
            printf("Nao foi possivel aumentar a lista de departamentos.\n");
            return;
        }
        gd->lista = temp;
        gd->capacidade = novaCapacidade;
    }

    gd->lista[gd->contador].idDepartamento = gd->contador + 1;

    printf("\n--- Criar Departamento (ID: %d) ---\n", gd->lista[gd->contador].idDepartamento);

    printf("Nome: ");
    scanf(" %99[^\n]", gd->lista[gd->contador].Nome);
    while (getchar() != '\n');

    printf("Responsavel: ");
    scanf(" %99[^\n]", gd->lista[gd->contador].Responsavel);
    while (getchar() != '\n');

    printf("Contacto: ");
    scanf(" %49[^\n]", gd->lista[gd->contador].Contacto);
    while (getchar() != '\n');

    gd->lista[gd->contador].ativo = 1;

    gd->contador++;
    printf("Departamento criado com sucesso.\n");
    escreverLog("Novo departamento criado.");
}

void lerDepartamento(GestaoDepartamentos *departamentos) {
    int i;
    int encontrouAtivo;

    encontrouAtivo = 0;

    printf("\n--- Lista de Departamentos ---\n");

    if (departamentos->contador == 0) {
        printf("Nao existem Departamentos no sistema.\n");
        return;
    }

    for (i = 0; i < departamentos->contador; i++) {
        if (departamentos->lista[i].ativo == 1) {
            encontrouAtivo = 1;
            printf("ID: %d | Nome: %s | Resp: %s | Contacto: %s\n",
                   departamentos->lista[i].idDepartamento,
                   departamentos->lista[i].Nome,
                   departamentos->lista[i].Responsavel,
                   departamentos->lista[i].Contacto);
        }
    }

    if (encontrouAtivo == 0) {
        printf("Nao existem departamentos ativos para mostrar.\n");
    }
}

void atualizarDepartamento(GestaoDepartamentos *departamentos) {
    int idProcurado, i, encontrado;

    encontrado = 0;

    printf("\nInsira o ID do Departamento que quer atualizar: ");
    if (scanf("%d", &idProcurado) != 1) {
        printf("Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < departamentos->contador; i++) {
        if (departamentos->lista[i].idDepartamento == idProcurado && departamentos->lista[i].ativo == 1) {
            encontrado = 1;

            printf("\n--- A Atualizar Departamento ID: %d ---\n", idProcurado);

            do {
                printf("Novo Nome (Atual: %s): ", departamentos->lista[i].Nome);
                scanf(" %99[^\n]", departamentos->lista[i].Nome);
                while (getchar() != '\n');
                if (strlen(departamentos->lista[i].Nome) == 0) {
                    printf("O nome do departamento e obrigatorio.\n");
                }
            } while (strlen(departamentos->lista[i].Nome) == 0);

            do {
                printf("Novo Responsavel (Atual: %s): ", departamentos->lista[i].Responsavel);
                scanf(" %99[^\n]", departamentos->lista[i].Responsavel);
                while (getchar() != '\n');
                if (strlen(departamentos->lista[i].Responsavel) == 0) {
                    printf("O nome do responsavel e obrigatorio.\n");
                }
            } while (strlen(departamentos->lista[i].Responsavel) == 0);

            do {
                printf("Novo Contacto (Atual: %s): ", departamentos->lista[i].Contacto);
                scanf(" %49[^\n]", departamentos->lista[i].Contacto);
                while (getchar() != '\n');
                if (strlen(departamentos->lista[i].Contacto) == 0) {
                    printf("O contacto e obrigatorio.\n");
                }
            } while (strlen(departamentos->lista[i].Contacto) == 0);

            escreverLogAuditoria("DEPARTAMENTO", idProcurado, "EDICAO", "Dados Alterados");
            printf("Dados do departamento atualizados.\n");
            break;
        }
    }

    if (encontrado == 0) {
        printf("Departamento com ID %d nao encontrado ou esta inativo.\n", idProcurado);
    }
}

void eliminarDepartamento(GestaoDepartamentos *departamentos, GestaoManutencao *gm) {
    int idProcurado, i, j, encontrado, temOrdensAtivas;

    encontrado = 0;
    temOrdensAtivas = 0;

    printf("\n--- Eliminar Departamento ---\n");
    printf("Insira o ID do Departamento: ");

    if (scanf("%d", &idProcurado) != 1) {
        printf("Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < departamentos->contador; i++) {
        if (departamentos->lista[i].idDepartamento == idProcurado) {
            encontrado = 1;

            if (departamentos->lista[i].ativo == 0) {
                printf("Este departamento ja se encontra inativo.\n");
                return;
            }

            for (j = 0; j < gm->contador; j++) {
                if (gm->lista[j].idDepartamento == idProcurado) {
                    if (gm->lista[j].estado == PENDENTE || gm->lista[j].estado == EM_EXECUCAO) {
                        temOrdensAtivas = 1;
                        break;
                    }
                }
            }

            if (temOrdensAtivas == 1) {
                printf("Nao e possivel inativar: existem ordens pendentes ou em execucao.\n");
            } else {
                departamentos->lista[i].ativo = 0;
                printf("Departamento ID %d marcado como Inativo.\n", idProcurado);
                escreverLogAuditoria("DEPARTAMENTO", idProcurado, "ATIVO", "INATIVADO");
                escreverLog("Departamento marcado como inativo.");
            }
            break;
        }
    }

    if (encontrado == 0) {
        printf("Departamento com o ID %d nao encontrado.\n", idProcurado);
    }
}

void reativarDepartamento(GestaoDepartamentos *departamentos) {
    int idProcurado, i, encontrado;
    encontrado = 0;

    printf("\n--- Reativar Departamento ---\n");
    printf("ID do Departamento: ");
    if (scanf("%d", &idProcurado) != 1) {
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < departamentos->contador; i++) {
        if (departamentos->lista[i].idDepartamento == idProcurado && departamentos->lista[i].ativo == 0) {
            departamentos->lista[i].ativo = 1;
            printf("Departamento ID %d reativado com sucesso.\n", idProcurado);
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) {
        printf("Departamento nao encontrado ou ja esta ativo.\n");
    }
}

void guardarDepartamentos(GestaoDepartamentos *gd) {
    FILE *f;
    int i;

    f = fopen("departamentos.txt", "w");
    if (f == NULL) {
        return;
    }

    fprintf(f, "%d\n", gd->contador);
    for (i = 0; i < gd->contador; i++) {
        fprintf(f, "%d;%s;%s;%s;%d\n",
                gd->lista[i].idDepartamento,
                gd->lista[i].Nome,
                gd->lista[i].Responsavel,
                gd->lista[i].Contacto,
                gd->lista[i].ativo);
    }
    fclose(f);
}

void carregarDepartamentos(GestaoDepartamentos *gd) {
    int i;
    FILE *f;

    f = fopen("departamentos.txt", "r");

    if (f == NULL) {
        return;
    }

    if (gd->lista != NULL) {
        free(gd->lista);
        gd->lista = NULL;
    }

    if (fscanf(f, "%d\n", &gd->contador) != 1) {
        fclose(f);
        return;
    }

    gd->capacidade = gd->contador;
    gd->lista = (Departamento *)malloc(gd->capacidade * sizeof(Departamento));

    if (gd->lista == NULL) {
        fclose(f);
        return;
    }

    for (i = 0; i < gd->contador; i++) {
        fscanf(f, "%d;%[^;];%[^;];%[^;];%d\n",
               &gd->lista[i].idDepartamento,
               gd->lista[i].Nome,
               gd->lista[i].Responsavel,
               gd->lista[i].Contacto,
               &gd->lista[i].ativo);
    }
    fclose(f);
}