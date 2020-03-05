#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <tuple>

#ifndef INCLUDES
#define INCLUDES

#include "Move.h"

#endif

#ifndef ZOBRIST
#define ZOBRIST

#include "Zobrist.h"

#endif

class Board{
 private :
  int player; // the player who has to do the next move
  std::vector<std::vector<int>> board; // contains 1 at coord (i,j) if there is a white pawn, -1 if there is a black pawn, 0 if it is empty
  
 public:
  uint64_t hashcode;
  
  Board();
  Board(std::vector<std::vector<int>>, int);
  ~Board();
  int get_player();
  std::vector<std::vector<int>> get_board(); //return the board
  void init();
  bool valid(Move m); // return 1 if the move is valide 0 otherwise
  int play(Move m, Zobrist zobrist); // return 1 if the Move m was played, 0 if it couldn't be played
  std::vector<Move> legal_moves(); // return a list of legal moves for the given player
  int game_state(); // returns 0 if the game isn't over, 1 if white won, 2 if black won
  void to_string();
};
