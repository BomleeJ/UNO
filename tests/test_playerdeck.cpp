#include <gtest/gtest.h>
#include "PlayerDeck.h"
#include "DrawDeck.h"
#include "DiscardPile.h"
#include <memory>

// Test constructor and initial state
TEST(PlayerDeck, Constructor) {
    PlayerDeck deck;
    EXPECT_TRUE(deck.empty());
}

// Test initial_fill functionality
TEST(PlayerDeck, InitialFill) {
    PlayerDeck deck;
    DrawDeck drawDeck;
    
    deck.initial_fill(drawDeck);
    
    EXPECT_FALSE(deck.empty());
    EXPECT_EQ(deck.size(), 7);
}

TEST(PlayerDeck, InitialFillReducesDrawDeck) {
    PlayerDeck deck;
    DrawDeck drawDeck;
    size_t initialDrawDeckSize = drawDeck.size();
    
    deck.initial_fill(drawDeck);
    
    EXPECT_EQ(drawDeck.size(), initialDrawDeckSize - 7);
}

// Test add functionality
TEST(PlayerDeck, AddCard) {
    PlayerDeck deck;
    auto card = std::make_unique<Card>(Color::RED, Label::Five);
    
    deck.add(std::move(card));
    
    EXPECT_FALSE(deck.empty());
    EXPECT_EQ(deck.size(), 1);
}

TEST(PlayerDeck, AddMultipleCards) {
    PlayerDeck deck;
    
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    deck.add(std::make_unique<Card>(Color::GREEN, Label::Three));
    
    EXPECT_EQ(deck.size(), 3);
}

// Test remove functionality
TEST(PlayerDeck, RemoveCard) {
    PlayerDeck deck;
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    
    EXPECT_EQ(deck.size(), 2);
    
    auto removedCard = deck.remove(0);
    EXPECT_EQ(removedCard->getColor(), Color::RED);
    EXPECT_EQ(removedCard->getLabel(), Label::Five);
    EXPECT_EQ(deck.size(), 1);
}

TEST(PlayerDeck, RemoveCardFromMiddle) {
    PlayerDeck deck;
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    deck.add(std::make_unique<Card>(Color::GREEN, Label::Three));
    
    auto removedCard = deck.remove(1);
    EXPECT_EQ(removedCard->getColor(), Color::BLUE);
    EXPECT_EQ(removedCard->getLabel(), Label::Skip);
    EXPECT_EQ(deck.size(), 2);
}

TEST(PlayerDeck, RemoveCardFromEnd) {
    PlayerDeck deck;
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    
    auto removedCard = deck.remove(1);
    EXPECT_EQ(removedCard->getColor(), Color::BLUE);
    EXPECT_EQ(removedCard->getLabel(), Label::Skip);
    EXPECT_EQ(deck.size(), 1);
}

TEST(PlayerDeck, RemoveCardOutOfRange) {
    PlayerDeck deck;
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    
    EXPECT_THROW(deck.remove(1), std::out_of_range);
    EXPECT_THROW(deck.remove(10), std::out_of_range);
}

TEST(PlayerDeck, RemoveFromEmptyDeck) {
    PlayerDeck deck;
    
    EXPECT_THROW(deck.remove(0), std::out_of_range);
}

// Test empty functionality
TEST(PlayerDeck, EmptyOnConstruction) {
    PlayerDeck deck;
    EXPECT_TRUE(deck.empty());
}

TEST(PlayerDeck, EmptyAfterAdd) {
    PlayerDeck deck;
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    EXPECT_FALSE(deck.empty());
}

TEST(PlayerDeck, EmptyAfterRemove) {
    PlayerDeck deck;
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.remove(0);
    EXPECT_TRUE(deck.empty());
}

// Test filter_playable functionality
TEST(PlayerDeck, FilterPlayableSameColor) {
    PlayerDeck deck;
    DiscardPile pile;
    
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    deck.add(std::make_unique<Card>(Color::RED, Label::Three));
    
    pile.add(std::make_unique<Card>(Color::RED, Label::Two));
    
    PlayableCards playable = deck.filter_playable(pile);
    
    EXPECT_EQ(playable.size(), 2);
    EXPECT_EQ(playable[0]->getColor(), Color::RED);
    EXPECT_EQ(playable[2]->getColor(), Color::RED);
}

