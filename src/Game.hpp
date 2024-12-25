#pragma once

#include <vector>

enum class Player
{
    Player1,
    Player2
};

class Game final
{
public:
    Game();

    std::vector<int32_t>::const_iterator GetPlayer1CardsIterator() const;
    std::vector<int32_t>::const_iterator GetPlayer1CardsEnd() const;

    std::vector<int32_t>::const_iterator GetPlayer2CardsIterator() const;
    std::vector<int32_t>::const_iterator GetPlayer2CardsEnd() const;

    int32_t GetPlayer1TopCard() const;
    int32_t GetPlayer2TopCard() const;

    int32_t GetPlayer1Score() const;
    int32_t GetPlayer2Score() const;

    bool GameOver() const;
    size_t Round() const;

    /**
     * @brief Plays a round of the game and returns the winner.
     * @return The winner of the round (Player::Player1 or Player::Player2).
     */
    [[nodiscard]] Player PlayRound();

private:
    static constexpr size_t NUM_CARDS = 52;
    static constexpr size_t NUM_CARDS_HALF = NUM_CARDS / 2;

    size_t round = 0;
    int32_t player_1_score = 0;
    int32_t player_2_score = 0;
    std::vector<int32_t> player_1_cards;
    std::vector<int32_t> player_2_cards;

    void Shuffle(std::vector<int32_t>& deck);
};
