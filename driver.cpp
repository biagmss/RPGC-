

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "MochilaCinto.h"

using namespace std;

const int NUMERO_NIVEIS = 6;

// Função para listar o item do topo da mochila
void listarItemMochila(Stack &mochila)
{
    Item item;
    if (mochila.Empty())
    {
        cout << "Mochila esta vazia." << endl;
    }
    else
    {
        mochila.Top(item);
        cout << "Nome: " << item.nome << " | Peso: " << item.peso << " | Tipo: " << item.tipo << " | Valor: " << item.valor << endl;
    }
}

// Função para listar os itens do cinto
void listarItensCinto(Cinto &cinto)
{
    if (cinto.Empty())
    {
        cout << "Cinto esta vazio." << endl;
    }
    else
    {
        cinto.ImprimirItensCinto();
    }
}

// Função para usar um item da mochila ou cinto
void UsarItem(Stack &mochila, Cinto &cinto, Item &item, int &pontosDeVida)
{
    int escolha;
    cout << "Deseja usar item da mochila (1) ou do cinto (2)? " << endl;
    cin >> escolha;

    if (escolha == 1) // Usar item da mochila
    {
        if (mochila.Empty())
        {
            cout << "Mochila esta vazia." << endl;
        }
        else
        {
            mochila.Pop(item);
            cout << "Voce usou o item: " << item.nome << "!" << endl;
        }
    }
    else if (escolha == 2) // Usar item do cinto
    {
        if (cinto.Empty())
        {
            cout << "Cinto esta vazio." << endl;
        }
        else
        {
            int pos;
            cout << "Informe a posicao do item no cinto: " << endl;
            cinto.ImprimirItensCinto();
            cin >> pos;
            cinto.Delete(item, pos);
            cout << "Voce usou o item: " << item.nome << "!" << endl;
        }
    }

    // Se for uma poção, restaura pontos de vida
    if (item.tipo == "pocao" && pontosDeVida < 100)
    {
        pontosDeVida += item.valor; // Corrigido para adicionar valor
        cout << "Seus pontos de vida foram restaurados! " << endl;
    }
}

// Função para ver ou usar um item
void VerOuUsarItem(Stack &mochila, Cinto &cinto, Item &item, int &pontosDeVida)
{   
    Inimigo inimigo;
    int escolha = 1;

    while (escolha == 1 || escolha == 2)
    {
        cout << "Ver a mochila (1), ver o cinto (2) ou usar um item (3)? ";
        cin >> escolha;

        if (escolha == 1)
        {
            listarItemMochila(mochila);
        }
        else if (escolha == 2)
        {
            listarItensCinto(cinto);
        }
        else if (escolha == 3)
        {
            UsarItem(mochila, cinto, item, pontosDeVida);
        }
    }
}

// Função para sortear e criar um item
Item SortearItem()
{
    Item item;

    // Definindo os itens de armas
    Item itensArma[5] = {
        {"Lanca do Crepusculo Feerico", 10, "arma", 50},
        {"Arco das Estrelas Cintilantes", 5, "arma", 25},
        {"Lammina do Vento Prateado", 10, "arma", 20},
        {"Espada da Aurora dos Elfos", 10, "arma", 20},
        {"Cajado do Coracao Luminoso", 30, "arma", 70}
    };

    // Definindo os itens de poções
    Item itensPocao[5] = {
        {"Elixir da Floresta Encantada", 5, "pocao", 100},
        {"Nectar da Vida Eterna", 10, "pocao", 100},
        {"Essencia da Luz Cristalina", 5, "pocao", 100},
        {"Pocao das Folhas Celestes", 5, "pocao", 100},
        {"Gotas de Renascimento Feerico", 5, "pocao", 100}
    };

    // Sorteia entre arma e poção
    int sorteio = rand() % 10; // 0 a 9
    if (sorteio < 5) // 0 a 4 para armas
    {
        item = itensArma[sorteio]; // Pega uma arma aleatória
    }
    else // 5 a 9 para poções
    {
        item = itensPocao[sorteio - 5]; // Pega uma poção aleatória
    }

    return item; // Retorna o item sorteado
}

