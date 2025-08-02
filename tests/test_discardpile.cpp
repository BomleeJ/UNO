#include <gtest/gtest.h>
#include "DiscardPile.h"
#include "Card.h"
#include <memory>

// Test construction and initial state
TEST(DiscardPile, Constructor) {
    DiscardPile pile;
    EXPECT_EQ(pile.size(), 0);
}

// Test adding a card increases size and top returns correct card
TEST(DiscardPile, AddAndTop) {
    DiscardPile pile;
    auto card = std::make_unique<Card>(Color::RED, Label::Five);
    Color color = card->getColor();
    Label label = card->getLabel();

    pile.add(std::move(card));
    EXPECT_EQ(pile.size(), 1);

    const Card& topCard = pile.top();
    EXPECT_EQ(topCard.getColor(), color);
    EXPECT_EQ(topCard.getLabel(), label);
}

// Test adding multiple cards and top always returns the last added
TEST(DiscardPile, AddMultipleAndTop) {
    DiscardPile pile;
    pile.add(std::make_unique<Card>(Color::GREEN, Label::Two));
    pile.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    pile.add(std::make_unique<Card>(Color::YELLOW, Label::Reverse));

    EXPECT_EQ(pile.size(), 3);

    const Card& topCard = pile.top();
    EXPECT_EQ(topCard.getColor(), Color::YELLOW);
    EXPECT_EQ(topCard.getLabel(), Label::Reverse);
}

// Test size after multiple adds
TEST(DiscardPile, SizeAfterAdds) {
    DiscardPile pile;
    for (int i = 0; i < 5; ++i) {
        pile.add(std::make_unique<Card>(Color::RED, Label::Five));
    }
    EXPECT_EQ(pile.size(), 5);
}

// Test top on empty pile (should throw)
TEST(DiscardPile, TopOnEmpty) {
    DiscardPile pile;

    EXPECT_ANY_THROW({
        pile.top();
    });
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}