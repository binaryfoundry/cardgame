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
    static constexpr size_t NUM_CARDS = 52;
    static_assert(NUM_CARDS % 2 == 0, "NUM_CARDS must be even");

    Game();
    Game(const std::array<uint32_t, NUM_CARDS>& pre_shuffled_deck);

    uint32_t GetPlayer1Score() const;
    uint32_t GetPlayer2Score() const;

    /**
     * @brief Plays a whole game. Calling again will simulate the game again.
     * @return The winner of the game (Player::Player1 or Player::Player2 or Player::None for a draw).
     */
    [[nodiscard]] Player PlayGame();

    /**
      * @brief Plays a whole game, calling round_callback with the winner each round. Calling again will simulate the game again.
      * @param round_callback A callback function that is called with the winner of each round.
      * @return The winner of the game (Player::Player1 or Player::Player2 or Player::None for a draw).
      */
    [[nodiscard]] Player PlayGame(const RoundCallback& round_callback);

private:

    static constexpr size_t NUM_CARDS_HALF = NUM_CARDS / 2;

    size_t round = 0;
    uint32_t player_1_score = 0;
    uint32_t player_2_score = 0;
    std::vector<uint32_t> player_1_cards;
    std::vector<uint32_t> player_2_cards;

    static constexpr std::vector<uint32_t> GenerateDeck();
    void Split(const std::vector<uint32_t>& deck);
    void Shuffle(std::vector<uint32_t>& deck);
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

}
// namespace cardgame
