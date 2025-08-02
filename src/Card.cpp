#include "Card.h"
#include <iostream>
#include <format>

bool Card::operator==(const Card& other) const
{
    return color == other.color && label == other.label;
}

bool Card::operator!=(const Card& other) const
{
    return !(*this == other);
}

std::string Card::ColortoString() const
{
    switch(color) {
        case Color::RED:
        return "RED";
        break;
        
        case Color::GREEN:
        return "GREEN";
        break;
        
        case Color::BLUE:
        return "BLUE";
        break;
       
        case Color::YELLOW:
        return "YELLOW";
        break;
        
        case Color::NONE:
        return "ANY"; // Wild
        break;
    }

    return "?";

}

bool Card::isvalid(const Card& other) const
{
    if (wild) { return true; }

    if (other.getColor() == color || other.getLabel() == label) {return true; }

    return false;
    
}


Color Card::getColor() const
{   
    return color;
}

Label Card::getLabel() const
{
    return label;
}

std::string Card::LabeltoString() const
{   

    if (label <= Label::Nine)
    {
        int num = static_cast<int>(label);
        return std::to_string(num);
    }

    switch(label)
    {
        case Label::Skip:
        return "SKIP";
        break;

        case Label::Reverse:
        return "REVERSE";
        break;

        case Label::DrawTwo:
        return "+2";
        break;

        case Label::Wild:
        return "WILD";
        break;

        case Label::WildDrawFour:
        return "WILD +4";
        break;
    }

    return "?";

}

void Card::print() const
{
    std::cout << "|" << Card::ColortoString() << Card::LabeltoString() << "|";
}

void Card::printFancy() const {
    std::string colorStr = ColortoString();
    std::string labelStr = LabeltoString();

    std::cout << std::format("┌───────────┐\n");
    std::cout << std::format("│{: ^11}│\n", "");           // Empty line
    std::cout << std::format("│{: ^11}│\n", colorStr);      // Center color
    std::cout << std::format("│{: ^11}│\n", labelStr);      // Center label
    std::cout << std::format("│{: ^11}│\n", "");           // Empty line
    std::cout << std::format("└───────────┘\n");
}