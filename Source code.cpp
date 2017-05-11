/*
 Author	 : Tamara - Sample Solutions
 Student # : 000376553
 Re-edited by : Daniel Lee
 Group members: Nick Crema, Kelsey Fortin
 Compiler Version: Code::Blocks 12.11 on Windows 8.1
 ---------------------------------------------------------------------------------------------------
 Last Update On: Nov 22, 2015
----------------------------------------------------------------------------------------------------
 Program Description: This program is designed for the rules of Tic Tak Toc game play.
                      There are two players in each game. The user and computer.
                      The user displays O and computer displays X in the gameboard.
                      A new game will be set as long as the user says Yes to play the next game.
                      The computer is set to be lost or won or drawn.
                      Error handling is included for the user's selection of a slot betwen 0 and 8
----------------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <cmath>
#include <string>
// included for compilation on windows 7 with Code::Blocks 13.12
#include <climits>
#include <limits>

using namespace std;

const int BOARD_SIZE = 9;

/* Constants for TTT game board symbols. */
const char EMPTY = ' ';
const char USER = 'O';
const char COMPUTER = 'X';


/* function proto-types (these are function declarations).
   Value returning functions tested by the automated driver.
*/
bool value_in_range(int value, int min, int max);
bool row_is_winner(char s1, char s2, char s3);
char TTT_opponent(char player);

/* I/O functions -- manually tested. */
int  get_int_input(int min, int max);
void display_horizontal_line();
void display_one_row(char s1, char s2, char s3);

/* Utility functions used by the automated test driver:
   int user_says_yes(string question);
*/
void report(int, bool, string);
void display_TTT_boards();
int user_says_yes(string);
char get_char_input();

void initialize_board(char[]);
void display_board(char[]);
int find_first_empty_slot (char[]);
bool slots_all_taken(char[],int);
bool winning_rows(char[]);


int main()
{
	/* Test oracle:  this portion will run some automated tests and report the results. */
	/* Automated tests for value_in_range() */

    char board[BOARD_SIZE];
    int slot;

do{

    initialize_board(board);
    display_board(board);
    cout << endl;

    while (slots_all_taken(board,BOARD_SIZE)==false && winning_rows(board) == false)
    {
        cout << "Please enter your move(0 - 8): ";
        slot = get_int_input(0, BOARD_SIZE-1); // get_int_input checks for input validity

/* USER CONTROL */
        if (board[slot] == EMPTY)
        {
            board[slot] = USER;
            display_board(board);
            cout<<endl;

/*User finished a move, and check if that moves make the user win the game*/
                if ( winning_rows(board) == true && board[slot] == USER)
                {
                    cout<<"You won!"<<endl;
                    cout<<endl;
                }

/* COMPUTER CONTROL */
/* If the user's last move doesn't make a winning row, then computer takes the next turn*/
                else
                {
                    slot = find_first_empty_slot(board);
                    board[slot] = COMPUTER;
                    display_board(board);
                    cout<<endl;

/* If computer makes a winning row, then display that computer won */
                    if (winning_rows(board) == true && board[slot] == COMPUTER)
                    {
                        cout<<"Computer won!"<<endl;
                    }

                    cout<<"Your opponent has finished a move."<<endl;
                    cout<<endl;
                }
        }//closure for if (board[slot]==EMPTY)

        else //The selected slot is already taken/occupied
        {
            cout<<"That's a bad move!"<<endl;
            cout<<endl;
        }
    } // all slots are taken

/*When all slots are taken, and none of the players wins a row, then display draw*/
    if (winning_rows(board)== false && slots_all_taken(board,BOARD_SIZE)==true)
    {
        cout<<"Draw!"<<endl; // try 1-6-4-5-8
        cout<<endl;
    }

/*keep looping as long as the user says yes*/

} while (user_says_yes("Do you want to continue?") == true);


    return 0;


/*****************************************************
*****************************************************
****  Test driver / Test oracle for functions *******
****	DO NOT CHANGE THE CODE IN THE MAIN FUNCTION!!!**
*****************************************************
*****************************************************/

    char temp;

	cout << endl << "Running test oracle for value_in_range() function..." << endl;
	cout << "These test cases should return true..." << endl;
	report(1,   value_in_range(5,1,10),		"value_in_range(5,1,10)");
	report(2,   value_in_range(1,1,1),		"value_in_range(1,1,1)");
	cout << "These test cases should return false..." << endl;
	report(3, !value_in_range(-1,1,10),		"value_in_range(-1,1,10)");
	report(4, !value_in_range(101,-100,100),	"value_in_range(101,-100,100)");

	cout << endl << "Press any key to continue " << endl;
	temp = get_char_input();

	/* Automated tests for row_is_winner() */

	cout << endl << "Running test oracle for row_is_winner() function..." << endl;
	cout << "These test cases should return true..." << endl;
	report(1,   row_is_winner('X', 'X', 'X'), "row_is_winner('X', 'X', 'X')");
	report(2,   row_is_winner('a', 'a', 'a'), "row_is_winner('a', 'a', 'a')");
	cout <<"These test cases should return false..." << endl;
	report(3, !row_is_winner(' ', 'X', 'O'), "row_is_winner(' ', 'X', 'O')");
	report(4, !row_is_winner(' ', ' ', ' '), "row_is_winner(' ', ' ', ' ')");


	cout << endl << "Running test oracle for TTT_opponent() function... "<< endl;
	report(1, TTT_opponent(COMPUTER) == USER, "TTT_opponent(COMPUTER) should return USER");
	report(2, TTT_opponent(USER) == COMPUTER, "TTT_opponent(USER) should return COMPUTER");

    cout << endl << "Press any key to continue " << endl;
	temp = get_char_input();

    cout << "Testing functions to display TTT board..." << endl;
	display_TTT_boards();

	/* Interactive Test driver:  this portion will allow you to run some custom tests. */
	int val, min, max;
	char s1, s2, s3;

	cout << endl << "Ready to run interactive tests..." << endl << endl;
	while ( user_says_yes("Do you want to run another test?") )
	{
		cout << "Testing get_int_input() function... "<< endl;
		cout << "Enter a minimum bound (any integer):" << endl;
		min = get_int_input(INT_MIN, INT_MAX);
        cout << "Enter a maximum bound (must be >= " << min << " )" << endl;
		max = get_int_input(min, INT_MAX);
        cout << "Enter a value between " << min << " and " << max;
		val = get_int_input(min, max);
		cout << "value_in_range(" << val << " , " << min << " , " << max << " ) returned " << (value_in_range(val,min,max)?"true":"false") << endl;


		cout << endl << endl << "Enter values(characters) for three squares from a TTT board:\n ";
		cin >> s1 >> s2 >> s3;
        string garbage;
        //get rid of what the user might have typed after the 3 chars
        getline(cin,garbage);

		cout <<  "That would " << (row_is_winner(s1, s2, s3)?" ":" NOT ") << " be considered a winning TTT row" << endl;

	}

	return 0;
}


