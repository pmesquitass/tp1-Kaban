#ifndef DOMINIOS_H
#define DOMINIOS_H

#include <string>
#include <stdexcept>

/**
 * @brief Representa um endereco de e-mail valido no formato parte-local@dominio.
 *
 * A parte local pode conter letra (a-z), digito (0-9), ponto (.) ou hifen (-);
 * nao pode iniciar ou terminar com ponto ou hifen; ponto ou hifen deve ser
 * seguido por letra(s) ou digito(s); comprimento maximo de 64 caracteres.
 * O dominio e composto por uma ou mais partes separadas por ponto; cada parte
 * pode conter letra (a-z), digito (0-9) ou hifen (-); nao pode iniciar ou
 * terminar com hifen; comprimento maximo de 255 caracteres.
 */
class Email {
private:
    std::string valor;

    static bool parteLocalValida(const std::string& parte);
    static bool dominioValido(const std::string& dominio);

public:
    Email();
    explicit Email(const std::string& valorInicial);

    /** @brief Retorna o valor do e-mail. */
    std::string getValor() const;

    /**
     * @brief Define o valor do e-mail.
     * @throws std::invalid_argument se o formato for invalido.
     */
    void setValor(const std::string& novoValor);
};

/**
 * @brief Representa o estado de um cartao de atividade no quadro Kanban:
 * A FAZER, FAZENDO ou FEITO.
 */
class Estado {
public:
    enum Valor { A_FAZER, FAZENDO, FEITO };

private:
    Valor valor;

    static Valor converter(const std::string& texto);

public:
    Estado();
    explicit Estado(Valor valorInicial);
    explicit Estado(const std::string& texto);

    /** @brief Retorna o valor do estado. */
    Valor getValor() const;

    /** @brief Define o valor do estado a partir do enum. */
    void setValor(Valor novoValor);

    /**
     * @brief Define o valor do estado a partir de texto ("A FAZER", "FAZENDO" ou "FEITO").
     * @throws std::invalid_argument se o texto nao corresponder a um estado valido.
     */
    void setValor(const std::string& texto);

    /** @brief Retorna a representacao textual do estado. */
    std::string toString() const;
};

/**
 * @brief Identificador de 6 caracteres: os 3 primeiros sao letras (a-z ou A-Z)
 * e os 3 ultimos sao digitos (0-9).
 */
class Identificador {
private:
    std::string valor;

public:
    Identificador();
    explicit Identificador(const std::string& valorInicial);

    /** @brief Retorna o valor do identificador. */
    std::string getValor() const;

    /**
     * @brief Define o valor do identificador.
     * @throws std::invalid_argument se o formato for invalido.
     */
    void setValor(const std::string& novoValor);
};

/**
 * @brief Limite numerico de work in progress (WIP) de uma coluna, de 1 a 25.
 */
class Limite {
private:
    int valor;

public:
    Limite();
    explicit Limite(int valorInicial);

    /** @brief Retorna o valor do limite. */
    int getValor() const;

    /**
     * @brief Define o valor do limite.
     * @throws std::invalid_argument se o valor nao estiver entre 1 e 25.
     */
    void setValor(int novoValor);
};

/**
 * @brief Texto de ate 15 caracteres usado como nome de pessoas, projetos e quadros.
 *
 * Caractere pode ser letra maiuscula (A-Z), letra minuscula (a-z) ou espaco em
 * branco; espaco em branco e seguido por letra; primeiro caractere nao e
 * espaco em branco; ultimo caractere nao e espaco em branco.
 */
class Nome {
private:
    std::string valor;

public:
    Nome();
    explicit Nome(const std::string& valorInicial);

    /** @brief Retorna o valor do nome. */
    std::string getValor() const;

    /**
     * @brief Define o valor do nome.
     * @throws std::invalid_argument se o formato for invalido.
     */
    void setValor(const std::string& novoValor);
};

/**
 * @brief Papel de uma pessoa no sistema: GESTOR ou DESENVOLVEDOR.
 */
class Papel {
public:
    enum Valor { GESTOR, DESENVOLVEDOR };

private:
    Valor valor;

    static Valor converter(const std::string& texto);

public:
    Papel();
    explicit Papel(Valor valorInicial);
    explicit Papel(const std::string& texto);

    /** @brief Retorna o valor do papel. */
    Valor getValor() const;

    /** @brief Define o valor do papel a partir do enum. */
    void setValor(Valor novoValor);

    /**
     * @brief Define o valor do papel a partir de texto ("GESTOR" ou "DESENVOLVEDOR").
     * @throws std::invalid_argument se o texto nao corresponder a um papel valido.
     */
    void setValor(const std::string& texto);

    /** @brief Retorna a representacao textual do papel. */
    std::string toString() const;
};

