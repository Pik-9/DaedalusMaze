#include "window.hpp"
#include "cell.hpp"

#include <QPaintEvent>
#include <QPainter>

Window::Window (QWidget *parent)
  : QMainWindow (parent)
{
  setWindowTitle ("Daedalus' Maze");
  resize (1000, 750);
  mgrid = new Mazegrid (6, 4);
  setCentralWidget (mgrid);
}

Window::~Window ()
{}
