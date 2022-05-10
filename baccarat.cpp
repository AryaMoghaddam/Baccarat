// clang++ -std=c++17 -o  baccarat team09-baccarat.cpp
//./baccarat
 
#include <iostream>
#include <ctime>
#include <string>
#include <stdio.h>
#include <limits>
#include <thread>
#include <chrono>
using namespace std;
using namespace this_thread;
 
//function prototype
void printCard1(int num1,int num2, int num3, int sum); //prints out the card value and the sum of the cards
void printCard2(int num1,int num2, int sum, string NaturalW); //prints out the card value and the sum of the cards
void printCard3(int num1,int num2, int sum);
bool playAgain(char x,int money); //makes a boolean check to determine whether or not the player wants to continue
int winnerFunction(int bankerCard, int playerCard); //compares two cards
int declareWinner(int winner, int decision, int bet); //a function to declare the winner of the bet, and the amount of money lost or gained
 
//getting all the different colours that we use for print statements
struct CardNumber //structure type for card number and its sum
{
    int num1, num2, sum, extraCard;
};
 
void yellow()
{
    cout << "\033[0;33m" <<endl;
}
 
void green()
{
    cout << "\033[0;92m" << endl;
}
 
void cyan()
{
    cout << "\033[0;36m" << endl;
}
 
void purple()
{
    cout << "\033[0;35m" << endl;
}
 
void red()
{
    cout << "\033[1;31m";
}
 
void reset()
{
  cout << "\033[0m" << endl;
}
 
