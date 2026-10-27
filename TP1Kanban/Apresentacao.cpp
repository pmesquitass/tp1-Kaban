#include "Apresentacao.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>

using namespace std;

// ---------------------------------------------------------------------
// Utilitarios de tela e leitura (visiveis apenas neste arquivo)
// ---------------------------------------------------------------------

namespace {

string num(int n) {
    ostringstream oss;
    oss << n;
    return oss.str();
}

void linha(char c, int n) {
    cout << string(n, c) << "\n";
}

void titulo(const string& t) {
    cout << "\n";
    linha('=', 64);
    cout << "  " << t << "\n";
    linha('=', 64);
}

string ajustar(const string& s, size_t larg) {
    if (s.size() > larg) return s.substr(0, larg - 1) + ".";
    return s + string(larg - s.size(), ' ');
}

string maiusculas(string s) {
    for (size_t i = 0; i < s.size(); i++) s[i] = (char)toupper((unsigned char)s[i]);
    return s;
}

string lerLinha(const string& prompt) {
    cout << prompt;
    string s;
    if (!getline(cin, s)) {
        cout << "\n  Entrada encerrada. Saindo...\n";
        exit(0);
    }
    if (!s.empty() && s[s.size() - 1] == '\r') s.erase(s.size() - 1);
    return s;
}

void pausar() {
    lerLinha("\n  Pressione ENTER para continuar...");
}

bool soDigitos(const string& s) {
    if (s.empty() || s.size() > 4) return false;
    for (size_t i = 0; i < s.size(); i++) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

/** Le uma opcao numerica de menu. Retorna -1 se a entrada nao for numero. */
int lerOpcao(const string& prompt) {
    string s = lerLinha(prompt);
    if (!soDigitos(s)) return -1;
    return atoi(s.c_str());
}

bool confirmar(const string& pergunta) {
    string s = maiusculas(lerLinha("  " + pergunta + " (S/N): "));
    return s == "S" || s == "SIM";
}

string ts(const Timestamp& t) {
    return t.getValor().empty() ? "--" : t.getValor();
}

/**
 * Le um campo de dominio, repetindo ate o valor ser valido.
 * Retorna false se o usuario digitou 0 (cancelar).
 */
template <typename T>
bool lerCampo(const string& rotulo, const string& dica, T& saida, bool caixaAlta = false) {
    while (true) {
        string s = lerLinha("  " + rotulo + (dica.empty() ? "" : " (" + dica + ")") + ": ");
        if (s == "0") {
            cout << "  Operacao cancelada.\n";
            return false;
        }
        if (caixaAlta) s = maiusculas(s);
        try {
            T tmp;
            tmp.setValor(s);
            saida = tmp;
            return true;
        } catch (const invalid_argument& e) {
            cout << "  ! Valor invalido: " << e.what() << "\n";
        }
    }
}

/**
 * Igual a lerCampo, mas ENTER mantem o valor atual (mostrado no prompt).
 * Retorna false se o usuario digitou 0 (cancelar).
 */
template <typename T>
bool lerOuManter(const string& rotulo, const string& dica, const string& atual, T& saida,
                 bool caixaAlta = false) {
    while (true) {
        string s = lerLinha("  " + rotulo + " [atual: " + atual + "] (" + dica + ", ENTER mantem): ");
        if (s == "0") {
            cout << "  Operacao cancelada.\n";
            return false;
        }
        if (s.empty()) return true;
        if (caixaAlta) s = maiusculas(s);
        try {
            T tmp;
            tmp.setValor(s);
            saida = tmp;
            return true;
        } catch (const invalid_argument& e) {
            cout << "  ! Valor invalido: " << e.what() << "\n";
        }
    }
}

/** Le o limite de WIP (1 a 25). Se manter for true, ENTER mantem o valor atual. */
bool lerLimite(Limite& saida, bool manter) {
    while (true) {
        string prompt = manter
            ? "  Limite de WIP [atual: " + num(saida.getValor()) + "] (1 a 25, ENTER mantem): "
            : "  Limite de WIP da coluna FAZENDO (1 a 25): ";
        string s = lerLinha(prompt);
        if (s == "0") {
            cout << "  Operacao cancelada.\n";
            return false;
        }
        if (manter && s.empty()) return true;
        if (!soDigitos(s)) {
            cout << "  ! Digite um numero inteiro.\n";
            continue;
        }
        try {
            Limite tmp;
            tmp.setValor(atoi(s.c_str()));
            saida = tmp;
            return true;
        } catch (const invalid_argument& e) {
            cout << "  ! Valor invalido: " << e.what() << "\n";
        }
    }
}

/** Verifica se existe item com o identificador dado na lista. */
template <typename T>
bool contem(const vector<T>& v, const Identificador& id) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i].getIdentificador().getValor() == id.getValor()) return true;
    }
    return false;
}

} // namespace

