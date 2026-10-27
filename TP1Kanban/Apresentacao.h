#ifndef APRESENTACAO_H
#define APRESENTACAO_H

#include <string>
#include "Interfaces.h"

/**
 * @brief Camada de apresentacao do sistema Kanban: interface de console com
 * menus por papel (GESTOR ou DESENVOLVEDOR).
 *
 * Esta classe nao contem regras de negocio. Ela le e valida o formato dos
 * dados digitados usando as classes de dominio, chama a camada de servico
 * por meio de IServico e exibe os resultados ou as mensagens de erro.
 * Digitar 0 em qualquer campo cancela a operacao atual.
 */
class ApresentacaoKanban : public IApresentacao {
private:
    IServico* servico; ///< Camada de servico usada pela apresentacao.
    bool autenticado;  ///< Indica se ha uma pessoa autenticada.
    Email usuario;     ///< E-mail da pessoa autenticada.
    Papel papel;       ///< Papel da pessoa autenticada.

    // Menus (cada chamada executa uma iteracao do menu)
    bool menuInicial();
    void menuGestor();
    void menuDesenvolvedor();
    void cabecalho();

    // Autenticacao e dados de exemplo
    void entrar();
    void cadastrarSe();
    void carregarExemplo();

    // Conta
    void verConta();
    void excluirConta();

    // Projetos
    void criarProjeto();
    void listarProjetos();
    void editarProjeto();
    void excluirProjeto();

    // Quadros
    void criarQuadro();
    void editarQuadro();
    void excluirQuadro();

    // Cartoes e Kanban
    void criarCartao();
    void editarCartao();
    void atribuirCartao();
    void moverCartao();
    void excluirCartao();
    void verQuadro();

    // Auxiliares de selecao e exibicao
    bool escolherProjeto(Identificador& id);
    bool escolherQuadro(Identificador& id);
    bool escolherCartao(const Identificador& quadro, Identificador& id);
    void exibirQuadro(const Identificador& idQuadro);
    std::string nomeDoResponsavel(const Identificador& idCartao);

public:
    ApresentacaoKanban();

    /** @brief Define a camada de servico usada pela apresentacao. */
    void setServico(IServico* novoServico);

    /** @brief Executa a interface ate o usuario escolher sair. */
    void executar();
};

#endif // APRESENTACAO_H
