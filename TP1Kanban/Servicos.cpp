#include "Servicos.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

using std::string;
using std::vector;
using std::runtime_error;

namespace {

/** Retorna o instante atual no formato DD-MES-AAAA-HH:MM. */
Timestamp agora() {
    static const char* meses[] = {"JAN", "FEV", "MAR", "ABR", "MAI", "JUN",
                                  "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"};
    time_t t = time(0);
    tm* lt = localtime(&t);
    char buf[32];
    snprintf(buf, sizeof(buf), "%02d-%s-%04d-%02d:%02d",
             lt->tm_mday, meses[lt->tm_mon], lt->tm_year + 1900, lt->tm_hour, lt->tm_min);
    return Timestamp(buf);
}

/** Converte um timestamp em numero comparavel (AAAAMMDDHHMM). */
long long chaveTempo(const Timestamp& t) {
    static const char* meses[] = {"JAN", "FEV", "MAR", "ABR", "MAI", "JUN",
                                  "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"};
    int m = 0;
    for (int i = 0; i < 12; i++) {
        if (t.getMes() == meses[i]) m = i + 1;
    }
    int hh = atoi(t.getHorario().substr(0, 2).c_str());
    int mm = atoi(t.getHorario().substr(3, 2).c_str());
    return ((((long long)t.getAno() * 100 + m) * 100 + t.getDia()) * 100 + hh) * 100 + mm;
}

void validarPeriodo(const Timestamp& inicio, const Timestamp& termino) {
    if (chaveTempo(termino) < chaveTempo(inicio)) {
        throw runtime_error("O termino nao pode ser anterior ao inicio.");
    }
}

string numero(int n) {
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", n);
    return buf;
}

} // namespace

// ---------------------------------------------------------------------
// Auxiliares privados
// ---------------------------------------------------------------------

int ServicoKanban::indicePessoa(const string& email) const {
    for (size_t i = 0; i < pessoas.size(); i++) {
        if (pessoas[i].getEmail().getValor() == email) return (int)i;
    }
    return -1;
}

int ServicoKanban::indiceProjeto(const string& id) const {
    for (size_t i = 0; i < projetos.size(); i++) {
        if (projetos[i].projeto.getIdentificador().getValor() == id) return (int)i;
    }
    return -1;
}

int ServicoKanban::indiceQuadro(const string& id) const {
    for (size_t i = 0; i < quadros.size(); i++) {
        if (quadros[i].quadro.getIdentificador().getValor() == id) return (int)i;
    }
    return -1;
}

int ServicoKanban::indiceCartao(const string& id) const {
    for (size_t i = 0; i < cartoes.size(); i++) {
        if (cartoes[i].cartao.getIdentificador().getValor() == id) return (int)i;
    }
    return -1;
}

bool ServicoKanban::temAcesso(const string& solicitante, const string& idProjeto) const {
    int ip = indiceProjeto(idProjeto);
    if (ip < 0) return false;
    if (projetos[ip].gestor == solicitante) return true;
    for (size_t i = 0; i < cartoes.size(); i++) {
        if (cartoes[i].responsavel != solicitante) continue;
        int iq = indiceQuadro(cartoes[i].quadro);
        if (iq >= 0 && quadros[iq].projeto == idProjeto) return true;
    }
    return false;
}

void ServicoKanban::exigirAcesso(const string& solicitante, const string& idProjeto) const {
    if (indiceProjeto(idProjeto) < 0) throw runtime_error("Projeto nao encontrado.");
    if (!temAcesso(solicitante, idProjeto)) throw runtime_error("Voce nao tem acesso a este projeto.");
}

void ServicoKanban::exigirGestor(const string& solicitante, const string& idProjeto) const {
    int ip = indiceProjeto(idProjeto);
    if (ip < 0) throw runtime_error("Projeto nao encontrado.");
    if (projetos[ip].gestor != solicitante) {
        throw runtime_error("Apenas o gestor deste projeto pode realizar esta operacao.");
    }
}

int ServicoKanban::contarEstado(const string& idQuadro, Estado::Valor estado) const {
    int n = 0;
    for (size_t i = 0; i < cartoes.size(); i++) {
        if (cartoes[i].quadro == idQuadro && cartoes[i].cartao.getEstado().getValor() == estado) n++;
    }
    return n;
}

