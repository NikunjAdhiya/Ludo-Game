#include"Board.h"
#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;
int main()
{
    system("COLOR 0A");
    // A command which changes the terminal color to green to enchance the appearance
    Board B;
    getch();
    system("CLS");
    cout << "Enter the number of players\n";
    int n;
    cin >> n;
    // taking number of players from the user
    while (!(n > 1 && n < 5))
    {
        cout << "No of players can be only 2 to 4, Enter correct number\n";
        cin >> n;
    }
    B.Set_No_Of_Players(n);
    system("CLS");
    B.Display_Board();
    queue<int> Turn_queue;
    // A queue used to give the turns to the players
    for (int i = 1; i <= n; i++)
        Turn_queue.push(i);
    while (true)
    {
        int i = Turn_queue.front();
        Turn_queue.pop();
        if (B.IsWon(i))
            continue;
        cout << "Player " << i << "'s turn\n";
        B.Make_throw(i);
        system("CLS");
        B.Display_Board();
        if (B.IsGameCompleted()) // exits the loop if game is completed
            break;
        Turn_queue.push(i);
    }
    B.Show_Result();
    // Shows the result to the user after completing the game
    return 0;
}
