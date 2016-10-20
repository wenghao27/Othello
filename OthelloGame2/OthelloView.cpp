#include "OthelloView.h"
#include <iostream>
using namespace std;

void OthelloView::PrintBoard(std::ostream &s) const {
   s << "-\t0\t1\t2\t3\t4\t5\t6\t7" << endl;
   for (int i = 0; i < BOARD_SIZE; i++) {
      s << i;
      for (int j = 0; j < BOARD_SIZE; j++) {
         if (mOthelloBoard->mBoard[i][j] == mOthelloBoard->EMPTY)
            s << "\t" << ".";
         else if (mOthelloBoard->mBoard[i][j] == mOthelloBoard->BLACK)
            s << "\t" << "B";
         else
            s << "\t" << "W";
      }
      s << endl;
   }
}

std::ostream& operator<< (std::ostream &lhs, const OthelloView &rhs) {
   rhs.PrintBoard(lhs);
   return lhs;
}


