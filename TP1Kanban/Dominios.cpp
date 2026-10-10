#include "Dominios.h"
#include <cctype>
#include <algorithm>
#include <vector>

// ---------------------------------------------------------------------
// Email
// ---------------------------------------------------------------------

Email::Email() : valor("parte-local@domínio") {}

Email::Email(const std::string& valorInicial) {
    setValor(valorInicial);
}

bool Email::parteLocalValida(const std::string& parte) {
    if (parte.empty() || parte.size() > 64) return false;
    if (parte.front() == '.' || parte.front() == '-') return false;
    if (parte.back() == '.' || parte.back() == '-') return false;

    for (size_t i = 0; i < parte.size(); ++i) {
        char c = parte[i];
        bool letra = (c >= 'a' && c <= 'z');
        bool digito = (c >= '0' && c <= '9');
        bool pontuacao = (c == '.' || c == '-');

        if (!letra && !digito && !pontuacao) return false;

        if (pontuacao) {
            char proximo = (i + 1 < parte.size()) ? parte[i + 1] : '\0';
            bool proximoValido = (proximo >= 'a' && proximo <= 'z') ||
                                  (proximo >= '0' && proximo <= '9');
            if (!proximoValido) return false;
        }
    }
    return true;
}

bool Email::dominioValido(const std::string& dominio) {
    if (dominio.empty() || dominio.size() > 255) return false;

    std::string parteAtual;
    std::vector<std::string> partes;
    for (char c : dominio) {
        if (c == '.') {
            partes.push_back(parteAtual);
            parteAtual.clear();
        } else {
            parteAtual += c;
        }
    }
    partes.push_back(parteAtual);

    for (const std::string& parte : partes) {
        if (parte.empty()) return false;
        if (parte.front() == '-' || parte.back() == '-') return false;
        for (char c : parte) {
            bool letra = (c >= 'a' && c <= 'z');
            bool digito = (c >= '0' && c <= '9');
            bool hifen = (c == '-');
            if (!letra && !digito && !hifen) return false;
        }
    }
    return true;
}

std::string Email::getValor() const {
    return valor;
}

void Email::setValor(const std::string& novoValor) {
    size_t posArroba = novoValor.find('@');
    if (posArroba == std::string::npos ||
        posArroba != novoValor.rfind('@')) {
        throw std::invalid_argument("Email invalido: deve conter exatamente um '@'.");
    }

    std::string parteLocal = novoValor.substr(0, posArroba);
    std::string dominio = novoValor.substr(posArroba + 1);

    if (!parteLocalValida(parteLocal) || !dominioValido(dominio)) {
        throw std::invalid_argument("Email invalido: formato nao corresponde ao esperado.");
    }

    valor = novoValor;
}

// ---------------------------------------------------------------------
// Estado
// ---------------------------------------------------------------------

Estado::Estado() : valor(A_FAZER) {}

Estado::Estado(Valor valorInicial) : valor(valorInicial) {}

Estado::Estado(const std::string& texto) {
    setValor(texto);
}

Estado::Valor Estado::converter(const std::string& texto) {
    if (texto == "A FAZER") return A_FAZER;
    if (texto == "FAZENDO") return FAZENDO;
    if (texto == "FEITO") return FEITO;
    throw std::invalid_argument("Estado invalido: " + texto);
}

Estado::Valor Estado::getValor() const {
    return valor;
}

void Estado::setValor(Valor novoValor) {
    valor = novoValor;
}

void Estado::setValor(const std::string& texto) {
    valor = converter(texto);
}

std::string Estado::toString() const {
    switch (valor) {
        case A_FAZER: return "A FAZER";
        case FAZENDO: return "FAZENDO";
        case FEITO: return "FEITO";
    }
    return "";
}

// ---------------------------------------------------------------------
// Identificador
// ---------------------------------------------------------------------

Identificador::Identificador() : valor("AAA000") {}

Identificador::Identificador(const std::string& valorInicial) {
    setValor(valorInicial);
}

std::string Identificador::getValor() const {
    return valor;
}

