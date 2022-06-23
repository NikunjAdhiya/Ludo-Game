#ifndef PLAYER_H
#define PLAYER_H
#include"Token.h"
class Board;
class Player
{
    int player_number;
    Token *tokens;
    // A pointer to array of tokens as each player has four tokens
public:
    friend class Board;
    // Declaring the Board class as freind as it should access the tokens pointer
    // in its methods while moving the tokens
    Player();
    // Getter and setter methods
    void set_player_number(int player_number);
    int get_player_number();
    void set_symbols();
    int get_no_of_unlocked();
    bool IsWon();
};


#endif // PLAYER_H
