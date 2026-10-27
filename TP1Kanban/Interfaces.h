#ifndef INTERFACES_H
#define INTERFACES_H

#include <string>
#include <vector>
#include <stdexcept>
#include "Entidades.h"

/**
 * @brief Interface da camada de servico (regras de negocio do sistema Kanban).
 *
 * Toda violacao de regra de negocio (item nao encontrado, identificador
 * duplicado, falta de permissao, limite de WIP excedido etc.) e sinalizada
 * com std::runtime_error. O parametro @c solicitante e sempre o e-mail da
 * pessoa autenticada que esta executando a operacao.
 *
 * Regras de acesso:
 * - GESTOR cria e administra seus projetos, quadros e cartoes.
 * - DESENVOLVEDOR enxerga os projetos em que possui cartao atribuido e pode
 *   mover os cartoes atribuidos a ele.
 */
class IServico {
public:
    virtual ~IServico() {}

    // ------------------------------------------------------------ Pessoas

    /** @brief Cadastra uma pessoa. @throws std::runtime_error se o e-mail ja existe. */
    virtual void cadastrarPessoa(const Pessoa& pessoa) = 0;

    /** @brief Autentica uma pessoa. @throws std::runtime_error se e-mail ou senha estiverem incorretos. */
    virtual Pessoa autenticar(const Email& email, const Senha& senha) = 0;

    /** @brief Consulta uma pessoa pelo e-mail. @throws std::runtime_error se nao existir. */
    virtual Pessoa consultarPessoa(const Email& email) const = 0;

    /**
     * @brief Atualiza nome e senha de uma pessoa (o e-mail e o papel nao mudam).
     * @throws std::runtime_error se a pessoa nao existir.
     */
    virtual void atualizarPessoa(const Pessoa& pessoa) = 0;

    /**
     * @brief Exclui uma pessoa. Cartoes atribuidos a ela ficam sem responsavel.
     * @throws std::runtime_error se for gestor com projetos ou se nao existir.
     */
    virtual void excluirPessoa(const Email& email) = 0;

    /** @brief Lista todas as pessoas com papel DESENVOLVEDOR. */
    virtual std::vector<Pessoa> listarDesenvolvedores() const = 0;

    // ----------------------------------------------------------- Projetos

    /** @brief Cria um projeto cujo gestor e o solicitante. */
    virtual void criarProjeto(const Email& solicitante, const Projeto& projeto) = 0;

    /** @brief Consulta um projeto ao qual o solicitante tem acesso. */
    virtual Projeto consultarProjeto(const Email& solicitante, const Identificador& id) const = 0;

    /** @brief Atualiza nome, descricao, inicio e termino de um projeto (somente o gestor). */
    virtual void atualizarProjeto(const Email& solicitante, const Projeto& projeto) = 0;

    /** @brief Exclui um projeto e, em cascata, seus quadros e cartoes (somente o gestor). */
    virtual void excluirProjeto(const Email& solicitante, const Identificador& id) = 0;

    /** @brief Lista os projetos acessiveis ao solicitante. */
    virtual std::vector<Projeto> listarProjetos(const Email& solicitante) const = 0;

    // ------------------------------------------------------------ Quadros

    /** @brief Cria um quadro dentro de um projeto (somente o gestor do projeto). */
    virtual void criarQuadro(const Email& solicitante, const Identificador& projeto, const Quadro& quadro) = 0;

    /** @brief Consulta um quadro ao qual o solicitante tem acesso. */
    virtual Quadro consultarQuadro(const Email& solicitante, const Identificador& id) const = 0;

    /**
     * @brief Atualiza nome e limite de WIP de um quadro (somente o gestor).
     * @throws std::runtime_error se o novo limite for menor que o numero de cartoes em FAZENDO.
     */
    virtual void atualizarQuadro(const Email& solicitante, const Quadro& quadro) = 0;

    /** @brief Exclui um quadro e, em cascata, seus cartoes (somente o gestor). */
    virtual void excluirQuadro(const Email& solicitante, const Identificador& id) = 0;

    /** @brief Lista os quadros de um projeto acessivel ao solicitante. */
    virtual std::vector<Quadro> listarQuadros(const Email& solicitante, const Identificador& projeto) const = 0;

    // ------------------------------------------------------------ Cartoes

    /**
     * @brief Cria um cartao em um quadro (somente o gestor do projeto).
     *
     * Estado, entrada, inicio e termino do cartao recebido sao ignorados:
     * o servico define o estado A FAZER e a entrada como o instante atual.
     */
    virtual void criarCartao(const Email& solicitante, const Identificador& quadro, const CartaoAtividade& cartao) = 0;

    /** @brief Consulta um cartao de um projeto acessivel ao solicitante. */
    virtual CartaoAtividade consultarCartao(const Email& solicitante, const Identificador& id) const = 0;

    /**
     * @brief Atualiza nome, descricao, prioridade e tamanho de um cartao (somente o gestor).
     * Estado e timestamps so mudam por meio de moverCartao().
     */
    virtual void atualizarCartao(const Email& solicitante, const CartaoAtividade& cartao) = 0;

    /** @brief Exclui um cartao (somente o gestor). */
    virtual void excluirCartao(const Email& solicitante, const Identificador& id) = 0;

    /** @brief Lista os cartoes de um quadro acessivel ao solicitante. */
    virtual std::vector<CartaoAtividade> listarCartoes(const Email& solicitante, const Identificador& quadro) const = 0;

    /** @brief Atribui um cartao a um desenvolvedor (somente o gestor). */
    virtual void atribuirCartao(const Email& solicitante, const Identificador& cartao, const Email& desenvolvedor) = 0;

    /** @brief Retorna o e-mail do responsavel pelo cartao, ou texto vazio se nao houver. */
    virtual std::string responsavelDoCartao(const Email& solicitante, const Identificador& cartao) const = 0;

    /**
     * @brief Move um cartao para outra coluna do quadro.
     *
     * Somente o gestor do projeto ou o desenvolvedor responsavel podem mover.
     * Os cartoes andam uma coluna por vez (A FAZER <-> FAZENDO <-> FEITO),
     * a entrada em FAZENDO respeita o limite de WIP do quadro, e os
     * timestamps de inicio e termino sao atualizados automaticamente.
     */
    virtual void moverCartao(const Email& solicitante, const Identificador& cartao, const Estado& destino) = 0;
};

/**
 * @brief Interface da camada de apresentacao (interface com o usuario).
 */
class IApresentacao {
public:
    virtual ~IApresentacao() {}

    /** @brief Define a camada de servico usada pela apresentacao. */
    virtual void setServico(IServico* servico) = 0;

    /** @brief Executa a interface com o usuario ate o encerramento do programa. */
    virtual void executar() = 0;
};

#endif // INTERFACES_H
