#include "window.hpp"

#include <QApplication>

int main (int argc, char *argv[])
{
  QApplication app (argc, argv);
  Window *mw = new Window ();
  mw->show ();
  return app.exec ();
}