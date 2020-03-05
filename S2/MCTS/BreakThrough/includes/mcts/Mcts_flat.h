#ifndef INCLUDES
#define INCLUDES

#include "../Move.h"
#include "../Board.h"

#endif

#ifndef ZOBRIST
#define ZOBRIST

#include "../Zobrist.h"

#endif

#include <math.h>
#include <map>

class Mcts_flat{
 private:
  Board board;

 public:
  Zobrist zobrist;
  Mcts_flat();
  Mcts_flat(Board,Zobrist);
  int playout(Board board); // returns the result of the playout from board b
  Move flat_mcts(Board board, int p); // develops a MCTS from the board b, returns the 'best' move to play
};