// ---------------------------------------------------------------------
// Construcao e laco principal
// ---------------------------------------------------------------------

ApresentacaoKanban::ApresentacaoKanban() : servico(0), autenticado(false) {}

void ApresentacaoKanban::setServico(IServico* novoServico) {
    servico = novoServico;
}

void ApresentacaoKanban::executar() {
    if (!servico) {
        cout << "Camada de servico nao configurada.\n";
        return;
    }
    bool continuar = true;
    while (continuar) {
        if (!autenticado) continuar = menuInicial();
        else if (papel.getValor() == Papel::GESTOR) menuGestor();
        else menuDesenvolvedor();
    }
}

void ApresentacaoKanban::cabecalho() {
    cout << "\n+" << string(62, '-') << "+\n";
    cout << "|" << ajustar("               SISTEMA KANBAN - GESTAO DE PROJETOS", 62) << "|\n";
    cout << "+" << string(62, '-') << "+\n";
    if (autenticado) {
        string quem = "  Logado: " + servico->consultarPessoa(usuario).getNome().getValor() +
                      " (" + papel.toString() + ")";
        cout << "|" << ajustar(quem, 62) << "|\n";
        cout << "+" << string(62, '-') << "+\n";
    }
}

// ---------------------------------------------------------------------
// Menus
// ---------------------------------------------------------------------

bool ApresentacaoKanban::menuInicial() {
    cabecalho();
    cout << "\n   1) Entrar\n";
    cout << "   2) Cadastrar-se\n";
    cout << "   3) Carregar dados de exemplo\n";
    cout << "   0) Sair\n\n";
    int op = lerOpcao("  Escolha uma opcao: ");

    try {
        switch (op) {
            case 1: entrar();         break;
            case 2: cadastrarSe();    break;
            case 3: carregarExemplo(); break;
            case 0: cout << "\n  Ate logo!\n"; return false;
            default: cout << "\n  Opcao invalida. Tente novamente.\n"; break;
        }
    } catch (const exception& e) {
        cout << "\n  ! " << e.what() << "\n";
    }
    pausar();
    return true;
}

void ApresentacaoKanban::menuGestor() {
    cabecalho();
    cout << "\n  --- PROJETOS ---\n";
    cout << "   1) Criar projeto\n";
    cout << "   2) Listar meus projetos\n";
    cout << "   3) Editar projeto\n";
    cout << "   4) Excluir projeto\n";
    cout << "  --- QUADROS ---\n";
    cout << "   5) Criar quadro\n";
    cout << "   6) Editar quadro\n";
    cout << "   7) Excluir quadro\n";
    cout << "  --- CARTOES ---\n";
    cout << "   8) Criar cartao\n";
    cout << "   9) Editar cartao\n";
    cout << "  10) Atribuir cartao a um desenvolvedor\n";
    cout << "  11) Mover cartao\n";
    cout << "  12) Excluir cartao\n";
    cout << "  --- KANBAN ---\n";
    cout << "  13) Ver quadro Kanban\n";
    cout << "  --- CONTA ---\n";
    cout << "  14) Minha conta\n";
    cout << "  15) Excluir minha conta\n";
    cout << "  16) Sair da conta\n\n";
    int op = lerOpcao("  Escolha uma opcao: ");

    try {
        switch (op) {
            case 1:  criarProjeto();    break;
            case 2:  listarProjetos();  break;
            case 3:  editarProjeto();   break;
            case 4:  excluirProjeto();  break;
            case 5:  criarQuadro();     break;
            case 6:  editarQuadro();    break;
            case 7:  excluirQuadro();   break;
            case 8:  criarCartao();     break;
            case 9:  editarCartao();    break;
            case 10: atribuirCartao();  break;
            case 11: moverCartao();     break;
            case 12: excluirCartao();   break;
            case 13: verQuadro();       break;
            case 14: verConta();        break;
            case 15: excluirConta();    break;
            case 16: autenticado = false; cout << "\n  Voce saiu da conta.\n"; break;
            default: cout << "\n  Opcao invalida. Tente novamente.\n"; break;
        }
    } catch (const exception& e) {
        cout << "\n  ! " << e.what() << "\n";
    }
    pausar();
}

