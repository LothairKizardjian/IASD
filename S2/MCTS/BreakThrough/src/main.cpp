#ifndef INCLUDES
#define INCLUDES

#include "../includes/Move.h"
#include "../includes/Board.h"

#endif

#include "../includes/mcts/Mcts_flat.h"
#include "../includes/mcts/Mcts_ucb.h"
#include <string>
#include <map>

void flat_vs_ucb(int games){

  std::map<std::string,int> wins;
  wins["flat"] = 0;
  wins["ucb"] = 0;
  
  Board b;
  b.to_string();
  Zobrist zobrist;
  Mcts_flat flat(b,zobrist);
  Mcts_ucb ucb(b,zobrist);

  for(int i = 0; i<games; i++){
    b.init();

    std::string first;
    std::string second;
    std::string player;
    int playouts = 100;

    if(rand() % 2 == 0){
      first = "flat";
      second = "ucb";
      player = "flat";
    }else{
      first = "ucb";
      second = "flat";
      player = "ucb";
    }
  
    while(b.game_state() == 0){ // state is not terminal
      if(player == "flat"){
	Move best_move = flat.flat_mcts(b,playouts);
	b.play(best_move,flat.zobrist);
	player = "ucb";
      }else{
	Move best_move = ucb.ucb(b,playouts,0.4);
	b.play(best_move,ucb.zobrist);
	player = "flat";
      }
    }

    if(b.game_state() == 1){
      wins[first] += 1;
    }else{
      wins[second] += 1;
    }

    std::cout << "flat won " << wins["flat"] << " games ---- ucb won " << wins["ucb"] << " games." << std::endl;
  }
}

int main(int argc, char** argv){
  flat_vs_ucb(100);
}
