#include <stdio.h>
#include <string.h>
#include "manutencao.h"
#include "comum.h"
#include <stdlib.h>
#include "ativo.h"
#include "departamentos.h"
#include "tecnicos.h"

void criarManutencao(GestaoManutencao *gm, GestaoAtivos *ga, GestaoDepartamentos *gd, GestaoTecnicos *gt) {
    int novaCapacidade;
    int idA, idD, i, encontrado;
    int dataOk;
    int n;
    char opcao;
    Manutencao *temp;
    Material *tempMat;
    dataOk = 0;

    if (gm->contador == gm->capacidade) {
        if (gm->capacidade == 0) {
            novaCapacidade = 1;
        } else {
            novaCapacidade = gm->capacidade * 2;
        }

        temp = (Manutencao *)realloc(gm->lista, novaCapacidade * sizeof(Manutencao));
        if (temp == NULL) {
            printf(" Nao foi possivel alocar memoria para a nova ordem.\n");
            return;
        }
        gm->lista = temp;
        gm->capacidade = novaCapacidade;
    }

    printf("\n Nova Ordem de Manutencao ");

    do {
        encontrado = 0;
        printf("ID do Ativo: ");
        if (scanf("%d", &idA) != 1) {
            printf("Por favor, digite um numero valido.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        for (i = 0; i < ga->contador; i++) {
            if (ga->lista[i].idAtivo == idA && ga->lista[i].estado != ATIVO_INATIVO) {
                encontrado = 1;
                break;
            }
        }

        if (encontrado == 0) {
            printf(" Ativo invalido ou ja se encontra inativo.\n");
        }
    } while (encontrado == 0);

    do {
        encontrado = 0;
        printf("ID do Departamento: ");

        if (scanf("%d", &idD) != 1) {
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
        }

        for (i = 0; i < gd->contador; i++) {
            if (gd->lista[i].idDepartamento == idD && gd->lista[i].ativo == 1) {
                encontrado = 1;
                break;
            }
        }

        if (encontrado == 0) {
            printf("Departamento invalido ou inativo.\n");
        }
    } while (encontrado == 0);

    gm->lista[gm->contador].idOrdem = gm->contador + 1;
    gm->lista[gm->contador].idAtivo = idA;
    gm->lista[gm->contador].idDepartamento = idD;
    gm->lista[gm->contador].idTecnico = 0;

    printf("Descricao do Problema: ");
    scanf(" %199[^\n]", gm->lista[gm->contador].descricao);
    while (getchar() != '\n');

    printf("Prioridade (0-Baixa, 1-Normal, 2-Urgente): ");
    scanf("%d", (int *)&gm->lista[gm->contador].prioridade);
    while (getchar() != '\n');

    printf("Tipo (0-Preventiva, 1-Corretiva): ");
    scanf("%d", (int *)&gm->lista[gm->contador].tipo);
    while (getchar() != '\n');

    gm->lista[gm->contador].dataConclusao.dia = 0;
    gm->lista[gm->contador].dataConclusao.mes = 0;
    gm->lista[gm->contador].dataConclusao.ano = 0;

    do {
        printf("Data do Pedido:\n");
        printf("  Dia: ");
        if (scanf("%d", &gm->lista[gm->contador].dataPedido.dia) != 1) {
            while (getchar() != '\n');
        }

        printf("  Mes: ");
        if (scanf("%d", &gm->lista[gm->contador].dataPedido.mes) != 1) {
            while (getchar() != '\n');
        }

        printf("  Ano: ");
        if (scanf("%d", &gm->lista[gm->contador].dataPedido.ano) != 1) {
            while (getchar() != '\n');
        }
        while (getchar() != '\n');

        if (validarData(gm->lista[gm->contador].dataPedido) == 1) {
            dataOk = 1;
        } else {
            printf("Data invalida ou inexistente. Tente novamente.\n");
        }
    } while (dataOk == 0);

    gm->lista[gm->contador].estado = PENDENTE;
    gm->lista[gm->contador].numMateriais = 0;
    gm->lista[gm->contador].materiais = NULL;

    do {
        printf("\nDeseja adicionar um material? (S/N): ");
        scanf(" %c", &opcao);
        while (getchar() != '\n');

        if (opcao == 'S' || opcao == 's') {
            n = gm->lista[gm->contador].numMateriais;
            tempMat = (Material *)realloc(gm->lista[gm->contador].materiais, (n + 1) * sizeof(Material));

            if (tempMat == NULL) {
                printf(" Nao foi possivel alocar memoria para o material.\n");
                break;
            }

            gm->lista[gm->contador].materiais = tempMat;

            printf("Nome do material: ");
            scanf(" %49[^\n]", gm->lista[gm->contador].materiais[n].item);
            while (getchar() != '\n');

            printf("Quantidade: ");
            scanf("%d", &gm->lista[gm->contador].materiais[n].quantidade);
            while (getchar() != '\n');

            printf("Custo Unitario: ");
            scanf("%f", &gm->lista[gm->contador].materiais[n].custoUnitario);
            while (getchar() != '\n');

            gm->lista[gm->contador].numMateriais++;
            printf(" Material adicionado.\n");
        }
    } while (opcao == 'S' || opcao == 's');

    gm->contador++;
    printf(" Ordem ID %d criada com sucesso.\n", gm->contador);
    escreverLog(" Nova ordem de manutencao aberta.");
}

void lerManutencao(GestaoManutencao *gm) {
    int i, j;
    char *nomesEstados[] = {"PENDENTE", "EM EXECUCAO", "CONCLUIDA", "CANCELADA"};

    printf("\n   Listagem de Manutencoes  \n");

    if (gm->contador == 0) {
        printf("Nao existem manutencoes no sistema.\n");
        return;
    }

    for (i = 0; i < gm->contador; i++) {
        printf("\nID ordem: %d ", gm->lista[i].idOrdem);
        printf("\nID ativo: %d", gm->lista[i].idAtivo);
        printf("\nId departamento: %d ", gm->lista[i].idDepartamento);
        printf("\nID tecnico: %d ", gm->lista[i].idTecnico);
        printf("| Data do pedido: %02d/%02d/%d ",
               gm->lista[i].dataPedido.dia,
               gm->lista[i].dataPedido.mes,
               gm->lista[i].dataPedido.ano);

        if (gm->lista[i].estado == CONCLUIDA) {
            printf("| Conclusao: %02d/%02d/%d \n",
                   gm->lista[i].dataConclusao.dia,
                   gm->lista[i].dataConclusao.mes,
                   gm->lista[i].dataConclusao.ano);
        } else {
            printf("| Conclusao: --- %s ---\n", nomesEstados[gm->lista[i].estado]);
        }

        printf("Prioridade: %d ", gm->lista[i].prioridade);
        printf("\nTipo: %d | ", gm->lista[i].tipo);
        printf("Estado: %s | ", nomesEstados[gm->lista[i].estado]);
        printf("Descricao: %s\n", gm->lista[i].descricao);

        if (gm->lista[i].numMateriais > 0 && gm->lista[i].materiais != NULL) {
            printf("Materiais Utilizados:\n");
            for (j = 0; j < gm->lista[i].numMateriais; j++) {
                printf("  - %s | Qtd: %d | Custo: %.2f\n",
                       gm->lista[i].materiais[j].item,
                       gm->lista[i].materiais[j].quantidade,
                       gm->lista[i].materiais[j].custoUnitario);
            }
        } else if (gm->lista[i].numMateriais > 0 && gm->lista[i].materiais == NULL) {
            printf("\n Materiais registados mas nao carregados.");
        }
    }
}

void atualizarManutencao(GestaoManutencao *gm, GestaoAtivos *ga, GestaoDepartamentos *gd, GestaoTecnicos *gt) {
    int idProcurado, i, j, encontrado, novaPrio, novoEst, novoTecnico, tecnicoValido, estadoAnterior, escolha, n_mat, dataValida;
    char *nomesEstados[] = {"Pendente", "Em Execucao", "Concluida", "Cancelada"};
    char opcaoMat;
    Material *tempMat;

    encontrado = 0;

    printf("\n    Atualizar Ordem de Manutencao ");
    printf("\nInsira o ID da Ordem: ");
    if (scanf("%d", &idProcurado) != 1) {
        printf(" Entrada invalida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < gm->contador; i++) {
        if (gm->lista[i].idOrdem == idProcurado) {
            encontrado = 1;
            estadoAnterior = gm->lista[i].estado;

            if (gm->lista[i].estado == CANCELADA) {
                printf("Nao e possivel editar uma ordem ja cancelada.\n");
                return;
            }

            printf("\n  A Editar Ordem ID %d ", idProcurado);

            printf("\nNova Descricao (Atual: %s): ", gm->lista[i].descricao);
            scanf(" %199[^\n]", gm->lista[i].descricao);
            while (getchar() != '\n');

            do {
                printf("Nova Prioridade (0-Baixa, 1-Normal, 2-Urgente) [Atual: %d]: ", gm->lista[i].prioridade);
                if (scanf("%d", &novaPrio) != 1) {
                    while (getchar() != '\n');
                    novaPrio = -1;
                }
            } while (novaPrio < 0 || novaPrio > 2);
            gm->lista[i].prioridade = (Prioridade)novaPrio;

            do {
                tecnicoValido = 0;
                printf("ID do Tecnico Responsavel (Atual: %d): ", gm->lista[i].idTecnico);
                if (scanf("%d", &novoTecnico) != 1) {
                    while (getchar() != '\n');
                    continue;
                }
                for (j = 0; j < gt->contador; j++) {
                    if (gt->lista[j].idTecnico == novoTecnico && gt->lista[j].estado != TECNICO_INATIVO) {
                        tecnicoValido = 1;
                        break;
                    }
                }
                if (tecnicoValido == 0) {
                    printf(" Tecnico inexistente ou inativo!\n");
                }
            } while (tecnicoValido == 0);
            gm->lista[i].idTecnico = novoTecnico;

            if (gm->lista[i].numMateriais > 0) {
                printf("\n   Materiais Atuais");
                for (j = 0; j < gm->lista[i].numMateriais; j++) {
                    printf("\n%d. %s (Qtd: %d, Preco: %.2f)", j + 1, gm->lista[i].materiais[j].item, gm->lista[i].materiais[j].quantidade, gm->lista[i].materiais[j].custoUnitario);
                }

                printf("\nDeseja editar algum material existente? (S/N): ");
                scanf(" %c", &opcaoMat);
                while (getchar() != '\n');

                if (opcaoMat == 'S' || opcaoMat == 's') {
                    printf("Qual o numero do material a editar (1 a %d): ", gm->lista[i].numMateriais);
                    scanf("%d", &escolha);
                    while (getchar() != '\n');
                    if (escolha >= 1 && escolha <= gm->lista[i].numMateriais) {
                        j = escolha - 1;
                        printf("Novo Nome: "); scanf(" %49[^\n]", gm->lista[i].materiais[j].item);
                        while (getchar() != '\n');
                        printf("Nova Qtd: "); scanf("%d", &gm->lista[i].materiais[j].quantidade);
                        while (getchar() != '\n');
                        printf("Novo Custo: "); scanf("%f", &gm->lista[i].materiais[j].custoUnitario);
                        while (getchar() != '\n');
                    }
                }
            }

            printf("\nDeseja adicionar mais materiais a esta ordem? (S/N): ");
            scanf(" %c", &opcaoMat);
            while (getchar() != '\n');

            while (opcaoMat == 'S' || opcaoMat == 's') {
                n_mat = gm->lista[i].numMateriais;
                tempMat = (Material *)realloc(gm->lista[i].materiais, (n_mat + 1) * sizeof(Material));
                if (tempMat != NULL) {
                    gm->lista[i].materiais = tempMat;
                    printf("Nome do Item: "); scanf(" %49[^\n]", gm->lista[i].materiais[n_mat].item);
                    while (getchar() != '\n');
                    printf("Quantidade: "); scanf("%d", &gm->lista[i].materiais[n_mat].quantidade);
                    while (getchar() != '\n');
                    printf("Custo Unitario: "); scanf("%f", &gm->lista[i].materiais[n_mat].custoUnitario);
                    while (getchar() != '\n');
                    gm->lista[i].numMateriais++;
                    printf("Material adicionado!");
                }
                printf("\nAdicionar outro? (S/N): ");
                scanf(" %c", &opcaoMat);
                while (getchar() != '\n');
            }

            do {
                printf("\nNovo Estado (0-Pendente, 1-Em Execucao, 2-Concluida, 3-Cancelada) [Atual: %d]: ", gm->lista[i].estado);
                if (scanf("%d", &novoEst) != 1) {
                    while (getchar() != '\n');
                    novoEst = -1;
                }
            } while (novoEst < 0 || novoEst > 3);

            if (estadoAnterior != novoEst) {
                escreverLogAuditoria("ORDEM_MANUT", idProcurado, nomesEstados[estadoAnterior], nomesEstados[novoEst]);
                gm->lista[i].estado = (EstadoOrdem)novoEst;
            }

            if (gm->lista[i].estado == CONCLUIDA) {
                dataValida = 0;
                do {
                    printf("Data de Conclusao (dia mes ano): ");
                    if (scanf("%d %d %d", &gm->lista[i].dataConclusao.dia, &gm->lista[i].dataConclusao.mes, &gm->lista[i].dataConclusao.ano) != 3) {
                        while (getchar() != '\n');
                    }
                    while (getchar() != '\n');

                    if (validarData(gm->lista[i].dataConclusao) == 1 &&
                        dataParaDias(gm->lista[i].dataConclusao) >= dataParaDias(gm->lista[i].dataPedido)) {
                        dataValida = 1;
                    } else {
                        printf(" Data invalida ou anterior ao pedido!\n");
                    }
                } while (dataValida == 0);
            }

            guardarManutencoes(gm);
            printf(" Ordem atualizada com sucesso.\n");
            break;
        }
    }
    if (encontrado == 0) {
        printf("Ordem ID %d nao encontrada.\n", idProcurado);
    }
}

void eliminarManutencao(GestaoManutencao *gm) {
    int idProcurado, i, encontrado;
    encontrado = 0;

    printf("\n   Cancelar Ordem de Manutencao");
    printf("\n Insira o ID da Ordem: ");
    scanf("%d", &idProcurado);
    while (getchar() != '\n');

    for (i = 0; i < gm->contador; i++) {
        if (gm->lista[i].idOrdem == idProcurado) {
            encontrado = 1;
            gm->lista[i].estado = CANCELADA;
            escreverLogAuditoria("ORDEM_MANUT", idProcurado, "ABERTA", "CANCELADA");
            printf(" A Ordem de ID %d foi marcada como cancelada.\n", idProcurado);
            escreverLog(" Uma ordem de manutencao foi cancelada.");
            break;
        }
    }

    if (encontrado == 0) {
        printf("Ordem de ID %d nao encontrada.\n", idProcurado);
    }
}

void guardarManutencoes(GestaoManutencao *gm) {
    FILE *f = fopen("manutencoes.txt", "w");
    int i, j;
    if (f == NULL) {
        return;
    }

    fprintf(f, "%d\n", gm->contador);
    for (i = 0; i < gm->contador; i++) {
        fprintf(f, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%s;%d\n",
                gm->lista[i].idOrdem, gm->lista[i].idAtivo, gm->lista[i].idDepartamento, gm->lista[i].idTecnico,
                gm->lista[i].dataPedido.dia, gm->lista[i].dataPedido.mes, gm->lista[i].dataPedido.ano,
                gm->lista[i].dataConclusao.dia, gm->lista[i].dataConclusao.mes, gm->lista[i].dataConclusao.ano,
                gm->lista[i].prioridade, gm->lista[i].tipo, gm->lista[i].descricao,
                gm->lista[i].numMateriais);

        for (j = 0; j < gm->lista[i].numMateriais; j++) {
            fprintf(f, "%s;%d;%.2f\n",
                    gm->lista[i].materiais[j].item,
                    gm->lista[i].materiais[j].quantidade,
                    gm->lista[i].materiais[j].custoUnitario);
        }
    }
    fclose(f);
}

void carregarManutencoes(GestaoManutencao *gm) {
    FILE *f = fopen("manutencoes.txt", "r");
    int i, j;
    if (f == NULL) {
        return;
    }

    if (gm->lista != NULL) {
        for (i = 0; i < gm->contador; i++) {
            if (gm->lista[i].materiais != NULL) {
                free(gm->lista[i].materiais);
            }
        }
        free(gm->lista);
        gm->lista = NULL;
    }

    if (fscanf(f, "%d\n", &gm->contador) != 1) {
        fclose(f);
        return;
    }

    gm->capacidade = gm->contador;
    gm->lista = (Manutencao *)malloc(gm->capacidade * sizeof(Manutencao));
    if (gm->lista == NULL) {
        fclose(f);
        return;
    }

    for (i = 0; i < gm->contador; i++) {
        fscanf(f, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%[^;];%d\n",
               &gm->lista[i].idOrdem, &gm->lista[i].idAtivo, &gm->lista[i].idDepartamento, &gm->lista[i].idTecnico,
               &gm->lista[i].dataPedido.dia, &gm->lista[i].dataPedido.mes, &gm->lista[i].dataPedido.ano,
               &gm->lista[i].dataConclusao.dia, &gm->lista[i].dataConclusao.mes, &gm->lista[i].dataConclusao.ano,
               (int *)&gm->lista[i].prioridade, (int *)&gm->lista[i].tipo, gm->lista[i].descricao,
               &gm->lista[i].numMateriais);

        if (gm->lista[i].numMateriais > 0) {
            gm->lista[i].materiais = (Material *)malloc(gm->lista[i].numMateriais * sizeof(Material));
            if (gm->lista[i].materiais != NULL) {
                for (j = 0; j < gm->lista[i].numMateriais; j++) {
                    fscanf(f, "%[^;];%d;%f\n",
                           gm->lista[i].materiais[j].item,
                           &gm->lista[i].materiais[j].quantidade,
                           &gm->lista[i].materiais[j].custoUnitario);
                }
            }
        } else {
            gm->lista[i].materiais = NULL;
        }
    }
    fclose(f);
}