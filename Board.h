#ifndef BOARD_H
#define BOARD_H
#include"Player.h"
#include<bits/stdc++.h>
using namespace std;
class Board
{
    // The class Board from which the whole controlling is done
    Player *players;
    // A pointer to the player class
    string paths[52];
    // A  array of strings to represent the outer cirlce in which the players move
    string winpaths[4][5];
    // A 2-d array which represent the winning path through which a player reaches HOME
    char Home[4][4];
    // A 2-d array of characters to represent the locked position of tokens for each player
    char WON[4][4];
    // A 2-d array of character to represent the tokens which completed the game
    int killed, reachedHome;
    // two integers to represent if in any move, any player killed other and to represent if any player reached
    // home which will be continously changing for each move
    int number_of_players;
    // integer to store number of players which is given by user
    queue<int> WinnerQueue;
    // A Queue to push the player numbers as they won the game
public:
    Board();
    void Set_No_Of_Players(int n);
    void unlock(char x);
    bool can_be_movable(int die_no, char x);
    int getplayerindex(char x);
    int gettokenindex(char x);
    void move(char token, int die_no);
    void Make_throw(int player_no);
    void Set_Board();
    void Display_Board();
    bool IsWon(int player_no);
    bool IsGameCompleted();
    void Show_Instructions();
    void Show_Result();
};
#endif // BOARD_H
