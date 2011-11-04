#include <SDL/SDL.h>
#include "emulator.h"
#include "graphics.h"

int	handle_events(t_emulator *emu, t_graphics *graphics, int *pause)
{
  SDL_Event event;
  int		i;

  SDL_PollEvent(&event);
  switch(event.type)
    {
    case SDL_QUIT:
      return 1;
      break ;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
	{
	case SDLK_SPACE:
	  do_cycle(emu);
	  break ;
	case SDLK_p:
	  if (graphics->p_release)
	    {
	      *pause = !*pause;
	      graphics->p_release = 0;
	    }
	  break ;
	case SDLK_ESCAPE:
	  return 1;
	  break ;
	default:
	  for (i = 0; i < 16; i++)
	    {
	      if (key_tab[i] == event.key.keysym.sym)
		graphics->key[i] = 1;
	    }
	  break ;
	}
      break;
    case SDL_KEYUP:
      if (event.key.keysym.sym == SDLK_p)
	graphics->p_release = 1;
      for (i = 0; i < 16; i++)
	{
	  if (key_tab[i] == event.key.keysym.sym)
	    graphics->key[i] = 0;
	}
      break;
    }
  return 0;
}
