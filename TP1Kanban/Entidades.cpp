#include "Entidades.h"

// ---------------------------------------------------------------------
// Pessoa
// ---------------------------------------------------------------------

Pessoa::Pessoa(const Email& email, const Nome& nome, const Senha& senha, const Papel& papel)
    : email(email), nome(nome), senha(senha), papel(papel) {}

Email Pessoa::getEmail() const {
    return email;
}

Nome Pessoa::getNome() const {
    return nome;
}

void Pessoa::setNome(const Nome& novoNome) {
    nome = novoNome;
}

Senha Pessoa::getSenha() const {
    return senha;
}

void Pessoa::setSenha(const Senha& novaSenha) {
    senha = novaSenha;
}

Papel Pessoa::getPapel() const {
    return papel;
}

void Pessoa::setPapel(const Papel& novoPapel) {
    papel = novoPapel;
}

// ---------------------------------------------------------------------
// Projeto
// ---------------------------------------------------------------------

Projeto::Projeto(const Identificador& identificador, const Nome& nome, const Texto& descricao,
                  const Timestamp& inicio, const Timestamp& termino)
    : identificador(identificador), nome(nome), descricao(descricao),
      inicio(inicio), termino(termino) {}

Identificador Projeto::getIdentificador() const {
    return identificador;
}

Nome Projeto::getNome() const {
    return nome;
}

void Projeto::setNome(const Nome& novoNome) {
    nome = novoNome;
}

Texto Projeto::getDescricao() const {
    return descricao;
}

void Projeto::setDescricao(const Texto& novaDescricao) {
    descricao = novaDescricao;
}

Timestamp Projeto::getInicio() const {
    return inicio;
}

void Projeto::setInicio(const Timestamp& novoInicio) {
    inicio = novoInicio;
}

Timestamp Projeto::getTermino() const {
    return termino;
}

void Projeto::setTermino(const Timestamp& novoTermino) {
    termino = novoTermino;
}

// ---------------------------------------------------------------------
// Quadro
// ---------------------------------------------------------------------

Quadro::Quadro(const Identificador& identificador, const Nome& nome, const Limite& limite)
    : identificador(identificador), nome(nome), limite(limite) {}

Identificador Quadro::getIdentificador() const {
    return identificador;
}

Nome Quadro::getNome() const {
    return nome;
}

void Quadro::setNome(const Nome& novoNome) {
    nome = novoNome;
}

Limite Quadro::getLimite() const {
    return limite;
}

void Quadro::setLimite(const Limite& novoLimite) {
    limite = novoLimite;
}

// ---------------------------------------------------------------------
// CartaoAtividade
// ---------------------------------------------------------------------

CartaoAtividade::CartaoAtividade(const Identificador& identificador, const Nome& nome, const Texto& descricao,
                                  const Prioridade& prioridade, const Estado& estado, const Tamanho& tamanho,
                                  const Timestamp& entrada, const Timestamp& inicio, const Timestamp& termino)
    : identificador(identificador), nome(nome), descricao(descricao),
      prioridade(prioridade), estado(estado), tamanho(tamanho),
      entrada(entrada), inicio(inicio), termino(termino) {}

Identificador CartaoAtividade::getIdentificador() const {
    return identificador;
}

Nome CartaoAtividade::getNome() const {
    return nome;
}

void CartaoAtividade::setNome(const Nome& novoNome) {
    nome = novoNome;
}

Texto CartaoAtividade::getDescricao() const {
    return descricao;
}

void CartaoAtividade::setDescricao(const Texto& novaDescricao) {
    descricao = novaDescricao;
}

Prioridade CartaoAtividade::getPrioridade() const {
    return prioridade;
}

void CartaoAtividade::setPrioridade(const Prioridade& novaPrioridade) {
    prioridade = novaPrioridade;
}

Estado CartaoAtividade::getEstado() const {
    return estado;
}

void CartaoAtividade::setEstado(const Estado& novoEstado) {
    estado = novoEstado;
}

Tamanho CartaoAtividade::getTamanho() const {
    return tamanho;
}

void CartaoAtividade::setTamanho(const Tamanho& novoTamanho) {
    tamanho = novoTamanho;
}

Timestamp CartaoAtividade::getEntrada() const {
    return entrada;
}

void CartaoAtividade::setEntrada(const Timestamp& novaEntrada) {
    entrada = novaEntrada;
}

Timestamp CartaoAtividade::getInicio() const {
    return inicio;
}

void CartaoAtividade::setInicio(const Timestamp& novoInicio) {
    inicio = novoInicio;
}

Timestamp CartaoAtividade::getTermino() const {
    return termino;
}

void CartaoAtividade::setTermino(const Timestamp& novoTermino) {
    termino = novoTermino;
}