void ServicoKanban::removerCartoesDoQuadro(const string& idQuadro) {
    for (size_t i = cartoes.size(); i > 0; i--) {
        if (cartoes[i - 1].quadro == idQuadro) cartoes.erase(cartoes.begin() + (i - 1));
    }
}

// ---------------------------------------------------------------------
// Pessoas
// ---------------------------------------------------------------------

void ServicoKanban::cadastrarPessoa(const Pessoa& pessoa) {
    if (indicePessoa(pessoa.getEmail().getValor()) >= 0) {
        throw runtime_error("Ja existe uma pessoa cadastrada com este e-mail.");
    }
    pessoas.push_back(pessoa);
}

Pessoa ServicoKanban::autenticar(const Email& email, const Senha& senha) {
    int i = indicePessoa(email.getValor());
    if (i < 0 || pessoas[i].getSenha().getValor() != senha.getValor()) {
        throw runtime_error("E-mail ou senha incorretos.");
    }
    return pessoas[i];
}

Pessoa ServicoKanban::consultarPessoa(const Email& email) const {
    int i = indicePessoa(email.getValor());
    if (i < 0) throw runtime_error("Pessoa nao encontrada.");
    return pessoas[i];
}

void ServicoKanban::atualizarPessoa(const Pessoa& pessoa) {
    int i = indicePessoa(pessoa.getEmail().getValor());
    if (i < 0) throw runtime_error("Pessoa nao encontrada.");
    pessoas[i].setNome(pessoa.getNome());
    pessoas[i].setSenha(pessoa.getSenha());
}

void ServicoKanban::excluirPessoa(const Email& email) {
    int i = indicePessoa(email.getValor());
    if (i < 0) throw runtime_error("Pessoa nao encontrada.");
    for (size_t k = 0; k < projetos.size(); k++) {
        if (projetos[k].gestor == email.getValor()) {
            throw runtime_error("Esta pessoa e gestora de projetos. Exclua os projetos antes de excluir a conta.");
        }
    }
    for (size_t k = 0; k < cartoes.size(); k++) {
        if (cartoes[k].responsavel == email.getValor()) cartoes[k].responsavel = "";
    }
    pessoas.erase(pessoas.begin() + i);
}

vector<Pessoa> ServicoKanban::listarDesenvolvedores() const {
    vector<Pessoa> r;
    for (size_t i = 0; i < pessoas.size(); i++) {
        if (pessoas[i].getPapel().getValor() == Papel::DESENVOLVEDOR) r.push_back(pessoas[i]);
    }
    return r;
}

// ---------------------------------------------------------------------
// Projetos
// ---------------------------------------------------------------------

void ServicoKanban::criarProjeto(const Email& solicitante, const Projeto& projeto) {
    int ig = indicePessoa(solicitante.getValor());
    if (ig < 0 || pessoas[ig].getPapel().getValor() != Papel::GESTOR) {
        throw runtime_error("Apenas gestores podem criar projetos.");
    }
    if (indiceProjeto(projeto.getIdentificador().getValor()) >= 0) {
        throw runtime_error("Ja existe um projeto com este identificador.");
    }
    validarPeriodo(projeto.getInicio(), projeto.getTermino());
    projetos.push_back(RegProjeto(projeto, solicitante.getValor()));
}

Projeto ServicoKanban::consultarProjeto(const Email& solicitante, const Identificador& id) const {
    exigirAcesso(solicitante.getValor(), id.getValor());
    return projetos[indiceProjeto(id.getValor())].projeto;
}

void ServicoKanban::atualizarProjeto(const Email& solicitante, const Projeto& projeto) {
    const string id = projeto.getIdentificador().getValor();
    exigirGestor(solicitante.getValor(), id);
    validarPeriodo(projeto.getInicio(), projeto.getTermino());
    projetos[indiceProjeto(id)].projeto = projeto;
}

void ServicoKanban::excluirProjeto(const Email& solicitante, const Identificador& id) {
    exigirGestor(solicitante.getValor(), id.getValor());
    for (size_t i = quadros.size(); i > 0; i--) {
        if (quadros[i - 1].projeto == id.getValor()) {
            removerCartoesDoQuadro(quadros[i - 1].quadro.getIdentificador().getValor());
            quadros.erase(quadros.begin() + (i - 1));
        }
    }
    projetos.erase(projetos.begin() + indiceProjeto(id.getValor()));
}

