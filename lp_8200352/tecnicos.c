#include <stdio.h>
#include <string.h>
#include "tecnicos.h"
#include "manutencao.h"
#include "stdlib.h"
#include "comum.h"

void criarTecnicos(GestaoTecnicos *gt) {
    int novaCapacidade;
    Tecnico *temp;

    if (gt->contador == gt->capacidade) {
        if (gt->capacidade == 0) {
            novaCapacidade = 1;
        } else {
            novaCapacidade = gt->capacidade * 2;
        }

        temp = (Tecnico *)realloc(gt->lista, novaCapacidade * sizeof(Tecnico));

        if (temp == NULL) {
            escreverLog(" Memoria insuficiente para novo tecnico.");
            return;
        }
        gt->lista = temp;
        gt->capacidade = novaCapacidade;
    }

    gt->lista[gt->contador].idTecnico = gt->contador + 1;

    printf("\n  Inserir Tecnico (ID: %d) ", gt->lista[gt->contador].idTecnico);

    printf("\nNome: ");
    scanf(" %99[^\n]", gt->lista[gt->contador].Nome);
    while (getchar() != '\n');

    printf("Especialidade: ");
    scanf(" %49[^\n]", gt->lista[gt->contador].Especialidade);
    while (getchar() != '\n');

    gt->lista[gt->contador].estado = DISPONIVEL;

    gt->contador++;
    printf("  Tecnico inserido.\n");
    escreverLog(" Tecnico registado no sistema.");
}

void lerTecnicos(GestaoTecnicos *tecnicos) {
    int i;
    int encontrouAtivo;

    encontrouAtivo = 0;

    printf("\n  Listagem de Tecnicos \n");

    if (tecnicos->contador == 0) {
        printf("Nao existem tecnicos no sistema.\n");
        return;
    }

    for (i = 0; i < tecnicos->contador; i++) {
        if (tecnicos->lista[i].estado != TECNICO_INATIVO) {
            encontrouAtivo = 1;
            printf("ID: %-3d | Nome: %-20s | Especialidade: %-15s | Estado: %d\n",
                   tecnicos->lista[i].idTecnico,
                   tecnicos->lista[i].Nome,
                   tecnicos->lista[i].Especialidade,
                   tecnicos->lista[i].estado);
        }
    }

    if (encontrouAtivo == 0) {
        printf("Nao existem tecnicos ativos no sistema.\n");
    }
}

