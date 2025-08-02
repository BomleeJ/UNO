#include <gtest/gtest.h>
#include "Player.h"
#include "DrawDeck.h"
#include "DiscardPile.h"
#include <memory>
#include <cstdlib>

// Test constructor and basic properties
TEST(CPU, Constructor) {
    CPU cpu;
    EXPECT_FALSE(cpu.ishuman());
    EXPECT_FALSE(cpu.hasWon());
    EXPECT_FALSE(cpu.hasPlayableCards());
}

// Test inheritance from Player
TEST(CPU, InheritsFromPlayer) {
    CPU cpu;
    Player* player = &cpu;
    EXPECT_FALSE(player->ishuman());
}

// Test drawing cards
TEST(CPU, DrawCard) {
    CPU cpu;
    DrawDeck drawDeck;
    
    cpu.drawCard(drawDeck);
    
    EXPECT_EQ(cpu.deck.size(), 1);
    EXPECT_EQ(drawDeck.size(), 111); // 112 - 1
}

TEST(CPU, DrawSevenCards) {
    CPU cpu;
    DrawDeck drawDeck;
    size_t initialDeckSize = drawDeck.size();
    
    cpu.drawSevenCards(drawDeck);
    
    EXPECT_EQ(cpu.deck.size(), 7);
    EXPECT_EQ(drawDeck.size(), initialDeckSize - 7);
}

TEST(CPU, DrawMultipleCards) {
    CPU cpu;
    DrawDeck drawDeck;
    
    cpu.drawCard(drawDeck);
    cpu.drawCard(drawDeck);
    cpu.drawCard(drawDeck);
    
    EXPECT_EQ(cpu.deck.size(), 3);
    EXPECT_EQ(drawDeck.size(), 109);
}

// Test removing cards
TEST(CPU, RemoveCard) {
    CPU cpu;
    DrawDeck drawDeck;
    
    cpu.drawSevenCards(drawDeck);
    EXPECT_EQ(cpu.deck.size(), 7);
    
    auto removedCard = cpu.removeCard(0);
    EXPECT_NE(removedCard, nullptr);
    EXPECT_EQ(cpu.deck.size(), 6);
}

TEST(CPU, RemoveCardFromMiddle) {
    CPU cpu;
    DrawDeck drawDeck;
    
    cpu.drawSevenCards(drawDeck);
    
    auto removedCard = cpu.removeCard(3);
    EXPECT_NE(removedCard, nullptr);
    EXPECT_EQ(cpu.deck.size(), 6);
}

TEST(CPU, RemoveCardOutOfRange) {
    CPU cpu;
    DrawDeck drawDeck;
    
    cpu.drawSevenCards(drawDeck);
    
    EXPECT_THROW(cpu.removeCard(10), std::out_of_range);
    EXPECT_THROW(cpu.removeCard(7), std::out_of_range);
}

// Test discarding cards
TEST(CPU, DiscardCard) {
    CPU cpu;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    cpu.drawSevenCards(drawDeck);
    size_t initialDeckSize = cpu.deck.size();
    
    cpu.discardCard(0, discardPile);
    
    EXPECT_EQ(cpu.deck.size(), initialDeckSize - 1);
    EXPECT_EQ(discardPile.size(), 1);
}

TEST(CPU, DiscardMultipleCards) {
    CPU cpu;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    cpu.drawSevenCards(drawDeck);
    
    cpu.discardCard(0, discardPile);
    cpu.discardCard(0, discardPile);
    cpu.discardCard(0, discardPile);
    
    EXPECT_EQ(cpu.deck.size(), 4);
    EXPECT_EQ(discardPile.size(), 3);
}

// Test win condition
TEST(CPU, HasWon) {
    CPU cpu;
    DrawDeck drawDeck;
    
    // Initially not won
    EXPECT_FALSE(cpu.hasWon());
    
    // Draw some cards
    cpu.drawSevenCards(drawDeck);
    EXPECT_FALSE(cpu.hasWon());
    
    // Remove all cards
    for (int i = 0; i < 7; i++) {
        cpu.removeCard(0);
    }
    
    EXPECT_TRUE(cpu.hasWon());
}

// Test CPUAlgorithm functionality
TEST(CPU, CPUAlgorithm) {
    CPU cpu;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    cpu.drawSevenCards(drawDeck);
    
    // Add a card to discard pile
    discardPile.add(std::make_unique<Card>(Color::RED, Label::Five));
    
    std::srand(42);
    int result = cpu.CPUAlgorithm(discardPile, drawDeck);
    
    // Result should be either a valid index or -1
    if (result != -1) {
        EXPECT_GE(result, 0);
        EXPECT_LT(result, static_cast<int>(cpu.deck.size()));
        std::unique_ptr<Card> card = cpu.removeCard(result);
        EXPECT_TRUE(card->isvalid(discardPile.top()));
    }
    
}



TEST(CPU, MultipleDrawAndDiscard) {
    CPU cpu;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    // Draw cards
    cpu.drawSevenCards(drawDeck);
    EXPECT_EQ(cpu.deck.size(), 7);
    
    // Discard some
    cpu.discardCard(0, discardPile);
    cpu.discardCard(0, discardPile);
    EXPECT_EQ(cpu.deck.size(), 5);
    EXPECT_EQ(discardPile.size(), 2);
    
    // Draw more
    cpu.drawCard(drawDeck);
    cpu.drawCard(drawDeck);
    EXPECT_EQ(cpu.deck.size(), 7);
}




// Test CPU algorithm with different scenarios
TEST(CPU, CPUAlgorithmMultipleRuns) {
    CPU cpu;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    cpu.drawSevenCards(drawDeck);
    
    // Add a card to discard pile
    discardPile.add(std::make_unique<Card>(Color::RED, Label::Five));
    
    // Run algorithm multiple times with different seeds
    for (int i = 0; i < 5; i++) {
        std::srand(i);
        int result = cpu.CPUAlgorithm(discardPile, drawDeck);
        EXPECT_GE(result, -1);
        std::unique_ptr<Card> card = cpu.removeCard(result);
        EXPECT_TRUE(card->isvalid(discardPile.top()));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}