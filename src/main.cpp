#include <SDL/SDL.h>
#include "emulator.h"
#include "graphics.h"

int		main(int ac, char **av)
{
  Graphics	*graphics;
  t_emulator	*emu;
  int		pause = 1;

  if (ac < 2)
    {
      printf("Not enought arguments\n");
      return EXIT_FAILURE;
    }
  graphics = new Graphics();
  emu = new Emulator(av[1]);
  emu->SetGraphics(graphics);
  printf("===== Chip8 emulator =====\n");
  printf("P to toogle pause\n");
  printf("Echap to exit\n");
  for(;;)
    {
      if (graphics->HandleEvents(emu, &pause) == 1)
	break ;
      if (!pause)
	emu->DoCycle();
      sync_CPU();
    }
  delete graphics;
  delete emu;
  return (0);
}

