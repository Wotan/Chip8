#include <SDL/SDL.h>
#include "graphics.h"

int	init_graphics(t_graphics **graphics)
{
  int	i;

  *graphics = malloc(sizeof(**graphics) * 1);

  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    return -1;
  if (!((*graphics)->screen = SDL_SetVideoMode(64 * 8, 32 * 8, 32,
					       SDL_HWSURFACE)))
    return -1;
  SDL_WM_SetCaption("Wotan's Chip8 emulator", NULL);

  for (i = 0; i < 16; i++)
    (*graphics)->key[i] = 0;
  (*graphics)->p_release = 1;
  return 0;
}

int	delete_graphics(t_graphics *graphics)
{
  SDL_Quit();
  free(graphics);
  return 0;
}

int	is_pixel_set(t_graphics *graphics, int x, int y)
{
  Uint8 *p;
  unsigned int	bpp = 4;

  x = x * 8;
  y = y * 8;

  if (y > 32 * 8 || x > 64 * 8 || x < 0 || y < 0)
    return 0;
  p = (Uint8 *)graphics->screen->pixels + y
    * graphics->screen->pitch + x * bpp;
  return (p[1] == 0xFF ? 1 : 0);
}

int	set_pixel(t_graphics *graphics, int x, int y, int on)
{
  unsigned int	bpp = 4;
  Uint8 *p;
  unsigned int i, j;

  x = x * 8;
  y = y * 8;

  p = (Uint8 *)graphics->screen->pixels +
    y * graphics->screen->pitch + x * bpp;
  if (y >= 32 * 8 || x >= 64 * 8 || x < 0 || y < 0)
    return 1;
  for (j = 0; j < 8; j++)
    {
      for (i = 0; i < bpp * 8; i++)
	p[i] = on ? 0xFF : 0x0;
      p += graphics->screen->pitch;
    }
  return 1;
}
