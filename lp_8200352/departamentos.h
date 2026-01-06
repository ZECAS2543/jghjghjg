/**
 * @file departamentos.h
 * @brief Definições e protótipos para a gestão de departamentos municipais.
 * * Este módulo permite gerir as entidades que solicitam manutenções, incluindo
 * o registo de responsáveis e contactos de cada serviço do município.
 * * @author Jose Meireles
 * @date 2026-01-06
 */

#ifndef LP_8200352_DEPARTAMENTOS_H
#define LP_8200352_DEPARTAMENTOS_H

#include "comum.h"

/** * @brief Forward declaration da estrutura de gestão de manutenção para evitar dependências cíclicas.
 */
typedef struct GestaoManutencao GestaoManutencao;

/**
 * @struct Departamento
 * @brief Estrutura que representa um departamento ou serviço do município.
 */
typedef struct Departamento {
    int idDepartamento;          /**< Identificador único e sequencial do departamento. */
    char Nome[MAX_NOME];         /**< Nome do serviço (ex: "Proteção Civil"). */
    char Responsavel[MAX_NOME];  /**< Nome do responsável pelo departamento. */
    char Contacto[MAX_TEXTO];    /**< Contacto telefónico ou e-mail. */
    int ativo;                   /**< Flag de estado: 1 para ativo, 0 para inativo (remoção lógica). */
} Departamento;

/**
 * @struct GestaoDepartamentos
 * @brief Estrutura para a gestão dinâmica da lista de departamentos.
 */
typedef struct GestaoDepartamentos {
    Departamento *lista; /**< Ponteiro para o array dinâmico de departamentos. */
    int contador;        /**< Número de departamentos registados no sistema. */
    int capacidade;      /**< Capacidade atual da memória alocada. */
} GestaoDepartamentos;

/* Protótipos das Funções */

/**
 * @brief Lista todos os departamentos marcados como ativos no sistema.
 * @param departamentos Ponteiro para a estrutura de gestão de departamentos.
 */
void lerDepartamento(GestaoDepartamentos *departamentos);

/**
 * @brief Permite a edição dos dados de um departamento (Nome, Responsável, Contacto).
 * @param departamentos Ponteiro para a estrutura de gestão de departamentos.
 */
void atualizarDepartamento(GestaoDepartamentos *departamentos);

/**
 * @brief Inativa um departamento, verificando se existem ordens de manutenção pendentes.
 * * Conforme os requisitos, se houver relações ativas, a entidade é marcada como
 * inativa em vez de ser eliminada fisicamente.
 * * @param departamentos Ponteiro para a gestão de departamentos.
 * @param gm Ponteiro para a gestão de manutenção para verificação de integridade referencial.
 */
void eliminarDepartamento(GestaoDepartamentos *departamentos, GestaoManutencao *gm);

/**
 * @brief Regista um novo departamento no sistema e aloca memória se necessário.
 * @param departamentos Ponteiro para a estrutura de gestão de departamentos.
 */
void criarDepartamento(GestaoDepartamentos *departamentos);

/**
 * @brief Reativa um departamento que tenha sido previamente inativado.
 * @param departamentos Ponteiro para a estrutura de gestão de departamentos.
 */
void reativarDepartamento(GestaoDepartamentos *departamentos);

/**
 * @brief Guarda os dados dos departamentos no ficheiro de persistência (departamentos.txt).
 * @param gd Ponteiro para a estrutura de gestão de departamentos.
 */
void guardarDepartamentos(GestaoDepartamentos *gd);

/**
 * @brief Carrega os dados dos departamentos a partir do ficheiro de persistência no arranque.
 * @param gd Ponteiro para a estrutura de gestão de departamentos.
 */
void carregarDepartamentos(GestaoDepartamentos *gd);

#endif //LP_8200352_DEPARTAMENTOS_H