TEST(PlayerDeck, FilterPlayableSameLabel) {
    PlayerDeck deck;
    DiscardPile pile;
    
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Five));
    deck.add(std::make_unique<Card>(Color::GREEN, Label::Three));
    
    pile.add(std::make_unique<Card>(Color::YELLOW, Label::Five));
    
    PlayableCards playable = deck.filter_playable(pile);
    
    EXPECT_EQ(playable.size(), 2);
    EXPECT_EQ(playable[0]->getLabel(), Label::Five);
    EXPECT_EQ(playable[1]->getLabel(), Label::Five);
}

TEST(PlayerDeck, FilterPlayableWildCards) {
    PlayerDeck deck;
    DiscardPile pile;
    
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.add(std::make_unique<Card>(Color::NONE, Label::Wild));
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    
    pile.add(std::make_unique<Card>(Color::YELLOW, Label::Two));
    
    PlayableCards playable = deck.filter_playable(pile);
    
    EXPECT_EQ(playable.size(), 1);
    EXPECT_TRUE(playable[1]->iswild());
}

TEST(PlayerDeck, FilterPlayableNoMatches) {
    PlayerDeck deck;
    DiscardPile pile;
    
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    
    pile.add(std::make_unique<Card>(Color::YELLOW, Label::Two));
    
    PlayableCards playable = deck.filter_playable(pile);
    
    EXPECT_EQ(playable.size(), 0);
}

TEST(PlayerDeck, FilterPlayableEmptyDeck) {
    PlayerDeck deck;
    DiscardPile pile;
    
    pile.add(std::make_unique<Card>(Color::RED, Label::Five));
    
    PlayableCards playable = deck.filter_playable(pile);
    
    EXPECT_EQ(playable.size(), 0);
}

// Test size functionality
TEST(PlayerDeck, SizeAfterAdd) {
    PlayerDeck deck;
    EXPECT_EQ(deck.size(), 0);
    
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    EXPECT_EQ(deck.size(), 1);
    
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    EXPECT_EQ(deck.size(), 2);
}

TEST(PlayerDeck, SizeAfterRemove) {
    PlayerDeck deck;
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    
    EXPECT_EQ(deck.size(), 2);
    
    deck.remove(0);
    EXPECT_EQ(deck.size(), 1);
    
    deck.remove(0);
    EXPECT_EQ(deck.size(), 0);
}

// Test edge cases
TEST(PlayerDeck, MultipleAddAndRemove) {
    PlayerDeck deck;
    
    for (int i = 0; i < 10; i++) {
        deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    }
    EXPECT_EQ(deck.size(), 10);
    
    for (int i = 0; i < 10; i++) {
        auto card = deck.remove(0);
        EXPECT_EQ(card->getColor(), Color::RED);
        EXPECT_EQ(card->getLabel(), Label::Five);
    }
    EXPECT_TRUE(deck.empty());
}

TEST(PlayerDeck, RemoveInReverseOrder) {
    PlayerDeck deck;
    
    deck.add(std::make_unique<Card>(Color::RED, Label::Five));
    deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    deck.add(std::make_unique<Card>(Color::GREEN, Label::Three));
    
    auto card3 = deck.remove(2);
    auto card2 = deck.remove(1);
    auto card1 = deck.remove(0);
    
    EXPECT_EQ(card1->getColor(), Color::RED);
    EXPECT_EQ(card2->getColor(), Color::BLUE);
    EXPECT_EQ(card3->getColor(), Color::GREEN);
    EXPECT_TRUE(deck.empty());
}

// Test integration
TEST(PlayerDeck, IntegrationWithDrawDeck) {
    PlayerDeck playerDeck;
    DrawDeck drawDeck;
    
    playerDeck.initial_fill(drawDeck);
    
    EXPECT_EQ(playerDeck.size(), 7);
    EXPECT_EQ(drawDeck.size(), 105);
    
    auto card = playerDeck.remove(0);
    playerDeck.add(std::move(card));
    
    EXPECT_EQ(playerDeck.size(), 7);
}

TEST(PlayerDeck, IntegrationWithDiscardPile) {
    PlayerDeck playerDeck;
    DiscardPile discardPile;
    
    playerDeck.add(std::make_unique<Card>(Color::RED, Label::Five));
    playerDeck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    
    discardPile.add(std::make_unique<Card>(Color::RED, Label::Two));
    
    PlayableCards playable = playerDeck.filter_playable(discardPile);
    
    EXPECT_EQ(playable.size(), 1);
    EXPECT_EQ(playable[0]->getColor(), Color::RED);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}