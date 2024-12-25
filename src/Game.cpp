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

void Game::Shuffle(std::vector<int32_t>& deck)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

std::vector<int32_t>::const_iterator Game::GetPlayer1CardsIterator() const
{
    if (flipped_cards >= player_1_cards.size())
    {
        return player_1_cards.end();
    }
    return player_1_cards.begin() + flipped_cards;
}

std::vector<int32_t>::const_iterator Game::GetPlayer1CardsEnd() const
{
    return player_1_cards.end();
}

std::vector<int32_t>::const_iterator Game::GetPlayer2CardsIterator() const
{
    if (flipped_cards >= player_2_cards.size())
    {
        return player_2_cards.end();
    }
    return player_2_cards.begin() + flipped_cards;
}

std::vector<int32_t>::const_iterator Game::GetPlayer2CardsEnd() const
{
    return player_2_cards.end();
}
