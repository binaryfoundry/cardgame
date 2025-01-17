#include "cardgame/Game.hpp"
#include <algorithm>
#include <random>

namespace cardgame
{

constexpr std::array<uint32_t, Game::NUM_CARDS> Game::GenerateDeck()
{
    std::array<uint32_t, NUM_CARDS> deck{};
    for (size_t i = 0; i < NUM_CARDS; ++i)
    {
        deck[i] = static_cast<uint32_t>(i);
    }
    return deck;
}

Game::Game()
{
    // Initialize the deck and shuffle it
    auto deck = GenerateDeck();
    Shuffle(deck);

    Split(deck);
}

Game::Game(const std::array<uint32_t, NUM_CARDS>& pre_shuffled_deck)
{
    auto deck = GenerateDeck();
    std::copy(pre_shuffled_deck.begin(), pre_shuffled_deck.begin() + NUM_CARDS, deck.begin());

    Split(deck);
}

void Game::Split(const std::array<uint32_t, Game::NUM_CARDS>& deck)
{
    // Resize the player card vectors
    player_1_cards.resize(NUM_CARDS_HALF);
    player_2_cards.resize(NUM_CARDS_HALF);

    // Distribute the cards to players
    std::copy(deck.begin(), deck.begin() + NUM_CARDS_HALF, player_1_cards.begin());
    std::copy(deck.begin() + NUM_CARDS_HALF, deck.end(), player_2_cards.begin());
}

void Game::Shuffle(std::array<uint32_t, Game::NUM_CARDS>& deck)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

uint32_t Game::GetPlayer1TopCard() const
{
    if (round >= player_1_cards.size())
    {
        return -1;
    }
    return player_1_cards[round];
}

uint32_t Game::GetPlayer2TopCard() const
{
    if (round >= player_2_cards.size())
    {
        return -1;
    }
    return player_2_cards[round];
}

uint32_t Game::GetPlayer1Score() const
{
    return player_1_score;
}

uint32_t Game::GetPlayer2Score() const
{
    return player_2_score;
}

Player Game::Play(const RoundCallback& round_callback)
{
    Reset();

    while (!GetGameOver())
    {
        const Player winner = PlayCurrentRound();
        if (round_callback)
        {
            const uint32_t player_1_card = GetPlayer1TopCard();
            const uint32_t player_2_card = GetPlayer2TopCard();
            round_callback(round, player_1_card, player_2_card, winner);
        }
        round++;
    }

    return GetWinner();
}

void Game::Reset()
{
    round = 0;
    player_1_score = 0;
    player_2_score = 0;
}

Player Game::PlayCurrentRound()
{
    const uint32_t player1TopCard = GetPlayer1TopCard();
    const uint32_t player2TopCard = GetPlayer2TopCard();

    Player round_winner;
    if (player1TopCard > player2TopCard)
    {
        round_winner = Player::Player1;
        player_1_score++;
    }
    else if (player2TopCard > player1TopCard)
    {
        round_winner = Player::Player2;
        player_2_score++;
    }
    else
    {
        player_1_score++;
        player_2_score++;
        round_winner = Player::None; // It's a draw
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

} // namespace cardgame
