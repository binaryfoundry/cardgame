#include "Presentation.hpp"

void PrintPlayGame(Game& game, std::ostream& os)
{
    const Player winner = game.PlayGame([&](Player winner)
    {
        os << "Round: " << game.GetRound() << std::endl;
        os << "Player 1 Card: " << game.GetPlayer1TopCard() << std::endl;
        os << "Player 2 Card: " << game.GetPlayer2TopCard() << std::endl;

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

