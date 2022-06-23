#include "Player.h"
#include<iostream>
using namespace std;
Player::Player()
{
    tokens = new Token[4];
    // Allocation of dynamic memory  of length 4 to the token as each player will have four tokens
}
void Player::set_player_number(int player_number)
{
    this->player_number = player_number;
}
int Player::get_player_number()
{
    return player_number;
}
void Player::set_symbols()
{
    int number = get_player_number();
    switch (number)
    {
    // In this, the symbols for the tokens of the player will be get intialises
    // with the respective symbols
    // capital letters for player 1
    // small letter for player 2
    // digits for player 3
    // special symbols like @,#,$,% for player 4
    case 1:
        tokens[0].Set_symbol('A');
        tokens[1].Set_symbol('B');
        tokens[2].Set_symbol('C');
        tokens[3].Set_symbol('D');
        break;
    case 2:
        tokens[0].Set_symbol('a');
        tokens[1].Set_symbol('b');
        tokens[2].Set_symbol('c');
        tokens[3].Set_symbol('d');
        break;
    case 3:
        tokens[0].Set_symbol('1');
        tokens[1].Set_symbol('2');
        tokens[2].Set_symbol('3');
        tokens[3].Set_symbol('4');
        break;
    case 4:
        tokens[0].Set_symbol('@');
        tokens[1].Set_symbol('#');
        tokens[2].Set_symbol('$');
        tokens[3].Set_symbol('%');
        break;
    default:
        cout << "Error player number\n";
        break;
    }
}
int Player::get_no_of_unlocked()
{
    // A function which returns number of tokens of this player which are unlocked
    int n = 0;
    for (int i = 0; i < 4; i++)
    {
        if (tokens[i].IsUnlocked())
            n++;
    }
    return n;
}
bool Player::IsWon()
{
    // returns true if all the tokens finished the game
    return tokens[0].IsFinished() && tokens[1].IsFinished() && tokens[2].IsFinished() && tokens[3].IsFinished();
}