void ApresentacaoKanban::menuDesenvolvedor() {
    cabecalho();
    cout << "\n   1) Meus projetos\n";
    cout << "   2) Ver quadro Kanban\n";
    cout << "   3) Mover cartao\n";
    cout << "   4) Minha conta\n";
    cout << "   5) Excluir minha conta\n";
    cout << "   6) Sair da conta\n\n";
    int op = lerOpcao("  Escolha uma opcao: ");

    try {
        switch (op) {
            case 1: listarProjetos(); break;
            case 2: verQuadro();      break;
            case 3: moverCartao();    break;
            case 4: verConta();       break;
            case 5: excluirConta();   break;
            case 6: autenticado = false; cout << "\n  Voce saiu da conta.\n"; break;
            default: cout << "\n  Opcao invalida. Tente novamente.\n"; break;
        }
    } catch (const exception& e) {
        cout << "\n  ! " << e.what() << "\n";
    }
    pausar();
}

// ---------------------------------------------------------------------
// Autenticacao e dados de exemplo
// ---------------------------------------------------------------------

void ApresentacaoKanban::entrar() {
    titulo("ENTRAR   (digite 0 para cancelar)");
    Email email;
    Senha senha;
    if (!lerCampo("E-mail", "", email)) return;
    if (!lerCampo("Senha", "", senha)) return;
    Pessoa p = servico->autenticar(email, senha);
    usuario = p.getEmail();
    papel = p.getPapel();
    autenticado = true;
    cout << "\n  Bem-vindo(a), " << p.getNome().getValor() << "!\n";
}

void ApresentacaoKanban::cadastrarSe() {
    titulo("CADASTRAR-SE   (digite 0 para cancelar)");
    Email email;
    Nome nome;
    Senha senha;
    Papel novoPapel;
    if (!lerCampo("E-mail", "ex: ana.silva@exemplo.com", email)) return;
    if (!lerCampo("Nome", "ate 15 letras", nome)) return;
    if (!lerCampo("Senha", "5 caracteres, com letra e digito", senha)) return;
    if (!lerCampo("Papel", "GESTOR ou DESENVOLVEDOR", novoPapel, true)) return;
    servico->cadastrarPessoa(Pessoa(email, nome, senha, novoPapel));
    cout << "\n  Cadastro realizado com sucesso! Agora voce ja pode entrar.\n";
}

