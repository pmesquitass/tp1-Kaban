    #ifndef DOMINIOS_H
#define DOMINIOS_H

#include <string>
#include <stdexcept>
/**
    * @class Email
    * @brief Representa um endereço de e-mail válido no sistema.
    * A classe Email é um domínio responsável por armazenar e validar o endereço de
    * correio eletrônico de um usuário. O e-mail segue o formato "parte-local@dominio".
    *
    * Regras de formato aceitas:
    * - Parte local: até 64 caracteres, contendo letras (a-z), dígitos (0-9), ponto (.) ou hífen (-).
    * Não pode iniciar ou terminar com ponto ou hífen. Ponto ou hífen deve ser seguido por letra ou dígito.
    * - Domínio: até 255 caracteres, composto por partes separadas por ponto (.). Cada parte contém
    * letras (a-z), dígitos (0-9) ou hífen (-), não podendo iniciar ou terminar com hífen.
*/
class Email {
private:
    std::string valor;

    static bool parteLocalValida(const std::string& parte);
    static bool dominioValido(const std::string& dominio);

public:
    /**
    * @brief Contrutor padrão da classe Email.
    * Inicializa o e-mail com um valor padrão válido ("usuario@dominio.com").
    */
    Email();
    /**
    * @brief  Construtor que inicializa o e-mail com um valor fornecido.
    * @param valorInicial String com endereço de e-mail a ser atribuído.
    * @throw std::invalid_argument Se o formato for inválido.
    */
    explicit Email(const std::string& valorInicial);

    /**
        * @brief Obtém o endereço de e-mail armazenado.
        * @return String contendo o e-mail atual.
        */
    std::string getValor() const;

    /**
     * @brief Define o valor do e-mail.
     * @param novoValor String contendo o endereço de email;
     * @throws std::invalid_argument se o novoValor não atender as regras de formato do e-mail.
     */
    void setValor(const std::string& novoValor);
};

/**
 * @class Estado
 * @brief Representa o estado de um cartao de atividade no quadro Kanban:
 * A FAZER, FAZENDO ou FEITO.
 */
class Estado {
public:
    /**
    *@brief Enumeração que representa os estados válidos de um cartão de atividade.
    */
    enum Valor { A_FAZER, FAZENDO, FEITO };

private:
    Valor valor;

    static Valor converter(const std::string& texto);

public:
    /**
    *@brief Construtor padrão da classe Estado.
    * Inicializa o estado com o valor A FAZER.
    */
    Estado();
    /**
        *@brief Construtor que inicializa o estado a partir de um valor fornecido.
        *@param valorInicial do tipo Valor (A FAZER, FAZENDO, FEITO).
    */
    explicit Estado(Valor valorInicial);
    /**
        *@brief Construtor que inicializa o estado a partir de um texto.
        *@param texto String contendo uma representação textual do estado ("A FAZER", "FAZENDO", FEITO").
        *@throw std::invalid_argument Se o texto for inválido.
    */
    explicit Estado(const std::string& texto);

    /**
        *@brief Retorna o valor do estado.
        *@return Valor do tipo enumerado (A_FAZER, FAZENDO, FEITO).
     */
    Valor getValor() const;

    /** @brief Define o valor do estado a partir do enum.
        @param novoValor Novo Valor a ser atribuído.
    */
    void setValor(Valor novoValor);

    /**
     * @brief Define o valor do estado a partir de texto ("A FAZER", "FAZENDO" ou "FEITO").
     * @param texto String contendo o estado.
     * @throws std::invalid_argument Se o texto nao corresponder a um estado valido.
     */
    void setValor(const std::string& texto);

    /**
        *@brief Retorna a representacao textual do estado.
        * @return String contendo "A FAZER", "FAZENDO" ou "FEITO".
     */
    std::string toString() const;
};

/**
 * @class Identificador
 * @brief Representao codigo identificador de 6 caracteres: os 3 primeiros sao letras (a-z ou A-Z)
 * e os 3 ultimos sao digitos (0-9).
 */
class Identificador {
private:
    std::string valor;

public:
    /**
    * @brief Construtor padrão onde a classe incializa com valor "AAA000".
    */
    Identificador();
    /**
    * @brief Construtor onde inicializa o identificador a partir de uma String.
    * @param valorInicial String em formato válido.
    * @throw std::invalid_argument Se valorInicial não possuir o formato de 3 letras seguidos de 3 digitos.
    */
    explicit Identificador(const std::string& valorInicial);