void atualizarTecnicos(GestaoTecnicos *tecnicos) {
    int idProcurado, i, encontrado, novoEstado, estadoAnterior;
    char *nomesEstados[] = {"Disponivel", "Ocupado", "Inativo"};

    encontrado = 0;

    printf("\nInsira o ID do tecnico que deseja editar: ");
    if (scanf("%d", &idProcurado) != 1) {
        printf(" Entrada invalida. Insira um ID numerico.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < tecnicos->contador; i++) {
        if (tecnicos->lista[i].idTecnico == idProcurado && tecnicos->lista[i].estado != TECNICO_INATIVO) {
            encontrado = 1;
            estadoAnterior = tecnicos->lista[i].estado;

            printf(" A Editar tecnico ID: %d ---\n", idProcurado);

            do {
                printf("Novo nome (Atual: %s): ", tecnicos->lista[i].Nome);
                scanf(" %99[^\n]", tecnicos->lista[i].Nome);
                while (getchar() != '\n');
                if (strlen(tecnicos->lista[i].Nome) == 0) {
                    printf("O nome e obrigatorio.\n");
                }
            } while (strlen(tecnicos->lista[i].Nome) == 0);

            do {
                printf("Nova especialidade (Atual: %s): ", tecnicos->lista[i].Especialidade);
                scanf(" %49[^\n]", tecnicos->lista[i].Especialidade);
                while (getchar() != '\n');
                if (strlen(tecnicos->lista[i].Especialidade) == 0) {
                    printf("A especialidade e obrigatoria.\n");
                }
            } while (strlen(tecnicos->lista[i].Especialidade) == 0);

            do {
                printf("Novo estado (0-Disponivel, 1-Ocupado, 2-Inativo) [Atual: %d]: ", tecnicos->lista[i].estado);
                if (scanf("%d", &novoEstado) != 1) {
                    printf("Insira um numero (0, 1 ou 2).\n");
                    while (getchar() != '\n');
                    novoEstado = -1;
                } else {
                    while (getchar() != '\n');
                }

                if (novoEstado < 0 || novoEstado > 2) {
                    printf("Estado invalido! Escolha entre 0 e 2.\n");
                }
            } while (novoEstado < 0 || novoEstado > 2);

            if (estadoAnterior != novoEstado) {
                escreverLogAuditoria("TECNICO", idProcurado, nomesEstados[estadoAnterior], nomesEstados[novoEstado]);
                tecnicos->lista[i].estado = (EstadoTecnico)novoEstado;
            }

            printf(" Dados do tecnico atualizados.\n");
            break;
        }
    }

    if (encontrado == 0) {
        printf("Tecnico com ID %d nao encontrado ou esta inativo.\n", idProcurado);
    }
}

void eliminarTecnicos(GestaoTecnicos *tecnicos, GestaoManutencao *gm) {
    int i, j, idProcurado, encontrado, temOrdensAtivas;

    encontrado = 0;
    temOrdensAtivas = 0;

    printf("\n   Inativar Tecnico ");
    printf("\nInsira o ID do Tecnico: ");
    if (scanf("%d", &idProcurado) != 1) {
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < tecnicos->contador; i++) {
        if (tecnicos->lista[i].idTecnico == idProcurado) {
            encontrado = 1;

            for (j = 0; j < gm->contador; j++) {
                if (gm->lista[j].idTecnico == idProcurado &&
                   (gm->lista[j].estado == PENDENTE || gm->lista[j].estado == EM_EXECUCAO)) {
                    temOrdensAtivas = 1;
                    break;
                }
            }

            if (temOrdensAtivas == 1) {
                printf(" Nao e possivel inativar: o tecnico tem ordens pendentes ou em execucao.\n");
            } else {
                tecnicos->lista[i].estado = TECNICO_INATIVO;
                printf("Tecnico ID %d marcado como Inativo.\n", idProcurado);
                escreverLogAuditoria("TECNICO", idProcurado, "ATIVO", "INATIVADO");
                escreverLog(" Tecnico inativado.");
            }
            break;
        }
    }

    if (encontrado == 0) {
        printf(" Tecnico com o ID %d nao encontrado.\n", idProcurado);
    }
}

void reativarTecnico(GestaoTecnicos *tecnicos) {
    int idProcurado, i, encontrado;
    encontrado = 0;

    printf("\n   Reativar Tecnico ");
    printf("\nID do Tecnico: ");
    if (scanf("%d", &idProcurado) != 1) {
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < tecnicos->contador; i++) {
        if (tecnicos->lista[i].idTecnico == idProcurado && tecnicos->lista[i].estado == TECNICO_INATIVO) {
            tecnicos->lista[i].estado = DISPONIVEL;
            printf(" Tecnico ID %d reativado.\n", idProcurado);
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) {
        printf("Tecnico nao encontrado ou ja esta ativo.\n");
    }
}

void guardarTecnicos(GestaoTecnicos *gt) {
    FILE *f = fopen("tecnicos.txt", "w");
    int i;
    if (f == NULL) {
        return;
    }

    fprintf(f, "%d\n", gt->contador);
    for (i = 0; i < gt->contador; i++) {
        fprintf(f, "%d;%s;%s;%d\n",
                gt->lista[i].idTecnico,
                gt->lista[i].Nome,
                gt->lista[i].Especialidade,
                gt->lista[i].estado);
    }
    fclose(f);
}

void carregarTecnicos(GestaoTecnicos *gt) {
    FILE *f = fopen("tecnicos.txt", "r");
    int i;
    if (f == NULL) {
        return;
    }
    if (gt->lista != NULL) {
        free(gt->lista);
        gt->lista = NULL;
    }
    if (fscanf(f, "%d\n", &gt->contador) != 1) {
        fclose(f);
        return;
    }
    gt->capacidade = gt->contador;
    gt->lista = (Tecnico *)malloc(gt->capacidade * sizeof(Tecnico));

    if (gt->lista == NULL) {
        fclose(f);
        return;
    }
    for (i = 0; i < gt->contador; i++) {
        fscanf(f, "%d;%[^;];%[^;];%d\n",
               &gt->lista[i].idTecnico,
               gt->lista[i].Nome,
               gt->lista[i].Especialidade,
               (int *)&gt->lista[i].estado);
    }
    fclose(f);
}