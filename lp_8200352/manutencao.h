/**
 * @file manutencao.h
 * @brief Definições e protótipos para a gestão de ordens de manutenção.
 * * Este ficheiro contém o núcleo do sistema, gerindo o ciclo de vida das
 * intervenções, a alocação de técnicos e o registo de materiais e custos associados.
 * * @author Jose meireles
 * @date 2026-01-06
 */

#ifndef LP_8200352_MANUTENCAO_H
#define LP_8200352_MANUTENCAO_H

#include "comum.h"

/** @brief Forward declarations para evitar dependências cíclicas entre módulos. */
typedef struct GestaoAtivos GestaoAtivos;
typedef struct GestaoDepartamentos GestaoDepartamentos;
typedef struct GestaoTecnicos GestaoTecnicos;

/**
 * @enum Prioridade
 * @brief Níveis de prioridade para uma ordem de manutenção.
 */
typedef enum {
    BAIXA,   /**< Intervenção sem urgência. */
    NORMAL,  /**< Intervenção de rotina. */
    URGENTE  /**< Intervenção prioritária com impacto operacional. */
} Prioridade;

/**
 * @enum TipoManutencao
 * @brief Tipos de manutenção permitidos pelo sistema.
 */
typedef enum {
    PREVENTIVA, /**< Manutenção planeada para evitar falhas. */
    CORRETIVA   /**< Manutenção realizada após a ocorrência de uma avaria. */
} TipoManutencao;

/**
 * @enum EstadoOrdem
 * @brief Estados possíveis no ciclo de vida de uma ordem de manutenção.
 */
typedef enum {
    PENDENTE,    /**< Ordem criada mas ainda não iniciada. */
    EM_EXECUCAO, /**< Ordem atribuída a um técnico e em curso. */
    CONCLUIDA,   /**< Intervenção finalizada com sucesso. */
    CANCELADA    /**< Ordem anulada pelo utilizador ou sistema. */
} EstadoOrdem;

/**
 * @struct Material
 * @brief Representa uma peça ou material utilizado numa manutenção.
 */
typedef struct Material {
    char item[MAX_TEXTO]; /**< Designação da peça/material. */
    int quantidade;       /**< Quantidade utilizada. */
    float custoUnitario;  /**< Preço por unidade. */
} Material;

/**
 * @struct Manutencao
 * @brief Estrutura principal que representa uma Ordem de Manutenção.
 */
typedef struct Manutencao {
    int idOrdem;                  /**< Identificador único e sequencial. */
    int idAtivo;                  /**< ID do equipamento associado. */
    int idDepartamento;           /**< ID do departamento requisitante. */
    int idTecnico;                /**< ID do técnico responsável (0 se não atribuído). */
    Data dataPedido;              /**< Data em que a manutenção foi solicitada. */
    Data dataConclusao;           /**< Data de finalização da intervenção. */
    Prioridade prioridade;        /**< Nível de prioridade (Baixa, Normal, Urgente). */
    TipoManutencao tipo;          /**< Tipo (Preventiva ou Corretiva). */
    EstadoOrdem estado;           /**< Estado atual da ordem. */
    char descricao[MAX_DESCRICAO]; /**< Descrição do problema ou serviço. */
    Material *materiais;          /**< Array dinâmico de materiais utilizados. */
    int numMateriais;             /**< Número total de tipos de materiais registados. */
} Manutencao;

/**
 * @struct GestaoManutencao
 * @brief Estrutura para gestão da lista dinâmica de ordens de manutenção.
 */
typedef struct GestaoManutencao {
    Manutencao *lista; /**< Ponteiro para o array de ordens. */
    int contador;      /**< Número de ordens registadas. */
    int capacidade;    /**< Capacidade de memória alocada. */
} GestaoManutencao;


/**
 * @brief Lista todas as ordens de manutenção e os seus detalhes (incluindo materiais).
 * @param manutencao Ponteiro para a gestão de manutenção.
 */
void lerManutencao(GestaoManutencao *manutencao);

/**
 * @brief Atualiza os dados de uma ordem, permitindo gerir o estado e atribuir técnicos.
 * @param gm Ponteiro para a gestão de manutenção.
 * @param ga Ponteiro para a gestão de ativos.
 * @param gd Ponteiro para a gestão de departamentos.
 * @param gt Ponteiro para a gestão de técnicos.
 */
void atualizarManutencao(GestaoManutencao *gm, GestaoAtivos *ga, GestaoDepartamentos *gd, GestaoTecnicos *gt);

/**
 * @brief Cancela uma ordem de manutenção ativa (remoção lógica).
 * @param manutencao Ponteiro para a gestão de manutenção.
 */
void eliminarManutencao(GestaoManutencao *manutencao);

/**
 * @brief Cria uma nova ordem de manutenção com validação de IDs e datas.
 * @param gm Ponteiro para a gestão de manutenção.
 * @param ga Ponteiro para a gestão de ativos.
 * @param gd Ponteiro para a gestão de departamentos.
 * @param gt Ponteiro para a gestão de técnicos.
 */
void criarManutencao(GestaoManutencao *gm, GestaoAtivos *ga, GestaoDepartamentos *gd, GestaoTecnicos *gt);

/**
 * @brief Funcionalidade adicional: Exibe alertas para ordens urgentes pendentes.
 * @param gm Ponteiro para a gestão de manutenção.
 */
void alertasOrdensCriticas(GestaoManutencao *gm);

/**
 * @brief Persiste a lista de ordens e materiais no ficheiro "manutencoes.txt".
 * @param gm Ponteiro para a gestão de manutenção.
 */
void guardarManutencoes(GestaoManutencao *gm);

/**
 * @brief Carrega as ordens e reconstrói a lista dinâmica de materiais a partir do ficheiro.
 * @param gm Ponteiro para a gestão de manutenção.
 */
void carregarManutencoes(GestaoManutencao *gm);

#endif //LP_8200352_MANUTENCAO_H