vector<Projeto> ServicoKanban::listarProjetos(const Email& solicitante) const {
    vector<Projeto> r;
    for (size_t i = 0; i < projetos.size(); i++) {
        if (temAcesso(solicitante.getValor(), projetos[i].projeto.getIdentificador().getValor())) {
            r.push_back(projetos[i].projeto);
        }
    }
    return r;
}

// ---------------------------------------------------------------------
// Quadros
// ---------------------------------------------------------------------

void ServicoKanban::criarQuadro(const Email& solicitante, const Identificador& projeto, const Quadro& quadro) {
    exigirGestor(solicitante.getValor(), projeto.getValor());
    if (indiceQuadro(quadro.getIdentificador().getValor()) >= 0) {
        throw runtime_error("Ja existe um quadro com este identificador.");
    }
    quadros.push_back(RegQuadro(quadro, projeto.getValor()));
}

Quadro ServicoKanban::consultarQuadro(const Email& solicitante, const Identificador& id) const {
    int iq = indiceQuadro(id.getValor());
    if (iq < 0) throw runtime_error("Quadro nao encontrado.");
    exigirAcesso(solicitante.getValor(), quadros[iq].projeto);
    return quadros[iq].quadro;
}

void ServicoKanban::atualizarQuadro(const Email& solicitante, const Quadro& quadro) {
    const string id = quadro.getIdentificador().getValor();
    int iq = indiceQuadro(id);
    if (iq < 0) throw runtime_error("Quadro nao encontrado.");
    exigirGestor(solicitante.getValor(), quadros[iq].projeto);
    int emAndamento = contarEstado(id, Estado::FAZENDO);
    if (emAndamento > quadro.getLimite().getValor()) {
        throw runtime_error("O quadro ja tem " + numero(emAndamento) +
                            " cartoes em FAZENDO, mais do que o novo limite.");
    }
    quadros[iq].quadro = quadro;
}

void ServicoKanban::excluirQuadro(const Email& solicitante, const Identificador& id) {
    int iq = indiceQuadro(id.getValor());
    if (iq < 0) throw runtime_error("Quadro nao encontrado.");
    exigirGestor(solicitante.getValor(), quadros[iq].projeto);
    removerCartoesDoQuadro(id.getValor());
    quadros.erase(quadros.begin() + iq);
}

vector<Quadro> ServicoKanban::listarQuadros(const Email& solicitante, const Identificador& projeto) const {
    exigirAcesso(solicitante.getValor(), projeto.getValor());
    vector<Quadro> r;
    for (size_t i = 0; i < quadros.size(); i++) {
        if (quadros[i].projeto == projeto.getValor()) r.push_back(quadros[i].quadro);
    }
    return r;
}

// ---------------------------------------------------------------------
// Cartoes
// ---------------------------------------------------------------------

void ServicoKanban::criarCartao(const Email& solicitante, const Identificador& quadro, const CartaoAtividade& cartao) {
    int iq = indiceQuadro(quadro.getValor());
    if (iq < 0) throw runtime_error("Quadro nao encontrado.");
    exigirGestor(solicitante.getValor(), quadros[iq].projeto);
    if (indiceCartao(cartao.getIdentificador().getValor()) >= 0) {
        throw runtime_error("Ja existe um cartao com este identificador.");
    }
    CartaoAtividade novo(cartao.getIdentificador(), cartao.getNome(), cartao.getDescricao(),
                         cartao.getPrioridade(), Estado(Estado::A_FAZER), cartao.getTamanho(),
                         agora(), Timestamp(), Timestamp());
    cartoes.push_back(RegCartao(novo, quadro.getValor(), ""));
}

CartaoAtividade ServicoKanban::consultarCartao(const Email& solicitante, const Identificador& id) const {
    int ic = indiceCartao(id.getValor());
    if (ic < 0) throw runtime_error("Cartao nao encontrado.");
    exigirAcesso(solicitante.getValor(), quadros[indiceQuadro(cartoes[ic].quadro)].projeto);
    return cartoes[ic].cartao;
}

void ServicoKanban::atualizarCartao(const Email& solicitante, const CartaoAtividade& cartao) {
    int ic = indiceCartao(cartao.getIdentificador().getValor());
    if (ic < 0) throw runtime_error("Cartao nao encontrado.");
    exigirGestor(solicitante.getValor(), quadros[indiceQuadro(cartoes[ic].quadro)].projeto);
    CartaoAtividade& c = cartoes[ic].cartao;
    c.setNome(cartao.getNome());
    c.setDescricao(cartao.getDescricao());
    c.setPrioridade(cartao.getPrioridade());
    c.setTamanho(cartao.getTamanho());
}