/**
 * @brief Prioridade de um cartao de atividade: ALTA, MEDIA ou BAIXA.
 */
class Prioridade {
public:
    enum Valor { ALTA, MEDIA, BAIXA };

private:
    Valor valor;

    static Valor converter(const std::string& texto);

public:
    Prioridade();
    explicit Prioridade(Valor valorInicial);
    explicit Prioridade(const std::string& texto);

    /** @brief Retorna o valor da prioridade. */
    Valor getValor() const;

    /** @brief Define o valor da prioridade a partir do enum. */
    void setValor(Valor novoValor);

    /**
     * @brief Define o valor da prioridade a partir de texto ("ALTA", "MEDIA" ou "BAIXA").
     * @throws std::invalid_argument se o texto nao corresponder a uma prioridade valida.
     */
    void setValor(const std::string& texto);

    /** @brief Retorna a representacao textual da prioridade. */
    std::string toString() const;
};

/**
 * @brief Senha de exatamente 5 caracteres, contendo letras (a-z ou A-Z) e/ou
 * digitos (0-9), com pelo menos uma letra e um digito.
 */
class Senha {
private:
    std::string valor;

public:
    Senha();
    explicit Senha(const std::string& valorInicial);

    /** @brief Retorna o valor da senha. */
    std::string getValor() const;

    /**
     * @brief Define o valor da senha.
     * @throws std::invalid_argument se o formato for invalido.
     */
    void setValor(const std::string& novoValor);
};

/**
 * @brief Tamanho de um cartao de atividade: GRANDE, MEDIO ou PEQUENO.
 */
class Tamanho {
public:
    enum Valor { GRANDE, MEDIO, PEQUENO };

private:
    Valor valor;

    static Valor converter(const std::string& texto);

public:
    Tamanho();
    explicit Tamanho(Valor valorInicial);
    explicit Tamanho(const std::string& texto);

    /** @brief Retorna o valor do tamanho. */
    Valor getValor() const;

    /** @brief Define o valor do tamanho a partir do enum. */
    void setValor(Valor novoValor);

    /**
     * @brief Define o valor do tamanho a partir de texto ("GRANDE", "MEDIO" ou "PEQUENO").
     * @throws std::invalid_argument se o texto nao corresponder a um tamanho valido.
     */
    void setValor(const std::string& texto);

    /** @brief Retorna a representacao textual do tamanho. */
    std::string toString() const;
};

/**
 * @brief Texto de ate 30 caracteres usado como descricao, com regras de pontuacao.
 *
 * Caractere pode ser letra (a-z ou A-Z), digito (0-9), espaco em branco ou
 * sinal de pontuacao (virgula, ponto-e-virgula, ponto, dois pontos, ponto de
 * interrogacao, ponto de exclamacao); sinal de pontuacao nao e seguido por
 * sinal de pontuacao; primeiro caractere e letra maiuscula; ultimo caractere
 * e ponto.
 */
class Texto {
private:
    std::string valor;

    static bool ehPontuacao(char c);

public:
    Texto();
    explicit Texto(const std::string& valorInicial);

    /** @brief Retorna o valor do texto. */
    std::string getValor() const;

    /**
     * @brief Define o valor do texto.
     * @throws std::invalid_argument se o formato for invalido.
     */
    void setValor(const std::string& novoValor);
};

/**
 * @brief Data e horario no formato DIA-MES-ANO-HORARIO (ex: "05-JAN-2026-14:30").
 *
 * DIA e numero de 1 a 31; MES e a sigla JAN, FEV, MAR, ABR, MAI, JUN, JUL,
 * AGO, SET, OUT, NOV ou DEZ; ANO e numero de 2000 a 2099; HORARIO e valor de
 * 00:00 a 23:59; a data deve ser valida considerando anos bissextos.
 */
class Timestamp {
private:
    std::string valor;
    int dia;
    std::string mes;
    int ano;
    std::string horario;

    static bool mesValido(const std::string& mes);
    static int diasNoMes(const std::string& mes, int ano);
    static bool anoBissexto(int ano);
    static bool horarioValido(const std::string& horario);

public:
    Timestamp();
    explicit Timestamp(const std::string& valorInicial);

    /** @brief Retorna o valor completo do timestamp. */
    std::string getValor() const;

    /**
     * @brief Define o valor do timestamp.
     * @throws std::invalid_argument se o formato ou a data forem invalidos.
     */
    void setValor(const std::string& novoValor);

    /** @brief Retorna o dia do timestamp. */
    int getDia() const;

    /** @brief Retorna o mes (sigla) do timestamp. */
    std::string getMes() const;

    /** @brief Retorna o ano do timestamp. */
    int getAno() const;

    /** @brief Retorna o horario (HH:MM) do timestamp. */
    std::string getHorario() const;
};

#endif // DOMINIOS_H
