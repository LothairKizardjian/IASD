#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <tuple>
#include "Move.h"

class Board{
 private :
  int player; // the player who has to do the next move
  std::vector<std::vector<int>> board; // contains 1 at coord (i,j) if there is a white pawn, -1 if there is a black pawn, 0 if it is empty
  
 public:
  Board();
  Board(std::vector<std::vector<int>>, int);
  int get_player();
  std::vector<std::vector<int>> get_board(); //return the board
  bool valid(Move m); // return 1 if the move is valide 0 otherwise
  int play(Move m); // return 1 if the Move m was played, 0 if it couldn't be played
  std::vector<Move> legal_moves(int player); // return a list of legal moves for the given player
  int game_state(); // returns 0 if the game isn't over, 1 if white won, 2 if black won
  int playout(); // plays a random game from the current state until the end, returns the result of the game (i.e 1 if white won, 2 if black won)"
  Move flat_monte_carlo(int playouts); // develops a MCTS from the current board state, returns the 'best' move to play
  void to_string();
};