void ApresentacaoKanban::carregarExemplo() {
    titulo("CARREGAR DADOS DE EXEMPLO");
    Email ana("ana.silva@exemplo.com");
    bool jaExiste = true;
    try {
        servico->consultarPessoa(ana);
    } catch (const runtime_error&) {
        jaExiste = false;
    }
    if (jaExiste) {
        cout << "  Os dados de exemplo ja foram carregados.\n";
        return;
    }

    Email bruno("bruno.costa@exemplo.com");
    Email carla("carla.dias@exemplo.com");
    servico->cadastrarPessoa(Pessoa(ana, Nome("Ana Silva"), Senha("ab12c"), Papel(Papel::GESTOR)));
    servico->cadastrarPessoa(Pessoa(bruno, Nome("Bruno Costa"), Senha("xy789"), Papel(Papel::DESENVOLVEDOR)));
    servico->cadastrarPessoa(Pessoa(carla, Nome("Carla Dias"), Senha("cd456"), Papel(Papel::DESENVOLVEDOR)));

    Identificador prj("prj001");
    Identificador qdr("qdr001");
    servico->criarProjeto(ana, Projeto(prj, Nome("Projeto Alfa"), Texto("Sistema de gestao Kanban."),
                                       Timestamp("01-OUT-2026-08:00"), Timestamp("30-NOV-2026-18:00")));
    servico->criarQuadro(ana, prj, Quadro(qdr, Nome("Sprint Um"), Limite(2)));

    const char* ids[] = {"crt001", "crt002", "crt003", "crt004", "crt005"};
    const char* nomes[] = {"Tela de login", "Banco de dados", "Testes", "Documentacao", "Deploy"};
    const char* descs[] = {"Criar a tela de login.", "Modelar as tabelas.", "Escrever os testes.",
                           "Gerar docs com Doxygen.", "Publicar a versao final."};
    Prioridade::Valor prios[] = {Prioridade::ALTA, Prioridade::ALTA, Prioridade::MEDIA,
                                 Prioridade::BAIXA, Prioridade::BAIXA};
    Tamanho::Valor tams[] = {Tamanho::MEDIO, Tamanho::GRANDE, Tamanho::PEQUENO,
                             Tamanho::PEQUENO, Tamanho::MEDIO};
    for (int i = 0; i < 5; i++) {
        servico->criarCartao(ana, qdr, CartaoAtividade(Identificador(ids[i]), Nome(nomes[i]),
                             Texto(descs[i]), Prioridade(prios[i]), Estado(Estado::A_FAZER),
                             Tamanho(tams[i]), Timestamp(), Timestamp(), Timestamp()));
    }

    servico->atribuirCartao(ana, Identificador("crt001"), bruno);
    servico->atribuirCartao(ana, Identificador("crt002"), bruno);
    servico->atribuirCartao(ana, Identificador("crt003"), carla);
    servico->atribuirCartao(ana, Identificador("crt004"), bruno);

    // crt004 vai ate FEITO; crt001 e crt002 ficam em FAZENDO (coluna cheia, limite 2).
    servico->moverCartao(ana, Identificador("crt004"), Estado(Estado::FAZENDO));
    servico->moverCartao(ana, Identificador("crt004"), Estado(Estado::FEITO));
    servico->moverCartao(ana, Identificador("crt001"), Estado(Estado::FAZENDO));
    servico->moverCartao(ana, Identificador("crt002"), Estado(Estado::FAZENDO));

    cout << "  Dados de exemplo carregados: 1 gestora, 2 desenvolvedores, 1 projeto, 1 quadro e 5 cartoes.\n\n";
    cout << "  Contas para testar (e-mail / senha):\n";
    cout << "    Gestora:         ana.silva@exemplo.com    / ab12c\n";
    cout << "    Desenvolvedor:   bruno.costa@exemplo.com  / xy789\n";
    cout << "    Desenvolvedora:  carla.dias@exemplo.com   / cd456\n\n";
    cout << "  Dica: a coluna FAZENDO do quadro qdr001 ja esta no limite de WIP.\n";
}

// ---------------------------------------------------------------------
// Conta
// ---------------------------------------------------------------------

void ApresentacaoKanban::verConta() {
    titulo("MINHA CONTA   (digite 0 para cancelar)");
    Pessoa p = servico->consultarPessoa(usuario);
    cout << "  E-mail: " << p.getEmail().getValor() << "\n";
    cout << "  Nome:   " << p.getNome().getValor() << "\n";
    cout << "  Papel:  " << p.getPapel().toString() << "\n";
    cout << "  Senha:  *****\n\n";
    if (!confirmar("Deseja editar nome ou senha?")) return;

    Nome nome = p.getNome();
    Senha senha = p.getSenha();
    if (!lerOuManter("Nome", "ate 15 letras", p.getNome().getValor(), nome)) return;
    if (!lerOuManter("Senha", "5 caracteres, com letra e digito", "*****", senha)) return;
    p.setNome(nome);
    p.setSenha(senha);
    servico->atualizarPessoa(p);
    cout << "\n  Dados atualizados com sucesso!\n";
}

void ApresentacaoKanban::excluirConta() {
    titulo("EXCLUIR MINHA CONTA");
    if (!confirmar("Tem certeza que deseja excluir sua conta? Isso nao pode ser desfeito.")) {
        cout << "  Operacao cancelada.\n";
        return;
    }
    servico->excluirPessoa(usuario);
    autenticado = false;
    cout << "\n  Conta excluida.\n";
}

// ---------------------------------------------------------------------
// Projetos
// ---------------------------------------------------------------------

