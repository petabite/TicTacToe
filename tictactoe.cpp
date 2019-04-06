#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class TicTacToe {
  public:
    TicTacToe(int players, string name1, string name2) {
      numofPlayers = players;
      playernames[0] = name1;
      playernames[1] = name2;
      printscreen();
      while (!gameOver) {
          askplayermove();
          if (currentPlayerTurn == 1) {
            currentPlayerTurn = 2;
          } else {
            currentPlayerTurn = 1;
          }
      }
    }

  private:
    void printscreen() {
      system("cls");
      cout << string(20, '=') << endl;
      cout << "Tic Tac Toe" << endl;
      cout << string(20, '=') << endl;
      //board
      cout << " A B C" << endl;
      for (int row = 0; row < 3; row++) {
        cout << row + 1;
        for (int column = 0; column < 3; column++){
          cout << board[row][column];
          if (column < 2){
            cout << '|';
          } else {
            cout << endl;
          }
        }
        if (row < 2){
            cout << " -----" << endl;
        }
      }
    }

    void askplayermove() {
        int rowMove;
        char columnMove;
        if (numofPlayers > 1 || currentPlayerTurn == 1){
            cout << playernames[currentPlayerTurn-1] << "'s turn. Which row do you want to move(1,2,3)? >> ";
            cin >> rowMove;
            cout << "\nColumn(a,b,c)? >> ";
            cin >> columnMove;
            cout << endl;
        } else {
            char letters[3] = {'a','b','c'};
            int openRow[8];
            int openColumn[8];
            int index = 0;
            for (int row = 0; row < 3; row++) {
                for (int column = 0; column < 3; column++) {
                    if (board[row][column] == ' ') {
                        openRow[index] = row;
                        openColumn[index] = column;
                        index++;
                    }
                }
            }
            srand(time(0));
            int randInd = 1 + (rand() % index);
            rowMove = openRow[randInd] +1;
            columnMove = letters[openColumn[randInd]];
        }
        makemove(rowMove, columnMove);
    }

    void makemove(int row, int column){
        int columnNumber;
        if (!(row <= 3)){
            cout << "Invalid Row" << endl;
            askplayermove();
        }
        switch (column) {
            case 'a':
                columnNumber = 1;
                break;
            case 'b':
                columnNumber = 2;
                break;
            case 'c':
                columnNumber = 3;
                break;
            default:
                cout << "Invalid column" << endl;
                askplayermove();
        }
        char movePiece;
        if (currentPlayerTurn == 1) {
            movePiece = 'X';
        } else {
            movePiece = 'O';
        }
        if (board[row-1][columnNumber-1] != ' ') {
            cout << "Invalid move" << endl;
            askplayermove();
        } else {
            board[row-1][columnNumber-1] = movePiece;
        }
        printscreen();
        checkwin();
    }

    void checkwin() {
        for(int i = 0; i < 3; i++) {
            if (three_in_a_row(board[i][0],board[i][1],board[i][2]) || three_in_a_row(board[0][i],board[1][i],board[2][i])) {
                gameOver = true;
                cout << playernames[currentPlayerTurn-1] << " WON THE GAME! GG!" << endl;
            }
        }
        if (three_in_a_row(board[0][0], board[1][1], board[2][2]) || three_in_a_row(board[2][0],board[1][1],board[0][2])){
            gameOver = true;
            cout << playernames[currentPlayerTurn-1] << " WON THE GAME! GG!" << endl;
        }
        checktie();
    }



    void checktie() {
        int blankSpaces = 0;
        for (int row = 0; row < 3; row++) {
            for (int column = 0; column < 3; column++){
                if (board[row][column] == ' ') {
                    blankSpaces++;
                }
            }
        }
        if (blankSpaces == 0) {
            gameOver = true;
            cout << "IT'S A DRAW! GG!!" << endl;
        }
    }

    bool three_in_a_row(char one, char two, char three) {
        if (one == two && one == three && one != ' ') {
            return true;
        } else {
            return false;
        }
    }
    char board[3][3] = {
      {' ', ' ', ' '},
      {' ', ' ', ' '},
      {' ', ' ', ' '}
    };
    int currentPlayerTurn = 1;
    string playernames[2];
    bool gameOver = false;
    int numofPlayers;
};

int main() {
    int players;
    string player1name, player2name;
    cout << "welcome to tic tac toe" << endl;
    cout << "how many players(1 ,2)? >> " ;
    cin >> players;
    cout << "\nwhat is player 1's name? >> " ;
    cin >> player1name;
    if (players > 1) {
        cout << "what is player 2's name? >> " ;
        cin >> player2name;
    } else {
        player2name = "Computer";
    }
    TicTacToe game(players,player1name,player2name);
    cout << "press a key then enter to close ";
    char key;
    cin >> key;
    return 0;
}
