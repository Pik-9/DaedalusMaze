#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QWidget>

class QPaintEvent;

class Window : public QWidget
{
private:
  
public:
  Window (QWidget *parent = 0);
  ~Window ();
  
protected:
  void paintEvent (QPaintEvent *event);
};

#endif