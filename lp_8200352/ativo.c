#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ativo.h"
#include "manutencao.h"
#include "comum.h"

void criarAtivo(GestaoAtivos *ga) {
    int novaCapacidade;
    int novoID;
    Ativo *temp;

    if (ga->contador == ga->capacidade) {
        if (ga->capacidade == 0) {
            novaCapacidade = 1;
        } else {
            novaCapacidade = ga->capacidade * 2;
        }

        temp = (Ativo *)realloc(ga->lista, novaCapacidade * sizeof(Ativo));

        if (temp == NULL) {
            escreverLog("Falha de memoria ao tentar inserir ativo.");
            return;
        }
        ga->lista = temp;
        ga->capacidade = novaCapacidade;
    }

    novoID = ga->contador + 1;
    ga->lista[ga->contador].idAtivo = novoID;

    printf("\n Criar Ativo (ID: %d) \n", novoID);

    printf("Nome/Designacao: ");
    scanf(" %49[^\n]", ga->lista[ga->contador].Nome);
    while (getchar() != '\n');

    printf("Categoria (0-Viatura, 1-Informatica, 2-Mobiliario, 3-Ferramenta): ");
    if (scanf("%d", (int *)&ga->lista[ga->contador].categoria) != 1) {
        while (getchar() != '\n');
    } else {
        while (getchar() != '\n');
    }

    printf("Localizacao: ");
    scanf(" %49[^\n]", ga->lista[ga->contador].localizacao);
    while (getchar() != '\n');

    do {
        printf("Data de Aquisicao:\n");
        printf("  Dia: ");
        if (scanf("%d", &ga->lista[ga->contador].data.dia) != 1) { while (getchar() != '\n'); }

        printf("  Mes: ");
        if (scanf("%d", &ga->lista[ga->contador].data.mes) != 1) { while (getchar() != '\n'); }

        printf("  Ano: ");
        if (scanf("%d", &ga->lista[ga->contador].data.ano) != 1) { while (getchar() != '\n'); }
        while (getchar() != '\n');

        if (validarData(ga->lista[ga->contador].data) == 0) {
            printf("Data invalida (%02d/%02d/%d). Tente novamente.\n",
                   ga->lista[ga->contador].data.dia,
                   ga->lista[ga->contador].data.mes,
                   ga->lista[ga->contador].data.ano);
        }
    } while (validarData(ga->lista[ga->contador].data) == 0);

    ga->lista[ga->contador].estado = OPERACIONAL;

    ga->contador++;
    printf("Ativo registado com sucesso.\n");
    escreverLog("Novo ativo criado no sistema.");
}

void lerAtivo(GestaoAtivos *ativos) {
    int i;

    printf("\n Lista de Ativos \n");

    if (ativos->contador == 0) {
        printf("Nao existem ativos no sistema.\n");
        return;
    }

    for (i = 0; i < ativos->contador; i++) {
        if (ativos->lista[i].estado != ATIVO_INATIVO) {
            printf("ID: %-3d | Nome: %-15s | Categoria: %d | Local: %-10s | Data: %02d/%02d/%d | Estado: %d\n",
                   ativos->lista[i].idAtivo,
                   ativos->lista[i].Nome,
                   ativos->lista[i].categoria,
                   ativos->lista[i].localizacao,
                   ativos->lista[i].data.dia,
                   ativos->lista[i].data.mes,
                   ativos->lista[i].data.ano,
                   ativos->lista[i].estado);
        }
    }
}

