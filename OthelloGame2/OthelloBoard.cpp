#include "OthelloBoard.h"
#include "OthelloMove.h"
#include <vector>
#include <iostream>

using namespace std;

OthelloBoard::OthelloBoard() 
   : mNextPlayer(BLACK), mValue(0), mPassCount(0){

   mBoard[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = BLACK;
   mBoard[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = BLACK;
   mBoard[BOARD_SIZE / 2][BOARD_SIZE / 2] = WHITE;
   mBoard[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = WHITE;
}

void OthelloBoard::ApplyMove(OthelloMove *move) {
   Player opponent;
   mNextPlayer == BLACK ? opponent = WHITE : opponent = BLACK;
   if (move->IsPass()) {
      mPassCount++;
   }
   else {
      mPassCount = 0;
      mNextPlayer == BLACK ? mValue++ : mValue--;
      for (int i = -1; i <= 1; i++){
         for (int j = -1; j <= 1; j++) {
            if (!InBounds(move->mRow + i, move->mCol + j))
               continue;
            if (mBoard[i + move->mRow][j + move->mCol] == opponent) {
               int rowDirt = move->mRow + i, colDirect = move->mCol + j;
               int flipCount = 0;
               for (;;) {
                  rowDirt += i, colDirect += j;
                  flipCount++;

                  if (mBoard[rowDirt][colDirect] == 0 || !InBounds
                     (rowDirt, colDirect)) {
                     break;
                  }
                  if (mBoard[rowDirt][colDirect] == mNextPlayer) {
                     while (mBoard[rowDirt -= i][colDirect -= j] == opponent) {
                        mBoard[rowDirt][colDirect] = mNextPlayer;
                        mNextPlayer == BLACK ? mValue += 2 : mValue -= 2;
                     }
                     OthelloMove::FlipSet flipSet(flipCount, i, j);
                     move->AddFlipSet(flipSet);
                     mBoard[move->mRow][move->mCol] = mNextPlayer;
                     break;
                  }
               }
            }
         }//end of inner for loop
      }//end of outter for loop
      mHistory.push_back(move);
     
   }//end of else
   //change turns
   mNextPlayer == BLACK ? mNextPlayer = WHITE : mNextPlayer = BLACK;
}


void OthelloBoard::GetPossibleMoves(std::vector<OthelloMove *> *list) const {
   Player opponent;
   mNextPlayer == BLACK ? opponent = WHITE : opponent = BLACK;

   for (int row = 0; row < BOARD_SIZE; row++) {
      for (int col = 0; col < BOARD_SIZE; col++) {
         if (mBoard[row][col] == EMPTY) {
            for (int i = -1; i <= 1; i++) {
               for (int j = -1; j <= 1; j++) {
                  if (!InBounds(row + i, col + j))
                     continue;
                  if (mBoard[row + i][col + j] == opponent) {
                     int rowDirect = row + i;
                     int colDirect = col + j;

                     for (;;) {
                        rowDirect += i;
                        colDirect += j;

                        if (mBoard[rowDirect][colDirect] == 0 || 
                           !InBounds(rowDirect, colDirect))
                           break;

                        if (mBoard[rowDirect][colDirect] == mNextPlayer) {
                           OthelloMove *temp = CreateMove();
                           temp->mRow = row;
                           temp->mCol = col;
                           bool exists = false;

                           //check for duplicates
                           for (int n = 0; n < list->size(); n++) {
                              if (*temp == *list->at(n)) {
                                 exists = true;
                                 delete temp; //clear it
                              }
                           }
                           //add a possible move
                           if (!exists) {
                              list->push_back(temp);
                           }

                           break;
                        }
                     }
                  }
               }// end of 4 for loop
            }//end of 3 for loop
         }// end of 1 if
      }//end of 2 for loop
   }// end of 1 for loop

   //if list is empty, add a default move (-1, -1)
   if (list->empty()) {
      list->push_back(new OthelloMove());
   }
       
}// end of function


void OthelloBoard::UndoLastMove() {
   if (mHistory.size() > 0) {
      OthelloMove *undoMove = mHistory.back();

      while (undoMove->mFlips.size() > 0) {
         int row = undoMove->mRow;
         int col = undoMove->mCol;
         mBoard[row][col] = 0;
         int rowDel = undoMove->mFlips.back().rowDelta;
         int colDel = undoMove->mFlips.back().colDelta;

         for (int n = 0; n < undoMove->mFlips.back().switched; n++) {

            mBoard[row + rowDel][col + colDel] = GetNextPlayer();
            rowDel += undoMove->mFlips.back().rowDelta;
            colDel += undoMove->mFlips.back().colDelta;
            mNextPlayer == BLACK ? mValue += 2 : mValue -= 2;
         }
         undoMove->mFlips.pop_back();
        
      }
      mHistory.pop_back();
      mNextPlayer == BLACK ? mValue++ : mValue--;
      delete undoMove;
      
   }
   mNextPlayer == BLACK ? mNextPlayer = WHITE : mNextPlayer = BLACK;
}