void ApresentacaoKanban::criarProjeto() {
    titulo("CRIAR PROJETO   (digite 0 para cancelar)");
    Identificador id;
    Nome nome;
    Texto descricao;
    Timestamp inicio, termino;
    if (!lerCampo("Identificador", "3 letras + 3 digitos, ex: prj001", id)) return;
    if (!lerCampo("Nome", "ate 15 letras", nome)) return;
    if (!lerCampo("Descricao", "ate 30 caracteres, comeca com maiuscula, termina com ponto", descricao)) return;
    if (!lerCampo("Inicio", "DD-MES-AAAA-HH:MM, ex: 05-JAN-2026-14:30", inicio, true)) return;
    if (!lerCampo("Termino", "DD-MES-AAAA-HH:MM", termino, true)) return;
    servico->criarProjeto(usuario, Projeto(id, nome, descricao, inicio, termino));
    cout << "\n  Projeto criado com sucesso!\n";
}

void ApresentacaoKanban::listarProjetos() {
    titulo("PROJETOS");
    vector<Projeto> lista = servico->listarProjetos(usuario);
    if (lista.empty()) {
        cout << "  Nenhum projeto disponivel.\n";
        return;
    }
    for (size_t i = 0; i < lista.size(); i++) {
        const Projeto& p = lista[i];
        cout << "\n  [" << p.getIdentificador().getValor() << "] " << p.getNome().getValor() << "\n";
        cout << "      " << p.getDescricao().getValor() << "\n";
        cout << "      " << ts(p.getInicio()) << "  ->  " << ts(p.getTermino()) << "\n";
        vector<Quadro> quadros = servico->listarQuadros(usuario, p.getIdentificador());
        if (quadros.empty()) cout << "      Quadros: nenhum\n";
        for (size_t k = 0; k < quadros.size(); k++) {
            cout << "      Quadro [" << quadros[k].getIdentificador().getValor() << "] "
                 << quadros[k].getNome().getValor() << " (WIP " << quadros[k].getLimite().getValor() << ")\n";
        }
    }
}

void ApresentacaoKanban::editarProjeto() {
    titulo("EDITAR PROJETO   (digite 0 para cancelar)");
    Identificador id;
    if (!escolherProjeto(id)) return;
    Projeto p = servico->consultarProjeto(usuario, id);
    Nome nome = p.getNome();
    Texto descricao = p.getDescricao();
    Timestamp inicio = p.getInicio();
    Timestamp termino = p.getTermino();
    if (!lerOuManter("Nome", "ate 15 letras", nome.getValor(), nome)) return;
    if (!lerOuManter("Descricao", "ate 30 caracteres", descricao.getValor(), descricao)) return;
    if (!lerOuManter("Inicio", "DD-MES-AAAA-HH:MM", inicio.getValor(), inicio, true)) return;
    if (!lerOuManter("Termino", "DD-MES-AAAA-HH:MM", termino.getValor(), termino, true)) return;
    p.setNome(nome);
    p.setDescricao(descricao);
    p.setInicio(inicio);
    p.setTermino(termino);
    servico->atualizarProjeto(usuario, p);
    cout << "\n  Projeto atualizado com sucesso!\n";
}

void ApresentacaoKanban::excluirProjeto() {
    titulo("EXCLUIR PROJETO   (digite 0 para cancelar)");
    Identificador id;
    if (!escolherProjeto(id)) return;
    if (!confirmar("Excluir o projeto e todos os seus quadros e cartoes?")) {
        cout << "  Operacao cancelada.\n";
        return;
    }
    servico->excluirProjeto(usuario, id);
    cout << "\n  Projeto excluido.\n";
}

// ---------------------------------------------------------------------
// Quadros
// ---------------------------------------------------------------------

void ApresentacaoKanban::criarQuadro() {
    titulo("CRIAR QUADRO   (digite 0 para cancelar)");
    Identificador idProjeto;
    if (!escolherProjeto(idProjeto)) return;
    Identificador id;
    Nome nome;
    Limite limite;
    if (!lerCampo("Identificador do quadro", "3 letras + 3 digitos, ex: qdr001", id)) return;
    if (!lerCampo("Nome", "ate 15 letras", nome)) return;
    if (!lerLimite(limite, false)) return;
    servico->criarQuadro(usuario, idProjeto, Quadro(id, nome, limite));
    cout << "\n  Quadro criado com sucesso!\n";
}

void ApresentacaoKanban::editarQuadro() {
    titulo("EDITAR QUADRO   (digite 0 para cancelar)");
    Identificador id;
    if (!escolherQuadro(id)) return;
    Quadro q = servico->consultarQuadro(usuario, id);
    Nome nome = q.getNome();
    Limite limite = q.getLimite();
    if (!lerOuManter("Nome", "ate 15 letras", nome.getValor(), nome)) return;
    if (!lerLimite(limite, true)) return;
    q.setNome(nome);
    q.setLimite(limite);
    servico->atualizarQuadro(usuario, q);
    cout << "\n  Quadro atualizado com sucesso!\n";
}

