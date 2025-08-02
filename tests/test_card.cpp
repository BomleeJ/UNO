#include <iostream>
#include <cassert>
#include <gtest/gtest.h>
#include "Card.h"
#include <string>
#include <vector>

// Test constructor and basic properties
TEST(Card, ConstructorBasic) {
    Card redFive(Color::RED, Label::Five);
    EXPECT_EQ(redFive.getColor(), Color::RED);
    EXPECT_EQ(redFive.getLabel(), Label::Five);
    EXPECT_FALSE(redFive.iswild());
    EXPECT_FALSE(redFive.isspecial());
}

TEST(Card, ConstructorSpecial) {
    Card skipCard(Color::BLUE, Label::Skip);
    EXPECT_EQ(skipCard.getColor(), Color::BLUE);
    EXPECT_EQ(skipCard.getLabel(), Label::Skip);
    EXPECT_FALSE(skipCard.iswild());
    EXPECT_TRUE(skipCard.isspecial());
}

TEST(Card, ConstructorWild) {
    Card wildCard(Color::NONE, Label::Wild);
    EXPECT_EQ(wildCard.getColor(), Color::NONE);
    EXPECT_EQ(wildCard.getLabel(), Label::Wild);
    EXPECT_TRUE(wildCard.iswild());
    EXPECT_TRUE(wildCard.isspecial());
}

// Test wild card validation
TEST(Card, WildCardValidation) {
    Card wildCard(Color::NONE, Label::Wild);
    Card wildDrawFour(Color::NONE, Label::WildDrawFour);
    
    EXPECT_TRUE(wildCard.iswild());
    EXPECT_TRUE(wildDrawFour.iswild());
    EXPECT_TRUE(wildCard.isspecial());
    EXPECT_TRUE(wildDrawFour.isspecial());
}

// Test card validation logic
TEST(Card, CardValidationSameColor) {
    Card redFive(Color::RED, Label::Five);
    Card redThree(Color::RED, Label::Three);
    
    EXPECT_TRUE(redFive.isvalid(redThree));  // Same color
}

TEST(Card, CardValidationSameLabel) {
    Card redFive(Color::RED, Label::Five);
    Card blueFive(Color::BLUE, Label::Five);
    
    EXPECT_TRUE(redFive.isvalid(blueFive));  // Same label
}

TEST(Card, CardValidationDifferent) {
    Card redFive(Color::RED, Label::Five);
    Card blueThree(Color::BLUE, Label::Three);
    
    EXPECT_FALSE(redFive.isvalid(blueThree));  // Different color and label
}

TEST(Card, WildCardAlwaysValid) {
    Card wildCard(Color::NONE, Label::Wild);
    Card redFive(Color::RED, Label::Five);
    Card blueThree(Color::BLUE, Label::Three);
    
    EXPECT_TRUE(wildCard.isvalid(redFive));    // Wild cards are always valid
    EXPECT_TRUE(wildCard.isvalid(blueThree));  // Wild cards are always valid
}

// Test number cards (0-9)
TEST(Card, NumberCards) {
    std::vector<Label> numbers = {Label::Zero, Label::One, Label::Two, Label::Three, 
                                 Label::Four, Label::Five, Label::Six, Label::Seven, 
                                 Label::Eight, Label::Nine};
    
    for (int i = 0; i < numbers.size(); i++) {
        Card card(Color::RED, numbers[i]);
        EXPECT_EQ(card.getLabel(), numbers[i]);
        EXPECT_EQ(card.getColor(), Color::RED);
        EXPECT_FALSE(card.iswild());
        EXPECT_FALSE(card.isspecial());
    }
}

// Test special cards
TEST(Card, SpecialCards) {
    Card skipCard(Color::BLUE, Label::Skip);
    Card reverseCard(Color::GREEN, Label::Reverse);
    Card drawTwoCard(Color::YELLOW, Label::DrawTwo);
    
    EXPECT_TRUE(skipCard.isspecial());
    EXPECT_TRUE(reverseCard.isspecial());
    EXPECT_TRUE(drawTwoCard.isspecial());
    EXPECT_FALSE(skipCard.iswild());
    EXPECT_FALSE(reverseCard.iswild());
    EXPECT_FALSE(drawTwoCard.iswild());
}

// Test all colors
TEST(Card, AllColors) {
    std::vector<Color> colors = {Color::RED, Color::GREEN, Color::BLUE, Color::YELLOW, Color::NONE};
    
    for (Color color : colors) {
        Card card(color, Label::Five);
        EXPECT_EQ(card.getColor(), color);
        EXPECT_EQ(card.getLabel(), Label::Five);
    }
}

// Test that wild cards can't have colors (constructor validation)
TEST(Card, WildCardColorValidation) {
    // This should throw an exception
    EXPECT_THROW(Card(Color::RED, Label::Wild), std::invalid_argument);
    EXPECT_THROW(Card(Color::BLUE, Label::WildDrawFour), std::invalid_argument);
    
    // These should work
    EXPECT_NO_THROW(Card(Color::NONE, Label::Wild));
    EXPECT_NO_THROW(Card(Color::NONE, Label::WildDrawFour));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}