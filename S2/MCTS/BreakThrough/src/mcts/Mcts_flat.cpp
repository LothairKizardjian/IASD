#include "../../includes/mcts/Mcts_flat.h"

Mcts_flat::Mcts_flat(){
}

Mcts_flat::Mcts_flat(Board b, Zobrist z){
  this->board = b;
  this->zobrist = z;
}

int Mcts_flat::playout(Board board){
  std::random_device rd;
  std::mt19937 g(rd());

  Board board_copy(board.get_board(),board.get_player());
  
  while(board_copy.game_state() == 0){
    std::vector<Move> move_list = board_copy.legal_moves();
    board_copy.play(move_list[int(rand() % move_list.size())],this->zobrist);
  }
  return board_copy.game_state();
}

Move Mcts_flat::flat_mcts(Board board, int p){ // Really naïve : there is no choice in the moves to explore or to eploit => There is 100 playouts for each move.
  std::vector<Move> move_list = board.legal_moves();
  std::vector<std::pair<Move,std::pair<int,int>>> moves_stats; // keeps the stats for each move with a tuple of the form (nb_of_playouts_won,nb_of_playouts_played_for_this_move).
  
  for(auto move : move_list){
    Board board_copy(board.get_board(),board.get_player());
    board_copy.play(move,this->zobrist);
    int playouts_won = 0;
    for(int i=0; i<(p/move_list.size()); i++){
      int result = this->playout(board_copy);
      if(result == board.get_player()){
	playouts_won += 1;
      }
    }
    moves_stats.push_back(std::make_pair(move,std::make_pair(playouts_won,p)));
  }
  
  Move best_move;
  float best_mean = 0.0;

  for(auto move: moves_stats){
    float mean = (float)move.second.first / (float)move.second.second;
    if(mean > best_mean){
      best_mean = mean;
      best_move = move.first;
    }
  }

  return best_move;  
}
