#include "Board.h"
#include<windows.h>
#include<conio.h>
using namespace std;
Board::Board()
{
    Show_Instructions();
    // Constructor which calls Show_Instruction() method which is defined later
    // This function will display the Instructions of the game to the user
}
void Board::Set_No_Of_Players(int n)
{
    // A setter method which intialises number of players in the game which is given by user
    number_of_players = n;
    players = new Player[n];
    for (int i = 0; i < n; i++)
    {
        players[i].set_player_number(i + 1);
        players[i].set_symbols();
    }
}
void Board::unlock(char x)
{
    // A function which unlocks the given token
    int i = getplayerindex(x);
    int j = gettokenindex(x);
    players[i].tokens[j].Set_path(1);
    players[i].tokens[j].Set_position(4 + i * 13);
}
bool Board::can_be_movable(int die_no, char x)
{
    // returns true if the token can be movable by the given die_no else returns false
    int i = getplayerindex(x);
    int j = gettokenindex(x);
    int path = players[i].tokens[j].Get_path();
    int position = players[i].tokens[j].Get_position();
    if (path == 2)
    {
        if (die_no > 5 - position)
            return false;
        else
            return true;
    }
    if (path == 3)
        return false;
    if (path == 1)
    {
        if ((position + die_no) % 52 == 4 || (position + die_no) % 52 == 17 || (position + die_no) % 52 == 30 || (position + die_no) % 52 == 43)
        {
            int turn_pos = 2 + i * 13;
            for (int z = 0; z < 6; z++)
            {
                if ((position + z) % 52 == turn_pos)
                    return true;
            }
            return false;
        }

        string str = paths[(position + die_no) % 52];
        if (str.compare("    ") == 0)
            return true;
        else if (str[0] != ' ' && str[1] == ' ' && str[2] == ' ' && str[3] == ' ')
        {
            return true;
        }
        else
        {
            int k = getplayerindex(str[0]);
            if (k == i)
                return true;
            else
                return false;
        }
    }
    return false;
}
int Board::getplayerindex(char x)
{
    // returns the player index in the array of players for the given token symbol
    if (x == 'A' || x == 'B' || x == 'C' || x == 'D')
        return 0;
    if (x == 'a' || x == 'b' || x == 'c' || x == 'd')
        return 1;
    if (x == '1' || x == '2' || x == '3' || x == '4')
        return 2;
    if (x == '@' || x == '$' || x == '%' || x == '#')
        return 3;
    return 0;
}
int Board::gettokenindex(char x)
{
    // returns the index in the tokens array of the given symbol of token
    if (x == 'A' || x == 'a' || x == '1' || x == '@')
        return 0;
    if (x == 'B' || x == 'b' || x == '2' || x == '#')
        return 1;
    if (x == 'C' || x == 'c' || x == '3' || x == '$')
        return 2;
    if (x == 'D' || x == 'd' || x == '4' || x == '%')
        return 3;
    return 0;
}
void Board::move(char token, int die_no)
{
    // function which changes the position of the token given to it by the given die_no
    int i = getplayerindex(token);
    int j = gettokenindex(token);
    int position = players[i].tokens[j].Get_position();
    int path = players[i].tokens[j].Get_path();
    int turn_position = 2 + i * 13;
    if (path == 1)
    {
        for (int k = 0; k < 6; k++)
        {
            if ((position + k) % 52 == turn_position && die_no > k)
            {
                if (die_no - k == 6)
                {
                    players[i].tokens[j].Set_path(3);
                    reachedHome = 1;
                    return;
                }
                players[i].tokens[j].Set_path(2);
                players[i].tokens[j].Set_position(die_no - k - 1);
                return;
            }
        }

        string str = paths[(position + die_no) % 52];
        if ((str.compare("    ") == 0 || getplayerindex(str[0]) == i) || (str[3] == ' ' && ((position + die_no) % 52 == 51 || (position + die_no) % 52 == 12 || (position + die_no) % 52 == 25 || (position + die_no) % 52 == 38)))
        {
            players[i].tokens[j].Set_position((position + die_no) % 52);
        }
        else
        {
            killed = 1;
            players[i].tokens[j].Set_position((position + die_no) % 52);
            players[getplayerindex(str[0])].tokens[gettokenindex(str[0])].Set_path(0);
            cout << "!!! " << token << " killed " << str[0] << endl;
            Sleep(1500);
        }
        return;
    }
    else if (path == 2)
    {

        players[i].tokens[j].Set_position((position + die_no));
        if (position + die_no == 5)
        {
            players[i].tokens[j].Set_path(3);
            reachedHome = 1;
            cout << "!!!" << token << " reached Home\n";
            Sleep(1500);
            return;
        }
    }
    else
        cout << "Invalid Move\n";
    return;
}
void Board::Make_throw(int player_no)
{
    srand(time(0)); // For generating actual random numbers
    int roll;
    // stores the number of the die
    char temp, choice, token1, token2, token3, token4;
    token1 = players[player_no - 1].tokens[0].Get_Symbol();
    token2 = players[player_no - 1].tokens[1].Get_Symbol();
    token3 = players[player_no - 1].tokens[2].Get_Symbol();
    token4 = players[player_no - 1].tokens[3].Get_Symbol();
    int continous_sixes = 0;
    while (true)
    {
        cout << "  Enter any key to roll die\r";
        getch();
        roll = ((rand() % 6) + 1);
        cout << "The number you got is --- " << roll << "      \n";
        if (roll == 6)
        {
            continous_sixes++;
            if (continous_sixes == 3)
            {
                cout << "You got three continous sixes, Your turn will be ended\n";
                Sleep(2000);
                return;
            }
            int number_of_unlocked = 0;
            for (int i = 0; i < 4; i++)
            {
                if (players[player_no - 1].tokens[i].IsUnlocked())
                    number_of_unlocked++;
            }
            int number_of_movable = 0;
            for (int i = 0; i < 4; i++)
            {
                if (can_be_movable(roll, players[player_no - 1].tokens[i].Get_Symbol()))
                    number_of_movable++;
            }
            if (number_of_unlocked == 0)
            {
                cout << "Enter token to unlock\n";
                cin >> choice;
                while ((!(choice == token1 || choice == token2 || choice == token3 || choice == token4)) || players[player_no - 1].tokens[gettokenindex(choice)].IsFinished())
                {
                    if ((getplayerindex(choice) == player_no - 1) && players[player_no - 1].tokens[gettokenindex(choice)].IsFinished())
                    {
                        cout << "Token " << choice << " already reached the Home!!\n";
                    }
                    cout << "!! Invalid token entry, Enter a valid Token\n";
                    cin >> choice;
                }
                unlock(choice);
            }
            else if (number_of_unlocked == 4)
            {
                if (number_of_movable == 0)
                {
                    cout << "You don't have any valid move\n";
                    Sleep(2500);
                    return;
                }
                if (number_of_movable == 1)
                {
                    if (can_be_movable(roll, token1))
                        move(token1, roll);
                    else if (can_be_movable(roll, token2))
                        move(token2, roll);
                    else if (can_be_movable(roll, token3))
                        move(token3, roll);
                    else if (can_be_movable(roll, token4))
                        move(token4, roll);
                }
                else
                {
                    cout << "Enter the token you wan't to move\n";
                    cin >> choice;
                    while (!(choice == token1 || choice == token2 || choice == token3 || choice == token4) || !can_be_movable(roll, choice))
                    {
                        cout << "!! Invalid token entry, Enter a valid Token\n";
                        cin >> choice;
                    }
                    move(choice, roll);
                }
            }
            else
            {
                if (number_of_movable == 0)
                {
                    cout << "Enter token to unlock\n";
                    cin >> choice;
                    while (!(choice == token1 || choice == token2 || choice == token3 || choice == token4) || players[player_no - 1].tokens[gettokenindex(choice)].IsUnlocked() || players[player_no - 1].tokens[gettokenindex(choice)].IsFinished())
                    {
                        cout << "!! Invalid token entry, Enter a valid Token\n";
                        cin >> choice;
                        if ((choice == token1 || choice == token2 || choice == token3 || choice == token4) && players[player_no - 1].tokens[gettokenindex(choice)].IsFinished())
                        {
                            cout << choice << " already finished game, can't be unlocked\n";
                            continue;
                        }
                        if ((choice == token1 || choice == token2 || choice == token3 || choice == token4) && players[player_no - 1].tokens[gettokenindex(choice)].IsUnlocked())
                        {
                            cout << choice << " is already unlocked\n";
                            continue;
                        }
                    }
                    unlock(choice);
                }
                else
                {
                    cout << "Enter Y to unlock or any other key to move\n";
                    cin >> temp;
                    if (temp == 'Y')
                    {
                        cout << "Enter token to unlock\n";
                        cin >> choice;
                        while (!(choice == token1 || choice == token2 || choice == token3 || choice == token4) || players[player_no - 1].tokens[gettokenindex(choice)].IsUnlocked() || players[player_no - 1].tokens[gettokenindex(choice)].IsFinished())
                        {
                            cout << "!! Invalid token entry, Enter a valid Token\n";
                            cin >> choice;
                            if ((choice == token1 || choice == token2 || choice == token3 || choice == token4) && players[player_no - 1].tokens[gettokenindex(choice)].IsFinished())
                            {
                                cout << choice << " already finished game, can't be unlocked\n";
                                continue;
                            }
                            if ((choice == token1 || choice == token2 || choice == token3 || choice == token4) && players[player_no - 1].tokens[gettokenindex(choice)].IsUnlocked())
                            {
                                cout << choice << " is already unlocked\n";
                                continue;
                            }
                        }
                        unlock(choice);
                    }
                    else
                    {
                        if (number_of_movable == 1)
                        {
                            if (can_be_movable(roll, token1))
                                move(token1, roll);
                            else if (can_be_movable(roll, token2))
                                move(token2, roll);
                            else if (can_be_movable(roll, token3))
                                move(token3, roll);
                            else if (can_be_movable(roll, token4))
                                move(token4, roll);
                        }
                        else
                        {
                            cout << "Enter the token you wan't to move\n";
                            cin >> choice;
                            while (!(choice == token1 || choice == token2 || choice == token3 || choice == token4) || !can_be_movable(roll, choice))
                            {
                                cout << "!! Invalid token entry, Enter a valid Token\n";
                                cin >> choice;
                            }
                            move(choice, roll);
                        }
                    }
                }
            }
            system("CLS");
            Display_Board();
            if (players[player_no - 1].IsWon())
            {
                cout << "-----**** player " << player_no << " completed the game\n";
                WinnerQueue.push(player_no);
                return;
            }
            cout << "player " << player_no << " got a bonus throw\n";
            continue;
        }
        else
        {
            continous_sixes--;
            killed = 0;
            reachedHome = 0;
            int number_of_movable = 0;
            for (int i = 0; i < 4; i++)
            {
                if (can_be_movable(roll, players[player_no - 1].tokens[i].Get_Symbol()))
                    number_of_movable++;
            }
            if (number_of_movable == 0)
            {
                cout << "You don't have a valid move\n";
                Sleep(2000);
                return;
            }
            if (number_of_movable == 1)
            {
                if (can_be_movable(roll, token1))
                    move(token1, roll);
                else if (can_be_movable(roll, token2))
                    move(token2, roll);
                else if (can_be_movable(roll, token3))
                    move(token3, roll);
                else if (can_be_movable(roll, token4))
                    move(token4, roll);
            }
            else
            {
                cout << "Enter the token you wan't to move\n";
                cin >> choice;
                while (!(choice == token1 || choice == token2 || choice == token3 || choice == token4) || !can_be_movable(roll, choice))
                {
                    cout << "!! Invalid token entry, Enter a valid Token\n";
                    cin >> choice;
                }
                move(choice, roll);
            }
        }
        if (players[player_no - 1].IsWon())
        {
            cout << "-----**** player " << player_no << " completed the game\n";
            WinnerQueue.push(player_no);
            return;
        }
        if (killed == 1 || reachedHome == 1)
        {
            system("CLS");
            Display_Board();
            cout << "!!! player " << player_no << " got a bonus throw\n";
            continue;
        }
        else
        {
            break;
        }
    }
    if (players[player_no - 1].IsWon())
    {
        cout << "-----**** player " << player_no << " completed the game\n";
        WinnerQueue.push(player_no);
        Sleep(1000);
        return;
    }
    Sleep(2000);
}
void Board::Set_Board()
{
    /*
        This function arranges the tokens in their respective positions in the board
        */
    for (int i = 0; i < 52; i++)
    {
        paths[i] = "    ";
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            winpaths[i][j] = "    ";
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Home[i][j] = ' ';
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            WON[i][j] = ' ';
        }
    }
    for (int i = 0; i < number_of_players; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int position = players[i].tokens[j].Get_position();
            int path = players[i].tokens[j].Get_path();
            char symbol = players[i].tokens[j].Get_Symbol();
            if (path == 0)
            {
                Home[i][j] = players[i].tokens[j].Get_Symbol();
            }
            else if (path == 1)
            {
                if (paths[position].compare("    ") == 0)
                {
                    paths[position] = "";
                    paths[position].push_back(players[i].tokens[j].Get_Symbol());
                    paths[position] += "   ";
                }
                else if ((paths[position])[0] != ' ' && (paths[position])[1] == ' ' && (paths[position])[2] == ' ' && (paths[position])[3] == ' ')
                {
                    char x = (paths[position])[0];
                    paths[position] = "";
                    paths[position] += x;
                    paths[position].push_back(players[i].tokens[j].Get_Symbol());
                    paths[position] += "  ";
                }
                else if ((paths[position])[0] != ' ' && (paths[position])[1] != ' ' && (paths[position])[2] == ' ' && (paths[position])[3] == ' ')
                {
                    char x = (paths[position])[0];
                    char y = (paths[position])[1];
                    paths[position] = "";
                    paths[position] += x;
                    paths[position] += y;
                    paths[position].push_back(players[i].tokens[j].Get_Symbol());
                    paths[position] += " ";
                }
                else if ((paths[position])[0] != ' ' && (paths[position])[1] != ' ' && (paths[position])[2] != ' ' && (paths[position])[3] == ' ')
                {
                    char x = (paths[position])[0];
                    char y = (paths[position])[1];
                    char z = (paths[position])[2];
                    paths[position] = "";
                    paths[position] += x;
                    paths[position] += y;
                    paths[position] += z;
                    paths[position].push_back(players[i].tokens[j].Get_Symbol());
                    paths[position] += "";
                }
            }
            else if (path == 2)
            {
                if (winpaths[i][position].compare("    ") == 0)
                {
                    winpaths[i][position] = "";
                    winpaths[i][position].push_back(players[i].tokens[j].Get_Symbol());
                    winpaths[i][position] += "   ";
                }
                else if ((winpaths[i][position])[0] != ' ' && (winpaths[i][position])[1] == ' ' && (winpaths[i][position])[2] == ' ' && (winpaths[i][position])[3] == ' ')
                {
                    char x = (winpaths[i][position])[0];
                    winpaths[i][position] = "";
                    winpaths[i][position] += x;
                    winpaths[i][position].push_back(players[i].tokens[j].Get_Symbol());
                    winpaths[i][position] += "  ";
                }
                else if ((paths[position])[0] != ' ' && (paths[position])[1] != ' ' && (paths[position])[2] == ' ' && (paths[position])[3] == ' ')
                {
                    char x = (winpaths[i][position])[0];
                    char y = (winpaths[i][position])[1];
                    winpaths[i][position] = "";
                    winpaths[i][position] += x;
                    winpaths[i][position] += y;
                    winpaths[i][position].push_back(players[i].tokens[j].Get_Symbol());
                    winpaths[i][position] += " ";
                }
                else if ((winpaths[i][position])[0] != ' ' && (winpaths[i][position])[1] != ' ' && (winpaths[i][position])[2] != ' ' && (winpaths[i][position])[3] == ' ')
                {
                    char x = (winpaths[i][position])[0];
                    char y = (winpaths[i][position])[1];
                    char z = (winpaths[i][position])[2];
                    winpaths[i][position] = "";
                    winpaths[i][position] += x;
                    winpaths[i][position] += y;
                    winpaths[i][position] += z;
                    winpaths[i][position].push_back(players[i].tokens[j].Get_Symbol());
                    winpaths[i][position] += "";
                }
            }
            else if (path == 3)
            {
                WON[i][j] = players[i].tokens[j].Get_Symbol();
            }
        }
    }
}
void Board::Display_Board()
{
    // A function to display the board to the user
    // First it calls the Set_Board function  and then displays
    Set_Board();
    cout << " ___________________________________________________________________________\n";
    cout << "|                             |" << paths[1] << "|" << paths[2] << "|" << paths[3] << "|                             |\n";
    cout << "|                             |----|----|----|                             |\n";
    cout << "|         ___________         |" << paths[0] << "|" << winpaths[0][0] << "|" << paths[4] << "|<---     ___________         |\n";
    cout << "|        |     |     |        |****|----|----|        |     |     |        |\n";
    cout << "|        |  " << Home[3][0] << "  |  " << Home[3][1] << "  |        |" << paths[51] << "|" << winpaths[0][1] << "|" << paths[5] << "|        |  " << Home[0][0] << "  |  " << Home[0][1] << "  |        |\n";
    cout << "|        |-----|-----|        |****|----|----|        |-----|-----|        |\n";
    cout << "|        |  " << Home[3][2] << "  |  " << Home[3][3] << "  |        |" << paths[50] << "|" << winpaths[0][2] << "|" << paths[6] << "|        |  " << Home[0][2] << "  |  " << Home[0][3] << "  |        |\n";
    cout << "|        |_____|_____|        |----|----|----|        |_____|_____|        |\n";
    cout << "|                             |" << paths[49] << "|" << winpaths[0][3] << "|" << paths[7] << "|                             |\n";
    cout << "|       |    PLAYER 4         |----|----|----|         PLAYER 1            |\n";
    cout << "|       |                     |" << paths[48] << "|" << winpaths[0][4] << "|" << paths[8] << "|                             |\n";
    cout << "|_______V_____________________|____|____|____|_______________****__________|\n";
    cout << "|" << paths[42] << "|" << paths[43] << "|" << paths[44] << "|" << paths[45] << "|" << paths[46] << "|" << paths[47] << "|   " << WON[0][0] << " " << WON[0][1] << " " << WON[0][2] << " " << WON[0][3] << "    |" << paths[9] << "|" << paths[10] << "|" << paths[11] << "|" << paths[12] << "|" << paths[13] << "|" << paths[14] << "|\n";
    cout << "|----|----|----|----|----|----|" << WON[3][0] << "   ______   " << WON[1][0] << "|----|----|----|****|----|----|\n";
    cout << "|" << paths[41] << "|" << winpaths[3][0] << "|" << winpaths[3][1] << "|" << winpaths[3][2] << "|" << winpaths[3][3] << "|" << winpaths[3][4] << "|" << WON[3][1] << "  | HOME |  " << WON[1][1] << "|" << winpaths[1][4] << "|" << winpaths[1][3] << "|" << winpaths[1][2] << "|" << winpaths[1][1] << "|" << winpaths[1][0] << "|" << paths[15] << "|\n";
    cout << "|----|----|****|----|----|----|" << WON[3][2] << "  |______|  " << WON[1][2] << "|----|----|----|----|----|----|\n";
    cout << "|" << paths[40] << "|" << paths[39] << "|" << paths[38] << "|" << paths[37] << "|" << paths[36] << "|" << paths[35] << "|" << WON[3][3] << "  " << WON[2][0] << " " << WON[2][1] << " " << WON[2][2] << " " << WON[2][3] << "   " << WON[1][3] << "|" << paths[21] << "|" << paths[20] << "|" << paths[19] << "|" << paths[18] << "|" << paths[17] << "|" << paths[16] << "|\n";
    cout << "|----|----|****|----|----|----|--------------|----|----|----|----|--^-|----|\n";
    cout << "|                             |" << paths[34] << "|" << winpaths[2][4] << "|" << paths[22] << "|                      |      |\n";
    cout << "|                             |----|----|----|                      |      |\n";
    cout << "|         ___________         |" << paths[33] << "|" << winpaths[2][3] << "|" << paths[23] << "|         ___________         |\n";
    cout << "|        |     |     |        |----|----|----|        |     |     |        |\n";
    cout << "|        |  " << Home[2][0] << "  |  " << Home[2][1] << "  |        |" << paths[32] << "|" << winpaths[2][2] << "|" << paths[24] << "|        |  " << Home[1][0] << "  |  " << Home[1][1] << "  |        |\n";
    cout << "|        |-----|-----|        |----|----|****|        |-----|-----|        |\n";
    cout << "|        |  " << Home[2][2] << "  |  " << Home[2][3] << "  |        |" << paths[31] << "|" << winpaths[2][1] << "|" << paths[25] << "|        |  " << Home[1][3] << "  |  " << Home[1][2] << "  |        |\n";
    cout << "|        |_____|_____|        |----|----|****|        |_____|_____|        |\n";
    cout << "|                         --->|" << paths[30] << "|" << winpaths[2][0] << "|" << paths[26] << "|                             |\n";
    cout << "|          PLAYER 3           |----|----|----|         PLAYER 2            |\n";
    cout << "|                             |" << paths[29] << "|" << paths[28] << "|" << paths[27] << "|                             |\n";
    cout << " --------------------------------------------------------------------------\n\n";
}
bool Board::IsWon(int player_no)
{
    // return true if the player finished the game
    return players[player_no - 1].IsWon();
}
bool Board::IsGameCompleted()
{
    // returns true if all the players finished the game
    for (int i = 0; i < number_of_players; i++)
    {
        if (!players[i].IsWon())
            return false;
    }
    return true;
}
void Board::Show_Instructions()
{
    // function which shows instructions to the user
    cout << "\n\n";
    Sleep(1000);
    cout << "\t-------------  WELCOME TO LUDO    ----------------\n";
    Sleep(1000);
    cout << " \t----------------****************-----------------\n";
    Sleep(1000);
    cout << "\t-----------------****************------------------\n";
    Sleep(1000);
    cout << "\t----------------------------------------------\n";
    cout << "\t------ Instructions for this game------\n";
    cout << "\t----------------------------------------------\n";
    Sleep(2000);
    cout << "\t1)The game can be played by  two ,three or four players\n\tYou have to choose number of players\n ";
    cout << "\t2)The players are numbered as player 1,player 2, player 3 and player 4\n";
    cout << "\t3)Each player has four tokens with the symbols given below\n";
    cout << "\t\t--- player 1 has tokens labelled with capital letters A,B,C,D\n";
    cout << "\t\t--- player 2 has tokens labelled with samll letters a,b,c,d\n";
    cout << "\t\t--- player 3 has tokens labelled with digits letters 1,2,3,4\n";
    cout << "\t\t--- player 4 has tokens labelled with special characters @,#,$,%\n";
    cout << "\t4)The player 1 starts the Game\n";
    cout << "\t5)Each player gets the turns one by one\n";
    cout << "\t6)A player has to enter any key(single key) as instructed to roll the dice and 6 is needed to unlock a token\n";
    cout << "\t7)Player will be asked to choose a move if there are more than one valid moves are possible\n";
    cout << "\t8)A player has to complete a whole circle clockwise to enter into the winning paths\n";
    cout << "\t9)There are four starting squares for each player and four safety squares\n";
    cout << "\t10)For every starting square of each player, other players can't enter into it\n";
    cout << "\t11)Any square can contain only a maximum of 4 tokens in it\n";
    cout << "\t12)If a single token of one player is landed upon by another player's token, then it will be \n\t\treturned to starting unlocked position, and the player who landed will get aditional throw\n ";
    cout << "\t13)Getting a six will also gives an extra throw\n";
    cout << "\t14)If there are more than one tokens of same player in a square, then other players can enter it only if it is a safety square\n";
    cout << "\t15)A player who is first to move all his tokens into HOME wins \n";
    cout << "\t16)The game ends after all players finished the game\n";
    Sleep(3000);
    cout << "\t----------------------Enter any key to start the game-------\n";
}
void Board::Show_Result()
{
    // Function which shows the final results to the user
    // By collecting information from winner queue it decides the winning positions of players and displays
    system("CLS");
    cout << "\n\t--------------*********************-------------\n";
    cout << "\n\t\tThe GAME is Completed\n";
    Sleep(1000);
    for (int i = 0; i < number_of_players - 1; i++)
    {
        cout << "The " << i + 1 << "the winner is " << WinnerQueue.front() << endl;
        WinnerQueue.pop();
        Sleep(1000);
    }
    Sleep(1000);
    cout << "The looser is " << WinnerQueue.front();
    WinnerQueue.pop();
    Sleep(1000);
    cout << "\n\t--------------------------------------------------\n";
    cout << "\n\t----------------Thank you for playing-------------\n";
    cout << "\n\t--------------------------------------------------\n";
}

