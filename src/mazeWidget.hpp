#ifndef MAZEWIDGET_HPP
#define MAZEWIDGET_HPP

#include <QWidget>

#include <vector>

#include "cell.hpp"

class QPainter;
class QPaintEvent;
class QTimer;
class Mazegrid;

class Cellwidget
{
private:
  Mazegrid *board;
  Cell *cell;
  uint32_t pos_x, pos_y;
  
protected:
  QPoint polar2cart (const uint32_t, const double);
  double r_ellipse (const double);
  
public:
  Cellwidget (Mazegrid*, const uint32_t, const uint32_t);
  virtual ~Cellwidget ();
  
  QRect getDrawingArea ();
  
  void draw (QPainter* painter, double phi = 0.0);
};

class Mazegrid : public QWidget
{
  Q_OBJECT
private:
  const uint32_t count_x, count_y;
  std::vector<Cellwidget*> cells;
  
  uint32_t animate_step;
  QTimer *animation_timer;
  
protected:
  Cellwidget& accessCell (const uint32_t, const uint32_t);
  void paintEvent (QPaintEvent*);
  
public:
  Mazegrid (const uint32_t, const uint32_t, QWidget *parent = 0);
  ~Mazegrid ();
  
  uint32_t getCountX () const;
  uint32_t getCountY () const;
  
protected slots:
  void doAnimation ();
};

#endif
