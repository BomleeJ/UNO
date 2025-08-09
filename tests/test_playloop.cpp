#include <gtest/gtest.h>
#include "Playloop.h"
#include "DrawDeck.h"
#include "Player.h"
#include <memory>

TEST(PlayLoop, ConstructorOneCPU) {
    DrawDeck drawDeck;
    PlayLoop playLoop(1, drawDeck);
    
    // Should have 2 players (human + 1 CPU)
    EXPECT_EQ(drawDeck.size(), 98); // 112 - 14 cards drawn (7 per player)
}

TEST(PlayLoop, ConstructorMultipleCPU) {
    DrawDeck drawDeck;
    PlayLoop playLoop(3, drawDeck);
    
    // Should have 4 players (human + 3 CPU)
    EXPECT_EQ(drawDeck.size(), 84); // 112 - 28 cards drawn (7 per player)
}

TEST(PlayLoop, ConstructorLargeCPUCount) {
    DrawDeck drawDeck;
    PlayLoop playLoop(10, drawDeck);
    
    // Should have 11 players (human + 10 CPU)
    EXPECT_EQ(drawDeck.size(), 35); // 112 - 77 cards drawn (7 per player)
}

TEST(PlayLoop, CurrentPlayerFirstCall) {
    DrawDeck drawDeck;
    PlayLoop playLoop(1, drawDeck);
    
    Player* firstPlayer = playLoop.CurrentPlayer();
    EXPECT_TRUE(firstPlayer->ishuman()); // First player should be human
}

// Test AdvanceTurn functionality
TEST(PlayLoop, AdvanceTurn) {
    DrawDeck drawDeck;
    PlayLoop playLoop(1, drawDeck);
    
    Player* human = playLoop.CurrentPlayer();
    EXPECT_TRUE(human->ishuman());
    
    playLoop.AdvanceTurn();
    Player* cpu = playLoop.CurrentPlayer();
    EXPECT_FALSE(cpu->ishuman());
}

TEST(PlayLoop, AdvanceTurnMultipleTimes) {
    DrawDeck drawDeck;
    PlayLoop playLoop(2, drawDeck); // 3 players
    
    // First player (human)
    Player* human = playLoop.CurrentPlayer();
    EXPECT_TRUE(human->ishuman());
    
    // Second player (CPU1)
    playLoop.AdvanceTurn();
    Player* cpu1 = playLoop.CurrentPlayer();
    EXPECT_FALSE(cpu1->ishuman());
    
    // Third player (CPU2)
    playLoop.AdvanceTurn();
    Player* cpu2 = playLoop.CurrentPlayer();
    EXPECT_FALSE(cpu2->ishuman());
    
    // Back to human
    playLoop.AdvanceTurn();
    Player* human2 = playLoop.CurrentPlayer();
    EXPECT_TRUE(human2->ishuman());
    EXPECT_EQ(human, human2);
}

TEST(PlayLoop, AdvanceTurnCycle) {
    DrawDeck drawDeck;
    PlayLoop playLoop(1, drawDeck); // 2 players
    
    Player* human = playLoop.CurrentPlayer();
    playLoop.AdvanceTurn();
    Player* cpu = playLoop.CurrentPlayer();
    playLoop.AdvanceTurn();
    Player* human2 = playLoop.CurrentPlayer();
    
    EXPECT_TRUE(human->ishuman());
    EXPECT_FALSE(cpu->ishuman());
    EXPECT_TRUE(human2->ishuman());
    EXPECT_EQ(human, human2);
}

// Test SkipTurn functionality
TEST(PlayLoop, SkipTurn) {
    DrawDeck drawDeck;
    PlayLoop playLoop(2, drawDeck); // 3 players
    
    Player* human = playLoop.CurrentPlayer();
    EXPECT_TRUE(human->ishuman());
    
    playLoop.SkipTurn();
    Player* cpu2 = playLoop.CurrentPlayer();
    EXPECT_FALSE(cpu2->ishuman());
    
    // Should skip over CPU1 and go to CPU2
    playLoop.AdvanceTurn();
    Player* human2 = playLoop.CurrentPlayer();
    EXPECT_TRUE(human2->ishuman());
}

// Test ReverseDirection functionality
TEST(PlayLoop, ReverseDirection) {
    DrawDeck drawDeck;
    PlayLoop playLoop(2, drawDeck); // 3 players
    
    // Go forward: Human -> CPU1 -> CPU2
    Player* human = playLoop.CurrentPlayer();
    playLoop.AdvanceTurn();
    Player* cpu1 = playLoop.CurrentPlayer();
    playLoop.AdvanceTurn();
    Player* cpu2 = playLoop.CurrentPlayer();
    
    // Reverse direction
    playLoop.ReverseDirection();
    
    // Now going backward: CPU2 -> CPU1 -> Human
    playLoop.AdvanceTurn();
    Player* cpu1_back = playLoop.CurrentPlayer();
    EXPECT_EQ(cpu1, cpu1_back);
    
    playLoop.AdvanceTurn();
    Player* human_back = playLoop.CurrentPlayer();
    EXPECT_EQ(human, human_back);
}