    /**
        * @brief Retorna o valor do identificador atual
        * @return String contendo o código identificador atual.
    . */
    std::string getValor() const;

    /**
     * @brief Define o valor do identificador.
     * @param novoValor String contendo o identificador;
     * @throw std::invalid_argument Se novoValor não contiver exatamente 6 caracteres,
     * sendo os 3 primeiros letras (a-z ou A-Z) e os 3 últimos dígitos (0-9).
     */
    void setValor(const std::string& novoValor);
};

/**
 * @class Limite
 * @brief Limite numerico de work in progress (WIP) de uma coluna, de 1 a 25.
 */
class Limite {
private:
    int valor;

public:
    /** @brief Construtor padrão da classe Limite, onde inicializa com valor 1.
    */
    Limite();
    /**
        * @brief Construtor onde inicializa a classe a partir de um valor fornecido.
        * @param valorInicial Int entre 1-25.
        * @throw std::invalid_argument se não estiver entre 1-25.
        */
    explicit Limite(int valorInicial);

    /**
        * @brief Retorna o valor atual do limite.
        * @return Int contendo o limite atual.
     */
    int getValor() const;

    /**
     * @brief Define o valor do limite.
     * @param novoValor Int com um valor valido entre 1-25.
     * @throw std::invalid_argument se o valor nao estiver entre 1 e 25.
     */
    void setValor(int novoValor);
};

/**
 * @class Nome
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
    /**
        * @brief Construtor padrão da classe Nome, onde valor inicia "Nome".
    */
    Nome();
    /**
     * @brief Construtor que inicializa a classe atraves de texto.
     * @param valorInicial String onde não pode iniciar e nem terminar em espaço em branco.
     * @throw std::invalid_argument se iniciar e terminar com espaço.
     */
    explicit Nome(const std::string& valorInicial);

    /**
        * @brief Retorna o valor do nome.
        * @return String contendo nome atual.
        */
    std::string getValor() const;

    /**
     * @brief Define o valor do nome.
     * @param novoValor String contendo o nome.
     * @throw std::invalid_argument Se novoValor não atender às regras de formato do domínio Nome.
     */
    void setValor(const std::string& novoValor);
};

/**
 * @class Papel
 * @brief Papel de uma pessoa no sistema: GESTOR ou DESENVOLVEDOR.
 */
class Papel {
public:
    /** Enumeracao que representa os papeis de um Pessoa. */
    enum Valor { GESTOR, DESENVOLVEDOR };

private:
    Valor valor;

    static Valor converter(const std::string& texto);

public:
    /**
    * @brief Construtor padrao da classe Papel.
    * Inicializa o papel com o valor padrão válido DESENVOLVEDOR.
    */
    Papel();
    /**
        * @brief Construtor que inicializa o papel a partir do enum Valor.
        * @param valorInicial Valor enumerado (GESTOR OU DESENVOLVEDOR).
    */
    explicit Papel(Valor valorInicial);
    /**
    * @brief @brief Define o valor do papel a partir de texto.
    * @param texto String contendo o nome do papel ("GESTOR" ou "DESENVOLVEDOR").
    */
    explicit Papel(const std::string& texto);

    /**
     * @brief Retorna o valor do papel.
     * @return Valor do tipo enumerado (GESTOR ou DESENVOLVEDOR).
     */
    Valor getValor() const;

    /**
     * @brief Define o valor do papel a partir do enum.
     * @param novoValor Valor enumerado a ser atribuido.
     */
    void setValor(Valor novoValor);

    /** @brief Define o valor do papel a partir de texto.
        * @param texto String contendo o nome do papel ("GESTOR" ou "DESENVOLVEDOR").
        * @throw std::invalid_argument Se o texto não corresponder a um papel válido.
    */
    void setValor(const std::string& texto);

    /**
        * @brief Retorna a representacao textual do papel.
        * @return String contendo "GESTOR" ou "DESENVOLVEDOR".
    */
    std::string toString() const;
};

/**
 * @class Prioridade
 * @brief Representa o nível de prioridade de um cartão de atividade no quadro Kanban.
 *
 * O domínio Prioridade classifica as tarefas em ALTA, MEDIA ou BAIXA.
 */
class Prioridade {

public:
    /**
     * @brief Enumeração que representa os níveis de prioridade válidos.
     */
    enum Valor {
        ALTA,
        MEDIA,
        BAIXA
    };

private:

    Valor valor;

