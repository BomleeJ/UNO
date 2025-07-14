#include "Card.h"
#include "DrawDeck.h"
#include <list>
#include <map>

using PlayableCards = std::map<int, Card*>;

class PlayerDeck 
{
private:
    std::list<Card*> deck; 

public:
    PlayerDeck(DrawDeck& deck);

    //filters card in the player deck 
    PlayableCards filter_playable(Card* other);

    Card* remove(size_t idx);

    void print();

    void print(PlayableCards playable);

    ~PlayerDeck();
    

};