TEST(PlayLoop, ReverseDirectionMultipleTimes) {
    DrawDeck drawDeck;
    PlayLoop playLoop(1, drawDeck); // 2 players
    
    Player* human = playLoop.CurrentPlayer();
    playLoop.AdvanceTurn();
    Player* cpu = playLoop.CurrentPlayer();
    
    // Reverse direction
    playLoop.ReverseDirection();
    playLoop.AdvanceTurn();
    Player* human2 = playLoop.CurrentPlayer();
    EXPECT_EQ(human, human2);
    
    // Reverse again (back to forward)
    playLoop.ReverseDirection();
    playLoop.AdvanceTurn();
    Player* cpu2 = playLoop.CurrentPlayer();
    EXPECT_EQ(cpu, cpu2);
}

// Test AddFourtoCurrentPlayer functionality
TEST(PlayLoop, AddFourtoNextPlayer) {
    DrawDeck drawDeck;
    PlayLoop playLoop(1, drawDeck);
    
    Player* player = playLoop.CurrentPlayer();
    Player* nextPlayer = playLoop.NextPlayer();
    size_t initialDeckSize = player->deck.size();
    size_t initialDrawDeckSize = drawDeck.size();
    
    playLoop.AddFourtoNextPlayer(drawDeck);
    
    EXPECT_EQ(nextPlayer->deck.size(), initialDeckSize + 4);
    EXPECT_EQ(drawDeck.size(), initialDrawDeckSize - 4);
}

// Test AddTwotoCurrentPlayer functionality
TEST(PlayLoop, AddTwotoNextPlayer) {
    DrawDeck drawDeck;
    PlayLoop playLoop(1, drawDeck);
    
    Player* player = playLoop.CurrentPlayer();
    size_t initialDeckSize = player->deck.size();
    size_t initialDrawDeckSize = drawDeck.size();
    Player* nextPlayer = playLoop.NextPlayer();

    playLoop.AddTwotoNextPlayer(drawDeck);
 
    
    EXPECT_EQ(nextPlayer->deck.size(), initialDeckSize + 2);
    EXPECT_EQ(drawDeck.size(), initialDrawDeckSize - 2);
}

TEST(PlayLoop, PlayerInitialization) {
    DrawDeck drawDeck;
    PlayLoop playLoop(3, drawDeck);
    
    // Check all players have 7 cards
    for (int i = 0; i < 4; i++) {
        Player* player = playLoop.CurrentPlayer();
        EXPECT_EQ(player->deck.size(), 7);
        playLoop.AdvanceTurn();
    }
}

// Test that all players are properly initialized
TEST(PlayLoop, AllPlayersInitialized) {
    DrawDeck drawDeck;
    PlayLoop playLoop(3, drawDeck); // 4 players
    
    // Check all players
    for (int i = 0; i < 4; i++) {
        Player* player = playLoop.CurrentPlayer();
        EXPECT_NE(player, nullptr);
        EXPECT_EQ(player->deck.size(), 7);
        
        if (i == 0) {
            EXPECT_TRUE(player->ishuman());
        } else {
            EXPECT_FALSE(player->ishuman());
        }
        playLoop.AdvanceTurn();
    }
}

// Test combination of methods
TEST(PlayLoop, CombinationOfMethods) {
    DrawDeck drawDeck;
    PlayLoop playLoop(2, drawDeck); // 3 players
    
    // Start with human
    Player* human = playLoop.CurrentPlayer();
    EXPECT_TRUE(human->ishuman());
    
    // Add 2 cards to next player (CPU1)
    Player* cpu1 = playLoop.NextPlayer();
    size_t cpu1_initial_deck = cpu1->deck.size();
    playLoop.AddTwotoNextPlayer(drawDeck);
    EXPECT_EQ(cpu1->deck.size(), cpu1_initial_deck + 2);

    // Advance to CPU1
    playLoop.AdvanceTurn();
    Player* cpu1_check = playLoop.CurrentPlayer();
    EXPECT_FALSE(cpu1_check->ishuman());
    EXPECT_EQ(cpu1_check, cpu1);

    // Add 2 cards to next player (CPU2)
    Player* cpu2 = playLoop.NextPlayer();
    size_t cpu2_initial_deck = cpu2->deck.size();
    playLoop.AddTwotoNextPlayer(drawDeck);
    EXPECT_EQ(cpu2->deck.size(), cpu2_initial_deck + 2);

    // Skip turn (should go to human)
    playLoop.SkipTurn();
    Player* human2 = playLoop.CurrentPlayer();
    EXPECT_TRUE(human2->ishuman());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}