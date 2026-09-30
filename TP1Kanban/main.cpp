#include <iostream>
#include "Entidades.h"

int main() {
    try {
        Pessoa p(Email("ana.silva@exemplo.com"), Nome("Ana Silva"), Senha("ab12c"), Papel("GESTOR"));
        std::cout << "Pessoa OK: " << p.getEmail().getValor() << " - " << p.getPapel().toString() << std::endl;

        Projeto proj(Identificador("abc123"), Nome("Projeto X"), Texto("Descricao valida."),
                     Timestamp("01-JAN-2026-08:00"), Timestamp("30-JUN-2026-18:00"));
        std::cout << "Projeto OK: " << proj.getIdentificador().getValor() << std::endl;

        Quadro q(Identificador("qua001"), Nome("Quadro Um"), Limite(5));
        std::cout << "Quadro OK, limite=" << q.getLimite().getValor() << std::endl;

        CartaoAtividade c(Identificador("crt001"), Nome("Tarefa Alfa"), Texto("Fazer algo importante."),
                           Prioridade("ALTA"), Estado("A FAZER"), Tamanho("MEDIO"),
                           Timestamp("01-JAN-2026-09:00"), Timestamp("02-JAN-2026-09:00"), Timestamp("05-JAN-2026-17:00"));
        std::cout << "Cartao OK: estado=" << c.getEstado().toString() << std::endl;

        // Testando validacao invalida (deve lancar excecao)
        try {
            Email invalido("email-invalido-sem-arroba.com");
        } catch (const std::invalid_argument& e) {
            std::cout << "Excecao esperada capturada: " << e.what() << std::endl;
        }

        try {
            Timestamp invalido("29-FEV-2025-10:00"); // 2025 nao e bissexto
        } catch (const std::invalid_argument& e) {
            std::cout << "Excecao esperada capturada: " << e.what() << std::endl;
        }

        std::cout << "TODOS OS TESTES PASSARAM" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERRO INESPERADO: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}