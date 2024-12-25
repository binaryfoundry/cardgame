#include <iostream>

#include "Game.hpp"

int main(int argc, char* argv[]) {
    Game game;

    while (!game.GameOver())
    {
        std::cout << "Round: " << game.Round() << std::endl;
        std::cout << "Player 1 Card: " << game.GetPlayer1TopCard() << std::endl;
        std::cout << "Player 2 Card: " << game.GetPlayer2TopCard() << std::endl;

        const Player winner = game.PlayRound();
        std::cout << "Winner: " << (winner == Player::Player1 ? "Player 1" : "Player 2") << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Game Over!" << std::endl;
    std::cout << "Player 1 Score: " << game.GetPlayer1Score() << std::endl;
    std::cout << "Player 2 Score: " << game.GetPlayer2Score() << std::endl;

    const Player winner = game.Winner();
    if (winner == Player::Player1)
    {
        std::cout << "Winner: Player 1" << std::endl;
    }
    else if (winner == Player::Player2)
    {
        std::cout << "Winner: Player 2" << std::endl;
    }
    else
    {
        std::cout << "It's a draw!" << std::endl;
    }
}
