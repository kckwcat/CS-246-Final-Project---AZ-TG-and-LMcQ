#ifndef SQUARE_H
#define SQUARE_H

import <string>;
import <memory>;
import <vector>;

class Player;
class Game;

class Square {
protected:
    std::string name;
    int index;
    
public:
    Square(const std::string& name, int index) : name(name), index(index) {}
    virtual ~Square() = default;
    
    virtual void landOn(Player& player, Game& game) = 0;
    virtual std::string getName() const { return name; }
    virtual int getIndex() const { return index; }
    virtual std::string getDisplaySymbol() const { 
        return name.length() >= 3 ? name.substr(0, 3) : name; 
    }
};

#endif
