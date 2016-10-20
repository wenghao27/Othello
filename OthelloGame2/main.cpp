#include "OthelloException.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
   // Initialization
   OthelloBoard board; // the state of the game board
   OthelloView v(&board); // a View for outputting the board via operator<<
   string userInput; // a string to hold the user's command choice
   vector<OthelloMove *> possMoves; // a holder for possible moves

   cout << "Initial board:" << endl;
  
   do {
      cout << v << endl;
      board.GetNextPlayer() == 1 ? cout << "Black's move.\nPossible Moves:\n"
         : cout << "\nWhite's move.\nPossible Moves:\n";

      board.GetPossibleMoves(&possMoves);
      for (OthelloMove* &i : possMoves) {
         cout << (string)*i << " ";
      }
      cout << endl << "Enter a command: ";
      getline(cin, userInput);

      if (userInput.find("move") == 0) { 

         OthelloMove *m = board.CreateMove();
         try {
            *m = userInput;
            bool valid = false;
            for (int i = 0; i < possMoves.size(); i++) {
               if (*m == *possMoves.at(i)) {
                  board.ApplyMove(m);
                  valid = true;
               }
            }
            if (!valid){
               delete m;
                cout << endl << "Not a valid move, try again!" << endl << endl;
            }
         }
         catch (OthelloException::exception &ex) {
            delete m;
            cout << endl << ex.what() << endl;
         }
      }  
   
      if (userInput.find("undo") == 0) {
         std::istringstream in(userInput);
         int num;
         string s;
         in >> s >> num;
         for (int i = 0; i < num; i++) {
            board.UndoLastMove();
         }
      }
      if (userInput.find("showHistory") == 0) { 
         auto rit = board.GetMoveHistory()->crbegin();
         int nextPlayer = 0;
         board.GetNextPlayer() == 1 ? nextPlayer = 1 : nextPlayer = -1;
         if (rit == board.GetMoveHistory()->crend())
            cout << "No recourds." << endl;
         else {
            for (rit;  rit != board.GetMoveHistory()->crend(); ++rit) {
               nextPlayer == 1 ? cout << "White: " : cout << "Black: ";
               cout << (string)**rit << endl;
               nextPlayer *= -1;
             }
         }       
      }
      if (userInput.find("showValue") == 0) {
         cout << "Board value: " << board.GetValue() << endl;
      }
      if (board.IsFinished()) { 
         if (board.GetValue() > 0)
            cout << "Black win!";
         else
            cout << "White win!";
      }

      for (int i = 0; i < possMoves.size(); i++) {
        delete possMoves.at(i);
      }
      possMoves.clear();

   } while (!board.IsFinished());
}