void Identificador::setValor(const std::string& novoValor) {
    if (novoValor.size() != 6) {
        throw std::invalid_argument("Identificador invalido: deve ter 6 caracteres.");
    }
    for (int i = 0; i < 3; ++i) {
        char c = novoValor[i];
        bool letra = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        if (!letra) {
            throw std::invalid_argument("Identificador invalido: os 3 primeiros caracteres devem ser letras.");
        }
    }
    for (int i = 3; i < 6; ++i) {
        char c = novoValor[i];
        if (!(c >= '0' && c <= '9')) {
            throw std::invalid_argument("Identificador invalido: os 3 ultimos caracteres devem ser digitos.");
        }
    }
    valor = novoValor;
}

// ---------------------------------------------------------------------
// Limite
// ---------------------------------------------------------------------

Limite::Limite() : valor(1) {}

Limite::Limite(int valorInicial) {
    setValor(valorInicial);
}

int Limite::getValor() const {
    return valor;
}

void Limite::setValor(int novoValor) {
    if (novoValor < 1 || novoValor > 25) {
        throw std::invalid_argument("Limite invalido: deve estar entre 1 e 25.");
    }
    valor = novoValor;
}

// ---------------------------------------------------------------------
// Nome
// ---------------------------------------------------------------------

Nome::Nome() : valor("Nome") {}

Nome::Nome(const std::string& valorInicial) {
    setValor(valorInicial);
}

std::string Nome::getValor() const {
    return valor;
}

void Nome::setValor(const std::string& novoValor) {
    if (novoValor.empty() || novoValor.size() > 15) {
        throw std::invalid_argument("Nome invalido: deve ter entre 1 e 15 caracteres.");
    }
    if (novoValor.front() == ' ' || novoValor.back() == ' ') {
        throw std::invalid_argument("Nome invalido: nao pode iniciar ou terminar com espaco.");
    }
    for (size_t i = 0; i < novoValor.size(); ++i) {
        char c = novoValor[i];
        bool letra = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        bool espaco = (c == ' ');
        if (!letra && !espaco) {
            throw std::invalid_argument("Nome invalido: caractere nao permitido.");
        }
        if (espaco) {
            char proximo = novoValor[i + 1]; // seguro: ultimo caractere nao e espaco
            bool proximoLetra = (proximo >= 'a' && proximo <= 'z') || (proximo >= 'A' && proximo <= 'Z');
            if (!proximoLetra) {
                throw std::invalid_argument("Nome invalido: espaco deve ser seguido por letra.");
            }
        }
    }
    valor = novoValor;
}

// ---------------------------------------------------------------------
// Papel
// ---------------------------------------------------------------------

Papel::Papel() : valor(DESENVOLVEDOR) {}

Papel::Papel(Valor valorInicial) : valor(valorInicial) {}

Papel::Papel(const std::string& texto) {
    setValor(texto);
}

Papel::Valor Papel::converter(const std::string& texto) {
    if (texto == "GESTOR") return GESTOR;
    if (texto == "DESENVOLVEDOR") return DESENVOLVEDOR;
    throw std::invalid_argument("Papel invalido: " + texto);
}

Papel::Valor Papel::getValor() const {
    return valor;
}

void Papel::setValor(Valor novoValor) {
    valor = novoValor;
}

void Papel::setValor(const std::string& texto) {
    valor = converter(texto);
}

std::string Papel::toString() const {
    switch (valor) {
        case GESTOR: return "GESTOR";
        case DESENVOLVEDOR: return "DESENVOLVEDOR";
    }
    return "";
}

// ---------------------------------------------------------------------
// Prioridade
// ---------------------------------------------------------------------

Prioridade::Prioridade() : valor(BAIXA) {}

Prioridade::Prioridade(Valor valorInicial) : valor(valorInicial) {}

Prioridade::Prioridade(const std::string& texto) {
    setValor(texto);
}

Prioridade::Valor Prioridade::converter(const std::string& texto) {
    if (texto == "ALTA") return ALTA;
    if (texto == "MEDIA") return MEDIA;
    if (texto == "BAIXA") return BAIXA;
    throw std::invalid_argument("Prioridade invalida: " + texto);
}

