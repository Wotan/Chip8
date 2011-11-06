#include <iostream>
#include "emulator.h"
#include "graphics.h"

int		main(int ac, char **av)
{
  Graphics	*graphics;
  t_emulator	*emu;
  int		pause = 1;

  if (ac < 2)
    {
      std::cout << "Not enought arguments" << std::endl;
      return EXIT_FAILURE;
    }
  graphics = new Graphics();
  emu = new Emulator(av[1]);
  emu->SetGraphics(graphics);
  std::cout << "===== Chip8 emulator =====" << std::endl;
  std::cout << "P to toogle pause" << std::endl;
  std::cout << "Echap to exit" << std::endl;
  for(;;)
    {
      if (graphics->HandleEvents(emu, &pause) == 1)
	break ;
      if (!pause)
	for (int i = 0; i < FREQUENCE / 60; i++)
	  emu->DoCycle();
      graphics->Flip();
    }
  delete graphics;
  delete emu;
  return (0);
}

