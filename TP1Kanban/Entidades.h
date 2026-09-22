#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "Dominios.h"

/**
 * @brief Representa uma pessoa cadastrada no sistema, podendo atuar como
 * gestora de projetos ou desenvolvedora de cartoes de atividade.
 *
 * O e-mail e a chave primaria da entidade e nao pode ser alterado apos
 * a criacao.
 */
class Pessoa {
private:
    Email email;     ///< Chave primaria da pessoa.
    Nome nome;
    Senha senha;
    Papel papel;

public:
    Pessoa(const Email& email, const Nome& nome, const Senha& senha, const Papel& papel);

    /** @brief Retorna o e-mail (chave primaria) da pessoa. */
    Email getEmail() const;

    /** @brief Retorna o nome da pessoa. */
    Nome getNome() const;
    /** @brief Define o nome da pessoa. */
    void setNome(const Nome& novoNome);

    /** @brief Retorna a senha da pessoa. */
    Senha getSenha() const;
    /** @brief Define a senha da pessoa. */
    void setSenha(const Senha& novaSenha);

    /** @brief Retorna o papel da pessoa. */
    Papel getPapel() const;
    /** @brief Define o papel da pessoa. */
    void setPapel(const Papel& novoPapel);
};

/**
 * @brief Representa um projeto de gestao no sistema, criado e mantido por
 * uma pessoa com papel de gestor.
 *
 * O identificador e a chave primaria da entidade e nao pode ser alterado
 * apos a criacao.
 */
class Projeto {
private:
    Identificador identificador; ///< Chave primaria do projeto.
    Nome nome;
    Texto descricao;
    Timestamp inicio;
    Timestamp termino;

public:
    Projeto(const Identificador& identificador, const Nome& nome, const Texto& descricao,
            const Timestamp& inicio, const Timestamp& termino);

    /** @brief Retorna o identificador (chave primaria) do projeto. */
    Identificador getIdentificador() const;

    /** @brief Retorna o nome do projeto. */
    Nome getNome() const;
    /** @brief Define o nome do projeto. */
    void setNome(const Nome& novoNome);

    /** @brief Retorna a descricao do projeto. */
    Texto getDescricao() const;
    /** @brief Define a descricao do projeto. */
    void setDescricao(const Texto& novaDescricao);

    /** @brief Retorna o timestamp de inicio do projeto. */
    Timestamp getInicio() const;
    /** @brief Define o timestamp de inicio do projeto. */
    void setInicio(const Timestamp& novoInicio);

    /** @brief Retorna o timestamp de termino do projeto. */
    Timestamp getTermino() const;
    /** @brief Define o timestamp de termino do projeto. */
    void setTermino(const Timestamp& novoTermino);
};

/**
 * @brief Representa um quadro Kanban pertencente a um projeto, composto
 * pelas colunas A FAZER, FAZENDO e FEITO.
 *
 * O identificador e a chave primaria da entidade e nao pode ser alterado
 * apos a criacao.
 */
class Quadro {
private:
    Identificador identificador; ///< Chave primaria do quadro.
    Nome nome;
    Limite limite; ///< Limite de work in progress (WIP) da coluna FAZENDO.

public:
    Quadro(const Identificador& identificador, const Nome& nome, const Limite& limite);

    /** @brief Retorna o identificador (chave primaria) do quadro. */
    Identificador getIdentificador() const;

    /** @brief Retorna o nome do quadro. */
    Nome getNome() const;
    /** @brief Define o nome do quadro. */
    void setNome(const Nome& novoNome);

    /** @brief Retorna o limite de WIP do quadro. */
    Limite getLimite() const;
    /** @brief Define o limite de WIP do quadro. */
    void setLimite(const Limite& novoLimite);
};

/**
 * @brief Representa um cartao de atividade dentro de um quadro Kanban,
 * atribuido a uma pessoa desenvolvedora.
 *
 * O identificador e a chave primaria da entidade e nao pode ser alterado
 * apos a criacao. Os timestamps de inicio e termino sao preenchidos quando
 * o cartao entra nas colunas FAZENDO e FEITO, respectivamente.
 */
class CartaoAtividade {
private:
    Identificador identificador; ///< Chave primaria do cartao de atividade.
    Nome nome;
    Texto descricao;
    Prioridade prioridade;
    Estado estado;
    Tamanho tamanho;
    Timestamp entrada;
    Timestamp inicio;
    Timestamp termino;

public:
    CartaoAtividade(const Identificador& identificador, const Nome& nome, const Texto& descricao,
                     const Prioridade& prioridade, const Estado& estado, const Tamanho& tamanho,
                     const Timestamp& entrada, const Timestamp& inicio, const Timestamp& termino);

    /** @brief Retorna o identificador (chave primaria) do cartao de atividade. */
    Identificador getIdentificador() const;

    /** @brief Retorna o nome do cartao de atividade. */
    Nome getNome() const;
    /** @brief Define o nome do cartao de atividade. */
    void setNome(const Nome& novoNome);

    /** @brief Retorna a descricao do cartao de atividade. */
    Texto getDescricao() const;
    /** @brief Define a descricao do cartao de atividade. */
    void setDescricao(const Texto& novaDescricao);

    /** @brief Retorna a prioridade do cartao de atividade. */
    Prioridade getPrioridade() const;
    /** @brief Define a prioridade do cartao de atividade. */
    void setPrioridade(const Prioridade& novaPrioridade);

    /** @brief Retorna o estado do cartao de atividade. */
    Estado getEstado() const;
    /** @brief Define o estado do cartao de atividade. */
    void setEstado(const Estado& novoEstado);

    /** @brief Retorna o tamanho do cartao de atividade. */
    Tamanho getTamanho() const;
    /** @brief Define o tamanho do cartao de atividade. */
    void setTamanho(const Tamanho& novoTamanho);

    /** @brief Retorna o timestamp de entrada do cartao no quadro. */
    Timestamp getEntrada() const;
    /** @brief Define o timestamp de entrada do cartao no quadro. */
    void setEntrada(const Timestamp& novaEntrada);

    /** @brief Retorna o timestamp de inicio (entrada em FAZENDO) do cartao. */
    Timestamp getInicio() const;
    /** @brief Define o timestamp de inicio do cartao. */
    void setInicio(const Timestamp& novoInicio);

    /** @brief Retorna o timestamp de termino (entrada em FEITO) do cartao. */
    Timestamp getTermino() const;
    /** @brief Define o timestamp de termino do cartao. */
    void setTermino(const Timestamp& novoTermino);
};

#endif // ENTIDADES_H
