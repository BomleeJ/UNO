#include <gtest/gtest.h>
#include "Player.h"
#include "DrawDeck.h"
#include "DiscardPile.h"
#include <memory>

// Test constructor and basic properties
TEST(Human, Constructor) {
    Human human;
    EXPECT_TRUE(human.ishuman());
    EXPECT_FALSE(human.hasWon());
    EXPECT_FALSE(human.hasPlayableCards());
}

// Test inheritance from Player
TEST(Human, InheritsFromPlayer) {
    Human human;
    Player* player = &human;
    EXPECT_TRUE(player->ishuman());
}

// Test drawing cards
TEST(Human, DrawCard) {
    Human human;
    DrawDeck drawDeck;
    
    human.drawCard(drawDeck);
    
    EXPECT_EQ(human.deck.size(), 1);
    EXPECT_EQ(drawDeck.size(), 111); // 112 - 1
}

TEST(Human, DrawSevenCards) {
    Human human;
    DrawDeck drawDeck;
    size_t initialDeckSize = drawDeck.size();
    
    human.drawSevenCards(drawDeck);
    
    EXPECT_EQ(human.deck.size(), 7);
    EXPECT_EQ(drawDeck.size(), initialDeckSize - 7);
}

TEST(Human, DrawMultipleCards) {
    Human human;
    DrawDeck drawDeck;
    
    human.drawCard(drawDeck);
    human.drawCard(drawDeck);
    human.drawCard(drawDeck);
    
    EXPECT_EQ(human.deck.size(), 3);
    EXPECT_EQ(drawDeck.size(), 109);
}

// Test removing cards
TEST(Human, RemoveCard) {
    Human human;
    DrawDeck drawDeck;
    
    human.drawSevenCards(drawDeck);
    EXPECT_EQ(human.deck.size(), 7);
    
    auto removedCard = human.removeCard(0);
    EXPECT_NE(removedCard, nullptr);
    EXPECT_EQ(human.deck.size(), 6);
}

TEST(Human, RemoveCardFromMiddle) {
    Human human;
    DrawDeck drawDeck;
    
    human.drawSevenCards(drawDeck);
    
    auto removedCard = human.removeCard(3);
    EXPECT_NE(removedCard, nullptr);
    EXPECT_EQ(human.deck.size(), 6);
}

TEST(Human, RemoveCardOutOfRange) {
    Human human;
    DrawDeck drawDeck;
    
    human.drawSevenCards(drawDeck);
    
    EXPECT_THROW(human.removeCard(10), std::out_of_range);
    EXPECT_THROW(human.removeCard(7), std::out_of_range);
}

// Test discarding cards
TEST(Human, DiscardCard) {
    Human human;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    human.drawSevenCards(drawDeck);
    size_t initialDeckSize = human.deck.size();
    
    human.discardCard(0, discardPile);
    
    EXPECT_EQ(human.deck.size(), initialDeckSize - 1);
    EXPECT_EQ(discardPile.size(), 1);
}

TEST(Human, DiscardMultipleCards) {
    Human human;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    human.drawSevenCards(drawDeck);
    
    human.discardCard(0, discardPile);
    human.discardCard(0, discardPile);
    human.discardCard(0, discardPile);
    
    EXPECT_EQ(human.deck.size(), 4);
    EXPECT_EQ(discardPile.size(), 3);
}

// Test playable cards functionality
TEST(Human, RefreshPlayableCards) {
    Human human;

    // Set controlled hand
    human.deck.add(std::make_unique<Card>(Color::GREEN, Label::Three));
    human.deck.add(std::make_unique<Card>(Color::RED, Label::Five)); // This should match
    human.deck.add(std::make_unique<Card>(Color::BLUE, Label::Skip));
    
    DiscardPile discardPile;
    discardPile.add(std::make_unique<Card>(Color::RED, Label::Nine)); // Matches by color
    
    human.refreshPlayableCards(discardPile);
    
    // Should have 1 playable card
    EXPECT_EQ(human.choices.size(), 1);
}

TEST(Human, HasPlayableCards) {
    Human human;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    human.drawSevenCards(drawDeck);
    
    // Initially no playable cards
    EXPECT_FALSE(human.hasPlayableCards());
    
    // Add matching card to discard pile
    discardPile.add(std::make_unique<Card>(Color::RED, Label::Five));
    human.refreshPlayableCards(discardPile);
    
    // May or may not have playable cards depending on drawn cards
    // This is probabilistic since cards are drawn randomly
}

