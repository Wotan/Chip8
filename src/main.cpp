#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include "emulator.h"
#include "graphics.h"

int		main(int ac, char **av)
{
  Graphics	*graphics;
  QApplication	app(ac, av);
  QMainWindow	mainWindow;

  mainWindow.setMaximumSize (WIN_X, WIN_Y + 25);
  mainWindow.setMinimumSize (WIN_X, WIN_Y + 25);

  graphics = new Graphics(&mainWindow, &app, QPoint(0, 25), QSize(WIN_X, WIN_Y));

  std::cout << "===== Chip8 emulator =====" << std::endl;
  graphics->show();
  mainWindow.show();
  app.exec();
  delete graphics;
  std::cout << "Bye Bye" << std::endl;
  return (0);
}

