#ifndef TESTES_HPP_INCLUDED
#define TESTES_HPP_INCLUDED
#include "Dominios.h"
#include "Entidades.h"
#include <stdexcept>
class TUEmail{
private:
    const std::string VALOR_VALIDO = "usuario@dominio.com";
    const std::string VALOR_INVALIDO = ".usuario@dominio.com";
    Email *email;
    int estado;
    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();
public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};
class TUEstado{
private:
    const std::string VALOR_VALIDO = "A FAZER";
    const std::string VALOR_INVALIDO = "EM_ANDAMENTO";
    Estado *tuestado;
    int estado;
    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();;
public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};
class TUIdentificador{
private:
    const std::string VALOR_VALIDO = "AAA000";
    const std::string VALOR_INVALIDO = "111BBB";
    Identificador *identificador;
    int estado;
    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();
public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};
class TULimite{

private:
    const static int VALOR_VALIDO = 2;
    const static int VALOR_INVALIDO = 26;
    Limite *limite;
    int estado;
    void setUP();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();
public:
    const static int SUCESSO = 0;
    const static int FALHA = 0;
    int run();
};
class TUNome{
private:
    const std::string VALOR_VALIDO = "Nome";
    const std::string VALOR_INVALIDO = " Nome ";
    Nome *nome;
    int estado;
    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();
public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};
class TUPapel{
    const std::string VALOR_VALIDO = "GESTOR";
    const std::string VALOR_INVALIDO = "JESTOR";
    Papel *papel;
    int estado;
    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();
public:
    const static int SUCESSO =0;
    const static int FALHA = -1;
    int run();
};
class TUPrioridade{
private:
    const std::string VALOR_VALIDO = "GRANDE";
    const std::string VALOR_INVALIDO = "GIGANTE";
    Prioridade *prioridade;
    int estado;
    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();
public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};
class TUSenha{
private:
    const std::string VALOR_VALIDO = "Abc12";
    const std::string VALOR_INVALIDO = "12345";
    Senha *senha;
    int estado;
    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();
public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};
class TUTamanho{
private:
    const std::string VALOR_VALIDO = "GRANDE";
    const std::string VALOR_INVALIDO = "FRANDE";
    Tamanho *tamanho;
    int estado;
    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();
public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};
class TUTexto{
private:
    const std::string VALOR_VALIDO = "Texto de descricao.";
    const std::string VALOR_INVALIDO = "texto sem ponto final";
    Texto *texto;
    int estado;
    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();
public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};
class TUTimeStamp{
private:
    const std::string VALOR_VALIDO = "05-JAN-2026-14:30";
    const std::string VALOR_INVALIDO = "29-FEV-2023-10:00";
    Timestamp *timestamp;
    int estado;
    void setUp();
    void tearDown();
    void testarCenarioValorValido();
    void testarCenarioValorInvalido();
public:
    const static int SUCESSO = 0;
    const static int FALHA = -1;
    int run();
};
#endif // TESTES_HPP_INCLUDED