void ApresentacaoKanban::excluirQuadro() {
    titulo("EXCLUIR QUADRO   (digite 0 para cancelar)");
    Identificador id;
    if (!escolherQuadro(id)) return;
    if (!confirmar("Excluir o quadro e todos os seus cartoes?")) {
        cout << "  Operacao cancelada.\n";
        return;
    }
    servico->excluirQuadro(usuario, id);
    cout << "\n  Quadro excluido.\n";
}

// ---------------------------------------------------------------------
// Cartoes e Kanban
// ---------------------------------------------------------------------

void ApresentacaoKanban::criarCartao() {
    titulo("CRIAR CARTAO   (digite 0 para cancelar)");
    Identificador idQuadro;
    if (!escolherQuadro(idQuadro)) return;
    Identificador id;
    Nome nome;
    Texto descricao;
    Prioridade prioridade;
    Tamanho tamanho;
    if (!lerCampo("Identificador do cartao", "3 letras + 3 digitos, ex: crt001", id)) return;
    if (!lerCampo("Nome", "ate 15 letras", nome)) return;
    if (!lerCampo("Descricao", "ate 30 caracteres, comeca com maiuscula, termina com ponto", descricao)) return;
    if (!lerCampo("Prioridade", "ALTA, MEDIA ou BAIXA", prioridade, true)) return;
    if (!lerCampo("Tamanho", "GRANDE, MEDIO ou PEQUENO", tamanho, true)) return;
    // Estado e timestamps sao definidos pelo servico.
    servico->criarCartao(usuario, idQuadro,
                         CartaoAtividade(id, nome, descricao, prioridade, Estado(Estado::A_FAZER),
                                         tamanho, Timestamp(), Timestamp(), Timestamp()));
    cout << "\n  Cartao criado na coluna A FAZER!\n";
}

void ApresentacaoKanban::editarCartao() {
    titulo("EDITAR CARTAO   (digite 0 para cancelar)");
    Identificador idQuadro, id;
    if (!escolherQuadro(idQuadro)) return;
    if (!escolherCartao(idQuadro, id)) return;
    CartaoAtividade c = servico->consultarCartao(usuario, id);
    Nome nome = c.getNome();
    Texto descricao = c.getDescricao();
    Prioridade prioridade = c.getPrioridade();
    Tamanho tamanho = c.getTamanho();
    if (!lerOuManter("Nome", "ate 15 letras", nome.getValor(), nome)) return;
    if (!lerOuManter("Descricao", "ate 30 caracteres", descricao.getValor(), descricao)) return;
    if (!lerOuManter("Prioridade", "ALTA, MEDIA ou BAIXA", prioridade.toString(), prioridade, true)) return;
    if (!lerOuManter("Tamanho", "GRANDE, MEDIO ou PEQUENO", tamanho.toString(), tamanho, true)) return;
    c.setNome(nome);
    c.setDescricao(descricao);
    c.setPrioridade(prioridade);
    c.setTamanho(tamanho);
    servico->atualizarCartao(usuario, c);
    cout << "\n  Cartao atualizado com sucesso!\n";
}

void ApresentacaoKanban::atribuirCartao() {
    titulo("ATRIBUIR CARTAO   (digite 0 para cancelar)");
    Identificador idQuadro, id;
    if (!escolherQuadro(idQuadro)) return;
    if (!escolherCartao(idQuadro, id)) return;

    vector<Pessoa> devs = servico->listarDesenvolvedores();
    if (devs.empty()) {
        cout << "  Nenhum desenvolvedor cadastrado.\n";
        return;
    }
    cout << "\n  Desenvolvedores:\n";
    for (size_t i = 0; i < devs.size(); i++) {
        cout << "    " << devs[i].getEmail().getValor() << " - " << devs[i].getNome().getValor() << "\n";
    }
    Email email;
    if (!lerCampo("E-mail do desenvolvedor", "", email)) return;
    servico->atribuirCartao(usuario, id, email);
    cout << "\n  Cartao atribuido com sucesso!\n";
}

