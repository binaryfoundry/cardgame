#include <iostream>
#include <sstream>

#include "Game.hpp"

template <typename Iterator, typename OutputStream>
void PrintPlayerCards(Iterator begin, Iterator end, OutputStream& os)
{
    for (; begin != end; ++begin)
    {
        std::cout << *begin << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    Game game;

    std::cout << "Player 1 Cards: " << std::endl;
    PrintPlayerCards(game.GetPlayer1CardsIterator(), game.GetPlayer1CardsEnd(), std::cout);
    std::cout << "Player 2 Cards: " << std::endl;
    PrintPlayerCards(game.GetPlayer2CardsIterator(), game.GetPlayer2CardsEnd(), std::cout);
}
