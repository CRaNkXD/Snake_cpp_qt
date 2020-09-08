#pragma once
#include "snake.h"

struct Food{
   Position position;
   bool eaten;
   const int points{100};
};
