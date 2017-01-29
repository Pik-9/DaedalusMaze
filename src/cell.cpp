#include "cell.hpp"

#include <QPainter>

Cell::Cell ()
{
  doors[0] = doors[1] = doors[2] = doors[3] = false;
  twists = 0;
}

Cell::~Cell ()
{}

bool Cell::doorOpen (const DIRECTION dir)
{
  return doors[(dir + twists) % 4];
}

void Cell::step ()
{
  twists++;
}
