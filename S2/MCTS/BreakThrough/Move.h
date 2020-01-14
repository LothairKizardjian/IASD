#include <iostream>
#include <string>

class Move{
 public:
  int x1;
  int y1;
  int x2;
  int y2;
  int player;
  
  Move();
  Move(int x1, int y1, int x2, int y2, int player);
  std::string to_string();
};
