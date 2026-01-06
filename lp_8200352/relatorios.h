/**
 * @file relatorios.h
 * @brief Definições dos protótipos para a geração de relatórios e análises estatísticas.
 * * Este módulo centraliza todas as funções de extração de dados e geração de métricas,
 * abrangendo desde inventários simples até análises complexas de desempenho e custos,
 * auxiliando na tomada de decisões estratégicas.
 * * @author Jose Meireles
 * @date 2026-01-06
 */

#ifndef LP_8200352_RELATORIOS_H
#define LP_8200352_RELATORIOS_H

#include "ativo.h"
#include "tecnicos.h"
#include "departamentos.h"
#include "manutencao.h"

/** @name Relatórios de Ativos
 * Funções focadas na análise do inventário e estado dos equipamentos.
 * @{ */

/**
 * @brief Exibe o total de ativos operacionais existentes no sistema.
 * @param ga Ponteiro para a gestão de ativos.
 */
void totalAtivos(GestaoAtivos *ga);

/**
 * @brief Apresenta a distribuição quantitativa de ativos por categoria e por estado.
 * @param ga Ponteiro para a gestão de ativos.
 */
void totalAtivosPorEstado(GestaoAtivos *ga);

/**
 * @brief Identifica os ativos com maior recorrência de manutenções corretivas.
 * @param ga Ponteiro para a gestão de ativos.
 * @param gm Ponteiro para a gestão de manutenção.
 */
void ativosMaiorOcurrencia(GestaoAtivos *ga, GestaoManutencao *gm);
/** @} */

/** @name Relatórios de Departamentos
 * Estatísticas sobre os pedidos realizados pelos serviços municipais.
 * @{ */

/**
 * @brief Mostra a quantidade total de departamentos registados e ativos.
 * @param gd Ponteiro para a gestão de departamentos.
 */
void totalDepartamentosRegistados(GestaoDepartamentos *gd);

/**
 * @brief Detalha os pedidos de manutenção e custos totais associados a cada departamento.
 * @param gd Ponteiro para a gestão de departamentos.
 * @param gm Ponteiro para a gestão de manutenção.
 */
void pedidosManutencaoPorDepartamento(GestaoDepartamentos *gd, GestaoManutencao *gm);

/**
 * @brief Analisa os departamentos que mais solicitam intervenções urgentes.
 * @param gd Ponteiro para a gestão de departamentos.
 * @param gm Ponteiro para a gestão de manutenção.
 */
void departamentosMaisIntervencoes(GestaoDepartamentos *gd, GestaoManutencao *gm);
/** @} */

/** @name Relatórios de Manutenção
 * Análise do fluxo de trabalho e eficiência das intervenções.
 * @{ */

/**
 * @brief Lista ordens de manutenção filtradas por estado, prioridade e tipo.
 * @param gm Ponteiro para a gestão de manutenção.
 * @param estProc Estado pretendido para filtragem.
 * @param prioProc Prioridade pretendida para filtragem.
 * @param tipoProc Tipo de manutenção pretendido para filtragem.
 */
void listarOrdensManutencao(GestaoManutencao *gm, EstadoOrdem estProc, Prioridade prioProc, TipoManutencao tipoProc);

/**
 * @brief Calcula o tempo médio de resolução para ordens concluídas.
 * @param gm Ponteiro para a gestão de manutenção.
 */
void tempoMedio(GestaoManutencao *gm);

/**
 * @brief Apresenta uma análise de custos totais segmentada por categoria e departamento.
 * @param gm Ponteiro para a gestão de manutenção.
 * @param ga Ponteiro para a gestão de ativos.
 * @param gd Ponteiro para a gestão de departamentos.
 */
void custosTotais(GestaoManutencao *gm, GestaoAtivos *ga, GestaoDepartamentos *gd);
/** @} */

/** @name Relatórios de Técnicos
 * Monitorização do desempenho e ocupação da equipa técnica.
 * @{ */

/**
 * @brief Lista técnicos filtrando por especialidade e disponibilidade atual.
 * @param gt Ponteiro para a gestão de técnicos.
 * @param especialidadeProc String com a especialidade a procurar.
 * @param estadoProc Estado de disponibilidade pretendido.
 */
void listarTecnicosEspecialidade(GestaoTecnicos *gt, char *especialidadeProc, EstadoTecnico estadoProc);

/**
 * @brief Calcula a taxa de ocupação de cada técnico com base em ordens ativas.
 * @param gt Ponteiro para a gestão de técnicos.
 * @param gm Ponteiro para a gestão de manutenção.
 */
void taxaOcupacao(GestaoTecnicos *gt, GestaoManutencao *gm);

/**
 * @brief Gera um ranking de desempenho baseado em ordens concluídas e tempo médio.
 * @param gt Ponteiro para a gestão de técnicos.
 * @param gm Ponteiro para a gestão de manutenção.
 */
void rankingDesempenho(GestaoTecnicos *gt, GestaoManutencao *gm);
/** @} */

/** @name Relatórios Estratégicos (Adicionais)
 * Relatórios complexos propostos para otimização de processos[cite: 86, 87].
 * @{ */

/**
 * @brief Identifica ativos operacionais que não tiveram revisões preventivas recentemente.
 * @param ga Ponteiro para a gestão de ativos.
 * @param gm Ponteiro para a gestão de manutenção.
 */
void ativosSemRevisao(GestaoAtivos *ga, GestaoManutencao *gm);

/**
 * @brief Calcula o custo médio de manutenção por categoria de ativo.
 * @param ga Ponteiro para a gestão de ativos.
 * @param gm Ponteiro para a gestão de manutenção.
 */
void custoMedioPorCategoria(GestaoAtivos *ga, GestaoManutencao *gm);

/**
 * @brief Permite visualizar o histórico de alterações (log) de um ativo específico.
 */
void auditoriaAtivo();

/**
 * @brief Analisa a percentagem e frequência de falhas por categoria de ativo.
 * @param ga Ponteiro para a gestão de ativos.
 */
void frequenciaFalhasPorCategoria(GestaoAtivos *ga);
/** @} */

#endif //LP_8200352_RELATORIOS_H