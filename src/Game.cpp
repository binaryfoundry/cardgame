#include "Game.hpp"
#include <algorithm>
#include <random>

constexpr std::vector<int32_t> Game::GenerateDeck()
{
    std::vector<int32_t> deck(NUM_CARDS);
    for (size_t i = 0; i < NUM_CARDS; ++i)
    {
        deck[i] = static_cast<int32_t>(i);
    }
    return deck;
}

Game::Game()
{
    // Initialize the deck and shuffle it
    std::vector<int32_t> deck = GenerateDeck();
    Shuffle(deck);

    Split(deck);
}

Game::Game(const std::vector<int32_t>& pre_shuffled_deck)
{
    // Ensure the pre-shuffled deck has the correct number of cards
    if (pre_shuffled_deck.size() != NUM_CARDS)
    {
        throw std::invalid_argument("Pre-shuffled deck must contain exactly NUM_CARDS cards.");
    }

    Split(pre_shuffled_deck);
}

void Game::Split(const std::vector<int32_t>& deck)
{
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

Player Game::PlayGame(const std::function<void(Player winner)>& round_callback)
{
    while (!GetGameOver())
    {
        const Player winner = PlayCurrentRound();
        round_callback(winner);
        round++;
    }

    return GetWinner();
}

Player Game::PlayCurrentRound()
{
    const int32_t player1TopCard = GetPlayer1TopCard();
    const int32_t player2TopCard = GetPlayer2TopCard();

    const Player round_winner = (player1TopCard > player2TopCard) ? Player::Player1 : Player::Player2;

    if (round_winner == Player::Player1)
    {
        player_1_score++;
    }
    else
    {
        player_2_score++;
    }

    return round_winner;
}

Player Game::GetWinner() const
{
    if (player_1_score > player_2_score)
    {
        return Player::Player1;
    }
    else if (player_2_score > player_1_score)
    {
        return Player::Player2;
    }
    else
    {
        return Player::None;
    }
}

bool Game::GetGameOver() const
{
    return round >= player_1_cards.size() || round >= player_2_cards.size();
}

size_t Game::GetRound() const
{
    return round;
}
