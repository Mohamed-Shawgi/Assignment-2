#ifndef FOURINROW_H
#define FOURINROW_H

#include "BoardGame_Classes.h"


template <typename T>
class fourInRow_Board:public Board<T> {
public:
    fourInRow_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool isValidPoint(int a, int b);
};


template <typename T>
class fourInRow_Player : public Player<T> {
public:
    fourInRow_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};


template <typename T>
class fourInRow_Random_Player : public RandomPlayer<T>{
public:
    fourInRow_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};


//--------------------------------------- IMPLEMENTATION



#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
fourInRow_Board<T>::fourInRow_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}


template <typename T>
bool fourInRow_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {

            if (x < this->rows - 1 && this->board[x + 1][y] == 0) {
                return false; 
            }
            

            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}


// Display the board and the pieces on it
template <typename T>
void fourInRow_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n----------------------------------------------------------";
    }
    cout << endl;
}


// Returns true if there is any winner
template <typename T>
bool fourInRow_Board<T>::is_win() {


    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {

            if (j <= this->columns - 4 && this->board[i][j] != 0 && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2] && this->board[i][j] == this->board[i][j + 3]) {
                return true;
            }

            if (i <= this->rows - 4 && this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j] && this->board[i][j] == this->board[i + 2][j] && this->board[i][j] == this->board[i + 3][j]) {
                return true;
            }
        }
    }


    // Check diagonals 
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (isValidPoint(i,j) && isValidPoint(i + 1,j + 1) && isValidPoint(i + 2,j + 2) && isValidPoint(i + 3,j + 3)) {
                if (this->board[i][j] == this->board[i + 1][j + 1] && this->board[i + 1][j + 1] == this->board[i + 2][j + 2] && this->board[i + 2][j + 2] == this->board[i + 3][j + 3] && this->board[i][j] != 0) {
                    return true;
                }
            }
        }
    }

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (isValidPoint(i,j) && isValidPoint(i + 1,j - 1) && isValidPoint(i + 2,j - 2) && isValidPoint(i + 3,j - 3)) {
                if (this->board[i][j] == this->board[i + 1][j - 1] && this->board[i + 1][j - 1] == this->board[i + 2][j - 2] && this->board[i + 2][j - 2] == this->board[i + 3][j - 3] && this->board[i][j] != 0) {
                    return true;
                }
            }
        }
    }

    return false;
}



template <typename T>
// ckeck if the point is in board dimensions
bool fourInRow_Board<T>::isValidPoint(int a, int b) {
    return (a < this->rows && b < this->columns);
}

// Return true if 42 moves are done and no winner
template <typename T>
bool fourInRow_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool fourInRow_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


// -------------------------------------------

// Constructor for X_O_Player
template <typename T>
fourInRow_Player<T>::fourInRow_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void fourInRow_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 6) separated by spaces: ";
    cin >> x >> y;
}


template <typename T>
fourInRow_Random_Player<T>::fourInRow_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 6;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void fourInRow_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 6
    y = rand() % this->dimension;
}



#endif