void atualizarAtivo(GestaoAtivos *ativos) {
    int idProcurado, i, encontrado, novoEstado, novaCategoria, dataValida, estadoAnterior;
    char *nomesEstados[] = {"Operacional", "Em Manutencao", "Abatido", "Inativo"};

    encontrado = 0;
    dataValida = 0;

    printf("\nInsira o ID do Ativo que quer atualizar: ");
    if (scanf("%d", &idProcurado) != 1) {
        printf("Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < ativos->contador; i++) {
        if (ativos->lista[i].idAtivo == idProcurado && ativos->lista[i].estado != ATIVO_INATIVO) {
            encontrado = 1;
            estadoAnterior = ativos->lista[i].estado;

            printf("\n A Atualizar Ativo ID: %d ---\n", idProcurado);

            do {
                printf("Novo Nome (Atual: %s): ", ativos->lista[i].Nome);
                scanf(" %49[^\n]", ativos->lista[i].Nome);
                while (getchar() != '\n');
                if (strlen(ativos->lista[i].Nome) == 0) {
                    printf("O nome e obrigatorio.\n");
                }
            } while (strlen(ativos->lista[i].Nome) == 0);

            do {
                printf("Nova Categoria (0-Viatura, 1-Informatica, 2-Mobiliario, 3-Ferramenta) [Atual: %d]: ", ativos->lista[i].categoria);
                if (scanf("%d", &novaCategoria) != 1 || novaCategoria < 0 || novaCategoria > 3) {
                    printf("Escolha um numero entre 0 e 3.\n");
                    while (getchar() != '\n');
                    novaCategoria = -1;
                } else {
                    while (getchar() != '\n');
                }
            } while (novaCategoria < 0 || novaCategoria > 3);
            ativos->lista[i].categoria = (CategoriaAtivo)novaCategoria;

            do {
                printf("Nova Localizacao (Atual: %s): ", ativos->lista[i].localizacao);
                scanf(" %49[^\n]", ativos->lista[i].localizacao);
                while (getchar() != '\n');
                if (strlen(ativos->lista[i].localizacao) == 0) {
                    printf("A localizacao e obrigatoria.\n");
                }
            } while (strlen(ativos->lista[i].localizacao) == 0);

            do {
                printf("Nova Data [Atual: %02d/%02d/%d]:\n", ativos->lista[i].data.dia, ativos->lista[i].data.mes, ativos->lista[i].data.ano);
                printf(" Novo Dia: "); scanf("%d", &ativos->lista[i].data.dia);
                printf(" Novo Mes: "); scanf("%d", &ativos->lista[i].data.mes);
                printf(" Novo Ano: "); scanf("%d", &ativos->lista[i].data.ano);
                while (getchar() != '\n');

                if (validarData(ativos->lista[i].data) == 1) {
                    dataValida = 1;
                } else {
                    printf("Data invalida. Tente novamente.\n");
                }
            } while (dataValida == 0);

            do {
                printf("Novo Estado (0-Operacional, 1-Em Manutencao, 2-Abatido) [Atual: %d]: ", ativos->lista[i].estado);
                if (scanf("%d", &novoEstado) != 1 || novoEstado < 0 || novoEstado > 2) {
                    printf("Escolha entre 0 e 2.\n");
                    while (getchar() != '\n');
                    novoEstado = -1;
                } else {
                    while (getchar() != '\n');
                }
            } while (novoEstado < 0 || novoEstado > 2);

            if (estadoAnterior != novoEstado) {
                escreverLogAuditoria("ATIVO", ativos->lista[i].idAtivo, nomesEstados[estadoAnterior], nomesEstados[novoEstado]);
                ativos->lista[i].estado = (EstadoAtivo)novoEstado;
            }

            printf("Dados atualizados com sucesso.\n");
            escreverLog("Dados de um ativo foram atualizados.");
            break;
        }
    }

    if (encontrado == 0) {
        printf("Ativo com ID %d nao encontrado ou esta inativo.\n", idProcurado);
    }
}

void eliminarAtivo(GestaoAtivos *ativos, GestaoManutencao *gm) {
    int i, j, idProcurado, encontrado, ativoComManutencao;
    encontrado = 0;
    ativoComManutencao = 0;

    printf("\nInsira o ID do Ativo a eliminar: ");
    if (scanf("%d", &idProcurado) != 1) {
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < ativos->contador; i++) {
        if (ativos->lista[i].idAtivo == idProcurado) {
            encontrado = 1;

            for (j = 0; j < gm->contador; j++) {
                if (gm->lista[j].idAtivo == idProcurado && (gm->lista[j].estado != CONCLUIDA && gm->lista[j].estado != CANCELADA)) {
                    ativoComManutencao = 1;
                    break;
                }
            }

            if (ativoComManutencao == 1) {
                printf("O Ativo tem manutencoes abertas e nao pode ser eliminado.\n");
            } else {
                ativos->lista[i].estado = ATIVO_INATIVO;
                printf("Ativo marcado como inativo.\n");
                escreverLog("Um ativo foi marcado como inativo.");
            }
            break;
        }
    }

    if (encontrado == 0) {
        printf("Ativo nao encontrado.\n");
    }
}

void reativarAtivo(GestaoAtivos *ativos) {
    int idProcurado, i, encontrado;
    encontrado = 0;

    printf("\n Reativar Ativo \n");
    printf("ID do Ativo: ");
    if (scanf("%d", &idProcurado) != 1) {
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < ativos->contador; i++) {
        if (ativos->lista[i].idAtivo == idProcurado && ativos->lista[i].estado == ATIVO_INATIVO) {
            ativos->lista[i].estado = OPERACIONAL;
            printf("Ativo ID %d reativado.\n", idProcurado);
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) {
        printf("Ativo nao encontrado ou ja esta ativo.\n");
    }
}

void guardarAtivos(GestaoAtivos *ga) {
    FILE *f;
    int i;

    f = fopen("ativos.txt", "w");
    if (f == NULL) {
        return;
    }

    fprintf(f, "%d\n", ga->contador);
    for (i = 0; i < ga->contador; i++) {
        fprintf(f, "%d;%s;%d;%s;%d;%d;%d;%d\n",
                ga->lista[i].idAtivo,
                ga->lista[i].Nome,
                ga->lista[i].categoria,
                ga->lista[i].localizacao,
                ga->lista[i].estado,
                ga->lista[i].data.dia,
                ga->lista[i].data.mes,
                ga->lista[i].data.ano);
    }
    fclose(f);
    escreverLog("Ativos guardados em ativos.txt");
}

void carregarAtivos(GestaoAtivos *ga) {
    FILE *f;
    int i;

    f = fopen("ativos.txt", "r");
    if (f == NULL) {
        return;
    }

    if (ga->lista != NULL) {
        free(ga->lista);
        ga->lista = NULL;
    }

    if (fscanf(f, "%d\n", &ga->contador) != 1) {
        fclose(f);
        return;
    }

    ga->capacidade = ga->contador;
    ga->lista = (Ativo *)malloc(ga->capacidade * sizeof(Ativo));
    if (ga->lista == NULL) {
        fclose(f);
        return;
    }

    for (i = 0; i < ga->contador; i++) {
        fscanf(f, "%d;%[^;];%d;%[^;];%d;%d;%d;%d\n",
               &ga->lista[i].idAtivo,
               ga->lista[i].Nome,
               (int *)&ga->lista[i].categoria,
               ga->lista[i].localizacao,
               (int *)&ga->lista[i].estado,
               &ga->lista[i].data.dia,
               &ga->lista[i].data.mes,
               &ga->lista[i].data.ano);
    }
    fclose(f);
}