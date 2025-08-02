#include <gtest/gtest.h>
#include "DrawDeck.h"
#include <vector>
#include <algorithm>

// Test constructor and basic properties
TEST(DrawDeck, Constructor) {
    DrawDeck deck;
    
    // Should have 112 cards (4 colors * 13 labels * 2 each + 8 wild cards)
    EXPECT_EQ(deck.size(), 112);
}

TEST(DrawDeck, ConstructorCardDistribution) {
    DrawDeck deck;
    
    // Count cards by color and label
    std::vector<int> colorCounts(5, 0); // RED, GREEN, BLUE, YELLOW, NONE
    std::vector<int> labelCounts(15, 0); // 0-9, Skip, Reverse, DrawTwo, Wild, WildDrawFour
    
    // Draw all cards and count them
    std::vector<std::unique_ptr<Card>> allCards;
    while (deck.size() > 0) {
        std::unique_ptr<Card> card = deck.draw();
        allCards.push_back(std::move(card));
        
        Color color = allCards.back()->getColor();
        Label label = allCards.back()->getLabel();
        
        colorCounts[static_cast<int>(color)]++;
        labelCounts[static_cast<int>(label)]++;
    }
    
    // Check color distribution (should be 2 of each card per color)
    for (int i = 0; i < 4; i++) { // RED, GREEN, BLUE, YELLOW
        EXPECT_EQ(colorCounts[i], 26); // 13 labels * 2 each
    }
    
    // Check label distribution (should be 8 of each label: 4 colors * 2 each)
    for (int i = 0; i < 13; i++) { // 0-9, Skip, Reverse, DrawTwo
        EXPECT_EQ(labelCounts[i], 8); // 4 colors * 2 each
    }
    
    // Wild cards in regular deck
    EXPECT_EQ(colorCounts[static_cast<int>(Color::NONE)], 8); 
    EXPECT_EQ(labelCounts[static_cast<int>(Label::Wild)], 4); 
    EXPECT_EQ(labelCounts[static_cast<int>(Label::WildDrawFour)], 4); 
}

// Test draw functionality
TEST(DrawDeck, DrawCard) {
    DrawDeck deck;
    size_t initialSize = deck.size();
    
    std::unique_ptr<Card> drawnCard = deck.draw();
    
    EXPECT_NE(drawnCard, nullptr);
    EXPECT_EQ(deck.size(), initialSize - 1);
}

TEST(DrawDeck, DrawMultipleCards) {
    DrawDeck deck;
    size_t initialSize = deck.size();
    
    std::vector<std::unique_ptr<Card>> drawnCards;
    
    // Draw 10 cards
    for (int i = 0; i < 10; i++) {
        std::unique_ptr<Card> card = deck.draw();
        EXPECT_NE(card, nullptr);
        drawnCards.push_back(std::move(card));
    }
    
    EXPECT_EQ(deck.size(), initialSize - 10);
}

TEST(DrawDeck, DrawAllCards) {
    DrawDeck deck;
    size_t initialSize = deck.size();
    
    std::vector<std::unique_ptr<Card>> allCards;
    
    // Draw all cards
    while (deck.size() > 0) {
        std::unique_ptr<Card> card = deck.draw();
        EXPECT_NE(card, nullptr);
        allCards.push_back(std::move(card));
    }
    
    EXPECT_EQ(deck.size(), 0);
    EXPECT_EQ(allCards.size(), initialSize);
}

// Test top functionality
TEST(DrawDeck, TopCard) {
    DrawDeck deck;
    size_t initialSize = deck.size();
    
    const Card& topCard = deck.top();
    
    // Can't compare Card& with nullptr, so just verify size doesn't change
    EXPECT_EQ(deck.size(), initialSize); // Size shouldn't change
    
    // Draw the card and verify it's the same
    std::unique_ptr<Card> drawnCard = deck.draw();
    EXPECT_EQ(topCard.getColor(), drawnCard->getColor());
    EXPECT_EQ(topCard.getLabel(), drawnCard->getLabel());
}

TEST(DrawDeck, TopCardMultipleTimes) {
    DrawDeck deck;
    
    const Card& top1 = deck.top();
    const Card& top2 = deck.top();
    
    // Should be the same card
    EXPECT_EQ(top1.getColor(), top2.getColor());
    EXPECT_EQ(top1.getLabel(), top2.getLabel());
    
    std::unique_ptr<Card> drawn = deck.draw();
    EXPECT_EQ(top1.getColor(), drawn->getColor());
    EXPECT_EQ(top1.getLabel(), drawn->getLabel());
}

TEST(DrawDeck, SizeAfterDrawing) {
    DrawDeck deck;
    
    EXPECT_EQ(deck.size(), 112);
    
    deck.draw();
    EXPECT_EQ(deck.size(), 111);
    
    deck.draw();
    EXPECT_EQ(deck.size(), 110);
}

// Test edge cases
TEST(DrawDeck, DrawFromEmptyDeck) {
    DrawDeck deck;
    
    // Draw all cards
    for (size_t i = 0; i < 200; i++) {
        deck.draw();
    }
    
    EXPECT_EQ(deck.size(), 24); // 112 - 200 + 112 = 24 (Deck is automatically and fully replenished upon emptying)
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}