int main()
{
    //variable decleration
    string name;
    int bet, decision, winner, prize;
    char play;
    bool logic = true;
    int money = 10000;
 
    //getting player's name
    cout << "Please enter your name ";
    getline( cin, name);
    sleep_for(1s);
    cyan();
    cout << "\n_________________________________________________________________________" << endl;
    purple();
    cout << "                ___          ___     ___              ___    _____    ___    " << endl;
    cout << "  |         |  |     |      |   |   |   |   |     |  |         |     |   |   " << endl;
    cout << "   |   |   |   |___  |     |       |     |  ||   ||  |___      |    |     |  " << endl;
    cout << "    | | | |    |     |     |       |     |  | | | |  |         |    |     |  " << endl;
    cout << "     |   |     |___  |___   |___|   |___|   |  |  |  |___      |     |___|   " << endl;
    cout << "                           ___   _____             _                         " << endl;
    cout << "              |     |  |  |   |    |    |     |   | |    |                   " << endl;
    cout << "               |   |   |  |___|    |    |     |  |___|   |                   " << endl;
    cout << "                | |    |  | |      |    |     |  |   |   |                   " << endl;
    cout << "                 |     |  |   |    |     |___|   |   |   |____               " << endl;
    cout << "                                                                             " << endl;
    cout << "  ██████      ██      ████      ████      ██    ██████      ██    █████████  " << endl;
    cout << "  ██    ██  ██  ██  ██    ██  ██    ██  ██  ██  ██    ██  ██  ██      ██     " << endl;
    cout << "  ██████    ██████  ██        ██        ██████  ██████    ██████      ██     " << endl;
    cout << "  ██    ██  ██  ██  ██    ██  ██    ██  ██  ██  ██  ██    ██  ██      ██     " << endl;
    cout << "  ███████   ██  ██    ████      ████    ██  ██  ██    ██  ██  ██      ██     " << endl;
    cout << "        " << endl;
    cout << "        " << endl;
    cout << "                       Your starting balance is $10 000                      " << endl;
    cyan();
    cout << "_________________________________________________________________________" << endl;
    reset();
    sleep_for(2s);
    green();
    //printing all of the rules of the game
    cout<<"                                   RULES                                    "<<endl;
    sleep_for(0.1s);
    cout<<" -There are 2 players that are playing the game, the player and the banker    "<<endl;
    sleep_for(0.1s);
    cout<<" -You get to bet on whoever you think is going to win the rounds"<<endl;
    sleep_for(0.1s);
    cout<<" -The player and banker are both dealt 2 random cards "<<endl;
    sleep_for(0.1s);
    cout<<" -The sum of these cards is calculated for each player "<<endl;
    sleep_for(0.1s);
    cout<<" -If the sum is greater than 9, the first digit is dropped (ex. 15 --> 5)  "<<endl;
    sleep_for(0.1s);
    cout<<" -If the sum is a 5 or below then that player is dealt an extra card and the sum is recalculated     "<<endl;
    sleep_for(0.1s);
    cout<<" -If the sum is a 6 or a 7 then that player must stand with those 2 cards     "<<endl;
    sleep_for(0.1s);
    cout<<"     -The other player is still able to pick up an extra card if their sum is 5 or below "<<endl;
    sleep_for(0.1s);
    cout<<" -If the sum is an 8 or a 9, this is known as a natural win "<<endl;
    sleep_for(0.1s);
    cout<<"     -When one player gets a natural win, no other player is dealt an extra card, even if their sum is a 5 or below   "<<endl;
    sleep_for(0.1s);
    cout<<" -If you bet on the player that wins then you are rewarded with twice the money that you bet                    "<<endl;
    sleep_for(0.1s);
    cout<<" -If you bet on the player that loses then you lose the amount of money that you chose to bet "<<endl;
    sleep_for(0.1s);
    cout<<" -If there is a tie between the players then you get your money back                    "<<endl;
    sleep_for(0.1s);
    cout<<"     "<<endl;
    cout<<" WIN AS MUCH MONEY AS YOU CAN!     "<<endl;
    cout<<" GOOD LUCK!     "<<endl;
    cout << "_________________________________________________________________________" << endl;
    sleep_for(3s);
    reset();
 
    do
    {
        //Shows that player their starting balance
        cout << "Current balance: $ " << money << endl;
        sleep_for(0.1s);
        //promptig the user to either bet on the player or the banker
        cout << "\nChoose your bet \n 1-Banker \n 2-Player \n";
        cin >> decision;
       
        // //Checks if the user inputed a 1 or 2
        while(cin.fail())
        {
          cout << "chose either 1 or 2" << endl;
          cin.clear();
          cin.ignore(256, '\n');
          cin >> decision;
        }
       
        //if the user didn't put in a valid input, promt them again
        while(decision != 1 && decision != 2)
        {
            cout << "please enter either a 1 or 2\n";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> decision;
        }
 
        if(decision == 1 || decision == 2)
        {
            cout << "you are betting on " << decision << endl;
        }
           
        do
        {
        //Checking if the bet is below balance money
         cout << "How much money would you like to bet?";
         cin >> bet ;
        }while (bet > money);
 
        //Banker Cards
        red();
        cout << "\n____________________\n";
        cout << "                   " << endl;
        cout << "   Banker's Cards " << endl;
        cout << "____________________\n";
        cout << "        \n";
        reset();
 
        //Random Card Generator
        struct CardNumber banker;
        banker.num1 = rand() % 10 + 1;
        banker.num2 = rand() % 10 + 1;
        banker.sum = banker.num1 + banker.num2;
        banker.sum = banker.sum % 10;
        string NaturalW = "This is a natural Win!";
 
        //draw anohter card if the sum is less than 6
        if(banker.sum < 6)
        {
            //Third Extra Card Drawn
            banker.extraCard = rand() % 10 +1;
            banker.sum += banker.extraCard;
            //getting the remainder of the third card's sum
            banker.sum = banker.sum % 10;
            printCard1(banker.num1, banker.num2, banker.extraCard, banker.sum);
        }
 
        else if (banker.sum > 7)
        {
            //Natural win 8 or win 9 and printing the cards
            printCard2(banker.num1,banker.num2,banker.sum, NaturalW);
        }
 
        else
        {
            //Check to see if sum is a 6 or a 7
           
            printCard3(banker.num1,banker.num2, banker.sum);
        }
        cyan();
        //Player's Card
        cout << "\n____________________\n";
        cout << "                  " << endl;
        cout << "   Player's Cards   " << endl;
        cout << "____________________\n";
        cout << "        \n";
        reset();
        //Random number generator for 2 cards
        struct CardNumber player;
        player.num1 = rand() % 10 + 1 ;
        player.num2 = rand() % 10 + 1;
        player.sum = player.num1 + player.num2;
        player.sum = player.sum % 10;
       
        //draw another card if the sum is less than 6
        if(player.sum < 6)
        {
 
            //Third Extra Card Drawn
            player.extraCard = rand() % 10 +1;
            player.sum += player.extraCard;
            //getting the remainder of the third card's sum
            player.sum = player.sum % 10;
            printCard1(player.num1, player.num2, player.extraCard, player.sum);
       
        }    
        //if the sum is 6 or 7 then they have to stand and don't recieve another card
        else if (player.sum > 7)
        {
            //Natural win 8 or win 9 and printing the cards
           
            printCard2(player.num1,player.num2,player.sum, NaturalW);
        }
       
        else //(player.sum < 8 && player.sum > 5)
        {
            //Check to see if sum is a 6 or a 7
           
            printCard3(player.num1,player.num2,player.sum);
        }
 
        //Declaring the winner by checking who has the higher sum
        winner = winnerFunction(banker.sum , player.sum);
 
        //awards prize for winner, increases their money by their bet value
        prize = declareWinner(winner, decision, bet);
        cout<< "$" << prize << "!\n" << endl;
        money += prize;
        cout << "____________________\n";
        cout << "\nCurrent Balance: $" << money << "\n\n";
 
        //Asking the user if they want to play again
        cout << "PLAY AGAIN? Y/N ";
        cin >> play;
        logic = playAgain(play, money);
   
    }while(logic != false);    
}
 
