#ifndef SERVICOS_H
#define SERVICOS_H

#include <string>
#include <vector>
#include "Interfaces.h"

/**
 * @brief Implementacao da camada de servico com armazenamento em memoria.
 *
 * Guarda as pessoas, projetos, quadros e cartoes em vetores e aplica as
 * regras de negocio descritas em IServico. As associacoes entre as entidades
 * (gestor do projeto, projeto do quadro, quadro e responsavel do cartao) sao
 * mantidas em registros internos, sem alterar as classes de entidade.
 */
class ServicoKanban : public IServico {
private:
    struct RegProjeto {
        Projeto projeto;
        std::string gestor; ///< e-mail do gestor
        RegProjeto(const Projeto& p, const std::string& g) : projeto(p), gestor(g) {}
    };

    struct RegQuadro {
        Quadro quadro;
        std::string projeto; ///< identificador do projeto
        RegQuadro(const Quadro& q, const std::string& p) : quadro(q), projeto(p) {}
    };

    struct RegCartao {
        CartaoAtividade cartao;
        std::string quadro;      ///< identificador do quadro
        std::string responsavel; ///< e-mail do desenvolvedor (vazio se nao atribuido)
        RegCartao(const CartaoAtividade& c, const std::string& q, const std::string& r)
            : cartao(c), quadro(q), responsavel(r) {}
    };

    std::vector<Pessoa> pessoas;
    std::vector<RegProjeto> projetos;
    std::vector<RegQuadro> quadros;
    std::vector<RegCartao> cartoes;

    int indicePessoa(const std::string& email) const;
    int indiceProjeto(const std::string& id) const;
    int indiceQuadro(const std::string& id) const;
    int indiceCartao(const std::string& id) const;

    bool temAcesso(const std::string& solicitante, const std::string& idProjeto) const;
    void exigirAcesso(const std::string& solicitante, const std::string& idProjeto) const;
    void exigirGestor(const std::string& solicitante, const std::string& idProjeto) const;

    int contarEstado(const std::string& idQuadro, Estado::Valor estado) const;
    void removerCartoesDoQuadro(const std::string& idQuadro);

public:
    // Pessoas
    void cadastrarPessoa(const Pessoa& pessoa);
    Pessoa autenticar(const Email& email, const Senha& senha);
    Pessoa consultarPessoa(const Email& email) const;
    void atualizarPessoa(const Pessoa& pessoa);
    void excluirPessoa(const Email& email);
    std::vector<Pessoa> listarDesenvolvedores() const;

    // Projetos
    void criarProjeto(const Email& solicitante, const Projeto& projeto);
    Projeto consultarProjeto(const Email& solicitante, const Identificador& id) const;
    void atualizarProjeto(const Email& solicitante, const Projeto& projeto);
    void excluirProjeto(const Email& solicitante, const Identificador& id);
    std::vector<Projeto> listarProjetos(const Email& solicitante) const;

    // Quadros
    void criarQuadro(const Email& solicitante, const Identificador& projeto, const Quadro& quadro);
    Quadro consultarQuadro(const Email& solicitante, const Identificador& id) const;
    void atualizarQuadro(const Email& solicitante, const Quadro& quadro);
    void excluirQuadro(const Email& solicitante, const Identificador& id);
    std::vector<Quadro> listarQuadros(const Email& solicitante, const Identificador& projeto) const;

    // Cartoes
    void criarCartao(const Email& solicitante, const Identificador& quadro, const CartaoAtividade& cartao);
    CartaoAtividade consultarCartao(const Email& solicitante, const Identificador& id) const;
    void atualizarCartao(const Email& solicitante, const CartaoAtividade& cartao);
    void excluirCartao(const Email& solicitante, const Identificador& id);
    std::vector<CartaoAtividade> listarCartoes(const Email& solicitante, const Identificador& quadro) const;
    void atribuirCartao(const Email& solicitante, const Identificador& cartao, const Email& desenvolvedor);
    std::string responsavelDoCartao(const Email& solicitante, const Identificador& cartao) const;
    void moverCartao(const Email& solicitante, const Identificador& cartao, const Estado& destino);
};

#endif // SERVICOS_H