Prioridade::Valor Prioridade::getValor() const {
    return valor;
}

void Prioridade::setValor(Valor novoValor) {
    valor = novoValor;
}

void Prioridade::setValor(const std::string& texto) {
    valor = converter(texto);
}

std::string Prioridade::toString() const {
    switch (valor) {
        case ALTA: return "ALTA";
        case MEDIA: return "MEDIA";
        case BAIXA: return "BAIXA";
    }
    return "";
}

// ---------------------------------------------------------------------
// Senha
// ---------------------------------------------------------------------

Senha::Senha() : valor("Abc12") {}

Senha::Senha(const std::string& valorInicial) {
    setValor(valorInicial);
}

std::string Senha::getValor() const {
    return valor;
}

void Senha::setValor(const std::string& novoValor) {
    if (novoValor.size() != 5) {
        throw std::invalid_argument("Senha invalida: deve ter 5 caracteres.");
    }
    bool temLetra = false;
    bool temDigito = false;
    for (char c : novoValor) {
        bool letra = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        bool digito = (c >= '0' && c <= '9');
        if (!letra && !digito) {
            throw std::invalid_argument("Senha invalida: caractere nao permitido.");
        }
        if (letra) temLetra = true;
        if (digito) temDigito = true;
    }
    if (!temLetra || !temDigito) {
        throw std::invalid_argument("Senha invalida: deve conter ao menos uma letra e um digito.");
    }
    valor = novoValor;
}

// ---------------------------------------------------------------------
// Tamanho
// ---------------------------------------------------------------------

Tamanho::Tamanho() : valor(MEDIO) {}

Tamanho::Tamanho(Valor valorInicial) : valor(valorInicial) {}

Tamanho::Tamanho(const std::string& texto) {
    setValor(texto);
}

Tamanho::Valor Tamanho::converter(const std::string& texto) {
    if (texto == "GRANDE") return GRANDE;
    if (texto == "MEDIO") return MEDIO;
    if (texto == "PEQUENO") return PEQUENO;
    throw std::invalid_argument("Tamanho invalido: " + texto);
}

Tamanho::Valor Tamanho::getValor() const {
    return valor;
}

void Tamanho::setValor(Valor novoValor) {
    valor = novoValor;
}

void Tamanho::setValor(const std::string& texto) {
    valor = converter(texto);
}

std::string Tamanho::toString() const {
    switch (valor) {
        case GRANDE: return "GRANDE";
        case MEDIO: return "MEDIO";
        case PEQUENO: return "PEQUENO";
    }
    return "";
}

// ---------------------------------------------------------------------
// Texto
// ---------------------------------------------------------------------

Texto::Texto() : valor("Texto.") {}

Texto::Texto(const std::string& valorInicial) {
    setValor(valorInicial);
}

bool Texto::ehPontuacao(char c) {
    return c == ',' || c == ';' || c == '.' || c == ':' || c == '?' || c == '!';
}

std::string Texto::getValor() const {
    return valor;
}

void Texto::setValor(const std::string& novoValor) {
    if (novoValor.empty() || novoValor.size() > 30) {
        throw std::invalid_argument("Texto invalido: deve ter entre 1 e 30 caracteres.");
    }
    if (!(novoValor.front() >= 'A' && novoValor.front() <= 'Z')) {
        throw std::invalid_argument("Texto invalido: primeiro caractere deve ser letra maiuscula.");
    }
    if (novoValor.back() != '.') {
        throw std::invalid_argument("Texto invalido: ultimo caractere deve ser ponto.");
    }

    for (size_t i = 0; i < novoValor.size(); ++i) {
        char c = novoValor[i];
        bool letra = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        bool digito = (c >= '0' && c <= '9');
        bool espaco = (c == ' ');
        bool pontuacao = ehPontuacao(c);

        if (!letra && !digito && !espaco && !pontuacao) {
            throw std::invalid_argument("Texto invalido: caractere nao permitido.");
        }

        if (pontuacao && i + 1 < novoValor.size() && ehPontuacao(novoValor[i + 1])) {
            throw std::invalid_argument("Texto invalido: sinal de pontuacao nao pode ser seguido por outro sinal de pontuacao.");
        }
    }
    valor = novoValor;
}

