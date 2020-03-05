#include "../../includes/mcts/Mcts_uct.h"

Mcts_uct::Mcts_uct(){
}

Mcts_uct::Mcts_uct(Board b, Zobrist z){
  this->board = b;
  this->zobrist = z;
}

int Mcts_uct::playout(Board board){
  std::random_device rd;
  std::mt19937 g(rd());

  Board board_copy(board.get_board(),board.get_player());
  
  while(board_copy.game_state() == 0){
    std::vector<Move> move_list = board_copy.legal_moves(); 
    board_copy.play(move_list[int(rand() % move_list.size())],this->zobrist);
  }
  return board_copy.game_state();
}

Move Mcts_uct::uct(Board board, int p, float c){
  Board board_copy(board.get_board(),board.get_player());
  std::vector<Move> move_list = board_copy.legal_moves();
  game_state = board_copy.game_state();

  if(game_state != 0){
    return game_state;
  }

  uint64_t t = 
}
