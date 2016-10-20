#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "OthelloMove.h"
#include "OthelloException.h"
#include "OthelloBoard.h"
using namespace std;

int OthelloMove::mOnHeap = 0;

OthelloMove::OthelloMove()
   : mRow(-1), mCol(-1) {
}

OthelloMove::OthelloMove(int row, int col)
   : mRow(row), mCol(col) {
}

OthelloMove::FlipSet::FlipSet(char sw, char rowD, char colD)
   : switched(sw), rowDelta(rowD), colDelta(colD) {

}

void OthelloMove::AddFlipSet(FlipSet set) {
   mFlips.push_back(set);
}

OthelloMove& OthelloMove::operator=(const string &rhs) { 
   istringstream inputString(rhs.substr(5));
   int col, row;
   char p1, comma, p2;
   inputString >> p1 >> row >> comma >> col >> p2;
   if (rhs != "move pass") {
      if (row >= 0 && col >= 0 && row < BOARD_SIZE && col < BOARD_SIZE) 
         mRow = row, mCol = col;
      else 
         throw OthelloException::exception("Input Out of Bounds");
   }
   return *this;
}


OthelloMove::operator string() const {
   stringstream outString;
   (mRow == -1 && mCol == -1) ? outString << "pass" :
      outString << "(" << mRow << "," << mCol << ")";
   return outString.str();
}

bool operator==(const OthelloMove &lhs, const OthelloMove &rhs) {
   return lhs.mCol == rhs.mCol && lhs.mRow == rhs.mRow;
}
