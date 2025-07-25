#pragma once
#include <string>
#include <unordered_set>
#include <stdexcept>

enum class Color { RED, GREEN, BLUE, YELLOW, NONE};

enum class Label {
    Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
    Skip, Reverse, DrawTwo,
    Wild, WildDrawFour
};

class Card {
    Color color;
    Label label; // 0-9, SKIP, REVERSE, +4, +2
    bool wild;
    bool special;

    std::string ColortoString();
    std::string LabeltoString();

public:
    Card(Color color, Label label):
    color { color }, label { label }, wild { false }, special { false }
    {
        if ((label == Label::Wild || label == Label::WildDrawFour) && color != Color::NONE)
        {
            throw std::invalid_argument("Wild Cards cannot have a color");
        }
        
        if (static_cast<int>(label) >= static_cast<int>(Label::Skip))
        {
            special = true;
        }

        if (label == Label::Wild || label == Label::WildDrawFour)
        {
            wild = true;
        }

        
            
    }

    bool isvalid(Card* other);
    bool isspecial() { return special; }
    bool iswild() { return wild; }
    
    Color getColor();
    Label getLabel();
    

    void print();
    void printFancy();
}; 