void ServicoKanban::excluirCartao(const Email& solicitante, const Identificador& id) {
    int ic = indiceCartao(id.getValor());
    if (ic < 0) throw runtime_error("Cartao nao encontrado.");
    exigirGestor(solicitante.getValor(), quadros[indiceQuadro(cartoes[ic].quadro)].projeto);
    cartoes.erase(cartoes.begin() + ic);
}

vector<CartaoAtividade> ServicoKanban::listarCartoes(const Email& solicitante, const Identificador& quadro) const {
    int iq = indiceQuadro(quadro.getValor());
    if (iq < 0) throw runtime_error("Quadro nao encontrado.");
    exigirAcesso(solicitante.getValor(), quadros[iq].projeto);
    vector<CartaoAtividade> r;
    for (size_t i = 0; i < cartoes.size(); i++) {
        if (cartoes[i].quadro == quadro.getValor()) r.push_back(cartoes[i].cartao);
    }
    return r;
}

void ServicoKanban::atribuirCartao(const Email& solicitante, const Identificador& cartao, const Email& desenvolvedor) {
    int ic = indiceCartao(cartao.getValor());
    if (ic < 0) throw runtime_error("Cartao nao encontrado.");
    exigirGestor(solicitante.getValor(), quadros[indiceQuadro(cartoes[ic].quadro)].projeto);
    int ip = indicePessoa(desenvolvedor.getValor());
    if (ip < 0 || pessoas[ip].getPapel().getValor() != Papel::DESENVOLVEDOR) {
        throw runtime_error("O responsavel precisa ser um desenvolvedor cadastrado.");
    }
    cartoes[ic].responsavel = desenvolvedor.getValor();
}

string ServicoKanban::responsavelDoCartao(const Email& solicitante, const Identificador& cartao) const {
    int ic = indiceCartao(cartao.getValor());
    if (ic < 0) throw runtime_error("Cartao nao encontrado.");
    exigirAcesso(solicitante.getValor(), quadros[indiceQuadro(cartoes[ic].quadro)].projeto);
    return cartoes[ic].responsavel;
}

void ServicoKanban::moverCartao(const Email& solicitante, const Identificador& cartao, const Estado& destino) {
    int ic = indiceCartao(cartao.getValor());
    if (ic < 0) throw runtime_error("Cartao nao encontrado.");
    int iq = indiceQuadro(cartoes[ic].quadro);
    const string idProjeto = quadros[iq].projeto;

    bool ehGestor = projetos[indiceProjeto(idProjeto)].gestor == solicitante.getValor();
    bool ehResponsavel = cartoes[ic].responsavel == solicitante.getValor();
    if (!ehGestor && !ehResponsavel) {
        throw runtime_error("Somente o gestor do projeto ou o desenvolvedor responsavel pode mover este cartao.");
    }

    CartaoAtividade& c = cartoes[ic].cartao;
    Estado::Valor atual = c.getEstado().getValor();
    Estado::Valor novo = destino.getValor();

    bool permitido = (atual == Estado::A_FAZER && novo == Estado::FAZENDO) ||
                     (atual == Estado::FAZENDO && (novo == Estado::FEITO || novo == Estado::A_FAZER)) ||
                     (atual == Estado::FEITO && novo == Estado::FAZENDO);
    if (!permitido) {
        throw runtime_error("Movimento nao permitido: " + Estado(atual).toString() + " -> " +
                            destino.toString() + ". Os cartoes andam uma coluna por vez.");
    }

    if (novo == Estado::FAZENDO) {
        int limite = quadros[iq].quadro.getLimite().getValor();
        if (contarEstado(cartoes[ic].quadro, Estado::FAZENDO) >= limite) {
            throw runtime_error("A coluna FAZENDO ja atingiu o limite de WIP (" + numero(limite) + ").");
        }
    }

    c.setEstado(Estado(novo));
    if (novo == Estado::FAZENDO) {
        if (atual == Estado::A_FAZER) c.setInicio(agora());
        else c.setTermino(Timestamp()); // voltou de FEITO
    } else if (novo == Estado::FEITO) {
        c.setTermino(agora());
    } else {
        c.setInicio(Timestamp()); // voltou para A FAZER
    }
}
