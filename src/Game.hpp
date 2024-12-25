#pragma once

#include <vector>
#include <functional>

enum class Player
{
    Player1,
    Player2,
    None
};

class Game final
{
public:
    Game();
    Game(const std::vector<int32_t>& pre_shuffled_deck);

    int32_t GetPlayer1TopCard() const;
    int32_t GetPlayer2TopCard() const;

    int32_t GetPlayer1Score() const;
    int32_t GetPlayer2Score() const;

    bool GameOver() const;
    size_t Round() const;

    /**
     * @brief Returns the currently winning player.
     * @return The winner of the round (Player::Player1 or Player::Player2 or Player::None for a draw).
     */
    [[nodiscard]] Player Winner();

    /**
     * @brief Plays a whole game, calling round_callback with the winner each round.
     * @return The winner of the game (Player::Player1 or Player::Player2 or Player::None for a draw).
     */
    [[nodiscard]] Player PlayGame(const std::function<void(Player winner)>& round_callback);

private:
    static constexpr size_t NUM_CARDS = 52;
    static constexpr size_t NUM_CARDS_HALF = NUM_CARDS / 2;

    static_assert(NUM_CARDS % 2 == 0, "NUM_CARDS must be even");

    size_t round = 0;
    int32_t player_1_score = 0;
    int32_t player_2_score = 0;
    std::vector<int32_t> player_1_cards;
    std::vector<int32_t> player_2_cards;

    void Split(const std::vector<int32_t>& deck);
    void Shuffle(std::vector<int32_t>& deck);

    /**
     * @brief Plays a round of the game and returns the winner.
     * @return The winner of the round (Player::Player1 or Player::Player2).
     */
    [[nodiscard]] Player PlayCurrentRound();
};
