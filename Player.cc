#ifndef PLAYER_H
#define PLAYER_H

import <string>;
import <vector>;
import <memory>;

class OwnableSquare;
class Game;

class Player {
    std::string name;
    char piece;
    int money;
    int position;
    int timsCups;
    int timsTurns;  // -1 if not in Tims line, 0-2 if in line
    std::vector<OwnableSquare*> properties;

public:
    Player(const std::string& name, char piece) 
        : name(name), piece(piece), money(1500), position(0), 
          timsCups(0), timsTurns(-1) {}
    
    void move(int steps, Game& game);
    // if player has to pay another player
    bool pay(int amount) {
        if (amount <= money) {
            money -= amount;
            return true;
        }
        return false;  // Need bankruptcy handling
    }
    
    void addMoney(int amount) { money += amount; }
    
    void receiveProperty(OwnableSquare* property) {
        properties.push_back(property);
        property->setOwner(this);
    }
    
    bool hasMonopoly(const std::string& block) const {
        // Count properties owned in this block
        int owned = 0;
        int total = getTotalInBlock(block);
        for (auto prop : properties) {
            if (prop->getMonopolyBlock() == block && !prop->isMortgaged()) {
                owned++;
            }
        }
        return owned == total && total > 0;
    }
    
    // Tims Line methods
    void enterTimsLine() {
        position = 10;  // DC Tims Line square
        timsTurns = 0;
    }
    
    void leaveTimsLine() {
        timsTurns = -1;
    }
    
    bool isInTimsLine() const { return timsTurns >= 0; }
    
    void incrementTimsTurn() { 
        if (timsTurns >= 0) timsTurns++; 
    }
    
    int getTimsTurns() const { return timsTurns; }
    
    // Bankruptcy
    bool declareBankruptcy(Game& game);
    
    // Getters
    int getMoney() const { return money; }
    int getPosition() const { return position; }
    char getPiece() const { return piece; }
    std::string getName() const { return name; }
};

#endif
