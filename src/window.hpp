#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QMainWindow>

#include "mazeWidget.hpp"

class Window : public QMainWindow
{
  Q_OBJECT
private:
  Mazegrid *mgrid;
public:
  Window (QWidget *parent = 0);
  ~Window ();
};

#endif