// ---------------------------------------------------------------------
// Timestamp
// ---------------------------------------------------------------------

Timestamp::Timestamp() : valor("01-JAN-2000-00:00"), dia(1), mes("JAN"), ano(2000), horario("00:00") {}

Timestamp::Timestamp(const std::string& valorInicial) {
    setValor(valorInicial);
}

bool Timestamp::mesValido(const std::string& mes) {
    static const std::string meses[] = {
        "JAN", "FEV", "MAR", "ABR", "MAI", "JUN",
        "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"
    };
    for (const std::string& m : meses) {
        if (mes == m) return true;
    }
    return false;
}

bool Timestamp::anoBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int Timestamp::diasNoMes(const std::string& mes, int ano) {
    if (mes == "JAN" || mes == "MAR" || mes == "MAI" || mes == "JUL" ||
        mes == "AGO" || mes == "OUT" || mes == "DEZ") {
        return 31;
    }
    if (mes == "ABR" || mes == "JUN" || mes == "SET" || mes == "NOV") {
        return 30;
    }
    if (mes == "FEV") {
        return anoBissexto(ano) ? 29 : 28;
    }
    return 0;
}

bool Timestamp::horarioValido(const std::string& horario) {
    if (horario.size() != 5 || horario[2] != ':') return false;
    for (int i = 0; i < 5; ++i) {
        if (i == 2) continue;
        if (!(horario[i] >= '0' && horario[i] <= '9')) return false;
    }
    int horas = std::stoi(horario.substr(0, 2));
    int minutos = std::stoi(horario.substr(3, 2));
    return horas >= 0 && horas <= 23 && minutos >= 0 && minutos <= 59;
}

std::string Timestamp::getValor() const {
    return valor;
}

void Timestamp::setValor(const std::string& novoValor) {
    // Formato esperado: DD-MES-AAAA-HH:MM (17 caracteres)
    if (novoValor.size() != 17 || novoValor[2] != '-' || novoValor[6] != '-' || novoValor[11] != '-') {
        throw std::invalid_argument("Timestamp invalido: formato deve ser DD-MES-AAAA-HH:MM.");
    }

    std::string diaTexto = novoValor.substr(0, 2);
    std::string mesTexto = novoValor.substr(3, 3);
    std::string anoTexto = novoValor.substr(7, 4);
    std::string horarioTexto = novoValor.substr(12, 5);

    for (char c : diaTexto) {
        if (!(c >= '0' && c <= '9')) {
            throw std::invalid_argument("Timestamp invalido: dia deve ser numerico.");
        }
    }
    for (char c : anoTexto) {
        if (!(c >= '0' && c <= '9')) {
            throw std::invalid_argument("Timestamp invalido: ano deve ser numerico.");
        }
    }

    int diaValor = std::stoi(diaTexto);
    int anoValor = std::stoi(anoTexto);

    if (!mesValido(mesTexto)) {
        throw std::invalid_argument("Timestamp invalido: mes deve ser uma sigla valida.");
    }
    if (anoValor < 2000 || anoValor > 2099) {
        throw std::invalid_argument("Timestamp invalido: ano deve estar entre 2000 e 2099.");
    }
    if (diaValor < 1 || diaValor > diasNoMes(mesTexto, anoValor)) {
        throw std::invalid_argument("Timestamp invalido: dia invalido para o mes/ano informados.");
    }
    if (!horarioValido(horarioTexto)) {
        throw std::invalid_argument("Timestamp invalido: horario deve estar entre 00:00 e 23:59.");
    }

    valor = novoValor;
    dia = diaValor;
    mes = mesTexto;
    ano = anoValor;
    horario = horarioTexto;
}

int Timestamp::getDia() const {
    return dia;
}

std::string Timestamp::getMes() const {
    return mes;
}

int Timestamp::getAno() const {
    return ano;
}

std::string Timestamp::getHorario() const {
    return horario;
}
