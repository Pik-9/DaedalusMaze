#include "mazeWidget.hpp"

#include <QPainter>
#include <QTimer>

#include <math.h>

Cellwidget::Cellwidget (Mazegrid *mother, const uint32_t x, const uint32_t y)
  : board (mother), pos_x (x), pos_y (y), cell (new Cell ())
{
}

QPoint Cellwidget::polar2cart (const uint32_t r, const double phi)
{
  QPoint ret;
  QRect area = getDrawingArea ();
  ret.setX (area.center ().x () + r * cos (phi));
  ret.setY (area.center ().y () + r * sin (phi));
  return ret;
}

double Cellwidget::r_ellipse (const double phi)
{
  QRect area = getDrawingArea ();
  double a = area.width () / 2.0;
  double b = area.height () / 2.0;
  return a * b / sqrt (pow (a * sin (phi), 2.0) + pow (b * cos (phi), 2.0));
}

Cellwidget::~Cellwidget ()
{
  delete cell;
}

QRect Cellwidget::getDrawingArea ()
{
  QRect ret;
  ret.setWidth (board->width () / board->getCountX ());
  ret.setHeight (board->height () / board->getCountY ());
  ret.moveLeft (pos_x * ret.width ());
  ret.moveTop (pos_y * ret.height ());
  return ret;
}

void Cellwidget::draw (QPainter *painter, double phi)
{
  QRect area = getDrawingArea ();
  QColor primary, secondary;
  primary = Qt::cyan;
  secondary = QColor (0, 64, 64);
  painter->setPen (primary);
  painter->setBrush (secondary);
  painter->fillRect (area, secondary);
  painter->drawRect (area);
  
  QPoint sun[24];
  for (int ii = 0; ii < 24; ++ii)  {
    uint32_t r = (ii % 2 ? 35 : 25);
    sun[ii] = polar2cart (r, ii * M_PI / 12 + phi);
  }
  painter->setBrush (primary);
  painter->drawPolygon (sun, 24);
  
  QPoint cc = area.center ();
  QPen way (Qt::white);
  way.setWidth (20);
  painter->setPen (way);
  
  if (cell->doorOpen (DIRECTION_RIGHT))  {
    double theta = phi;
    QPoint dest = polar2cart (r_ellipse (theta), theta);
    painter->drawLine (cc, dest);
  }
  if (cell->doorOpen (DIRECTION_LEFT))  {
    double theta = M_PI + phi;
    QPoint dest = polar2cart (r_ellipse (theta), theta);
    painter->drawLine (cc, dest);
  }
  if (cell->doorOpen (DIRECTION_TOP))  {
    double theta = 3 * M_PI / 2 + phi;
    QPoint dest = polar2cart (r_ellipse (theta), theta);
    painter->drawLine (cc, dest);
  }
  if (cell->doorOpen (DIRECTION_BOTTOM))  {
    double theta = M_PI / 2 + phi;
    QPoint dest = polar2cart (r_ellipse (theta), theta);
    painter->drawLine (cc, dest);
  }
}

Mazegrid::Mazegrid (const uint32_t x, const uint32_t y, QWidget* parent)
  : QWidget (parent), count_x (x), count_y (y), animate_step (0)
{
  cells.resize (x * y);
  for (int ix = 0; ix < x; ++ix)  {
    for (int iy = 0; iy < y; ++iy)  {
      cells[count_x * iy + ix] = new Cellwidget (this, ix, iy);
    }
  }
  
  animation_timer = new QTimer ();
  connect (animation_timer, SIGNAL (timeout ()), this, SLOT (doAnimation ()));
  animation_timer->start (100);
}

Cellwidget& Mazegrid::accessCell (const uint32_t x, const uint32_t y)
{
  return *cells[count_x * y + x];
}

Mazegrid::~Mazegrid ()
{
  for (int ii = 0; ii < cells.size (); ++ii)  {
    delete cells[ii];
  }
  delete animation_timer;
}

void Mazegrid::paintEvent (QPaintEvent *event)
{
  QPainter pnt (this);
  for (int ix = 0; ix < count_x; ++ix)  {
    for (int iy = 0; iy < count_y; ++iy)  {
      accessCell (ix, iy).draw (&pnt, animate_step * M_PI / 20);
    }
  }
  pnt.end ();
}

uint32_t Mazegrid::getCountX () const
{
  return count_x;
}

uint32_t Mazegrid::getCountY () const
{
  return count_y;
}

void Mazegrid::doAnimation ()
{
  repaint ();
  animate_step++;
}
