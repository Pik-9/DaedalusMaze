#ifndef CELL_HPP
#define CELL_HPP

#include <stdint.h>

enum DIRECTION
{
  DIRECTION_TOP = 0,
  DIRECTION_RIGHT = 1,
  DIRECTION_BOTTOM = 2,
  DIRECTION_LEFT = 3
};

class Cell
{
private:
  bool doors[4];
  uint32_t twists;
  
public:
  Cell ();
  virtual ~Cell ();
  
  bool doorOpen (const DIRECTION);
  void step ();
};

#endif
