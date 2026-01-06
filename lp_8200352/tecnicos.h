/**
 * @file tecnicos.h
 * @brief Definições e protótipos para a gestão da equipa técnica.
 * * Este módulo contém as estruturas para representar os técnicos do município,
 * permitindo gerir o seu estado de ocupação, especialidades e a persistência
 * dos seus dados no sistema.
 * * @author Jose Meireles
 * @date 2026-01-06
 */

#ifndef LP_8200352_TECNICOS_H
#define LP_8200352_TECNICOS_H

#include "comum.h"

/** * @brief Forward declaration da estrutura de gestão de manutenção.
 */
typedef struct GestaoManutencao GestaoManutencao;

/**
 * @enum EstadoTecnico
 * @brief Estados de disponibilidade possíveis para um técnico.
 */
typedef enum {
    DISPONIVEL,      /**< Técnico livre para novas atribuições. */
    OCUPADO,         /**< Técnico atualmente alocado a uma manutenção em execução. */
    TECNICO_INATIVO  /**< Técnico removido logicamente do sistema. */
} EstadoTecnico;

/**
 * @struct Tecnico
 * @brief Estrutura que representa um técnico da equipa municipal.
 */
typedef struct Tecnico {
    int idTecnico;              /**< Identificador único e sequencial. */
    char Nome[MAX_NOME];        /**< Nome completo do técnico. */
    char Especialidade[MAX_TEXTO]; /**< Área de especialidade (ex: Mecânico, Eletricista). */
    EstadoTecnico estado;       /**< Estado de disponibilidade atual. */
} Tecnico;

/**
 * @struct GestaoTecnicos
 * @brief Estrutura para gestão da lista dinâmica de técnicos.
 */
typedef struct GestaoTecnicos {
    Tecnico *lista;     /**< Ponteiro para o array dinâmico de técnicos. */
    int contador;       /**< Número de técnicos registados. */
    int capacidade;     /**< Capacidade total de memória alocada. */
} GestaoTecnicos;


/**
 * @brief Apresenta a lista de técnicos registados no sistema.
 * @param gestao Ponteiro para a estrutura de gestão de técnicos.
 */
void lerTecnicos(GestaoTecnicos *gestao);

/**
 * @brief Permite editar os dados (nome e especialidade) de um técnico existente.
 * @param tecnicos Ponteiro para a estrutura de gestão de técnicos.
 */
void atualizarTecnicos(GestaoTecnicos *tecnicos);

/**
 * @brief Inativa um técnico se não houver ordens de manutenção pendentes sob a sua responsabilidade.
 * * De acordo com as regras de integridade, um técnico com trabalhos em curso não
 * pode ser removido[cite: 118].
 * * @param tecnicos Ponteiro para a gestão de técnicos.
 * @param gm Ponteiro para a gestão de manutenção para verificação de dependências.
 */
void eliminarTecnicos(GestaoTecnicos *tecnicos, GestaoManutencao *gm);

/**
 * @brief Regista um novo técnico no sistema e aloca memória dinamicamente se necessário.
 * @param tecnicos Ponteiro para a estrutura de gestão de técnicos.
 */
void criarTecnicos(GestaoTecnicos *tecnicos);

/**
 * @brief Reativa um técnico que tenha sido previamente marcado como inativo.
 * @param tecnicos Ponteiro para a estrutura de gestão de técnicos.
 */
void reativarTecnico(GestaoTecnicos *tecnicos);

/**
 * @brief Guarda os dados dos técnicos no ficheiro "tecnicos.txt".
 * @param gt Ponteiro para a estrutura de gestão de técnicos.
 */
void guardarTecnicos(GestaoTecnicos *gt);

/**
 * @brief Carrega os dados dos técnicos a partir do ficheiro de persistência no arranque da aplicação.
 * @param gt Ponteiro para a estrutura de gestão de técnicos.
 */
void carregarTecnicos(GestaoTecnicos *gt);

#endif //LP_8200352_TECNICOS_H