    /**
     * @brief Converte uma string em um valor de prioridade.
     *
     * @param texto String contendo a prioridade.
     * @return Valor correspondente à prioridade.
     * @throw std::invalid_argument Se o texto não corresponder a uma prioridade válida.
     */
    static Valor converter(const std::string& texto);

public:

    /**
     * @brief Construtor padrão da classe Prioridade.
     *
     * Inicializa a prioridade com o valor padrão válido BAIXA.
     */
    Prioridade();

    /**
     * @brief Construtor que inicializa a prioridade a partir do enum Valor.
     *
     * @param valorInicial Valor enumerado (ALTA, MEDIA ou BAIXA).
     */
    explicit Prioridade(Valor valorInicial);

    /**
     * @brief Construtor que inicializa a prioridade por texto.
     *
     * @param texto String contendo a prioridade ("ALTA", "MEDIA" ou "BAIXA").
     * @throw std::invalid_argument Se o texto não corresponder a uma prioridade válida.
     */
    explicit Prioridade(const std::string& texto);

    /**
     * @brief Retorna o valor da prioridade.
     *
     * @return Valor do tipo enumerado (ALTA, MEDIA ou BAIXA).
     */
    Valor getValor() const;

    /**
     * @brief Define o valor da prioridade a partir do enum.
     *
     * @param novoValor Valor enumerado a ser atribuído.
     */
    void setValor(Valor novoValor);

    /**
     * @brief Define o valor da prioridade a partir de texto.
     *
     * @param texto String contendo a prioridade ("ALTA", "MEDIA" ou "BAIXA").
     * @throw std::invalid_argument Se o texto não corresponder a uma prioridade válida.
     */
    void setValor(const std::string& texto);

    /**
     * @brief Retorna a representação textual da prioridade.
     *
     * @return String contendo "ALTA", "MEDIA" ou "BAIXA".
     */
    std::string toString() const;
};
/**
 * @class Senha
 * @brief Senha de exatamente 5 caracteres, contendo letras (a-z ou A-Z) e/ou
 * digitos (0-9), com pelo menos uma letra e um digito.
 */
class Senha {
private:
    std::string valor;

public:
    /**
     * @brief Construtor padrao da classe Senha.
     * Inicializa a senha com valor padrão valido "Abc12".
    */
    Senha();
    /**
     * @brief Construtor que inicializa a senha a partir de um texto.
     * @param valorInicial String contendo a senha.
     * @throw std::invalid_argument Se o texto nao corresponder a uma senha valida.
    */
    explicit Senha(const std::string& valorInicial);

    /**
     * @brief Retorna o valor da senha.
     * @return String contendo a senha.
    */
    std::string getValor() const;

    /**
     * @brief Define o valor da senha.
     * @param novoValor String contendo a senha.
     * @throw std::invalid_argument se o formato for invalido.
     */
    void setValor(const std::string& novoValor);
};

/**
 * @class Tamanho
 * @brief Tamanho de um cartao de atividade: GRANDE, MEDIO ou PEQUENO.
 */
class Tamanho {
public:
    /**@brief Enumeracao que representa os tamanhos de um cartao de atividade.
    */
    enum Valor { GRANDE, MEDIO, PEQUENO };
private:
    Valor valor;

    static Valor converter(const std::string& texto);
public:
    /**
    * @brief Construtor padrão da classe Tamanho.
    * Inicializa o tamanho com o valor padrao valido MEDIO.
    */
    Tamanho();
    /**
    * @brief Construtor que inicializa o Tamanho a partir do enum Valor.
    * @param valorInicial Valor enumerado (GRANDE, MEDIO, PEQUENO).
    */
    explicit Tamanho(Valor valorInicial);
    /**
    * @brief Construtor que inicializa o Tamanho por texto.
    * @param texto String contendo o tamanho ("GRANDE", "MEDIO" ou "PEQUENO").
    * @throw std::invalid_argument Se o texto nao corresponder a um tamanho valido.
    */
    explicit Tamanho(const std::string& texto);

    /**
    * @brief Retorna o valor do tamanho.
    * @return Valor do tipo enumerado (GRANDE, MEDIO, PEQUENO).
     */
    Valor getValor() const;

    /**
    * @brief Define o valor do tamanho a partir do enum.
    * @param novoValor Valor enumerado (GRANDE, MEDIO, PEQUENO).
    */
    void setValor(Valor novoValor);

