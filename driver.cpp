#include "Heroi.h"
#include "Inimigo.h"
#include <iostream>

int main() {
    std::string nomeJogador;
    std::cout << "Digite o nome do herói: ";
    std::cin >> nomeJogador;

    Heroi heroi(nomeJogador, 100);
    Inimigo inimigo("Goblin", 30, 10);

    heroi.status();
    inimigo.status();

    // Simulação de batalha
    heroi.usarPocao();

    return 0;
}
