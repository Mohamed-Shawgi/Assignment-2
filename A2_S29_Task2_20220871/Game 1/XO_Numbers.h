#ifndef XO_NUMBERS_H
#define XO_NUMBERS_H

#include "BoardGame_Classes.h"


template <typename T>
class XO_Numbers_Board:public Board<T>
{
public:
    XO_Numbers_Board();
    bool update_board (int x , int y , T number);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool evenOrOdd(int n1, int n2, int n3);
};

template <typename T>
class XO_Numbers_Player : public Player<T> {
public:
    XO_Numbers_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
    T getsymbol();
   private: 
       vector<int> player_movies;

};


template <typename T>
class XO_Numbers_Random_Player : public RandomPlayer<T>{
public:
    XO_Numbers_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION


#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <vector>  // for toupper()
#include <algorithm>

using namespace std;


// Constructor for XO_Numbers_Board
template <typename T>
XO_Numbers_Board<T>::XO_Numbers_Board() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}


template <typename T>
bool XO_Numbers_Board<T>::update_board(int x, int y, T number) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| number == 0)) {
        if (number == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = number;
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void XO_Numbers_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// template <typename T>
// bool XO_Numbers_Board<T>::evenOrOdd(int n1, int n2, int n3) {

//     // check if are not empty first
//     if (n1 == 0 || n2 == 0 || n3 == 0) return false; // there is a empty cell winner 

//     bool isEven = (n1 % 2 == 0 && n2 % 2 == 0 && n3 % 2 == 0) ? true : false;
//     bool isOdd = (n1 % 2 != 0 && n2 % 2 != 0 && n3 % 2 != 0) ? true : false;
//     if (isEven || isOdd) {
//         return true;
//     } else {
//         false;
//     }
//     return false;

// }

// Returns true if there is any winner
template <typename T>
bool XO_Numbers_Board<T>::is_win() {



    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        
        // // check if the column or row is even or odd
        // if (!evenOrOdd(this->board[i][0], this->board[i][1] , this->board[i][2]) ||
        // !evenOrOdd(this->board[0][i], this->board[1][i] , this->board[2][i])) {
        //     continue;
        // }

        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15)) {
            return true;
        }
    }

    // // Check diagonals if one them is odd or even
    // if (!evenOrOdd(this->board[0][0], this->board[1][1], this->board[2][2]) ||
    //     !evenOrOdd(this->board[0][2], this->board[1][1], this->board[2][0])) {
    //         return false;
    // }

    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) ||
        (this->board[0][2] + this->board[1][1] == this->board[2][0]== 15)) {
        return true;
    }

    return false;
}


// Return true if 9 moves are done and no winner
template <typename T>
bool XO_Numbers_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool XO_Numbers_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
XO_Numbers_Player<T>::XO_Numbers_Player(string name, T symbol) : Player<T>(name, symbol) {
     if (symbol == 0) {
            this->player_movies = {1, 3, 5, 7, 9};
        } else {
            this->player_movies = {2, 4, 6, 8};
    }
}

template <typename T>
void XO_Numbers_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
XO_Numbers_Random_Player<T>::XO_Numbers_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void XO_Numbers_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

template <typename T>
T XO_Numbers_Player<T>::getsymbol() {
    int number;

    while (true) {
        cout << "\nPlease enter your number from these numbers: ";
        for (int i = 0; i < player_movies.size(); i++) {
            cout << this->player_movies[i] << " ";
        }
        cout << ": ";
        cin >> number;

        int cnt = count(this->player_movies.begin(), this->player_movies.end(), number);

        if (cnt > 0)
            break;
        else
            cout << "Please enter a valid number." << endl;
    }

    return number;
}



#endif