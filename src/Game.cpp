#include "Game.hpp"
#include <algorithm>
#include <random>

Game::Game()
{
    // Initialize the deck and shuffle it
    std::vector<int32_t> deck(NUM_CARDS);
    for (size_t i = 0; i < NUM_CARDS; ++i)
    {
        deck[i] = static_cast<int32_t>(i);
    }
    Shuffle(deck);

    // Resize the player card vectors
    player_1_cards.resize(NUM_CARDS_HALF);
    player_2_cards.resize(NUM_CARDS_HALF);

    // Distribute the cards to players
    std::copy(deck.begin(), deck.begin() + NUM_CARDS_HALF, player_1_cards.begin());
    std::copy(deck.begin() + NUM_CARDS_HALF, deck.end(), player_2_cards.begin());
}

/**
 * @brief Shuffles the deck using a random number generator.
 *
 * This function uses the Fisher-Yates (Knuth) shuffle algorithm, which operates in linear time O(n).
 *
 * @param deck The deck of cards to shuffle.
 */
void Game::Shuffle(std::vector<int32_t>& deck)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

int32_t Game::GetPlayer1TopCard() const
{
    if (round >= player_1_cards.size())
    {
        return -1;
    }
    return player_1_cards[round];
}

int32_t Game::GetPlayer2TopCard() const
{
    if (round >= player_2_cards.size())
    {
        return -1;
    }
    return player_2_cards[round];
}

int32_t Game::GetPlayer1Score() const
{
    return player_1_score;
}

int32_t Game::GetPlayer2Score() const
{
    return player_2_score;
}

bool Game::GameOver() const
{
    return round >= player_1_cards.size() || round >= player_2_cards.size();
}

size_t Game::Round() const
{
    return round;
}

Player Game::PlayRound()
{
    const int32_t player1TopCard = GetPlayer1TopCard();
    const int32_t player2TopCard = GetPlayer2TopCard();

    const Player winner = (player1TopCard > player2TopCard) ? Player::Player1 : Player::Player2;

    if (winner == Player::Player1)
    {
        player_1_score++;
    }
    else
    {
        player_2_score++;
    }

    round++;

    return winner;
}