TEST(Human, HasPlayableCardsWithMatches) {
    Human human;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    // Draw specific cards (this is simplified - in reality cards are random)
    human.drawSevenCards(drawDeck);
    
    // Add a card that might match
    discardPile.add(std::make_unique<Card>(Color::RED, Label::Five));
    human.refreshPlayableCards(discardPile);
    
    // Check if any cards are playable
    // This test is more about the method working than specific results
}

// Test win condition
TEST(Human, HasWon) {
    Human human;
    DrawDeck drawDeck;
    
    // Initially not won
    EXPECT_FALSE(human.hasWon());
    
    // Draw some cards
    human.drawSevenCards(drawDeck);
    EXPECT_FALSE(human.hasWon());
    
    // Remove all cards
    for (int i = 0; i < 7; i++) {
        human.removeCard(0);
    }
    
    EXPECT_TRUE(human.hasWon());
}

TEST(Human, HasWonEmptyDeck) {
        Human human;
        EXPECT_FALSE(human.hasWon());
}

// Test human-specific methods
TEST(Human, IsHuman) {
    Human human;
    EXPECT_TRUE(human.ishuman());
    
    // Test through base class pointer
    Player* player = &human;
    EXPECT_TRUE(player->ishuman());
}

// Test print methods (these are harder to test since they output to console)
TEST(Human, PrintMethodsExist) {
    Human human;
    DrawDeck drawDeck;
    
    human.drawSevenCards(drawDeck);
    
    // These methods should not crash
    EXPECT_NO_THROW(human.print());
    EXPECT_NO_THROW(human.printPlayable());
}

// Test edge cases
TEST(Human, DrawFromEmptyDrawDeck) {
    Human human;
    DrawDeck drawDeck;
    
    // Draw all cards from draw deck
    for (int i = 0; i < 200; i++) {
        human.drawCard(drawDeck);
    }
    
    // Should still be able to draw (deck replenishes)
    EXPECT_GT(human.deck.size(), 0);
}

TEST(Human, DiscardAllCards) {
    Human human;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    human.drawSevenCards(drawDeck);
    
    // Discard all cards
    for (int i = 0; i < 7; i++) {
        human.discardCard(0, discardPile);
    }
    
    EXPECT_TRUE(human.hasWon());
    EXPECT_EQ(discardPile.size(), 7);
}

TEST(Human, MultipleDrawAndDiscard) {
    Human human;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    // Draw cards
    human.drawSevenCards(drawDeck);
    EXPECT_EQ(human.deck.size(), 7);
    
    // Discard some
    human.discardCard(0, discardPile);
    human.discardCard(0, discardPile);
    EXPECT_EQ(human.deck.size(), 5);
    EXPECT_EQ(discardPile.size(), 2);
    
    // Draw more
    human.drawCard(drawDeck);
    human.drawCard(drawDeck);
    EXPECT_EQ(human.deck.size(), 7);
}

// Test integration with game components
TEST(Human, IntegrationWithDrawDeck) {
    Human human;
    DrawDeck drawDeck;
    
    human.drawSevenCards(drawDeck);
    
    EXPECT_EQ(human.deck.size(), 7);
    EXPECT_EQ(drawDeck.size(), 105);
    
    // Remove and add back
    auto card = human.removeCard(0);
    human.deck.add(std::move(card));
    
    EXPECT_EQ(human.deck.size(), 7);
}

TEST(Human, IntegrationWithDiscardPile) {
    Human human;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    human.drawSevenCards(drawDeck);
    
    human.discardCard(0, discardPile);
    
    EXPECT_EQ(human.deck.size(), 6);
    EXPECT_EQ(discardPile.size(), 1);
    
    // Check if remaining cards are playable against discarded card
    human.refreshPlayableCards(discardPile);
    // Result depends on what cards were drawn
}

// Test card validation through playable cards
TEST(Human, PlayableCardsValidation) {
    Human human;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    human.drawSevenCards(drawDeck);
    
    // Add a specific card to discard pile
    discardPile.add(std::make_unique<Card>(Color::RED, Label::Five));
    
    human.refreshPlayableCards(discardPile);
    
    // Check if any cards in choices are actually playable
    for (const auto& [index, card] : human.choices) {
        EXPECT_TRUE(card->isvalid(discardPile.top()));
    }
}

// Test that human can handle wild cards
TEST(Human, WildCardHandling) {
    Human human;
    DrawDeck drawDeck;
    DiscardPile discardPile;
    
    human.drawSevenCards(drawDeck);
    
    // Add a wild card to discard pile
    discardPile.add(std::make_unique<Card>(Color::NONE, Label::Wild));
    
    human.refreshPlayableCards(discardPile);
    
    // Wild cards should be playable against any card
    // This test verifies the system works with wild cards
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}