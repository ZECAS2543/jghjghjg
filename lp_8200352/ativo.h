/**
 * @file ativo.h
 * @brief Definições e protótipos para a gestão de ativos municipais.
 * * Este ficheiro contém as estruturas de dados para representar ativos (equipamentos),
 * bem como as funções necessárias para a sua manipulação e persistência.
 * * @author José Meireles
 * @date 2026-01-06
 */

#ifndef LP_8200352_ATIVO_H
#define LP_8200352_ATIVO_H

#include "comum.h"

/** * @brief Forward declaration da estrutura de gestão de manutenção.
 */
typedef struct GestaoManutencao GestaoManutencao;

/**
 * @enum CategoriaAtivo
 * @brief Categorias possíveis para um ativo municipal.
 */
typedef enum {
    VIATURA,            /**< Veículos municipais. */
    EQ_INFORMATICO,     /**< Computadores, impressoras e periféricos. */
    MOBILIARIO_URBANO,  /**< Bancos, paragens de autocarro, etc. */
    FERRAMENTA          /**< Equipamento manual ou mecânico. */
} CategoriaAtivo;

/**
 * @enum EstadoAtivo
 * @brief Estados operacionais de um ativo.
 */
typedef enum {
    OPERACIONAL,        /**< Ativo pronto a ser utilizado. */
    EM_MANUTENCAO,      /**< Ativo com ordem de manutenção em curso. */
    ABATIDO,            /**< Ativo fora de serviço permanentemente. */
    ATIVO_INATIVO       /**< Ativo removido logicamente (inativado). */
} EstadoAtivo;

/**
 * @struct Ativo
 * @brief Estrutura que representa um ativo municipal.
 */
typedef struct Ativo {
    int idAtivo;                /**< Identificador único e sequencial. */
    char Nome[MAX_TEXTO];       /**< Designação do ativo. */
    CategoriaAtivo categoria;   /**< Categoria à qual pertence. */
    char localizacao[MAX_TEXTO];/**< Localização física ou departamento depositário. */
    EstadoAtivo estado;         /**< Estado operacional atual. */
    Data data;                  /**< Data de aquisição do ativo. */
} Ativo;

/**
 * @struct GestaoAtivos
 * @brief Estrutura para gestão de uma lista dinâmica de ativos.
 */
typedef struct GestaoAtivos {
    Ativo *lista;       /**< Ponteiro para o array dinâmico de ativos. */
    int contador;       /**< Número atual de ativos registados. */
    int capacidade;     /**< Capacidade total alocada em memória. */
} GestaoAtivos;

/**
 * @brief Lista os ativos ativos no sistema.
 * @param ativos Ponteiro para a estrutura de gestão de ativos.
 */
void lerAtivo(GestaoAtivos *ativos);

/**
 * @brief Permite atualizar os dados de um ativo existente.
 * @param ativos Ponteiro para a estrutura de gestão de ativos.
 */
void atualizarAtivo(GestaoAtivos *ativos);

/**
 * @brief Inativa um ativo se não houver manutenções pendentes.
 * @param ativos Ponteiro para a gestão de ativos.
 * @param gm Ponteiro para a gestão de manutenção .
 */
void eliminarAtivo(GestaoAtivos *ativos, GestaoManutencao *gm);

/**
 * @brief Cria um novo ativo e adiciona-o à lista dinâmica.
 * @param ativos Ponteiro para a estrutura de gestão de ativos.
 */
void criarAtivo(GestaoAtivos *ativos);

/**
 * @brief Reativa um ativo que se encontrava inativo.
 * @param ativos Ponteiro para a estrutura de gestão de ativos.
 */
void reativarAtivo(GestaoAtivos *ativos);

/**
 * @brief Guarda a lista de ativos no ficheiro de persistência.
 * @param ga Ponteiro para a estrutura de gestão de ativos.
 */
void guardarAtivos(GestaoAtivos *ga);

/**
 * @brief Carrega os ativos a partir do ficheiro de persistência.
 * @param ga Ponteiro para a estrutura de gestão de ativos.
 */
void carregarAtivos(GestaoAtivos *ga);

#endif //LP_8200352_ATIVO_H