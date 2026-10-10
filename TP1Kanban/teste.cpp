#include "testes.hpp"
/// TESTE UNITARIO EMAIL///
void TUEmail::setUp(){
    email = new Email();
    estado = SUCESSO;
}
void TUEmail::tearDown(){
    delete email;
}
void TUEmail::testarCenarioValorValido(){
    try{
        email->setValor(VALOR_VALIDO);
        if(email->getValor()!= VALOR_VALIDO)
        estado = FALHA;
    }
    catch(std::invalid_argument &excecao){estado = FALHA;}
}
void TUEmail::testarCenarioValorInvalido(){
    try{
        email->setValor(VALOR_INVALIDO);
        estado = FALHA;
    }
    catch(std::invalid_argument &excecao){
        if(email->getValor() == VALOR_INVALIDO)
            estado = FALHA;
    }
}
int TUEmail::run(){
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}
/// TESTE UNITARIO ESTADO ///
void TUEstado::setUp(){
    tuestado = new Estado();
    estado = SUCESSO;
}
void TUEstado::tearDown(){
    delete tuestado;
}
void TUEstado::testarCenarioValorValido(){
    try{
    tuestado->setValor(VALOR_VALIDO);
    tuestado->toString();
    if(tuestado->toString()!=VALOR_VALIDO)
        estado=FALHA;
    }
    catch(std::invalid_argument &excecao){estado = FALHA;}
}
void TUEstado::testarCenarioValorInvalido(){
    try{
        tuestado->setValor(VALOR_INVALIDO);
        estado = FALHA;
    }
    catch(std::invalid_argument &excecao){
        if(tuestado->toString()==VALOR_INVALIDO)
            estado=FALHA;
    }
}
int TUEstado::run(){
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}
/// TESTE UNITARIO IDENTIFICADOR ///

void TUIdentificador::setUp(){
    identificador = new Identificador();
    estado = SUCESSO;
}
void TUIdentificador::tearDown(){delete identificador;}
void TUIdentificador::testarCenarioValorValido(){
    try{
    identificador->setValor(VALOR_VALIDO);
    if(identificador->getValor()!= VALOR_VALIDO)
        estado=FALHA;
    }
    catch(std::invalid_argument &excecao){
        estado=FALHA;
    }
}
void TUIdentificador::testarCenarioValorInvalido(){
    try{
        identificador->setValor(VALOR_INVALIDO);
        estado = FALHA;
    }
    catch(std::invalid_argument &excecao){
        if(identificador->getValor()==VALOR_INVALIDO)
            estado = FALHA;
    }
}
int TUIdentificador::run(){
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}
/// TESTE UNITARIO LIMITE ///
void TULimite::setUP(){
    limite = new Limite();
    estado = SUCESSO;
}
void TULimite::tearDown(){delete limite;}

void TULimite::testarCenarioValorValido(){
    try{
        limite->setValor(VALOR_VALIDO);
        if(limite->getValor()!= VALOR_VALIDO)
            estado = FALHA;
    }
    catch(std::invalid_argument &excecao){ estado = FALHA;}
}
void TULimite::testarCenarioValorInvalido(){
    try{
        limite->setValor(VALOR_INVALIDO);
        estado = FALHA;
    }
    catch(std::invalid_argument &excecao){
        if(limite->getValor() == VALOR_INVALIDO)
            estado = FALHA;
    }
}
int TULimite::run(){
    setUP();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}
/// TESTE UNITARIO NOME ///
void TUNome::setUp(){
    nome = new Nome();
    estado = SUCESSO;
}
void TUNome::tearDown(){delete nome;}
void TUNome::testarCenarioValorValido(){
    try{
    nome->setValor(VALOR_VALIDO);
    if(nome->getValor()!=VALOR_VALIDO)
        estado = FALHA;
    }
    catch(std::invalid_argument &excecao){estado = FALHA;}
}
void TUNome::testarCenarioValorInvalido(){
    try{
        nome->setValor(VALOR_INVALIDO);
        estado = FALHA;
    }
    catch(std::invalid_argument &excecao){
        if(nome->getValor() == VALOR_INVALIDO)
            estado = FALHA;
    }
}
/// TESTES UNITARIO PAPEL ///
void TUPapel::setUp(){
    papel = new Papel();
    estado = SUCESSO;
}
void TUPapel::tearDown(){delete papel;}
void TUPapel::testarCenarioValorValido(){
    try{
        papel->setValor(VALOR_VALIDO);
        papel->toString();
        if(papel->toString()!=VALOR_VALIDO)
            estado = FALHA;
    }catch(std::invalid_argument &excecao){
        estado = FALHA;
    }
}
void TUPapel::testarCenarioValorInvalido(){
    try{
        papel->setValor(VALOR_INVALIDO);
        estado = FALHA;
        papel->toString();
    }catch(std::invalid_argument &excecao){
        if(papel->toString()==VALOR_INVALIDO)
            estado = FALHA;
    }
}
int TUPapel::run(){
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}
/// TESTE UNITARIO PRIORIDADE ///

