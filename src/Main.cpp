#include <iostream>

#include "Game.hpp"

template <typename Iterator, typename OutputStream>
void PrintPlayerCards(Iterator begin, Iterator end, OutputStream& os)
{
    for (; begin != end; ++begin)
    {
        os << *begin << " ";
    }
    os << std::endl;
}

int main(int argc, char* argv[]) {
    Game game;

    while (!game.GameOver())
    {
        std::cout << "Round: " << game.Round() << std::endl;
        std::cout << "Player 1 Cards: " << std::endl;
        PrintPlayerCards(game.GetPlayer1CardsIterator(), game.GetPlayer1CardsEnd(), std::cout);
        std::cout << "Player 2 Cards: " << std::endl;
        PrintPlayerCards(game.GetPlayer2CardsIterator(), game.GetPlayer2CardsEnd(), std::cout);

        const Player winner = game.PlayRound();
        std::cout << "Winner: " << (winner == Player::Player1 ? "Player 1" : "Player 2") << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Player 1 Score: " << game.GetPlayer1Score() << std::endl;
    std::cout << "Player 2 Score: " << game.GetPlayer2Score() << std::endl;
    std::cout << "Game Over!" << std::endl;
}
