#include "../../includes/mcts/Mcts_ucb.h"

Mcts_ucb::Mcts_ucb(){
}

Mcts_ucb::Mcts_ucb(Board b, Zobrist z){
  this->board = b;
  this->zobrist = z;
}

int Mcts_ucb::playout(Board board){
  std::random_device rd;
  std::mt19937 g(rd());

  Board board_copy(board.get_board(),board.get_player());
  
  while(board_copy.game_state() == 0){
    std::vector<Move> move_list = board_copy.legal_moves();
    // std:: cout << move_list.size() << std::endl;
    if(move_list.size() == 0){
      board.to_string();
      std::cout << board.get_player() << std::endl;
    }
    board_copy.play(move_list[int(rand() % move_list.size())],this->zobrist);
  }
  return board_copy.game_state();
}

Move Mcts_ucb::ucb(Board board, int p, float c){
  std::vector<Move> move_list = board.legal_moves();
  
  for(auto move : move_list){
    //we haven't seen those moves yet so we do one playout for each
    Board board_copy(board.get_board(),board.get_player());
    board_copy.play(move,this->zobrist);
    int result = this->playout(board_copy);
    int win = 0;
    if(result == board.get_player()){
      win = 1;
    }
    moves_stats.push_back(std::make_pair(move,std::make_pair(win,1)));
  }
  
  int total_playouts = move_list.size();
  
  while(total_playouts < p){
    //we have already seen all the possible moves so we chose the move to play according to UCB
    int best_ucb_move_idx = 0;
    float best_ucb = 0.0;
    
    for(int i=0; i<move_list.size(); i++){
      float ucb = ((float)moves_stats[i].second.first / (float)moves_stats[i].second.second) + (c*sqrt(log((float)total_playouts)/(float)moves_stats[i].second.second));
      if(ucb > best_ucb){
	best_ucb_move_idx = i;
	best_ucb = ucb;
      }
    }
    
    Board board_copy(board.get_board(),board.get_player());
    board_copy.play(moves_stats[best_ucb_move_idx].first,this->zobrist);
    int result = this->playout(board_copy);
    int win = 0;
    if(result == board.get_player()){
      win = 1;
    }
    moves_stats[best_ucb_move_idx].second.first += win;
    moves_stats[best_ucb_move_idx].second.second += 1;
    total_playouts += 1;
  }
  
  float best_mean = 0;
  Move best_move;
  for(auto move: moves_stats){
    float mean = (float)move.second.first/(float)move.second.second;
    if(mean > best_mean){
      best_mean = mean;
      best_move = move.first;
    }
  }
  return best_move;
}