void ApresentacaoKanban::moverCartao() {
    titulo("MOVER CARTAO   (digite 0 para cancelar)");
    Identificador idQuadro, id;
    if (!escolherQuadro(idQuadro)) return;
    exibirQuadro(idQuadro);
    if (!escolherCartao(idQuadro, id)) return;

    CartaoAtividade c = servico->consultarCartao(usuario, id);
    Estado::Valor atual = c.getEstado().getValor();
    vector<Estado::Valor> destinos;
    if (atual == Estado::A_FAZER) {
        destinos.push_back(Estado::FAZENDO);
    } else if (atual == Estado::FAZENDO) {
        destinos.push_back(Estado::FEITO);
        destinos.push_back(Estado::A_FAZER);
    } else {
        destinos.push_back(Estado::FAZENDO);
    }

    cout << "\n  Estado atual: " << c.getEstado().toString() << "\n  Mover para:\n";
    for (size_t i = 0; i < destinos.size(); i++) {
        cout << "    " << (i + 1) << ") " << Estado(destinos[i]).toString() << "\n";
    }
    int op = lerOpcao("  Escolha: ");
    if (op < 1 || op > (int)destinos.size()) {
        cout << "  Opcao invalida. Nada foi alterado.\n";
        return;
    }
    servico->moverCartao(usuario, id, Estado(destinos[op - 1]));
    cout << "\n  Cartao movido com sucesso!\n";
    exibirQuadro(idQuadro);
}

void ApresentacaoKanban::excluirCartao() {
    titulo("EXCLUIR CARTAO   (digite 0 para cancelar)");
    Identificador idQuadro, id;
    if (!escolherQuadro(idQuadro)) return;
    if (!escolherCartao(idQuadro, id)) return;
    if (!confirmar("Excluir este cartao?")) {
        cout << "  Operacao cancelada.\n";
        return;
    }
    servico->excluirCartao(usuario, id);
    cout << "\n  Cartao excluido.\n";
}

void ApresentacaoKanban::verQuadro() {
    titulo("VER QUADRO KANBAN   (digite 0 para cancelar)");
    Identificador idQuadro;
    if (!escolherQuadro(idQuadro)) return;
    exibirQuadro(idQuadro);

    vector<CartaoAtividade> cartoes = servico->listarCartoes(usuario, idQuadro);
    if (cartoes.empty()) return;
    cout << "\n  Digite o identificador de um cartao para ver os detalhes (ENTER para voltar).\n";
    while (true) {
        string s = lerLinha("  Cartao: ");
        if (s.empty() || s == "0") return;
        bool achou = false;
        for (size_t i = 0; i < cartoes.size() && !achou; i++) {
            const CartaoAtividade& c = cartoes[i];
            if (c.getIdentificador().getValor() != s) continue;
            achou = true;
            cout << "\n  Cartao [" << s << "]\n";
            linha('-', 40);
            cout << "  Nome:        " << c.getNome().getValor() << "\n";
            cout << "  Descricao:   " << c.getDescricao().getValor() << "\n";
            cout << "  Prioridade:  " << c.getPrioridade().toString() << "\n";
            cout << "  Tamanho:     " << c.getTamanho().toString() << "\n";
            cout << "  Estado:      " << c.getEstado().toString() << "\n";
            cout << "  Responsavel: " << nomeDoResponsavel(c.getIdentificador()) << "\n";
            cout << "  Entrada:     " << ts(c.getEntrada()) << "\n";
            cout << "  Inicio:      " << ts(c.getInicio()) << "\n";
            cout << "  Termino:     " << ts(c.getTermino()) << "\n";
        }
        if (!achou) cout << "  ! Cartao nao encontrado neste quadro.\n";
    }
}

// ---------------------------------------------------------------------
// Auxiliares de selecao e exibicao
// ---------------------------------------------------------------------

bool ApresentacaoKanban::escolherProjeto(Identificador& id) {
    vector<Projeto> lista = servico->listarProjetos(usuario);
    if (lista.empty()) {
        cout << "  Nenhum projeto disponivel.\n";
        return false;
    }
    cout << "  Projetos disponiveis:\n";
    for (size_t i = 0; i < lista.size(); i++) {
        cout << "    " << lista[i].getIdentificador().getValor() << " - " << lista[i].getNome().getValor() << "\n";
    }
    while (true) {
        Identificador tmp;
        if (!lerCampo("Identificador do projeto", "", tmp)) return false;
        if (contem(lista, tmp)) {
            id = tmp;
            return true;
        }
        cout << "  ! Identificador fora da lista.\n";
    }
}