    /**
     * @brief Define o valor do tamanho a partir de texto.
     * @param texto String contendo o tamanho ("GRANDE", "MEDIO" ou "PEQUENO").
     * @throw std::invalid_argument Se o texto nao corresponder a um tamanho valido.
     */
    void setValor(const std::string& texto);

    /**
    * @brief Retorna a representacao textual do tamanho.
    * @return String contendo "GRANDE", "MEDIO" ou "PEQUENO".
    */
    std::string toString() const;
};

/**
 * @class Texto
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
    /**
     * @brief Construtor padrão da classe Texto.
     * Inicializa o texto com valor padrão valido "Texto.".
    */
    Texto();
    /**
     * @brief Construtor que inicializa Texto por um texto.
     * @param valorInicial String contendo o texto.
     * @throw std::invalid_argument Se o texto não atender às regras de formato de Texto.
     */
    explicit Texto(const std::string& valorInicial);

    /**
     * @brief Retorna o valor do texto.
     * @return String contendo o texto.
    */
    std::string getValor() const;

    /**
     * @brief Define o valor do texto.
     * @param novoValor String contendo o texto.
     * @throw std::invalid_argument se o formato for invalido.
     */
    void setValor(const std::string& novoValor);
};


/**
 * @class Timestamp
 * @brief Representa uma data e horário no sistema Kanban no formato DIA-MÊS-ANO-HORÁRIO.
 *
 * Regras de formato:
 * - DIA: Número de 1 a 31.
 * - MÊS: Sigla em maiúsculas (JAN, FEV, MAR, ABR, MAI, JUN, JUL, AGO, SET, OUT, NOV, DEZ).
 * - ANO: Número entre 2000 e 2099.
 * - HORÁRIO: Valor de 00:00 a 23:59.
 * - A data deve ser válida considerando o número de dias do mês e anos bissextos.
 */
class Timestamp {

private:

    std::string valor;
    int dia;
    std::string mes;
    int ano;
    std::string horario;

    /**
     * @brief Verifica se o mês informado é válido.
     *
     * @param mes Sigla do mês a ser verificada.
     * @return true se o mês for válido, false caso contrário.
     */
    static bool mesValido(const std::string& mes);

    /**
     * @brief Retorna a quantidade de dias de um determinado mês.
     *
     * @param mes Sigla do mês.
     * @param ano Ano utilizado para verificar anos bissextos.
     * @return Número de dias existentes no mês.
     */
    static int diasNoMes(const std::string& mes, int ano);

    /**
     * @brief Verifica se um ano é bissexto.
     *
     * @param ano Ano a ser verificado.
     * @return true se o ano for bissexto, false caso contrário.
     */
    static bool anoBissexto(int ano);

    /**
     * @brief Verifica se o horário informado é válido.
     *
     * @param horario Horário no formato "HH:MM".
     * @return true se o horário for válido, false caso contrário.
     */
    static bool horarioValido(const std::string& horario);

public:

    /**
     * @brief Construtor padrão da classe Timestamp.
     *
     * Inicializa o timestamp com o valor padrão válido
     * "01-JAN-2000-00:00".
     */
    Timestamp();

    /**
     * @brief Construtor que inicializa o timestamp a partir de um texto.
     *
     * @param valorInicial String no formato "DIA-MÊS-ANO-HORÁRIO".
     * @throw std::invalid_argument Se o formato, os limites ou a data/horário forem inválidos.
     */
    explicit Timestamp(const std::string& valorInicial);

    /**
     * @brief Retorna o valor completo do timestamp.
     *
     * @return String contendo o timestamp no formato "DIA-MÊS-ANO-HORÁRIO".
     */
    std::string getValor() const;

    /**
     * @brief Define o valor do timestamp após validação.
     *
     * @param novoValor String contendo o novo timestamp.
     * @throw std::invalid_argument Se o formato ou a data forem inválidos.
     */
    void setValor(const std::string& novoValor);

    /**
     * @brief Retorna o dia do timestamp.
     *
     * @return Número inteiro representando o dia (1 a 31).
     */
    int getDia() const;

    /**
     * @brief Retorna o mês do timestamp.
     *
     * @return String contendo a sigla do mês (ex: "JAN", "FEV").
     */
    std::string getMes() const;

    /**
     * @brief Retorna o ano do timestamp.
     *
     * @return Número inteiro representando o ano (2000 a 2099).
     */
    int getAno() const;

    /**
     * @brief Retorna o horário do timestamp.
     *
     * @return String contendo o horário no formato "HH:MM".
     */
    std::string getHorario() const;
};

#endif // DOMINIOS_H
