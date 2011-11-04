#include <SDL/SDL.h>
#include "emulator.h"
#include "graphics.h"

int		main(int ac, char **av)
{
  t_graphics	*graphics;
  t_emulator	*emu;
  int		pause = 1;

  if (ac < 2)
    {
      printf("Not enought arguments\n");
      return EXIT_FAILURE;
    }
  init_graphics(&graphics);
  if ((emu = init_emulator(av[1])) == NULL)
    {
      perror(av[1]);
      return EXIT_FAILURE;
    }
  emu->graphics = graphics;
  printf("===== Chip8 emulator =====\n");
  printf("P to toogle pause\n");
  printf("Echap to exit\n");
  for(;;)
    {
      if (handle_events(emu, graphics, &pause) == 1)
	break ;
      if (!pause)
	do_cycle(emu);
      sync_CPU();
    }
  delete_graphics(graphics);
  free(emu);
  return (0);
}

