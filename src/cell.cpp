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

void Cell::drawCell (QPainter *pnt, const QRect *area)
{
  QRect matrix[3][3];
  for (int ix = 0; ix < 3; ix++)  {
    for (int iy = 0; iy < 3; iy++)  {
      matrix[ix][iy].setHeight (area->height () / 3);
      matrix[ix][iy].setWidth (area->width () / 3);
      
      if (ix)  {
        matrix[ix][iy].moveLeft (matrix[ix - 1][iy].right ());
      } else  {
        matrix[ix][iy].moveLeft (area->left ());
      }
      
      if (iy)  {
        matrix[ix][iy].moveTop (matrix[ix][iy - 1].bottom ());
      } else  {
        matrix[ix][iy].moveTop (area->top ());
      }
    }
  }
  
  pnt->fillRect (matrix[1][1], Qt::green);
  if (doorOpen (DIRECTION_TOP))  {
    pnt->fillRect (matrix[1][0], Qt::green);
  }
  if (doorOpen (DIRECTION_RIGHT))  {
    pnt->fillRect (matrix[2][1], Qt::green);
  }
  if (doorOpen (DIRECTION_BOTTOM))  {
    pnt->fillRect (matrix[1][2], Qt::green);
  }
  if (doorOpen (DIRECTION_LEFT))  {
    pnt->fillRect (matrix[0][1], Qt::green);
  }
}