#include "Token.h"
#include<bits/stdc++.h>
Token::Token()
{
    path = 0;
    // Construction which intialises path to 0 it means it is in starting position
}
char Token::Get_Symbol()
{
    return symbol;
}
int Token::Get_position()
{
    return position;
}
int Token::Get_path()
{
    return path;
}
void Token::Set_path(int path)
{
    this->path = path;
}
void Token::Set_position(int position)
{
    this->position = position;
}
void Token::Set_symbol(char symbol)
{
    this->symbol = symbol;
}
bool Token::IsUnlocked()
{
    // returns false if the token is in locked position else return true
    return path != 0;
}
bool Token::IsFinished()
{
    return path == 3;
    // returns true if the token finished the game, that is if the path is 3
}
