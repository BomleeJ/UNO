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

    std::string ColortoString();
    std::string LabeltoString();

public:
    Card(Color color, Label label):
    color { color }, label { label }
    {
        if ((label == Label::Wild || label == Label::WildDrawFour) && color != Color::NONE)
        {
            throw std::invalid_argument("Wild Cards cannot have a color");
        }
        
        if (label == Label::Wild || label == Label::WildDrawFour)
            wild = true;
    }

    bool isvalid(Card* other);
    
    Color getColor();
    Label getLabel();

    void print();
    
}; 