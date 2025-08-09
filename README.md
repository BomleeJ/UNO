# UNO Terminal Game (C++20)

A modern terminal-based UNO game implemented in **C++20**, featuring an ASCII-art user interface, advanced memory management, and object-oriented design patterns.  

**C++20 is required** to compile and run this project.  



## Build Instructions

**1. Configure**
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```
2. Compile
```bash
cmake --build build -j
```
3. Run the game
```bash
cmake --build build --target run
```
Or run the executable directly:
```bash
./build/bin/cardgame
```
4. Run tests
```bash
ctest --test-dir build --output-on-failure
```

## ASCII User Interface

### The game uses a fully ASCII-based interface to display menus, cards, and game state:

### Main Menu
<img width="306" height="251" alt="Screenshot 2025-08-09 at 2 22 40 PM" src="https://github.com/user-attachments/assets/c122dff0-7911-4ba9-90ca-41296dd15127" />

### Hand Display
<img width="383" height="291" alt="Screenshot 2025-08-09 at 2 23 05 PM" src="https://github.com/user-attachments/assets/181a600f-9f65-45f7-bafa-12221b501187" />

### Cards
<img width="368" height="111" alt="Screenshot 2025-08-09 at 2 23 00 PM" src="https://github.com/user-attachments/assets/64812b66-e773-4ccb-b14b-9c4b9901a346" />




# Technical Details

## Memory Management & Automatic Resource Cleanup

### Smart Pointer Ownership
### Example
```cpp
class PlayerDeck {
private:
    std::list<std::unique_ptr<Card>> deck;  // Automatic memory management
public:
    void add(std::unique_ptr<Card> card) {
        deck.push_back(std::move(card));    // Transfer ownership
    }
};
```
### Composition-Based Resource Management
### Example
```cpp
class UNOGame {
private:
    DiscardPile played;      // Automatic cleanup via composition
    DrawDeck todraw;         // Stack-allocated, destructor handles cleanup
    PlayLoop Players;        // All resources cleaned up automatically
};
```
Features Demonstrated:
- Automatic memory management through smart pointers
- Composition over manual resource handling
- Zero memory leaks without explicit cleanup code
- Exception safety via automatic unwinding of objects during stack unwinds
- No raw new/delete calls in gameplay logic


## Object-Oriented Design Patterns
### Example
```cpp
class Player {
public:
    virtual bool ishuman() const { return false; }
};

class Human : public Player {
public:
    bool ishuman() const override { return true; }
};

class CPU : public Player {
    // AI-specific logic
};
```
-	Inheritance and polymorphism for extensibility
-	Clean separation of player types (human vs CPU)
-	Virtual functions for runtime dispatch



## Operator Overloading
### Example
```cpp
class Card {
public:
    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;
};
```



## Strong Type Safety
### Example
```cpp
enum class Color { RED, GREEN, BLUE, YELLOW, NONE };
enum class Label { Zero, One, Two, /* ... */ Wild, WildDrawFour };
```
-	Scoped enums prevent implicit conversions
-	Forces explicit handling of all label and color cases



## Comprehensive Testing
- Google Test–based unit and integration testing
- ~1450 LOC
- Tests cover:
  - Core gameplay mechanics
  - Edge cases
  - Exception safety

## Exception Safety & Error Handling

**Strong Guarantee Example – `PlayerDeck::remove`**
```cpp
std::unique_ptr<Card> PlayerDeck::remove(size_t idx) {
    if (idx >= deck.size()) {
        throw std::out_of_range("Index out of range");
    }
    auto it = deck.begin();
    std::advance(it, idx);
    std::unique_ptr<Card> card = std::move(*it);
    deck.erase(it);
    return card;
}
```
- Designed for strong exception safety — either removes the card or leaves the deck untouched.
-	Leveraged std::list<std::unique_ptr<Card>> for O(1) erasure without copies and leak-free transfers of ownership.
-	Guarantees no allocations during removal, keeping it exception-neutral.


## Important Data Structure Choices

### PlayerDeck – std::list<std::unique_ptr<Card>> 
PlayerDeck represents the current hand of a player—human or AI—managing storage, display, and efficient removal of cards, while also serving as the basis for AI decision-making by exposing the state of the hand.

-	Goal: Remove arbitrary cards in O(1) without copying Card objects.
-	Why: In UNO, any card in hand may be played; avoiding O(n) shifts and deep copies is critical for performance and memory safety.
-	Trade-off: Sacrifices random access — acceptable since hand sizes are small.


### PlayLoop – std::vector<std::unique_ptr<Player>> with modulo turn logic
PlayLoop is the core data structure that manages turn order in the game, keeping track of the current player, applying card effects to the next player, and handling seamless transitions between players in both forward and reverse directions.

-	Goal: Maintain circular turn order with minimal logic.
-	Why: Vector provides fast random access and cache-friendly iteration; players never change mid-game, so no need for O(1) insertion/removal.
-	Modulo arithmetic: **nextPlayer = (numPlayers + currentPlayeridx + direction) % numPlayers** wraps the index correctly for both forward (direction = +1) and reverse (direction = -1) play without extra branching.
-	Result: Cleaner, faster turn management than linked list traversal.

## How to Play
1.	Launch the game and select the number of CPU players
2.  Select Start Game from the main menu.
3.	Your hand will be shown in a table grouped by card color.
4.	Below the table, you’ll see playable cards listed with an INDEX.
   
   <img width="376" height="96" alt="Screenshot 2025-08-09 at 2 23 21 PM" src="https://github.com/user-attachments/assets/13612d0a-558b-4beb-a159-50970e675275" /> 
  
5.	To play a card, enter its associated index number.
6.	Follow UNO rules to match the color or label of the top discard card, or play a wild card.
