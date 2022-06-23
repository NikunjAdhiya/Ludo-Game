#ifndef TOKEN_H
#define TOKEN_H


class Token
{

    /*
    Declaration of class token which can be used for all tokens of all player
    */
    char symbol;
    // A character to store symbol of the token
    int path;
    /* A interger to store the path of the token
     If path =0 , it means it is not unlocked yet
     If path=1, it means it is unlocked and in the main circle in which every token should
    complete a circle in clockwise direction to go to Home
     If path =2, it means the token is in the winning path from which it reaches HOME
     If path=3, it mean the token completed the game and reached the home position
    */
    int position;

public:
    Token();

    // Getter and setter methods for the data members
    char Get_Symbol();
    int Get_position();
    int Get_path();
    void Set_path(int path);
    void Set_position(int position);
    void Set_symbol(char symbol);
    bool IsUnlocked();
    bool IsFinished();
};


#endif // TOKEN_H
