#include "cardgame/Game.hpp"

#include <iostream>

void PrintPlayGame(Game& game, std::ostream& os)
{
    const Player winner = game.PlayGame([&](const size_t played_round, const int32_t player_1_card, const int32_t player_2_card, const Player winner)
    {
        os << "Round: " << played_round << std::endl;
        os << "Player 1 Card: " << player_1_card << std::endl;
        os << "Player 2 Card: " << player_2_card << std::endl;

        os << "Winner: " << (winner == Player::Player1 ? "Player 1" : "Player 2") << std::endl;
    });

    os << "Game Over!" << std::endl;
    os << "Player 1 Score: " << game.GetPlayer1Score() << std::endl;
    os << "Player 2 Score: " << game.GetPlayer2Score() << std::endl;

    if (winner == Player::Player1)
    {
        os << "Winner: Player 1" << std::endl;
    }
    else if (winner == Player::Player2)
    {
        os << "Winner: Player 2" << std::endl;
    }
    else
    {
        os << "It's a draw!" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    Game game;
    PrintPlayGame(game, std::cout);
}
