#pragma once

#include <vector>

class Game final
{
public:
    Game();

    std::vector<int32_t>::const_iterator GetPlayer1CardsIterator() const;
    std::vector<int32_t>::const_iterator GetPlayer1CardsEnd() const;

    std::vector<int32_t>::const_iterator GetPlayer2CardsIterator() const;
    std::vector<int32_t>::const_iterator GetPlayer2CardsEnd() const;

private:
    static constexpr size_t NUM_CARDS = 52;
    static constexpr size_t NUM_CARDS_HALF = NUM_CARDS / 2;

    size_t flipped_cards = 0;
    std::vector<int32_t> player_1_cards;
    std::vector<int32_t> player_2_cards;

    void Shuffle(std::vector<int32_t>& deck);
};
