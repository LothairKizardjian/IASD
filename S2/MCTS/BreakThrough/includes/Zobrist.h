#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <tuple>
#include <cstddef>
#include <limits>

#ifndef INCLUDES
#define INCLUDES

#include "Move.h"

#endif

class Zobrist{
 public:
  std::map<std::tuple<int,int,int>,uint64_t> hash_map; // stores a hashcode for each possible move
  int total_playouts;
  std::map<std::tuple<int,int,int>,int> wins; // stores number of wins when using a move
  std::map<std::tuple<int,int,int>,int> playouts; // stores number of playouts using a move

  Zobrist();
  uint64_t get_hash(uint64_t,Move);
};
