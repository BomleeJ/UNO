#include "Card.h"
#include <iostream>
#include <format>



std::string Card::ColortoString()
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

bool Card::isvalid(Card* other)
{
    if (wild) { return true; }

    if (other->getColor() == color || other->getLabel() == label) {return true; }

    return false;
    
}


Color Card::getColor()
{   
    return color;
}

Label Card::getLabel()
{
    return label;
}

std::string Card::LabeltoString()
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

void Card::print()
{
    std::cout << "|" << Card::ColortoString() << Card::LabeltoString() << "|";
}

void Card::printFancy() {
    std::string colorStr = ColortoString();
    std::string labelStr = LabeltoString();

    std::cout << std::format("┌───────────┐\n");
    std::cout << std::format("│{: ^11}│\n", "");           // Empty line
    std::cout << std::format("│{: ^11}│\n", colorStr);      // Center color
    std::cout << std::format("│{: ^11}│\n", labelStr);      // Center label
    std::cout << std::format("│{: ^11}│\n", "");           // Empty line
    std::cout << std::format("└───────────┘\n");
}