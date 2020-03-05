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

class Mcts_ucb{
 private:
  Board board;
  std::vector<std::pair<Move,std::pair<int,int>>> moves_stats; // keeps the stats for each move with a tuple of the form (nb_of_playouts_won,nb_of_playouts_played_for_this_move).

 public:
  Zobrist zobrist;
  Mcts_ucb();
  Mcts_ucb(Board,Zobrist);
  int playout(Board board); // returns the result of the playout from board b
  Move ucb(Board board, int p, float c); // same as flat_mcts
};
