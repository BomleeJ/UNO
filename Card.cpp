#include "Card.h"
#include <iostream>



std::string Card::ColortoString()
{
    switch(color) {
        case Color::RED:
        return "R";
        break;
        
        case Color::GREEN:
        return "G";
        break;
        
        case Color::BLUE:
        return "B";
        break;
       
        case Color::YELLOW:
        return "Y";
        break;
        
        case Color::NONE:
        return "W"; // Wild
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
        return "S";
        break;

        case Label::Reverse:
        return "R";
        break;

        case Label::DrawTwo:
        return "+2";
        break;

        case Label::Wild:
        return "W";
        break;

        case Label::WildDrawFour:
        return "+4";
        break;
    }

    return "?";

}

void Card::print()
{
    std::cout << "|" << Card::ColortoString() << Card::LabeltoString() << "|";
}
