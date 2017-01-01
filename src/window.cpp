#include "window.hpp"

#include <QPaintEvent>
#include <QPainter>

Window::Window (QWidget *parent)
  : QWidget (parent)
{
  setWindowTitle ("Daedalus' Maze");
  resize (1000, 750);
}

Window::~Window ()
{}

void Window::paintEvent (QPaintEvent *event)
{
  QPainter painter (this);
  painter.fillRect (rect (), Qt::black);
  painter.end ();
}