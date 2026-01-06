/**
 * @file comum.h
 * @brief Definições de estruturas, macros e funções utilitárias comuns a todo o sistema.
 * * Este ficheiro centraliza as constantes de tamanho, a definição de data e
 * as ferramentas de validação e registo (logs) utilizadas pelos diversos módulos.
 * * @author José Meireles
 * @date 2026-01-06
 */

#ifndef LP_8200352_COMUM_H
#define LP_8200352_COMUM_H

/** @name Constantes de Tamanho
 * Definição de limites máximos para campos de texto.
 * @{ */
#define MAX_NOME 100      /**< Tamanho máximo para nomes completos. */
#define MAX_TEXTO 50      /**< Tamanho máximo para descrições curtas ou localizações. */
#define MAX_DESCRICAO 200 /**< Tamanho máximo para descrições detalhadas de problemas. */
/** @} */

/**
 * @struct Data
 * @brief Estrutura para representação de datas no formato dia/mês/ano.
 */
typedef struct {
    int dia; /**< Dia do mês. */
    int mes; /**< Mês do ano. */
    int ano; /**< Ano. */
} Data;

/**
 * @struct AuxRanking
 * @brief Estrutura auxiliar para cálculo e ordenação do ranking de desempenho dos técnicos.
 */
typedef struct {
    int idTecnico;        /**< ID do técnico. */
    char nome[MAX_NOME];  /**< Nome do técnico. */
    int concluidas;       /**< Número total de ordens concluídas. */
    float tempoMedio;     /**< Média de dias gastos por ordem. */
} AuxRanking;

/**
 * @brief Converte uma data para o número total de dias.
 * * Utilizada para calcular a diferença entre datas (ex: tempo de resolução).
 * * @param d A data a ser convertida.
 * @return long O número total de dias acumulados.
 */
long dataParaDias(Data d);

/**
 * @brief Valida se uma data é cronologicamente possível.
 * * Verifica limites de meses (1-12) e dias de acordo com o mês correspondente.
 * * @param d A data a validar.
 * @return int 1 se for válida, 0 se for inválida.
 */
int validarData(Data d);

/**
 * @brief Regista uma mensagem genérica no ficheiro de sistema (log.txt).
 * @param mensagem String com a mensagem a gravar.
 */
void escreverLog(char *mensagem);

/**
 * @brief Regista alterações críticas para efeitos de auditoria (auditoria.txt).
 * * Grava o timestamp atual, a entidade alterada, o ID e os estados "antes" e "depois".
 * * @param entidade Nome da entidade (ex: "ATIVO", "TECNICO").
 * @param id Identificador da entidade alterada.
 * @param antes Estado ou valor antes da alteração.
 * @param depois Estado ou valor após a alteração.
 */
void escreverLogAuditoria(char *entidade, int id, char *antes, char *depois);

#endif // LP_8200352_COMUM_H