#include "Move.h"

Move::Move(){
  this->x1 = 0;
  this->y1 = 0;
  this->x2 = 0;
  this->y2 = 0;
  this->player = 1;
}

Move::Move(int x1, int y1, int x2, int y2, int player){
  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;
  this->player = player;
}

std::string Move::to_string(){
  std::string result;
  result += "[(x1=";
  result += std::to_string(this->x1);
  result += ", y1=";
  result += std::to_string(this->y1);
  result += "),(x2=";
  result += std::to_string(this->x2);
  result += ",y2=";
  result += std::to_string(this->y2);
  result += "),p=";
  result += std::to_string(this->player);
  result += "]";
  return result;
}