bool ApresentacaoKanban::escolherQuadro(Identificador& id) {
    Identificador idProjeto;
    if (!escolherProjeto(idProjeto)) return false;
    vector<Quadro> lista = servico->listarQuadros(usuario, idProjeto);
    if (lista.empty()) {
        cout << "  Este projeto ainda nao tem quadros.\n";
        return false;
    }
    cout << "\n  Quadros do projeto:\n";
    for (size_t i = 0; i < lista.size(); i++) {
        cout << "    " << lista[i].getIdentificador().getValor() << " - " << lista[i].getNome().getValor() << "\n";
    }
    while (true) {
        Identificador tmp;
        if (!lerCampo("Identificador do quadro", "", tmp)) return false;
        if (contem(lista, tmp)) {
            id = tmp;
            return true;
        }
        cout << "  ! Identificador fora da lista.\n";
    }
}

bool ApresentacaoKanban::escolherCartao(const Identificador& quadro, Identificador& id) {
    vector<CartaoAtividade> lista = servico->listarCartoes(usuario, quadro);
    if (lista.empty()) {
        cout << "  Este quadro ainda nao tem cartoes.\n";
        return false;
    }
    cout << "\n  Cartoes do quadro:\n";
    for (size_t i = 0; i < lista.size(); i++) {
        cout << "    " << lista[i].getIdentificador().getValor() << " - " << lista[i].getNome().getValor()
             << " (" << lista[i].getEstado().toString() << ")\n";
    }
    while (true) {
        Identificador tmp;
        if (!lerCampo("Identificador do cartao", "", tmp)) return false;
        if (contem(lista, tmp)) {
            id = tmp;
            return true;
        }
        cout << "  ! Identificador fora da lista.\n";
    }
}

string ApresentacaoKanban::nomeDoResponsavel(const Identificador& idCartao) {
    string e = servico->responsavelDoCartao(usuario, idCartao);
    if (e.empty()) return "--";
    return servico->consultarPessoa(Email(e)).getNome().getValor();
}

void ApresentacaoKanban::exibirQuadro(const Identificador& idQuadro) {
    Quadro q = servico->consultarQuadro(usuario, idQuadro);
    vector<CartaoAtividade> v = servico->listarCartoes(usuario, idQuadro);

    const size_t L = 22;
    vector<string> col[3];
    int cont[3] = {0, 0, 0};
    for (size_t i = 0; i < v.size(); i++) {
        int k = (int)v[i].getEstado().getValor(); // A_FAZER=0, FAZENDO=1, FEITO=2
        cont[k]++;
        col[k].push_back("[" + v[i].getIdentificador().getValor() + "]");
        col[k].push_back(v[i].getNome().getValor());
        col[k].push_back(v[i].getPrioridade().toString() + " | " + v[i].getTamanho().toString());
        col[k].push_back("Resp: " + nomeDoResponsavel(v[i].getIdentificador()));
        col[k].push_back("");
    }
    size_t linhas = 1;
    for (int k = 0; k < 3; k++) {
        if (col[k].empty()) col[k].push_back("(vazio)");
        if (col[k].size() > linhas) linhas = col[k].size();
    }

    string cab[3];
    cab[0] = "A FAZER (" + num(cont[0]) + ")";
    cab[1] = "FAZENDO (" + num(cont[1]) + "/" + num(q.getLimite().getValor()) + ")";
    cab[2] = "FEITO (" + num(cont[2]) + ")";

    string sep;
    for (int k = 0; k < 3; k++) sep += "+" + string(L + 2, '-');
    sep += "+";

    cout << "\n  Quadro: " << q.getNome().getValor() << " [" << q.getIdentificador().getValor() << "]\n";
    cout << sep << "\n";
    for (int k = 0; k < 3; k++) cout << "| " << ajustar(cab[k], L) << " ";
    cout << "|\n" << sep << "\n";
    for (size_t r = 0; r < linhas; r++) {
        for (int k = 0; k < 3; k++) {
            cout << "| " << ajustar(r < col[k].size() ? col[k][r] : "", L) << " ";
        }
        cout << "|\n";
    }
    cout << sep << "\n";
    if (cont[1] >= q.getLimite().getValor()) {
        cout << "  ! A coluna FAZENDO atingiu o limite de WIP.\n";
    }
}