//run the function that will print all of the cards
void printCard1(int num1, int num2, int num3, int sum)
{
    cout << "  First Card " << num1 << "\n";
    sleep_for(1s);
    cout << "  Second Card " << num2 << "\n";
    sleep_for(1s);
    cout << "  Extra Card " << num3 << "\n";
    sleep_for(1s);
    cout << "Sum is: " << "\n";
 
    yellow();
    cout << "=======\n";
    cout << "|     |\n";
    cout << "|  " << sum  << "  |\n";
    cout << "|     |\n";
    cout << "=======\n";
    reset();
}
 
//runs the function for when either player's sum is a 8 or 9
void printCard2(int num1,int num2, int sum, string NaturalW)
{
    cout << "  First Card " << num1 << "\n";
    sleep_for(1s);
    cout << "  Second Card " << num2 << "\n" << endl;
    sleep_for(1s);
    cout << NaturalW << "\n";
    sleep_for(1s);
    cout << "Sum is: " << "\n";
 
    yellow();
    cout << "=======\n";
    cout << "|     |\n";
    cout << "|  " << sum  << "  |\n";
    cout << "|     |\n";
    cout << "=======\n";
    reset();
 
}
//runs function for when either players sum is a 6 or a 7
void printCard3(int num1,int num2, int sum)
{
    cout << "  First Card " << num1 << "\n";
    sleep_for(1s);
    cout << "  Second Card " << num2 << "\n" << endl;
    sleep_for(1s);
    cout << "Sum is: " << "\n";
 
    yellow();
    cout << "=======\n";
    cout << "|     |\n";
    cout << "|  " << sum  << "  |\n";
    cout << "|     |\n";
    cout << "=======\n";
    reset();
}
 
//a boolean check functiion to see what option the user choses
//if they chose to play again, and have a sufficient amount of money, run the code to start the game
//if they do not have enough funds to play, then break
bool playAgain(char x , int money)
{
 
    if (money > 0)
    {
 
        if (x == 'Y' || x == 'y')
        {
            return true;
        }
        else if(x == 'N' || x == 'n')
        {
            cout << "THANK YOU FOR PLAYING!" << endl;
            return false;
        }
    }
 
    else
    {
        cout << "Insufficient Funds!\n";
        return false;
    }return 0;
}
 
//Function to determine nearest number to 9
//returns 1,2,3 depending on condition met
int winnerFunction(int bankerCard, int playerCard)
{  
    if (bankerCard > playerCard)
    {
        cout << "\nBanker wins the hand! ";
        return 1;
    }
    else if(bankerCard < playerCard)
    {
        cout<< "\nPlayer wins the hand! ";
        return 2;
    }
    else if(bankerCard == playerCard)
    {
 
        cout << "\n DRAW, ";
        return 3;
    }return 0 ;
 
}
 
//tells the user the outcome of the bet
int declareWinner(int winner, int decision, int bet)
{
    if (winner == decision )
    {
        // win pays the bet
        cout << "You win ";
        return bet;    
    }
    if (winner == 3)
    {
        //draw
        cout << "Tie!" << endl;
        return 0 ;
    }
    else
    {
        cout << "You lose ";
        bet *= -1;
        return bet;
    }
}