int main()
{
    srand(time(0)); // Inicializa a semente para geração de' números aleatórios

    int pontosDeVida = 100;
    int countNumeroNivel = 0;
    string nomeJogador, nomeHeroi;

    cout << "Digite seu nome: ";
    getline(cin, nomeJogador);

    cout << "Digite o nome do heroi: ";
    getline(cin, nomeHeroi);

    Stack mochila;
    Cinto cinto;
    Item item;

    // Loop dos 6 níveis
    for (int i = 1; i <= NUMERO_NIVEIS; i++)
    {
        cout << "Nivel " << i << endl;

        if (i >= 1 && i <= 4)
        {
            // Níveis 1 a 4: Receber arma ou poção
            item = SortearItem();
            cout << "Voce encontrou um item: " << item.nome << " | Tipo: " << item.tipo << "| Peso: " << item.peso << " | Valor: " << item.valor << endl;

            int escolha;
            cout << "Deseja guardar o item na mochila (1), no cinto (2) ou descartar (3)? ";
            cin >> escolha;

            if (escolha == 1)
            {
                mochila.Push(item);
                cout << item.nome << " foi guardado na mochila!" << endl;
            }
            else if (escolha == 2)
            {
                if (cinto.Full())
                {
                    cout << "Cinto esta cheio!" << endl;
                }
                else
                {
                    int pos;
                    cout << "Informe a posicao no cinto: ";
                    cinto.ImprimirPosicoesCinto();
                    cin >> pos;
                    cinto.Insert(item, pos);
                    cout << item.nome << " foi guardado no cinto!" << endl;
                }
            }
            else if (escolha == 3)
            {
                cout << item.nome << " descartado! " << endl;
            }
            countNumeroNivel++;
        }
        else if (i == 5)
        {
            // Nível 5: Batalha com inimigo
            Inimigo inimigo = {"Espreitador das Nevoas Noturnas", 50, 25};

            cout << "Um " << inimigo.nome << " apareceu!" << endl;
            while (pontosDeVida > 0 && inimigo.vida > 0)
            {
                // Turno do jogador
                VerOuUsarItem(mochila, cinto, item, pontosDeVida);

                // Verificar se o item é válido
                if (item.nome != "") // Supondo que um item vazio indique que não há item
                {
                    if (item.tipo == "arma")
                    {
                        inimigo.vida = inimigo.vida - item.valor;
                        cout << "Voce atacou o " << inimigo.nome << " com " << item.nome << " e causou " << item.valor << " de dano!" << endl;
                    }
                    else if (item.tipo == "pocao")
                    {
                        pontosDeVida = item.valor; // Corrigido para adicionar valor
                        cout << "Voce usou " << item.nome << " e restaurou " << item.valor << " de vida!" << endl;
                    }
                }
                else
                {
                    cout << "Sua mochila e cinto estao vazios! O " << inimigo.nome << " vai te atacar!" << endl;
                    inimigo.ataque;
                    cout << "O " << inimigo.nome << " atacou voce e causou " << inimigo.ataque << " de dano!" << endl;
                    cout << "Vida atual: " << pontosDeVida << endl;
                }

                // Turno do inimigo
                if (inimigo.vida > 0)
                {
                    pontosDeVida = pontosDeVida - inimigo.ataque;
                    cout << "O " << inimigo.nome << " atacou voce e causou " << inimigo.ataque << " de dano!" << endl;
                    cout << "Vida atual: " << pontosDeVida << endl;
                }
                else
                {
                    cout << "Voce derrotou o " << inimigo.nome << "!" << endl;
                }
            }
            countNumeroNivel++;
        }
        else if (i == 6)
        {
            // Nível 6: Luta com o chefe final
            Inimigo chefao = {"Morgath o Soberano do Abismo Etereo", 100, 50};

            cout << "Voce chegou ao nivel final! O " << chefao.nome << " apareceu!" << endl;
            while (pontosDeVida > 0 && chefao.vida > 0)
            {
                // Turno do jogador
                VerOuUsarItem(mochila, cinto, item, pontosDeVida);

                // Verificar se o item é válido
                if (item.nome != "") // Supondo que um item vazio indica que não há item
                {
                    if (item.tipo == "arma")
                    {
                        chefao.vida = chefao.vida - item.valor;
                        cout << "Voce atacou o " << chefao.nome << " com " << item.nome << " e causou " << item.valor << " de dano!" << endl;
                    }
                    else if (item.tipo == "pocao")
                    {
                        pontosDeVida = item.valor; // Corrigido para adicionar valor
                        cout << "Voce usou " << item.nome << " e restaurou " << item.valor << " de vida!" << endl;
                    }
                }
                else
                {
                    cout << "Sua mochila e cinto estao vazios! O " << chefao.nome << " vai te atacar!" << endl;
                    chefao.ataque;
                    cout << "O " << chefao.nome << " atacou voce e causou " << chefao.ataque << " de dano!" << endl;
                    cout << "Vida atual: " << pontosDeVida << endl;
                }

                // Turno do chefao
                if (chefao.vida > 0)
                {
                    pontosDeVida = pontosDeVida - chefao.ataque;
                    cout << "O " << chefao.nome << " atacou voce e causou " << chefao.ataque << " de dano!" << endl;
                    cout << "Vida atual: " << pontosDeVida << endl;
                }
                else
                {
                    cout << "Voce derrotou o " << chefao.nome << "!" << endl;
                }
            }
            countNumeroNivel++;
        }
    }

    // Salvar os resultados em um arquivo
    ofstream nomedoarquivo("high_scores.txt", ios::app);

    if (!nomedoarquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo!" << endl;
        abort();
    }

    nomedoarquivo << "Resultados -> seu nome: " << nomeJogador << " -> nome heroi:" << nomeHeroi << ", nivel: " << countNumeroNivel << endl;
    nomedoarquivo.close();

    return 0;
}
