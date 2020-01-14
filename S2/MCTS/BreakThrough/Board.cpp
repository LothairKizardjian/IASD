#include "Board.h"

Board::Board(){
  this->player = 1;
  for(int i=0; i<5; i++){
    this->board.push_back(std::vector<int>(5));
  }
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      if(i<2){
	this->board[i][j] = 1;
      }else if(i>=3 and i<5){
	this->board[i][j] = 2;
      }else{
	this->board[i][j] = 0;
      }
    }
  }
}

Board::Board(std::vector<std::vector<int>> board, int player){
  this->player = player;
  for(int i=0; i<5; i++){
    this->board.push_back(std::vector<int>(5));
  }
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      this->board[i][j] = board[i][j];
    }
  }
}

int Board::get_player(){
  return this->player;
}

std::vector<std::vector<int>> Board::get_board(){
  return this->board;
}

bool Board::valid(Move m){
  if(m.x2 >= 5 or m.y2 >= 5 or m.x2 < 0 or m.y2 < 0){
    return false;
  }else if(m.player == 1){ // white
    if(m.x2 != m.x1+1){
      return false;
    }
    if(this->board[m.x2][m.y2] == 2){
      if(m.y2 == m.y1+1 or m.y2 == m.y1-1){
	return true;
      }
      return false;
    }else if(this->board[m.x2][m.y2] == 0){
      if(m.y2 == m.y1+1 or m.y2 == m.y1-1 or m.y2 == m.y1){
	return true;
      }else{
	return false;
      }
    }
  }else if(m.player == 2){ // black
    if(m.x2 != m.x1-1){
      return false;
    }else{
      if(this->board[m.x2][m.y2] == 1){
	if(m.y2 == m.y1+1 or m.y2 == m.y1-1){
	  return true;
	}
      }else if(this->board[m.x2][m.y2] == 0){
	if(m.y2 == m.y1+1 or m.y2 == m.y1-1 or m.y2 == m.y1){
	  return true;
	}
	return false;
      }else{
	return false;
      }
    }
  }
}

std::vector<Move> Board::legal_moves(int player){
  std::vector<Move> legal_moves;
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      if(this->board[i][j] == player){
	for(int k=-1; k<=1; k++){
	  for(int l=-1; l<=1; l++){
	    Move m(i, j, i+k, j+l, player);
	    if(valid(m)){
	      legal_moves.push_back(m);
	    }
	  }
	}
      }
    }
  }
  return legal_moves;
}

int Board::play(Move m){
  if(valid(m)){
    this->board[m.x1][m.y1] = 0;
    this->board[m.x2][m.y2] = m.player;
    if(m.player == 1){
      this->player = 2;
    }else{
      this->player = 1;
    }
    return 1;
  }
  return 0;
}

int Board::game_state(){
  std::vector<int> first_row = this->board[0];
  if(std::find(first_row.begin(), first_row.end(), 2) != first_row.end()){
    return 2;
  }
  std::vector<int> last_row = this->board[4];
  if(std::find(last_row.begin(), last_row.end(), 1) != last_row.end()){
    return 1;
  }
  return 0;
}

int Board::playout(){
  std::random_device rd;
  std::mt19937 g(rd());

  Board board_copy(this->board,this->player);
  
  while(board_copy.game_state() == 0){
    std::vector<Move> move_list = board_copy.legal_moves(board_copy.player);
    std::shuffle(move_list.begin(), move_list.end(), g);    
    board_copy.play(move_list[0]);
  }
  return board_copy.game_state();
}

void Board::to_string(){
  std::cout << std::endl;
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      std::cout << "|" << this->board[i][j];
      if(j==4){
	std::cout << "|";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

// Comparison function to sort the vector elements 
// by second element of tuples 
bool sortbysec(const std::tuple<Move, float>& a,  
               const std::tuple<Move, float>& b) 
{ 
  return (std::get<1>(a) > std::get<1>(b)); 
} 

Move Board::flat_monte_carlo(int playouts){ // Really naïve : there is no choice in the moves to explore or to eploit => There is 100 playouts for each move.
  std::vector<Move> move_list = legal_moves(this->player);
  std::vector<std::tuple<Move,float>> moves_stats; // keeps the stats for each move with a tuple of the form (move,%_of_playouts_won).!!
  for(auto move : move_list){
    Board board(this->board,this->player);
    board.play(move);
    int playouts_won = 0;
    for(int i=0; i<playouts; i++){
      int result = board.playout();
      if(result == this->player){
	playouts_won += 1;
      }
    }
    moves_stats.push_back(std::make_tuple(move,(float)playouts_won/(float)playouts));
  }
  std::sort(moves_stats.begin(), moves_stats.end(), sortbysec);
  Move best_move = std::get<0>(moves_stats[0]);
  return best_move;
}

int main(int argc, char** argv){
  Board b;
  b.to_string();
  Move best_move = b.flat_monte_carlo(100);
  b.play(best_move);
  b.to_string();
}
