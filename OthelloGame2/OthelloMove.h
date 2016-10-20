#ifndef __OTHELLOMOVE_H
#define __OTHELLOMOVE_H

#include <string>
#include <vector>
#include <iostream>

/*
An OthelloMove encapsulates a single potential move on an OthelloBoard. It
is represented internally by a row and column, both 0-based.
*/


/*
A FlipSet tracks a direction and # of pieces that got flipped when this
move was applied. See spec.
*/
class OthelloMove {
private:
   
   friend class OthelloBoard;

   class FlipSet {
   public:
      FlipSet(char sw, char rowD, char colD);
      char switched;
      char rowDelta, colDelta;
   };

   int mRow, mCol;
   std::vector<FlipSet> mFlips;

   OthelloMove();

   OthelloMove(int row, int col);

   void AddFlipSet(FlipSet set);

public:

   OthelloMove& operator=(const std::string &);

   friend bool operator==(const OthelloMove &lhs, const OthelloMove &rhs);

   operator std::string() const;

   inline bool IsPass() const { 
      return mRow == -1 && mCol == -1 ? true : false;
   }

   static int mOnHeap;

};
#endif