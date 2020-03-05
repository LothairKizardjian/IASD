#include "../includes/Zobrist.h"

Zobrist::Zobrist(){
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      this->hash_map[std::make_tuple(i,j,1)] = rand() % std::numeric_limits<uint64_t>::max();
      this->hash_map[std::make_tuple(i,j,2)] = rand() % std::numeric_limits<uint64_t>::max();
    }
  }

  this->total_playouts = 0;
}

uint64_t Zobrist::get_hash(uint64_t hashcode, Move move){
  uint64_t hash_move = this->hash_map[std::make_tuple(move.x2,move.y2,move.player)];
  return hashcode^hash_move;
}