void TUPrioridade::setUp(){
    prioridade = new Prioridade();
    estado = SUCESSO;
}
void TUPrioridade::tearDown(){delete prioridade;}

void TUPrioridade::testarCenarioValorValido(){
    try{
        prioridade->setValor(VALOR_VALIDO);
        prioridade->toString();
        if(prioridade->toString() == VALOR_VALIDO)
            estado = FALHA;
    }catch(std::invalid_argument &excecao){
        estado =  FALHA;
    }
}
void TUPrioridade::testarCenarioValorInvalido(){
    try{
        prioridade->setValor(VALOR_INVALIDO);
        estado = FALHA;
        prioridade ->toString();
    }
    catch(std::invalid_argument &excecao){
        if(prioridade->toString() == VALOR_INVALIDO)
            estado = FALHA;
    }
}
int TUPrioridade::run(){
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}
/// TESTE UNITARIO SENHA ///
void TUSenha::setUp(){
    senha = new Senha();
    estado = SUCESSO;
}
void TUSenha::tearDown(){delete senha;}
void TUSenha::testarCenarioValorValido(){
    try{
        senha->setValor(VALOR_VALIDO);
        if(senha->getValor() != VALOR_VALIDO)
            estado = FALHA;
    }catch(std::invalid_argument &excecao){ estado = FALHA;}
}
void TUSenha::testarCenarioValorInvalido(){
    try{
        senha->setValor(VALOR_INVALIDO);
        estado = FALHA;
    }catch(std::invalid_argument &excecao){
        if(senha->getValor()== VALOR_INVALIDO)
            estado = FALHA;
    }
}
int TUSenha::run(){
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}
/// TESTE UNITARIO TAMANHO ///
void TUTamanho::setUp(){
    tamanho = new Tamanho();
    estado = SUCESSO;
}
void TUTamanho::tearDown(){delete tamanho;}
void TUTamanho::testarCenarioValorValido(){
    try{
        tamanho->setValor(VALOR_VALIDO);
        tamanho->toString();
        if(tamanho->toString()!= VALOR_VALIDO)
            estado = FALHA;
    }
    catch(std::invalid_argument &excecao){estado = FALHA;}
}
void TUTamanho::testarCenarioValorInvalido(){
    try{
        tamanho->setValor(VALOR_INVALIDO);
        estado = FALHA;
        tamanho->toString();

    }catch(std::invalid_argument &excecao){
        if(tamanho->toString()== VALOR_INVALIDO)
            estado = FALHA;
    }
}
int TUTamanho::run(){
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}
/// TESTE UNITARIO TEXTO ///
void TUTexto::setUp(){
    texto = new Texto();
    estado = SUCESSO;
}
void TUTexto::tearDown(){delete texto;}
void TUTexto::testarCenarioValorValido(){
    try{
        texto->setValor(VALOR_VALIDO);
        if(texto->getValor() != VALOR_VALIDO)
            estado = FALHA;
    }catch(std::invalid_argument &excecao){estado = FALHA;}
}
void TUTexto::testarCenarioValorInvalido(){
    try{
        texto->setValor(VALOR_INVALIDO);
        estado = FALHA;
    }catch(std::invalid_argument &excecao){
        if(texto->getValor() == VALOR_INVALIDO)
            estado = FALHA;
    }
}
/// TESTE UNITARIO TIMESTAMP ///
void TUTimeStamp::setUp(){
    timestamp = new Timestamp();
    estado = SUCESSO;
}
void TUTimeStamp::tearDown(){delete timestamp;}
void TUTimeStamp::testarCenarioValorValido(){
    try{
        timestamp->setValor(VALOR_VALIDO);
        if(timestamp ->getValor()!=VALOR_VALIDO)
            estado = FALHA;
    }catch(std::invalid_argument &excecao){estado = FALHA;}
}
void TUTimeStamp::testarCenarioValorInvalido(){
    try{
        timestamp->setValor(VALOR_INVALIDO);
        estado = FALHA;
    }catch(std::invalid_argument &excecao){
        if(timestamp->getValor()== VALOR_INVALIDO)
            estado = FALHA;
    }
}
int TUTimeStamp::run(){
    setUp();
    testarCenarioValorValido();
    testarCenarioValorInvalido();
    tearDown();
    return estado;
}



