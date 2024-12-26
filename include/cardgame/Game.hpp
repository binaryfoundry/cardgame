#pragma once

#include <array>
#include <vector>
#include <functional>

namespace cardgame
{

enum class Player
{
    Player1,
    Player2,
    None
};

using RoundCallback = std::function<void(const size_t played_round, const uint32_t player_1_card, const uint32_t player_2_card, const Player winner)>;

class Game final
{
public:
    // Constants
    /**
     * @brief The total number of cards in the Game deck.
     */
    static constexpr size_t NUM_CARDS = 52;
    static_assert(NUM_CARDS % 2 == 0, "NUM_CARDS must be even");

    /**
     * @brief The number of cards each player gets.
     */
    static constexpr size_t NUM_CARDS_HALF = NUM_CARDS / 2;

    // Constructors
    /**
     * @brief Constructs a new Game object with a shuffled deck.
     *
     * This constructor initializes the game by generating a deck of cards,
     * shuffling it, and then splitting it between the two players.
     */
    Game();

    /**
     * @brief Constructs a new Game object with a pre-shuffled deck.
     *
     * This constructor initializes the game using a pre-shuffled deck provided
     * by the caller. The deck is split between the two players.
     *
     * @param pre_shuffled_deck An array containing a pre-shuffled deck of cards.
     */
    Game(const std::array<uint32_t, NUM_CARDS>& pre_shuffled_deck);

    // Public methods
    /**
     * @brief Gets the current score of Player 1.
     *
     * @return The score of Player 1.
     */
    uint32_t GetPlayer1Score() const;

    /**
     * @brief Gets the current score of Player 2.
     *
     * @return The score of Player 2.
     */
    uint32_t GetPlayer2Score() const;

    /**
     * @brief Plays a whole game, calling round_callback with the winner each round. Calling again will simulate the game again.
     * @param round_callback An optional callback function that is called with the winner of each round. Default is nullptr.
     * @return The winner of the game (Player::Player1 or Player::Player2 or Player::None for a draw).
     */
    [[nodiscard]] Player PlayGame(const RoundCallback& round_callback = nullptr);

private:
    // Private members
    /**
     * @brief The current round number.
     */
    size_t round = 0;

    /**
     * @brief The current score of Player 1.
     */
    uint32_t player_1_score = 0;

    /**
     * @brief The current score of Player 2.
     */
    uint32_t player_2_score = 0;

    /**
     * @brief The cards held by Player 1.
     */
    std::vector<uint32_t> player_1_cards;

    /**
     * @brief The cards held by Player 2.
     */
    std::vector<uint32_t> player_2_cards;

    // Private methods
    static constexpr std::vector<uint32_t> GenerateDeck();

    /**
     * @brief Shuffles the deck using a random number generator.
     *
     * This function uses the Fisher-Yates (Knuth) shuffle algorithm, which operates in linear time O(n).
     *
     * @param deck The deck of cards to shuffle.
     */
    void Shuffle(std::vector<uint32_t>& deck);

    void Split(const std::vector<uint32_t>& deck);
    void Reset();

    uint32_t GetPlayer1TopCard() const;
    uint32_t GetPlayer2TopCard() const;

    size_t GetRound() const;
    bool GetGameOver() const;

    /**
     * @brief Returns the currently winning player.
     * @return The winner of the round (Player::Player1 or Player::Player2 or Player::None for a draw).
     */
    [[nodiscard]] Player GetWinner() const;

    /**
     * @brief Plays a round of the game and returns the winner.
     * @return The winner of the round (Player::Player1 or Player::Player2 or Player::None for a draw).
     */
    [[nodiscard]] Player PlayCurrentRound();
};

} // namespace cardgame