/*****************************************************
*** Function stubs are provide below for the six  ***
*** functions that you need to write.             ***
*****************************************************/
/* This function determines if an int value is within a range.
 PRE: min <= max and value is defined
 POST: returns true if min <= value <= max, and false otherwise.
*/
bool value_in_range(int value, int min, int max)
{
	return (value <= max && value >=min);
}
/* This function determines if a row of tic-tac-toe squares is a winning row.
 PRE: s1, s2, and s3 are defined
 POST: returns true if a row (horizontal, vertical, or diagonal) on
		 a tic-tac-toe board containing [s1, s2, s3],
		 is a winning row, and false otherwise.
*/
bool row_is_winner(char s1, char s2, char s3)
{
	/* this function assumes that an empty square
			 contains the value EMPTY, but should make no assumptions
			 about how the other game pieces (X's and O's) are represented! */
	return (s1==s2 && s2==s3 && s3 != EMPTY );
}

/* This function returns the opponent of the player.
 PRE: player == COMPUTER or player == USER
 POST: returns the opponent of player.
*/
char TTT_opponent(char player)
{
	if (player == USER)
        return COMPUTER;
    else
        return USER;
}

/* This function gets a valid integer input from the user.
 PRE: User has been prompted to enter an integer and min <= max.
 POST: an integer value, i, entered by user is returned, where min <= i <= max.
*/
int  get_int_input(int min, int max)
{
	/* Your code goes here
	 Note: you should call your value_in_range function to validate the user's input!
			 This function must also check that the user enters integer data,
			 and issue an error message and re-prompt the user if they make a mistake. */

    int num;

    cin.unsetf(ios::skipws);

    while ( !(cin >> num) || ( cin.get() != '\n') ||  (num > max) || (num < min) )
    {
        cout << "Please enter an integer in the range " << min << "..." << max << ": ";
        cin.clear(); // unset failbit
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.setf(ios::skipws);
    return num;

}

/* This function displays one of the horizontal line in a TTT board.
 PRE: the output marker is at the start of a new line.
 POST: A horizontal line has been drawn on the screen.
*/
void display_horizontal_line()
{
	cout << "---------" << endl;
}

/* This function displays one row of a TTT board with squares s1, s2 and s3
 PRE: the output marker is at the start of a new line.
 POST: A row of the TTT board is drawn on the screen.
*/
void display_one_row(char s1, char s2, char s3)
{
	cout << s1 << " | " << s2 << " | " << s3 << endl;
}


/* Below are the helper functions for test driver. DO NOT CHANGE!!! */

/* PRE: none
   POST: a message indicating results of test has been displayed
*/
void report(int testNumber, bool testSuccess, string testCase)
{

	if (testSuccess)
    {
        cout << "\t     CORRECT ";
        cout << "\t \x02 \x01 \x02  " ; /* display funny faces if test is successful */
    }

	else
		cout << "\tX  INCORRECT ";

	cout << "result produced by test # " << testNumber << endl;

	//if (!testSuccess)
		cout <<  "\t\tTest case was : " << testCase << endl;
}

/* This function prompts the user with a yes/no question and returns their answer.
   PRE:	 question is a yes/no question the user should answer
   POST: returns true if user answered YES, false if they answer NO
*/
int user_says_yes(string question)
{
	char answer;

	do {
		cout << question << " (Y/N):";

        answer= get_char_input();
		answer = toupper(answer);

	} while (!(answer == 'Y' || answer == 'N'));

	cout << "\n\n";
	return (answer == 'Y');
}

/* This function uses the two output functions display a few of TTT boards
   PRE: none.
   POST: three TTT boards have been drawn on the output stream.
*/
void display_TTT_boards()
{
	cout <<  "An empty TTT board should be drawn below:\n\n";
	display_one_row(' ',' ',' ');
	display_horizontal_line();
	display_one_row(' ',' ',' ');
	display_horizontal_line();
	display_one_row(' ',' ',' ');

	cout << "\nA TTT board in play should be drawn below:\n\n";
	display_one_row(COMPUTER,' ',COMPUTER);
	display_horizontal_line();
	display_one_row(' ',USER,USER);
	display_horizontal_line();
	display_one_row(USER,COMPUTER,' ');

	cout << "\nA numbered TTT board in play should be drawn below:\n";
	display_one_row('0','1','2');
	display_horizontal_line();
	display_one_row('3','4','5');
	display_horizontal_line();
	display_one_row('6','7','8');

}

/* This function returns the first character entered by the user
   Pre: cin is in a good state
   Post: The first entered character is returned (even if is '\n')
*/
char get_char_input()
{
     char input;
     string line;

     getline (cin,line);

     return line[0];
}

/* This function initializes the game board. All slots become vacant.

    Input: i (a slot location of the array ttt_board)
    Parameter: ttt_board array
    Output: Display an empty board
*/
void initialize_board(char ttt_board[])
{
    for (int i = 0; i < BOARD_SIZE; i++)
        ttt_board[i] = EMPTY;
}

/* This function displays the gameboard in the form of array elements

    Input: elements of an array named board
    Parameter: board array
    Output: Display lines and columns by calling functions
*/
void display_board(char board[])
{
    display_one_row(board[0],board[1],board[2]);
	display_horizontal_line();
	display_one_row(board[3],board[4],board[5]);
	display_horizontal_line();
	display_one_row(board[6],board[7],board[8]);
}

/* This fucntion finds the empty slot and returns the location number i back to main

    Intput: i (a slot location of the arrray board)
    Parameter: board array
    Output: either integer varaible i ( i is the location of an empty slot) or BOARD_SIZE (8, the last element of board array)
*/
int find_first_empty_slot(char board[])
{
    for (int i = 0; i < BOARD_SIZE; i++)
        if ( board[i] == EMPTY )
            return i;
    return BOARD_SIZE;
}

/* This function checks if there is an empty slot in the game board

    Input: i (a slot location of the gameboard)
    Parameter: an array named array, and size (the size of the board array which is 9)
    Output: true or false

*/
bool slots_all_taken (char array[],int size) //boardsize=9
{
    for (int i=0; i< BOARD_SIZE; i++)
      {
          if (array[i] == EMPTY)
            return false;
      }
    return true; // if there is no empty slots
}

/* This function checks if any of horizontal,vertical and diagonal lines has identical characters
   either X or Y, if there is a row of the same characters, then the fucntion returns true

   Input: array elements
   Parameter: an array named array
   Ouput: true or false

*/
bool winning_rows (char array[])
{

    return (
                row_is_winner(array[0],array[1],array[2]) || // horizontal line winning cases
                row_is_winner(array[3],array[4],array[5]) ||
                row_is_winner(array[6],array[7],array[8]) ||

                row_is_winner(array[0],array[3],array[6]) || // vertical line winning cases
                row_is_winner(array[1],array[4],array[7]) ||
                row_is_winner(array[2],array[5],array[8]) ||

                row_is_winner(array[0],array[4],array[8]) || // diagonal line winning cases
                row_is_winner(array[2],array[4],array[6])
    ); // return 1(=true) if there's a row of identical characters

}
