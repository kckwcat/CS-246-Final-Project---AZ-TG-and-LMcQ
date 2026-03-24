#ifndef OWNABLE_SQUARE_H
#define OWNABLE_SQUARE_H

import <Square.cc>;

class OwnableSquare : public Square {
protected:
    Player* owner;
    bool mortgaged;
    
public:
    OwnableSquare(const std::string& name, int index) 
        : Square(name, index), owner(nullptr), mortgaged(false) {}
    
    virtual ~OwnableSquare() = default;
    
    virtual int calculateRent() const = 0;
    virtual int getPurchaseCost() const = 0;
    virtual int getMortgageValue() const = 0;
    virtual std::string getMonopolyBlock() const = 0;
    
    Player* getOwner() const { return owner; }
    void setOwner(Player* newOwner) { owner = newOwner; }
    
    bool isMortgaged() const { return mortgaged; }
    void setMortgaged(bool m) { mortgaged = m; }
    
    bool mortgage() {
        if (!mortgaged && owner) {
            mortgaged = true;
            return true;
        }
        return false;
    }
    
    bool unmortgage() {
        if (mortgaged && owner) {
            mortgaged = false;
            return true;
        }
        return false;
    }
};

#endif
