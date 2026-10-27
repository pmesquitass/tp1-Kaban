/**
 * @file main.cpp
 * @brief Ponto de entrada do sistema Kanban (TP1).
 *
 * Monta as camadas do sistema: a camada de servico (regras de negocio, dados
 * em memoria) e a camada de apresentacao (interface de console), ligando uma
 * a outra por meio das interfaces abstratas IServico e IApresentacao.
 */

#include "Servicos.h"
#include "Apresentacao.h"

int main() {
    ServicoKanban servico;
    ApresentacaoKanban apresentacao;
    apresentacao.setServico(&servico);
    apresentacao.executar();
    return 0;
}
